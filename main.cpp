#include "mbed.h"
#include "LSM6DSLSensor.h"
#include "RGBLed.h"

I2C i2c(I2C_SDA, I2C_SCL);  // Create I2C communication instance
LSM6DSLSensor acc_gyro(&i2c);  // Instantiate the LSM6DSLSensor object using I2C
RGBLed led(LED1_R, LED1_G, LED1_B);  // Instantiate the RGBLed object

int main() {
    // Initialize the accelerometer
    acc_gyro.init(nullptr);
    acc_gyro.enable_x();
    acc_gyro.enable_y();
    acc_gyro.enable_z();

    while (1) {
        MotionSensorData_axes_t axes_data;
        acc_gyro.GetAxes(&axes_data);

        int16_t x_acc = axes_data.x;
        int16_t y_acc = axes_data.y;
        int16_t z_acc = axes_data.z;

        // Normalize accelerometer data to RGB color range (0-255)
        uint8_t red_brightness = static_cast<uint8_t>((x_acc + 32768) / 128);
        uint8_t green_brightness = static_cast<uint8_t>((y_acc + 32768) / 128);
        uint8_t blue_brightness = static_cast<uint8_t>((z_acc + 32768) / 128);

        // Set the LED color based on accelerometer data
        led.setColour(red_brightness, green_brightness, blue_brightness);

        ThisThread::sleep_for(std::chrono::milliseconds(100)); // Delay for a while
    }
}
