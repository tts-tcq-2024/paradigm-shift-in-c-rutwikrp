#include <stdio.h>
#include <assert.h>

#define TEMPERATURE_MIN 0
#define TEMPERATURE_MAX 45
#define SOC_MIN 20
#define SOC_MAX 80
#define CHARGE_RATE_MAX 0.8

typedef enum {
    TEMPERATURE,
    SOC,
    CHARGE_RATE
} Parameter;

const char* parameterNames[] = {"Temperature", "State of Charge", "Charge Rate"};

int isInRange(float value, float min, float max) {
    return value >= min && value <= max;
}

void printBreachMessage(Parameter parameter, float value, float min, float max) {
    if (value < min) {
        printf("%s too low!\n", parameterNames[parameter]);
    } else if (value > max) {
        printf("%s too high!\n", parameterNames[parameter]);
    }
}

int isTemperatureOk(float temperature) {
    if (!isInRange(temperature, TEMPERATURE_MIN, TEMPERATURE_MAX)) {
        printBreachMessage(TEMPERATURE, temperature, TEMPERATURE_MIN, TEMPERATURE_MAX);
        return 0;
    }
    return 1;
}

int isSocOk(float soc) {
    if (!isInRange(soc, SOC_MIN, SOC_MAX)) {
        printBreachMessage(SOC, soc, SOC_MIN, SOC_MAX);
        return 0;
    }
    return 1;
}

int isChargeRateOk(float chargeRate) {
    if (!isInRange(chargeRate, 0, CHARGE_RATE_MAX)) {
        printBreachMessage(CHARGE_RATE, chargeRate, 0, CHARGE_RATE_MAX);
        return 0;
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    return isTemperatureOk(temperature) && isSocOk(soc) && isChargeRateOk(chargeRate);
}

void runTests() {
    // Test cases for normal conditions
    assert(batteryIsOk(25, 70, 0.7));
    
    // Test cases for temperature breaches
    assert(!batteryIsOk(-1, 70, 0.7)); // Temperature too low
    assert(!batteryIsOk(46, 70, 0.7)); // Temperature too high
    
    // Test cases for SOC breaches
    assert(!batteryIsOk(25, 19, 0.7)); // SOC too low
    assert(!batteryIsOk(25, 81, 0.7)); // SOC too high
    
    // Test cases for charge rate breaches
    assert(!batteryIsOk(25, 70, 0.9)); // Charge rate too high
}

int main() {
    runTests();
    printf("All tests passed.\n");
    return 0;
}
