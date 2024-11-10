/*
Name: Aizah Ahmed
Student ID: 1237146
Assignment 2, Question 1
*/
#include "q1.h"


/* function will display the primary user interface
    This is already done for you*/
void prompt(){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date){
    struct car *node;
    struct car *temp = *head; // if head is null create new struct node
    node = (struct car *)malloc(sizeof(struct car));

    strcpy(node->plate, plate);  // Ensure plate is copied safely
    node->mileage = mileage;
    node->return_date = return_date;
    node->next = NULL;


    if (*head == NULL){ 
        *head = node;
    }
    else{
        while (temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = node;
    }

    return node;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){
    while (head != NULL){
        printf("%d, %s, %d", head -> mileage, head ->plate, head -> return_date);
        head = head -> next;
    }
    return;
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    struct car *temp = head;

    // Traverse the list and compare plates
    while (temp != NULL) {
        if (strcmp(temp->plate, plate) == 0) {
            // Plate found in the list
            return true;
        }
        temp = temp->next;
    }

    // Plate not found
    return false;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){
    char t_plate[8]; //temporary plate holder
    int t_mileage; // temp mileage variable
    int t_return_date; //temp return date variable

    if (a == NULL|| b == NULL)
        return;

    strcpy(t_plate, a->plate);
    strcpy(a->plate, b->plate);
    strcpy(b->plate, t_plate);

    t_mileage = a->mileage;
    a->mileage = b->mileage;
    b->mileage = t_mileage;

    t_return_date = a->return_date;
    a->return_date = b->return_date;
    b->return_date = t_return_date;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date) {
    if (*head == NULL) {
        return;
    }

    struct car *current, *next, *lowest;

    for (current = *head; current != NULL; current = current->next) {
        lowest = current;
        for (next = current->next; next != NULL; next = next->next) {
            if (sort_by_mileage && next->mileage < lowest->mileage) {
                lowest = next;
            }
            if (sort_by_return_date && next->return_date < lowest->return_date && next->return_date != -1) {
                lowest = next;
            }
        }
        if (lowest != current) {
            swap(current, lowest);
        }
    }
}


/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]){ //I am not sure whether it should be ** head or *head
    struct car *temp = *head;
    struct car *prev;

// get a counter to iterate through list to find matching plate number, if same then we will say prev -> next = temp -> next

    if (temp == NULL) {
    return NULL;  // If the list is empty, return NULL
    }

    if (strcmp(temp->plate, plate) == 0) {
    *head = temp->next;
    return temp;  // Return the removed car (but don't free it here)
    }

    while (temp != NULL && strcmp(temp->plate, plate) != 0) {
    prev = temp;
    temp = temp->next;
    }

    if (temp == NULL) {
    printf("Car with plate %s not found.\n", plate);
    return NULL;
    }

    prev->next = temp->next;
    return temp;  // Return the removed car (don't free it here)
}
/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){
    struct car *temp = *head;
    
    if (*head == NULL){
        return NULL;
    }
    // Store the current head in a temporary variable

    // Move the head to the next node
    *head = temp -> next;

    free(temp);

    // Return the new head
    return *head;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){
    int d, total_charge, charge;
    
    if (initial_mileage <= 200){
        total_charge = 80.00;
    }
    else if(initial_mileage > 200){
        d = final_mileage - initial_mileage;
        charge = d * 0.15;
        total_charge = 80.00 + charge;
    }
    return total_charge;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head) {
    FILE *file = fopen(filename, "w");  // Open in write mode
    if (file == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    struct car *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%d,%d\n", temp->plate, temp->mileage, temp->return_date);
        temp = temp->next;
    }

    fclose(file);
}


/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head) {
    FILE *file = fopen(filename, "r");  // Open in read mode
    if (file == NULL) {
    printf("File does not exist.\n");
    fclose(file);
    return;  // Remove return -1 since the function is void
    }

    char plate[8];
    int mileage, return_date;
    while (fscanf(file, "%8[^,],%d,%d\n", plate, &mileage, &return_date) != EOF) {
        insert_to_list(head, plate, mileage, return_date);
    }

    fclose(file);
}


/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){
    int day = date%100;
    int month = (date/100) %100;
    int year = date / 10000;  // Divide by 10000 to extract the year


    printf("%02d/%02d/%02d\n", year, month, day);
    return;
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head){
    struct car *temp;

    while (*head != NULL){
        temp = *head;
        *head = (*head) -> next;
        free(temp);
    }
    *head = NULL;
    return;
}