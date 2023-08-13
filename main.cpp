#include "mbed.h"
#include "LSM6DSLSensor.h"

// Define LED objects
PwmOut redLED(LED1);
PwmOut greenLED(LED2);
PwmOut blueLED(LED3);

// Create an instance of DevI2C and LSM6DSLSensor
static DevI2C devI2c(PB_11, PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5); // high address

// Function to map input value to output range
float mapValue(float value, float inMin, float inMax, float outMin, float outMax) {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

int main() {
    uint8_t id;
    int32_t axes[3];

    // Initialize accelerometer and gyroscope
    acc_gyro.init(NULL);
    acc_gyro.enable_x();

    while (1) {
        // Read accelerometer axes
        acc_gyro.get_x_axes(axes);

        // Map accelerometer data to LED brightness range
        float redBrightness = mapValue(static_cast<float>(axes[0]), -100.0, 100.0, 0.99, 0.10);
        float greenBrightness = mapValue(static_cast<float>(axes[1]), -100.0, 100.0, 0.99, 0.10);
        float blueBrightness = mapValue(static_cast<float>(axes[2]), -400.0, 1000.0, 0.99, 0.10);

        // Print accelerometer data and calculated brightness values
        printf("Acc X: %d, Acc Y: %d, Acc Z: %d\r\n", axes[0], axes[1], axes[2]);
        printf("Red Brightness: %f, Green Brightness: %f, Blue Brightness: %f\r\n", redBrightness, greenBrightness, blueBrightness);

        // Set LED brightness levels
        redLED = redBrightness;
        greenLED = greenBrightness;
        blueLED = blueBrightness;

        // Wait for a short duration
        ThisThread::sleep_for(2000ms);
    }
}
