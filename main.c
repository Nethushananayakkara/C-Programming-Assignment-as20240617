#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LEN 50
#define NUM_VEHICLES 3
#define FUEL_PRICE 310.0

    char vehicleName[20];
    int vehicleCapacity[];
    double vehicleRate[];
    double vehicleSpeed[];
    double vehicleEfficiency[];


    int deliverySource[];
    int deliveryDestination[];
    int deliveryVehicleType[];
    double deliveryWeight[];
    double deliveryDistance[];
    double deliveryBaseCost[];
    double deliveryFuelUsed[];
    double deliveryFuelCost[];
    double deliveryOperationalCost[];
    double deliveryProfit[];
    double deliveryCustomerCharge[];
    double deliveryTime[];


char cities[MAX_CITIES][MAX_NAME_LEN];
int cityCount = 0;
double distanceMatrix[MAX_CITIES][MAX_CITIES];
int deliveries[MAX_DELIVERIES];
int deliveryCount = 0;

char * vehicles[NUM_VEHICLES] = {
    {"Van",   1000, 30.0, 60.0, 12.0},
    {"Truck", 5000, 40.0, 50.0, 6.0},
    {"Lorry", 10000, 80.0, 45.0, 4.0}
};



int vehicleCapacity[]={1000,5000,10000};
double vehicleRate[]={30.0,40.0,80.0};
double vehicleSpeed[]={60.0,50.0,45.0};
double vehicleEfficiency[]={12.0,6.0,4.0};

void menu();
void cityManagement();
void distanceManagement();
void newDelivery();
void viewReports();
void saveData();
void loadData();
void displayCities();
void displayDistanceTable();
int takeCityIndex(const char *prompt);
double calculateCost(double d, double r, double w);
double calculateFuel(double d, double e);
double calculateTime(double d, double s);

void saveRoutesToFile();
void loadRoutesFromFile();
void saveDeliveriesToFile();
void loadDeliveriesFromFile();

int main() {
    //distance matrix
    for (int i = 0; i < MAX_CITIES; i++){
        for (int j = 0; j < MAX_CITIES; j++){
            distanceMatrix[i][j] = (i == j) ? 0 : -1;
        }
    }
    loadData();
    menu();
    saveData();
    return 0;
}
void menu() {
    int choice;
    do {
        printf("\n---------- LOGISTICS MANAGEMENT SYSTEM ----------\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. New Delivery Request\n");
        printf("4. Reports\n");
        printf("5. Save Data to Files\n");
        printf("6. Load Data from Files\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

                switch(choice) {
            case 1: cityManagement();
            break;
            case 2: distanceManagement();
            break;
            case 3: newDelivery();
            break;
            case 4: viewReports();
            break;
            case 5: saveData();
            break;
            case 6: loadData();
            break;
            case 0: printf("Exiting...\n");
            break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);
}
void cityManagement() {
    int choiceOfManagement;
    do {
        printf("\n--- CITY MANAGEMENT ---\n");
        printf("1. Add new city\n");
        printf("2. Rename city\n");
        printf("3. Remove city\n");
        printf("4. Display cities\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choiceOfManagement);

         if (choiceOfManagement == 1) {
            if (cityCount >= MAX_CITIES) {
                printf("City limit reached!\n");
            } else {
                printf("Enter city name: ");
                scanf("%s", cities[cityCount]);
                cityCount++;
                printf("City added.\n");
            }
        } else if (choiceOfManagement == 2) {
            displayCities();
            int index = takeCityIndex("Enter city index to rename: ");
            if (index >= 0 && index < cityCount) {
                printf("Enter new name: ");
                scanf("%s", cities[index]);
                printf("City renamed.\n");
            }
        } else if (choiceOfManagement == 3) {
            displayCities();
            int index = takeCityIndex("Enter city index to remove: ");
            if (index >= 0 && index < cityCount) {
                for (int i = index; i < cityCount - 1; i++) {
                    strcpy(cities[i], cities[i + 1]);
                    for (int j = 0; j < cityCount; j++) {
                        distanceMatrix[i][j] = distanceMatrix[i + 1][j];
                        distanceMatrix[j][i] = distanceMatrix[j][i + 1];
                    }
                }
                cityCount--;
                printf("City removed.\n");
            }
        } else if (choiceOfManagement == 4) {
            displayCities();
        }
    } while (choiceOfManagement != 0);
}
void distanceManagement() {
    int ch;
    do {
        printf("\n--- DISTANCE MANAGEMENT ---\n");
        printf("1. Enter/Edit distance\n");
        printf("2. Display distance table\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

                if (ch == 1) {
            if (cityCount < 2) {
                printf("Add at least two cities first.\n");
                continue;
            }
            displayCities();
            int a = takeCityIndex("Enter source city index: ");
            int b = takeCityIndex("Enter destination city index: ");
            if (a == b) {
                printf("Distance from city to itself = 0.\n");
                continue;
            }
            double d;
            printf("Enter distance (km): ");
            scanf("%lf", &d);
            distanceMatrix[a][b] = d;
            distanceMatrix[b][a] = d;
            printf("Distance updated.\n");
        } else if (ch == 2) {
            displayDistanceTable();
        }
    } while(ch != 0);
}
void newDelivery() {
    if (cityCount < 2) {
        printf("Add cities and distances first!\n");
        return;
    }

    displayCities();
    int sourceIndex = takeCityIndex("Enter source city index: ");
    int destIndex = takeCityIndex("Enter destination city index: ");
    if (sourceIndex == destIndex) {
        printf("Source and destination must differ.\n");
        return;
    }

    double dist = distanceMatrix[sourceIndex][destIndex];
    if (dist <= 0) {
        printf("Distance not set between these cities.\n");
        return;
    }

    double weight;
    printf("Enter weight (kg): ");
    scanf("%lf", &weight);

    printf("\nSelect vehicle type:\n");
    int i;
    for (i = 0; i < NUM_VEHICLES; i++) {
        printf("%d. %s (Capacity: %d kg, Rate: %f LKR/km)\n",
               i+1, vehicleName[i], vehicleCapacity[i], vehicleRate[i]);
    }

    int choice;
    printf("Enter vehicle number: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > NUM_VEHICLES) {
        printf("Invalid vehicle.\n");
        return;
    }
    int v = choice - 1;

    if (weight > vehicleCapacity[v]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }
 double cost = calculateCost(dist, vehicleRate[v], weight);
    double fuelUsed = calculateFuel(dist, vehicleEfficiency[v]);
    double fuelCost = fuelUsed * FUEL_PRICE;
    double operational = cost + fuelCost;
    double profit = cost * 0.25;
    double charge = operational + profit;
    double time = calculateTime(dist, vehicleSpeed[v]);

    int delivery[] = {sourceIndex, destIndex, v, weight, dist, cost, fuelUsed, fuelCost, operational, profit, charge, time};
    deliveries[deliveryCount++] = *delivery;

    printf("\n---------- DELIVERY SUMMARY ----------\n");
    printf("From: %s  To: %s\n", cities[sourceIndex], cities[destIndex]);
    printf("Distance: %.2f km\n", dist);
    printf("Vehicle: %s\n", vehicleName[v]);
    printf("Weight: %.2f kg\n", deliveryWeight);
    printf("--------------------------------------\n");
    printf("Base Cost: %.2f LKR\n", cost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", operational);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", charge);
    printf("Estimated Time: %.2f hours\n", time);
    printf("======================================\n");
}
