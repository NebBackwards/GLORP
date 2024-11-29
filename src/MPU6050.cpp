#include <Arduino.h>
#include <MPU6050.h>
#include <Wire.h>

MPU6050::MPU6050(uint8_t i2c_address){
    //defaults to 0x68
    address = i2c_address;
    Wire.begin();
}

void MPU6050::init_default(){
    writeReg(PWR_MGMT_1, 1);
    writeReg(INT_ENABLE, 1);
    setDLPF(1);
    setAccelFSR(ACCEL_FSR_4);
    setGyroFSR(GYRO_FSR_500);
    setSampleRate(1000);
    Serial.println("MPU6050 Init Done");
}

void MPU6050::toggleSleep(SLEEP_MODE mode){
    writeReg(PWR_MGMT_1, mode);
}

uint8_t MPU6050::readReg(regAddr reg)
{
    uint8_t value;

    Wire.beginTransmission(address);
    Wire.write(reg);
    last_status = Wire.endTransmission();
    Wire.requestFrom(address, (uint8_t)1);
    value = Wire.read();
    Wire.endTransmission();

    return value;
}

void MPU6050::writeReg(regAddr reg, uint8_t value)
{
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);
    last_status = Wire.endTransmission();
}

uint8_t MPU6050::dataAvailable(){
   return readReg(INT_STATUS) & 0x01;
}

void MPU6050::readAccel(){
    uint8_t x_h = readReg(ACCEL_XOUT_H);
    uint8_t x_l = readReg(ACCEL_XOUT_L);
    uint8_t y_h = readReg(ACCEL_YOUT_H);
    uint8_t y_l = readReg(ACCEL_YOUT_L);
    uint8_t z_h = readReg(ACCEL_ZOUT_H);
    uint8_t z_l = readReg(ACCEL_ZOUT_L);

    a.x = (float)((x_h<<8)|x_l) - offsetAccX;
    a.y = (float)((y_h<<8)|y_l);
    a.z = (float)((z_h<<8)|z_l);
}

void MPU6050::readGyro(){
    uint8_t x_h = readReg(GYRO_XOUT_H);
    uint8_t x_l = readReg(GYRO_XOUT_L);
    uint8_t y_h = readReg(GYRO_YOUT_H);
    uint8_t y_l = readReg(GYRO_YOUT_L);
    uint8_t z_h = readReg(GYRO_ZOUT_H);
    uint8_t z_l = readReg(GYRO_ZOUT_L);

    g.x = (float)((x_h<<8)|x_l) - offsetGyroX;
    g.y = (float)((y_h<<8)|y_l) - offsetGyroY;
    g.z = (float)((z_h<<8)|z_l) - offsetGyroZ;
}

void MPU6050::read(){
        readAccel();
        readGyro();
}

void MPU6050::setSampleRateDiv(uint8_t div){    
    writeReg(SMPLRT_DIV, div);
}

/// @brief sets the data sample rate for all sensors
/// @param sampleRate data output rate in Hz
void MPU6050::setSampleRate(int sampleRate){
    setSampleRateDiv((gyroOutputRate/sampleRate)-1);
    sample_rate = sampleRate;
}

/// @brief sets the digital low-pass filter register, must be set before anything else as this defines the gyro output rate
/// @param dlpf_cfg value 0-7 corresponding to desired DLPF setting
void MPU6050::setDLPF(uint8_t dlpf_cfg){
    if(dlpf_cfg > 7){
        Serial.println("Error: DLPF parameter out of bounds");
        return;       
    }else if (dlpf_cfg == 0 ||dlpf_cfg == 7){gyroOutputRate = 8000;}
    else {gyroOutputRate = 1000;}
    
    writeReg(CONFIG, (dlpf_cfg&0b00000111));
}

/// @brief sets gyroscope full scale range
/// @param fsr a selection of one of 4 possible FSR values
void MPU6050::setGyroFSR(GYRO_FSR fsr){
    uint8_t writeVal = (fsr << 3) & 0b00011000;
    writeReg(GYRO_CONFIG, writeVal);
       switch(fsr){
        case GYRO_FSR_250:
            gyro_lsb_dps = 131.0;
            break;
        case GYRO_FSR_500:
            gyro_lsb_dps = 65.5;
            break;
        case GYRO_FSR_1000:
            gyro_lsb_dps = 32.8;
            break;
        case GYRO_FSR_2000:
            gyro_lsb_dps = 16.4;
            break;
    }
}

/// @brief sets accelerometer full scale range
/// @param fsr a selection of one of the 4 possible FSR values
void MPU6050::setAccelFSR(ACCEL_FSR fsr){
    uint8_t writeVal = (fsr << 3) & 0b00011000;
    writeReg(ACCEL_CONFIG, writeVal);
    switch(fsr){
        case ACCEL_FSR_2:
            accel_lsb_g = 16384.0;
            break;
        case ACCEL_FSR_4:
            accel_lsb_g = 8192.0;
            break;
        case ACCEL_FSR_8:
            accel_lsb_g = 4096.0;
            break;
        case ACCEL_FSR_16:
            accel_lsb_g = 2048.0;
            break;
    }
}

bool MPU6050::checkForPitchUpdate(float &pitchAngle)
{
    if (dataAvailable())
    {
        read();
        pitchObservation = atan2((-a.x/accel_lsb_g), (a.z/accel_lsb_g))* 180 / 3.1416; // deg
        estimatedPitchAngle = pitchAngle + (1.0 / sample_rate) * (g.y/gyro_lsb_dps);
        pitchAngle = estimatedPitchAngle + 0.5 * (pitchObservation - estimatedPitchAngle);
        gyroBiasY -= epsilon * sample_rate / (gyro_lsb_dps) * (pitchObservation - estimatedPitchAngle);

#ifdef __DEBUG_IMU__
        Serial.print(estimatedPitchAngle);
        Serial.print("\t");
        Serial.print(pitchObservation);
        Serial.print("\t");
        Serial.print(pitchAngle);
        Serial.print("\t");
        Serial.print(gyroBiasY);
        Serial.print("\n");
#endif
        return true;
    }
    return false;
}

void MPU6050::calibrate(int numValues)
{
    float avgAccX = 0;
    float avgGyroX = 0;
    float avgGyroY = 0;
    float avgGyroZ = 0;

    for (int i = 0; i < numValues; i++)
    {
        while (!(dataAvailable())); // blocking code, wait for next reading
        read();
        avgAccX += a.x / (float)numValues;
        avgGyroX += g.x / (float)numValues;
        avgGyroY += g.y / (float)numValues;
        avgGyroZ += g.z / (float)numValues;


        //print statment while calibrating
        Serial.print("Calibrating: ");
        Serial.print("\t");
        Serial.print(i/2.0);
        Serial.println(" %");
    }

    offsetAccX = avgAccX;
    offsetGyroX = avgGyroX;
    offsetGyroY = avgGyroY;
    offsetGyroZ = avgGyroZ;
}