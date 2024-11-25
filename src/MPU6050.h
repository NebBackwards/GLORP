#include <stdint.h>

class MPU6050{
    private:

        enum regAddr{
            INT_STATUS = 0x3A,
            INT_ENABLE = 0x38,

            //Sample rate = Gyro Output rate/(1+SMPLRT_DIV)
            SMPLRT_DIV = 0x19,
            //last 3 bits set DLPF, which determines gyro output rate
            CONFIG = 0x1A,
            
            //self-test & full-scale range
            //Bits 3 & 4 set FSR
            GYRO_CONFIG = 0x1B, 
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

        enum GYRO_FSR{
            GYRO_FSR_250,
            GYRO_FSR_500,
            GYRO_FSR_1000,
            GYRO_FSR_2000,
        };
        enum ACCEL_FSR{
            ACCEL_FSR_2,
            ACCEL_FSR_4,
            ACCEL_FSR_8,
            ACCEL_FSR_16,
        };
        enum SLEEP_MODE{
            SLEEP_OFF = 0,
            SLEEP_ON = 0b01000000
        };

        struct vector{
            float x, y, z;
        };
        
        uint8_t last_status;
        uint8_t address;
        int gyroOutputRate;
        float accel_lsb_g;
        float gyro_lsb_dps;
        float offsetAccX = 0.0;
        float offsetGyroX = 0.0;
        float offsetGyroY = 0.0;
        float offsetGyroZ = 0.0;
        float pitchObservation;
        float estimatedPitchAngle;
        int sample_rate;
        float gyroBiasY = 0.0;
        const float epsilon = 0.001 * 3.14156 / 180;
        const float kappa = 0.15;
        
    public:
        MPU6050(uint8_t i2c_address);
        void init_default();
        void toggleSleep(SLEEP_MODE mode);
        vector a, g;
        uint8_t readReg(regAddr reg);
        void writeReg(regAddr reg, uint8_t value);
        uint8_t dataAvailable();
        void readAccel();
        void readGyro();
        void read();
        void setSampleRateDiv(uint8_t div);
        void setSampleRate(int sampleRate);
        void setDLPF(uint8_t dlpf_cfg);
        void setGyroFSR(GYRO_FSR fsr);
        void setAccelFSR(ACCEL_FSR fsr);
        bool checkForPitchUpdate(float &pitchAngle);
        void calibrate(int numValues);

};