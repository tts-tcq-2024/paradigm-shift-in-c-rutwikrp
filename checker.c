#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool checkLimits(float value, float lower, float upper, const char* name) {
    if (value < lower) {
        printf("%s is too low!\n", name);
        return false;
    }
    if (value > upper) {
        printf("%s is too high!\n", name);
        return false;
    }
    return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool tempStatus = checkLimits(temperature, 0, 45, "Temperature");
    bool socStatus = checkLimits(soc, 20, 80, "State of Charge");
    bool chargeStatus = checkLimits(chargeRate, 0, 0.8, "Charge Rate");
    return tempStatus && socStatus && chargeStatus;
}

void runTests() {
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0.0) == false);
    assert(batteryIsOk(-1, 70, 0.7) == false);
    assert(batteryIsOk(25, 10, 0.7) == false);
    assert(batteryIsOk(25, 70, 0.9) == false);
    printf("All tests passed!\n");
}

int main() {
    runTests();
    printf("Additional tests may be required.\n");
    return 0;
}
