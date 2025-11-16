#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    int id;
    char model[50];
    char status[20];
    float pricePerDay;
};

struct Customer {
    int id;
    char name[50];
    char phone[50];
};

struct Rental {
    int carId;
    struct Car car;
    struct Customer customer;
    int customerId;
    char rentDate[20];
    char returnDate[20];
    float totalCost;
};

void carMenu();
void CustomerMenu();
void rentalMenu();

// all of this is uses void to easily code

void addCar(struct Car cars[], int *carCount);
void viewCars(struct Car cars[], int carCount);
void updateCar(struct Car cars[], int carCount);
void deleteCar(struct Car cars[], int *carCount);
void reportdamageCar(struct Car cars[], int carCount);

void addCustomer(struct Customer customers[], int *customerCount);
void viewCustomers(struct Customer customers[], int customerCount);

void rentCar(struct Car cars[], int rentCount, struct Customer customers[], int customerCount, struct Rental rentals[], int *rentalCount);
void renturnCar(struct Car cars[], int returnCount, struct Rental rentals[], int rentalCount);
void viewRentals(struct Rental rentals[], int rentalCount);

void saveData(struct Car cars[], int rentCount, struct Customer customers[], int customerCount, struct Rental rentals[], int rentalCount);
void loadData(struct Car cars[], int *rentCount, struct Customer customers[], int customerCount, struct Rental rentals[], int *renatlCount);

void clearInputBuffer();
void pausemsg();
void trimNewline(char *str);

// we will start for introduction of main functions

int main () {
    struct Car cars;
    struct Customer customers;
    struct Rental rentals;

    int carCount = 0, customerCount = 0, rentalCount = 0;
    int choice;

    loadData(cars, &carCount, customers, &customerCount, rentals, &rentalCount);

    do {
        printf("==============================\n");
        printf(" CAR RENTAL SYSTEM MENU\n");
        printf("==============================\n");
        printf("1. Car Management\n");
        printf("2. Customer Management\n");
        printf("3. Rental Management\n");
        printf("4. Save and Exit!\n");
        printf("==============================\n");
        printf("Enter Your Choice: \n")
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

                    switch(carChoice){
                        case 1: addCar(cars, &carCount);break;
                        case 2: viewCars(cars, carCount);break;
                        case 3: updateCar(cars, carCount);break;
                        case 4: deleteCar(cars, carCount);break;
                        case 5: reportdamageCar(cars, carCount);break;
                        case 6: break;
                        default: printf("Invalid Choice!\n");
                    }
                } while(carChoice != 6);
                break;
            }

            case 2: {
                int customerChoice;
                do {
                    CustomerMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &customerChoice):
                    clearInputBuffer();

                    switch(customerChoice) {
                        case !: addCustomer(customers, &customerCount);
                        case 2: viewCustomers(customers, customerCount);
                        case 3: break;
                        default: printf("Invalid Choice!\n");
                    }
                } while(customerChoice !=3);
                break;
            }

            case 3: {
                int rentChoice;
                do {
                    rentMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &rentChoice);
                    clearInputBuffer();

                    switch(rentChoice) {
                        case 1: rentCar(cars, carCount, customers, customerCount, rentals, &rentalCount);break;
                        case 2: returnCar(cars, carCount, customers, customerCount);break;

                        case 3: viewRentals(renatals, rentalCount);break;
                        case 4: break:
                        default: printf("Invalid Choice!\n");
                    }
                } while(rentChoice !=4);
                break;
            }

            case 4:
                saveData(cars, carCount, customers, customerCount. rentals, rentalCount);
                printf("\nAll Data Saved. Exiting Program.....\n");
                break;

                default: printf("Invalid Choice! Try Again.\n");
            }
        } while(choice !=4);

    return 0;
}

void clearInputBuffer() {
    int c;
    while (( c = getchar()) != '\n' && c ! = EOF);
}

void pausemsg() {
    printf("\Press Enter To Continue...");
    getchar();
}

void trimNewline() {
    str[strcspn(str, "\n")] = '\0';
}

void carMenu() {
    printf("\n===== CAR MANAGEMENT MENU =====\n");
    printf("1. Add Car\n");
    printf("2. View Cars\n");
    printf("3. Update Car\n");
    printf("4. Delete Car\n");
    printf("5. Report Damage Car\n");
    printf("6. Back to Main Menu\n");
}

void customerMenu() {
    printf("\n===== CUSTOMER MANAGEMENT MENU =====\n");
    printf("1. Add Customer\n");
    printf("2. View Customers\n");
    printf("3. Back to Main Menu\n");
}

void rentalMenu() {
    printf("\n===== RENTAL MANAGEMENT =====\n");
    printf("1. Rent Car\n");
    printf("2. Renturn Car\n");
    printf("3. View Rentals\n");
    printf("4. Back to Main Menu\n");
}

void addCar(struct Car cars[], int *carCount) {
    struct Car newcar;
    newCar.id = *carCount + 1;

    printf("Enter Model: ");
    fgets(newCar.model, sizeof(newCar.model), stdin);

    printf("Enter Price Per Day: ");
    scanf("%d", &newCar.pricePerDay);
    clearInputBuffer();

    strcpy(newCar.status, "Available");

    cars[*carCount] = newCar;
    (*carCount)++;

    printf("Car Addded Successfully!\n");
    pausemsg();
}

void updateCar(struct Car cars[], int carCount) {
    int id, found = 0;
    printf("Enter Car ID to Update: ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < carCount; i++) {
        if (cars[i].id == id) {
            printf("Enter Your Model: ");
            fgets(cars[i].model, sizeof(cars[i].model), stdin);
            trimNewline(cars[i].model);

            printf("Enter New Price: ");
            scanf("&f", &cars[i].pricePerDay);
            clearInputBuffer();

            printf("Enter New Status: ");
            fgets(cars[i].status, sizeof(cars[i].status), stdin);
            trimNewline(cars[i].status);

            printf("Car Update Successfully!\n");
            found = 1;
            break;
        }
    }
    if(!found)
        printf("Car not found.\n");
        pausemsg();
}

void deleteCar(struct Car cars[], int* carCount) {
    int id, found = 0;
    printf("Enter Car ID to Delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < carCount; i++) {
        if(cars[i].id == id) {
            for(int j = i; j < *carCount - 1; j++)
                cars[i] = cars [j + 1];
            (*carCount)--;
            found = 1;

            printf("Car Deleted.\n");
            break;
        }
    }
    if(!found)
        printf("Car not found.\n");
        pausemsg();
}

void reportdamageCar(struct Car cars[], int carCount) {
    int id;
    printf("Enter Car ID to Mark as Damaaged: ");
    scanf("%d", &id);
    clearInputBuffer();

    for(int i = 0; i < carCount; i++) {
        if(cars[i].id == id) {
            strcpy(cars[i].status "Damaged");
            printf("Car %d Mark as Damaged.\n", id);
            pausemsg();
            return;
        }
    }
    printf("Car not found.\n");
    pausemsg();
}
