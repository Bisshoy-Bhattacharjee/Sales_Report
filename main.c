#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MonthlyData {
    char month[20];
    double sales;
};

double calculateAverage(double sales[], int numMonths) {
    double sum = 0;
    for (int i = 0; i < numMonths; i++) {
        sum += sales[i];
    }
    return sum / numMonths;
}

void sortMonthlyData(struct MonthlyData data[], int numMonths) {
    int i, j;
    struct MonthlyData temp;
    for (i = 0; i < numMonths - 1; i++) {
        for (j = i + 1; j < numMonths; j++) {
            if (data[i].sales < data[j].sales) {
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
}

int main() {
    FILE *inputFile = fopen("file.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    double sales[12];
    struct MonthlyData monthlyData[12];


    for (int i = 0; i < 12; i++) {
        fscanf(inputFile, "%lf", &sales[i]);
    }
    fclose(inputFile);


    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


    for (int i = 0; i < 12; i++) {
        strcpy(monthlyData[i].month, months[i]);
        monthlyData[i].sales = sales[i];
    }


    double minSales = sales[0];
    double maxSales = sales[0];
    double avgSales = calculateAverage(sales, 12);

    for (int i = 1; i < 12; i++) {
        if (sales[i] < minSales) {
            minSales = sales[i];
        }
        if (sales[i] > maxSales) {
            maxSales = sales[i];
        }
    }


    sortMonthlyData(monthlyData, 12);


    printf("Monthly sales report for 2022:\n");
    for (int i = 0; i < 12; i++) {
        printf("%s $%.2lf\n", monthlyData[i].month, monthlyData[i].sales);
    }

    printf("\nSales summary:\n");
    printf("Minimum sales: $%.2lf (%s)\n", minSales, months[0]);
    printf("Maximum sales: $%.2lf (%s)\n", maxSales, months[11]);
    printf("Average sales: $%.2lf\n", avgSales);

    printf("\nSix-Month Moving Average Report:\n");

    for (int i = 0; i < 12 - 6; i++) {
        double movingAvg = 0;
        for (int j = 0; j < 6; j++) {
            movingAvg += sales[i + j];
        }
        movingAvg /= 6;
        printf("Moving Avg %s-%s: $%.2lf\n", months[i], months[i + 5], movingAvg);
    }

    printf("\nSales Report (Highest to Lowest):\n");
    for (int i = 0; i < 12; i++) {
        printf("%s $%.2lf\n", monthlyData[i].month, monthlyData[i].sales);
    }

    return 0;
}

