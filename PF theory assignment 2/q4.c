#include <stdio.h>
int getValidDays();
float calculateDailySales(int dayNumber);
int findHighestSalesDay(float dailySales[], int numberOfDays);
void displayBarChart(float dailySales[], int numberOfDays);
int main() {

    int days = getValidDays();
    
    float dailySales[7];
    float festivalTotalSales = 0.0;
    
    for (int i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotalSales += dailySales[i];
    }
    
    int highestDay = findHighestSalesDay(dailySales, days);
    
    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotalSales);
    printf("Day with highest sales: Day %d\n", highestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[highestDay - 1]);
    displayBarChart(dailySales, days);
    
    return 0;
}
int getValidDays() {
    int days;
    do {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days < 1 || days > 7) {
            printf("Invalid input! Please enter a value between 1 and 7.\n");
        }
    } while (days < 1 || days > 7);
    return days;
}
float calculateDailySales(int dayNumber) {
    int numOrders;
    printf("\n--- Day %d ---\n", dayNumber);
    printf("Enter number of orders: ");
    scanf("%d", &numOrders);
    
    float totalSales = 0.0;
    float highestOrder = 0.0;
    
    for (int i = 1; i <= numOrders; i++) {
        float orderAmount;
        do {
            printf("Enter amount for order %d: ", i);
            scanf("%f", &orderAmount);
            if (orderAmount <= 0) {
                printf("Invalid amount! Order amount must be greater than zero.\n");
            }
        } while (orderAmount <= 0);
        
        totalSales += orderAmount;
        if (i == 1 || orderAmount > highestOrder) {
            highestOrder = orderAmount;
        }
    }
    
    float averageOrder = totalSales / numOrders;
    
    printf("Total sales: Rs. %.2f\n", totalSales);
    printf("Average order: Rs. %.2f\n", averageOrder);
    printf("Highest order: Rs. %.2f\n", highestOrder);
    
    return totalSales;
}
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int maxIndex = 0;
    for (int i = 1; i < numberOfDays; i++) {
        // Using strictly '>' ensures the earliest day is kept in case of a tie
        if (dailySales[i] > dailySales[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex + 1;
}
void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (int i = 0; i < numberOfDays; i++) {
        int asterisks = (int)(dailySales[i] / 100);
        
        printf("Day %d: ", i + 1);
        for (int j = 0; j < asterisks; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}