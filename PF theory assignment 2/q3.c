#include <stdio.h>
#define MAX_SENSORS 10
#define MAX_HOURS 24

void inputReadings(int sensors, int hours, float temp[MAX_SENSORS][MAX_HOURS]);
void analyzeSensor(int sensorIndex, int hours, float temp[MAX_SENSORS][MAX_HOURS]);
int findHighestAverageSensor(int sensors, int hours, float temp[MAX_SENSORS][MAX_HOURS]);
int main() {
    int sensors, hours;
    float temp[MAX_SENSORS][MAX_HOURS];

    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings: ");
    scanf("%d", &hours);

    inputReadings(sensors, hours, temp);

    printf("\n--- INDIVIDUAL SENSOR REPORTS ---\n");
    for (int i = 0; i < sensors; i++) {
        analyzeSensor(i, hours, temp);
    }

    int bestSensor = findHighestAverageSensor(sensors, hours, temp);
    
    float bestSum = 0;
    for (int j = 0; j < hours; j++) {
        bestSum += temp[bestSensor - 1][j];
    }
    float bestAvg = bestSum / hours;

    printf("\nHighest average: Sensor %d (%.2f)\n", bestSensor, bestAvg);
    return 0;
}
void inputReadings(int sensors, int hours, float temp[MAX_SENSORS][MAX_HOURS]) {
    for (int i = 0; i < sensors; i++) {
        printf("\nEnter readings for Sensor %d:\n", i + 1);
        for (int j = 0; j < hours; j++) {
            printf("  Hour %d: ", j + 1);
            scanf("%f", &temp[i][j]);
        }
    }
}
void analyzeSensor(int sensorIndex, int hours, float temp[MAX_SENSORS][MAX_HOURS]) {
    float total = 0;
    float max = temp[sensorIndex][0];
    float min = temp[sensorIndex][0];
    int criticalCount = 0;
    int warningCount = 0;
    int currentStreak = 0;
    int maxStreak = 0;

    for (int j = 0; j < hours; j++) {
        float val = temp[sensorIndex][j];
        total += val;

        if (j == 0 || val > max) max = val;
        if (j == 0 || val < min) min = val;

        if (val >= 40.0) {
            criticalCount++;
        } else if (val >= 35.0 && val <= 39.0) {
            warningCount++;
        }

        if (val >= 35.0) {
            currentStreak++;
            if (currentStreak > maxStreak) {
                maxStreak = currentStreak;
            }
        } else {
            currentStreak = 0;
        }
    }
    float avg = total / hours;

    printf("Sensor %d: Total=%.0f Avg=%.2f Max=%.0f Min=%.0f\n", 
           sensorIndex + 1, total, avg, max, min);
    printf("         Critical=%d Warning=%d Longest hot streak=%d\n", 
           criticalCount, warningCount, maxStreak);
}
int findHighestAverageSensor(int sensors, int hours, float temp[MAX_SENSORS][MAX_HOURS]) {
    int bestSensor = 0;
    float maxAvg = 0.0;
    for (int i = 0; i < sensors; i++) {
        float sum = 0;
        for (int j = 0; j < hours; j++) {
            sum += temp[i][j];
        }
        float avg = sum / hours;
        
        if (i == 0 || avg > maxAvg) {
            maxAvg = avg;
            bestSensor = i + 1;
        }
    }
    return bestSensor;
}