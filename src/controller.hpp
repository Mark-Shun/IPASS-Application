#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "MPU6050.hpp"
#include "defines.hpp"

class controller{
private:
    float position_x = 120;
    float position_y = 120;

    float angle_x_offset;
    float angle_y_offset;

    float angle_x, angle_y, angle_z;
    float new_angle_acc_x, new_angle_acc_y, new_angle_cc_z;
    unsigned long prev_time;

    unsigned long previous_update_time;
    unsigned long current_update_time;

    uint16_t gyro_scale;
    mpu6050 sensor;

    SensorData raw_data;

public:
    controller(mpu6050 & sensor);
    byte init();
    void update();
    void mapAnglesToCoordinates(float region_width, float region_height);
    void reset(float region_width, float region_height);
    float getPositionX();
    float getPositionY();
    
    int16_t getRawGyroX(){return raw_data.gyro_x;};
    int16_t getRawGyroY(){return raw_data.gyro_y;};
    int16_t getRawGyroZ(){return raw_data.gyro_z;};

    float getAngleX();
    float getAngleY();
    float getAngleZ();
};


#endif