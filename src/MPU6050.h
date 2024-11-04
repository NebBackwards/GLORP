class MPU6050{
    private:

    enum regAddr{
        INT_STATUS = 0x3A,
        INT_ENABLE = 0x38,
        CONFIG = 0x1A,
        GYRO_CONFIG = 0x1B, //self-test & full-scale range
        //Bits 3 & 4 set FSR
        ACCEL_CONFIG = 0x1C,
        MOT_THR = 0x1F, //motion detetion threshold 

        //Accelerometer Outputs       
        ACCEL_XOUT_H = 0x3B,
        ACCEL_XOUT_L = 0x3C,
        ACCEL_YOUT_H = 0x3D,
        ACCEL_YOUT_L = 0x3E,
        ACCEL_ZOUT_H = 0x3F,
        ACCEL_ZOUT_L = 0x40,

        //Gyroscope Outputs
        GYRO_XOUT_H = 0x43,
        GYRO_XOUT_L = 0x44,
        GYRO_YOUT_H = 0x45,
        GYRO_YOUT_L = 0x46,
        GYRO_ZOUT_H = 0x47,
        GYRO_ZOUT_L = 0x48,

        //Temperature Outputs
        TEMP_OUT_H = 0x41,
        TEMP_OUT_L = 0x42,

        //Clock & Power Management
        PWR_MGMT_1 = 0x6B,
        
    };
    public:


};