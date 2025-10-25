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
