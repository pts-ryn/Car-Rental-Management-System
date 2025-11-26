#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =======================================
   STRUCT DEFINITIONS
   ======================================= */
struct Car {
    int id;
    char model[50];
    char status[20];
    float pricePerDay;
};

struct Customer {
    int id;
    char name[50];
    char phone[20];
};

struct Rental {
    int rentalId;
    struct Car car;
    struct Customer customer;
    char rentDate[20];
    char returnDate[20];
    float totalCost;
};

/* =======================================
   FUNCTION DECLARATIONS
   ======================================= */
void carMenu();
void customerMenu();
void rentalMenu();

void addCar(struct Car cars[], int *carCount);
void viewCars(struct Car cars[], int carCount);
void updateCar(struct Car cars[], int carCount);
void deleteCar(struct Car cars[], int *carCount);
void reportDamagedCar(struct Car cars[], int carCount);

void addCustomer(struct Customer customers[], int *customerCount);
void viewCustomers(struct Customer customers[], int customerCount);

void rentCar(struct Car cars[], int carCount, struct Customer customers[], int customerCount, struct Rental rentals[], int *rentalCount);
void returnCar(struct Car cars[], int carCount, struct Rental rentals[], int rentalCount);
void viewRentals(struct Rental rentals[], int rentalCount);

void saveData(struct Car cars[], int carCount, struct Customer customers[], int customerCount, struct Rental rentals[], int rentalCount);
void loadData(struct Car cars[], int *carCount, struct Customer customers[], int *customerCount, struct Rental rentals[], int *rentalCount);

void clearInputBuffer();
void pausemsg();
void trimNewline(char *str);

/* =======================================
   MAIN FUNCTION
   ======================================= */
int main() {
    struct Car cars[100];
    struct Customer customers[100];
    struct Rental rentals[100];
    int carCount = 0, customerCount = 0, rentalCount = 0;
    int choice;

    loadData(cars, &carCount, customers, &customerCount, rentals, &rentalCount);

    do {
        printf("\n==============================\n");
        printf("     CAR RENTAL SYSTEM MENU");
        printf("\n==============================\n");
        printf("1. Car Management\n");
        printf("2. Customer Management\n");
        printf("3. Rental Management\n");
        printf("4. Save and Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: {
                int carChoice;
                do {
                    carMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &carChoice);
                    clearInputBuffer();

                    switch (carChoice) {
                        case 1: addCar(cars, &carCount); break;
                        case 2: viewCars(cars, carCount); break;
                        case 3: updateCar(cars, carCount); break;
                        case 4: deleteCar(cars, &carCount); break;
                        case 5: reportDamagedCar(cars, carCount); break;
                        case 6: break;
                        default: printf("Invalid choice!\n");
                    }
                } while (carChoice != 6);
                break;
            }

            case 2: {
                int custChoice;
                do {
                    customerMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &custChoice);
                    clearInputBuffer();

                    switch (custChoice) {
                        case 1: addCustomer(customers, &customerCount); break;
                        case 2: viewCustomers(customers, customerCount); break;
                        case 3: break;
                        default: printf("Invalid choice!\n");
                    }
                } while (custChoice != 3);
                break;
            }

            case 3: {
                int rentChoice;
                do {
                    rentalMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &rentChoice);
                    clearInputBuffer();

                    switch (rentChoice) {
                        case 1: rentCar(cars, carCount, customers, customerCount, rentals, &rentalCount); break;
                        case 2: returnCar(cars, carCount, rentals, rentalCount); break;
                        case 3: viewRentals(rentals, rentalCount); break;
                        case 4: break;
                        default: printf("Invalid choice!\n");
                    }
                } while (rentChoice != 4);
                break;
            }

            case 4:
                saveData(cars, carCount, customers, customerCount, rentals, rentalCount);
                printf("\nAll data saved. Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}

/* =======================================
   UTILITY FUNCTIONS
   ======================================= */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void pausemsg() {
    printf("\nPress Enter to continue...");
    getchar();
}
void trimNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* =======================================
   MENUS
   ======================================= */
void carMenu() {
    printf("\n=== CAR MANAGEMENT MENU ===\n");
    printf("1. Add Car\n");
    printf("2. View Cars\n");
    printf("3. Update Car\n");
    printf("4. Delete Car\n");
    printf("5. Report Damaged Car\n");
    printf("6. Back to Main Menu\n");
}

void customerMenu() {
    printf("\n=== CUSTOMER MANAGEMENT MENU ===\n");
    printf("1. Add Customer\n");
    printf("2. View Customers\n");
    printf("3. Back to Main Menu\n");
}

void rentalMenu() {
    printf("\n=== RENTAL MANAGEMENT MENU ===\n");
    printf("1. Rent Car\n");
    printf("2. Return Car\n");
    printf("3. View Rentals\n");
    printf("4. Back to Main Menu\n");
}

/* =======================================
   CAR FUNCTIONS
   ======================================= */
void addCar(struct Car cars[], int *carCount) {
    struct Car newCar;
    newCar.id = *carCount + 1;

    printf("Enter model: ");
    fgets(newCar.model, sizeof(newCar.model), stdin);
    trimNewline(newCar.model);

    printf("Enter price per day: ");
    scanf("%f", &newCar.pricePerDay);
    clearInputBuffer();

    strcpy(newCar.status, "Available");

    cars[*carCount] = newCar;
    (*carCount)++;

    printf("Car added successfully!\n");
    pausemsg();
}

void viewCars(struct Car cars[], int carCount) {
    if (carCount == 0) {
        printf("No cars available.\n");
        pausemsg();
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "Model", "Status", "Price");
    printf("------------------------------------------\n");
    for (int i = 0; i < carCount; i++)
        printf("%-5d %-20s %-10s $%.2f\n", cars[i].id, cars[i].model, cars[i].status, cars[i].pricePerDay);
    pausemsg();
}

void updateCar(struct Car cars[], int carCount) {
    int id, found = 0;
    printf("Enter Car ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < carCount; i++) {
        if (cars[i].id == id) {
            printf("Enter new model: ");
            fgets(cars[i].model, sizeof(cars[i].model), stdin);
            trimNewline(cars[i].model);
            printf("Enter new price: ");
            scanf("%f", &cars[i].pricePerDay);
            clearInputBuffer();
            printf("Enter new status: ");
            fgets(cars[i].status, sizeof(cars[i].status), stdin);
            trimNewline(cars[i].status);
            printf("Car updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Car not found.\n");
    pausemsg();
}

void deleteCar(struct Car cars[], int *carCount) {
    int id, found = 0;
    printf("Enter Car ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < *carCount; i++) {
        if (cars[i].id == id) {
            for (int j = i; j < *carCount - 1; j++)
                cars[j] = cars[j + 1];
            (*carCount)--;
            found = 1;
            printf("Car deleted.\n");
            break;
        }
    }
    if (!found) printf("Car not found.\n");
    pausemsg();
}

void reportDamagedCar(struct Car cars[], int carCount) {
    int id;
    printf("Enter Car ID to mark as Damaged: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < carCount; i++) {
        if (cars[i].id == id) {
            strcpy(cars[i].status, "Damaged");
            printf("Car %d marked as damaged.\n", id);
            pausemsg();
            return;
        }
    }
    printf("Car not found.\n");
    pausemsg();
}

/* =======================================
   CUSTOMER FUNCTIONS
   ======================================= */
void addCustomer(struct Customer customers[], int *customerCount) {
    struct Customer newCustomer;
    newCustomer.id = *customerCount + 1;

    printf("Enter name: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    trimNewline(newCustomer.name);

    printf("Enter phone: ");
    fgets(newCustomer.phone, sizeof(newCustomer.phone), stdin);
    trimNewline(newCustomer.phone);

    customers[*customerCount] = newCustomer;
    (*customerCount)++;

    printf("Customer added successfully!\n");
    pausemsg();
}

void viewCustomers(struct Customer customers[], int customerCount) {
    if (customerCount == 0) {
        printf("No customers found.\n");
        pausemsg();
        return;
    }

    printf("\n%-5s %-20s %-15s\n", "ID", "Name", "Phone");
    printf("-------------------------------------\n");
    for (int i = 0; i < customerCount; i++)
        printf("%-5d %-20s %-15s\n", customers[i].id, customers[i].name, customers[i].phone);
    pausemsg();
}

/* =======================================
   RENTAL FUNCTIONS
   ======================================= */
void rentCar(struct Car cars[], int carCount, struct Customer customers[], int customerCount, struct Rental rentals[], int *rentalCount) {
    int carId, custId, carIndex = -1, custIndex = -1;
    printf("Enter Car ID to rent: ");
    scanf("%d", &carId);
    clearInputBuffer();
    printf("Enter Customer ID: ");
    scanf("%d", &custId);
    clearInputBuffer();

    for (int i = 0; i < carCount; i++)
        if (cars[i].id == carId && strcmp(cars[i].status, "Available") == 0)
            carIndex = i;

    for (int j = 0; j < customerCount; j++)
        if (customers[j].id == custId)
            custIndex = j;

    if (carIndex == -1) { printf("Car not available.\n"); pausemsg(); return; }
    if (custIndex == -1) { printf("Customer not found.\n"); pausemsg(); return; }

    struct Rental newRental;
    newRental.rentalId = *rentalCount + 1;
    newRental.car = cars[carIndex];
    newRental.customer = customers[custIndex];

    printf("Enter rent date (DD/MM/YYYY): ");
    fgets(newRental.rentDate, sizeof(newRental.rentDate), stdin);
    trimNewline(newRental.rentDate);
    strcpy(newRental.returnDate, "-");

    printf("Enter total days rented: ");
    int days; scanf("%d", &days); clearInputBuffer();
    newRental.totalCost = days * cars[carIndex].pricePerDay;

    strcpy(cars[carIndex].status, "Rented");
    rentals[*rentalCount] = newRental;
    (*rentalCount)++;

    printf("Car rented successfully! Total cost: $%.2f\n", newRental.totalCost);
    pausemsg();
}

void returnCar(struct Car cars[], int carCount, struct Rental rentals[], int rentalCount) {
    int id, found = 0;
    printf("Enter Rental ID to return: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < rentalCount; i++) {
        if (rentals[i].rentalId == id && strcmp(rentals[i].returnDate, "-") == 0) {
            printf("Enter return date (DD/MM/YYYY): ");
            fgets(rentals[i].returnDate, sizeof(rentals[i].returnDate), stdin);
            trimNewline(rentals[i].returnDate);
            for (int i = 0; j < carCount; i++)
                if (cars[i].id == rentals[i].car.id)
                    strcpy(cars[i].status, "Available");
            printf("Car returned successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Rental not found or already returned.\n");
    pausemsg();
}

void viewRentals(struct Rental rentals[], int rentalCount) {
    if (rentalCount == 0) {
        printf("No rentals found.\n");
        pausemsg();
        return;
    }

    printf("\n%-5s %-15s %-15s %-10s %-10s %-10s\n", "ID", "Customer", "Car", "RentDate", "Return", "Total");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < rentalCount; i++) {
        printf("%-5d %-15s %-15s %-10s %-10s $%.2f\n",
               rentals[i].rentalId, rentals[i].customer.name, rentals[i].car.model,
               rentals[i].rentDate, rentals[i].returnDate, rentals[i].totalCost);
    }
    pausemsg();
}

/* =======================================
   FILE HANDLING
   ======================================= */
void saveData(struct Car cars[], int carCount, struct Customer customers[], int customerCount, struct Rental rentals[], int rentalCount) {
    FILE *fp = fopen("car_rental_data.txt", "w");
    if (!fp) {
        printf("Error saving data.\n");
        return;
    }

    fprintf(fp, "CARS %d\n", carCount);
    for (int i = 0; i < carCount; i++)
        fprintf(fp, "%d|%s|%s|%.2f\n", cars[i].id, cars[i].model, cars[i].status, cars[i].pricePerDay);

    fprintf(fp, "CUSTOMERS %d\n", customerCount);
    for (int i = 0; i < customerCount; i++)
        fprintf(fp, "%d|%s|%s\n", customers[i].id, customers[i].name, customers[i].phone);

    fprintf(fp, "RENTALS %d\n", rentalCount);
    for (int i = 0; i < rentalCount; i++)
        fprintf(fp, "%d|%s|%s|%s|%s|%.2f\n",
                rentals[i].rentalId,
                rentals[i].customer.name,
                rentals[i].car.model,
                rentals[i].rentDate,
                rentals[i].returnDate,
                rentals[i].totalCost);

    fclose(fp);
}

void loadData(struct Car cars[], int *carCount, struct Customer customers[], int *customerCount, struct Rental rentals[], int *rentalCount) {
    FILE *fp = fopen("car_rental_data.txt", "r");
    if (!fp) return;

    fscanf(fp, "CARS %d\n", carCount);
    for (int i = 0; i < *carCount; i++)
        fscanf(fp, "%d|%49[^|]|%19[^|]|%f\n", &cars[i].id, cars[i].model, cars[i].status, &cars[i].pricePerDay);

    fscanf(fp, "CUSTOMERS %d\n", customerCount);
    for (int i = 0; i < *customerCount; i++)
        fscanf(fp, "%d|%49[^|]|%19[^\n]\n", &customers[i].id, customers[i].name, customers[i].phone);

    fscanf(fp, "RENTALS %d\n", rentalCount);
    for (int i = 0; i < *rentalCount; i++)
        fscanf(fp, "%d|%49[^|]|%49[^|]|%19[^|]|%19[^|]|%f\n",
               &rentals[i].rentalId,
               rentals[i].customer.name,
               rentals[i].car.model,
               rentals[i].rentDate,
               rentals[i].returnDate,
               &rentals[i].totalCost);

    fclose(fp);
}
