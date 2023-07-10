#include "controller.hpp"

/* Wrap an angle in the range [-limit,+limit] (special thanks to Edgar Bonet!) */
static float wrap(float angle,float limit){
  while (angle >  limit) angle -= 2*limit;
  while (angle < -limit) angle += 2*limit;
  return angle;
}

controller::controller(mpu6050 & sensor): 
    position_x(0.0f),
    position_y(0.0f),
    angle_x_offset(0.0f),
    angle_y_offset(0.0f),
    angle_x(0.0f),
    angle_y(0.0f),
    angle_z(0.0f),
    previous_update_time(0),
    current_update_time(0),
    gyro_scale(0),
    sensor(sensor)
{}

byte controller::init(){
    byte status;
    status = sensor.wakeUp();
    if(status != 0){
        return status;
    }
    delay(50);
    sensor.setClockSource(0x01); // 1 = PLL with X axis gyroscope reference
    sensor.setSampleRate(0x00); // 8kHz sample rate: SMPLRT_DIV = 0x00 (Default with DMP disabled)
    sensor.setFSYNC(0x00); // Input disabled
    sensor.setDLPF(0x00); // Bandwith 260Hz delay = 0ms
    sensor.setGyroFullScaleRange(1); // ±500°/s and the sensitivity is 65.5 LSB per °/s
    sensor.setAccelFullScaleRange(0); // ±2g

    // Setting up gyro scale to use for later with gyro_dps calculations
    uint8_t gyro_fsr_setting = sensor.getGyroFullScaleRange();
    if(gyro_fsr_setting == 0x00){
        gyro_scale = 250;
    }
    else if(gyro_fsr_setting == 0x01){
        gyro_scale = 500;
    }
    else if(gyro_fsr_setting == 0x02){
        gyro_scale = 1000;
    }
    else{
        gyro_scale = 2000;
    }
    
    sensor.calcOffsets();

    return status;
}



// Code modified from MPU6050_light
void controller::update(){
  // retrieve raw data
  CalcSensorData data = sensor.getAllCalcSensorData();
  
  // estimate tilt angles: this is an approximation for small angles!
  float sgZ = ((data.calc_accel_z)>=0)-((data.calc_accel_z)<0); // allow one angle to go from -180 to +180 degrees
  new_angle_acc_x =   atan2(data.calc_accel_y, sgZ*sqrt(data.calc_accel_z*data.calc_accel_z + data.calc_accel_x*data.calc_accel_x)) * RADIAL_TO_DEGREES; // [-180,+180] deg
  new_angle_acc_y = - atan2(data.calc_accel_x,     sqrt(data.calc_accel_z*data.calc_accel_z + data.calc_accel_y*data.calc_accel_y)) * RADIAL_TO_DEGREES; // [- 90,+ 90] deg

  unsigned long new_time = millis();
  float dt = (new_time - prev_time) * 1e-3; // Converting to seconds
  prev_time = new_time;

  // Correctly wrap X and Y angles (special thanks to Edgar Bonet!)
  // https://github.com/gabriel-milan/TinyMPU6050/issues/6
  angle_x = wrap(DEFAULT_GYRO_COEFF*(new_angle_acc_x + wrap(angle_x -     data.calc_gyro_x*dt - new_angle_acc_x,180)) + (1.0-DEFAULT_GYRO_COEFF)*new_angle_acc_x,180);
  angle_y = wrap(DEFAULT_GYRO_COEFF*(new_angle_acc_y + wrap(angle_y + sgZ*data.calc_gyro_y*dt - new_angle_acc_y, 90)) + (1.0-DEFAULT_GYRO_COEFF)*new_angle_acc_y, 90);
  angle_z += data.calc_gyro_z*dt; // not wrapped (to do???)
}

void controller::mapAnglesToCoordinates(float region_width, float region_height){
   
    this->position_x = map((angle_x + angle_x_offset), -60, 60, 0, region_width);
    this->position_y = map((angle_y + angle_y_offset), -60, 60, 0, region_height);

}

void controller::reset(float region_width, float region_height){
    angle_x_offset = angle_x - map(position_x, 0, region_width, -60, 60);
    angle_y_offset = angle_y - map(position_y, 0, region_height, -60, 60);
}

float controller::getPositionX(){
    return position_x;
}

float controller::getPositionY(){
    return position_y;
}

int16_t controller::getRawGyroX(){
    return sensor.getGyroX();
}

int16_t controller::getRawGyroY(){
    return sensor.getGyroY();
}

int16_t controller::getRawGyroZ(){
    return sensor.getGyroZ();
}

float controller::getAngleX(){
    return angle_x;
}

float controller::getAngleY(){
    return angle_y;
}

float controller::getAngleZ(){
    return angle_z;
}