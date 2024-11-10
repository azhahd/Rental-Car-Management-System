#include "q1.h"

int main() {
    struct car *available_head = NULL;
    struct car *rented_head = NULL;
    struct car *repair_head = NULL;
    struct car *temp = NULL;

    int choice;
    int mileage;
    int return_date;
    char plate[8];  // The plate number must be 2-8 characters long

    // Read data from files into the linked lists
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    do {
        prompt();

        printf("Enter a choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // Insert a new car into the available list
            printf("Enter your plate number (up to 8 characters): ");
            scanf("%8s", plate);  // Limiting input to 8 characters + null terminator
            printf("Enter your current total mileage: ");
            scanf("%d", &mileage);
            insert_to_list(&available_head, plate, mileage, -1);  // Use -1 for no return date
            break;

        case 2:
            // Move car from available to rented
            printf("Enter your plate number: ");
            scanf("%8s", plate);  // Limiting input to 8 characters
            temp = remove_car_from_list(&rented_head, plate);
            if (temp != NULL) {
                printf("Enter the return date (YYMMDD): ");
                scanf("%d", &return_date);
                temp->return_date = return_date;
                insert_to_list(&available_head, temp->plate, temp->mileage, temp->return_date);
                sort_list(&available_head, true, false);
            } else {
                printf("Car with plate %s not found in the available list.\n", plate);
            }
            break;

        case 3:
            // Move a returned car to the repair list
            printf("Enter your plate number: ");
            scanf("%8s", plate);
            temp = remove_car_from_list(&rented_head, plate);
            if (temp != NULL) {
                insert_to_list(&repair_head, temp->plate, temp->mileage, temp->return_date);

            } else {
                printf("Car with plate %s not found in the rented list.\n", plate);
                sort_list(&available_head, true, false);
            }
            break;

        case 4:
            // Move a repaired car back to available
            printf("Enter your plate number: ");
            scanf("%8s", plate);
            temp = remove_car_from_list(&repair_head, plate);
            if (temp != NULL) {
                insert_to_list(&available_head, temp->plate, temp->mileage, temp->return_date);
            } else {
                printf("Car with plate %s not found in the repair list.\n", plate);
            }
            break;

        case 5:
            // Rent the first available car
            temp = remove_first_from_list(&available_head);
            if (temp != NULL) {
                printf("Enter the return date (YYMMDD): ");
                scanf("%d", &return_date);
                temp->return_date = return_date;
                insert_to_list(&rented_head, temp->plate, temp->mileage, temp->return_date);
            } else {
                printf("No cars available for renting.\n");
            }
            break;

        case 6:
            // Print the available, rented, and repair lists
            printf("Available Cars:\n");
            print_list(available_head);

            printf("\nRented Cars:\n");
            print_list(rented_head);

            printf("\nCars in Repair:\n");
            print_list(repair_head);
            break;

        case 7:
            // Save lists to files before quitting
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);

            printf("Exiting the program.\n");
            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);
            return 0;  // Exit the program

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

    } while (true);  // Keep running until the user chooses to exit

    return 0;
}
