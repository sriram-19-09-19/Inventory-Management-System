#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Item {
    char name[50];
    float price;
    int quantity;
};


void addItem(struct Item **inventory, int *count);
void updateItem(struct Item *inventory, int count);
void deleteItem(struct Item **inventory, int *count);
void displayInventory(const struct Item *inventory, int count);
float totalValue(const struct Item *inventory, int count);

int main() {
    int count = 0;
    struct Item *inventory = NULL;

   
    printf("Enter the initial number of items in inventory: ");
    if (scanf("%d", &count) != 1 || count < 0) {
        printf("Invalid number of items.\n");
        return 1;
    }

    
    if (count > 0) {
        inventory = (struct Item *)malloc(count * sizeof(struct Item));
        if (inventory == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        
        for (int i = 0; i < count; i++) {
            printf("\nEnter details for item %d:\n", i + 1);
            printf("Name: ");
            scanf(" %[^\n]s", inventory[i].name);
            printf("Price: ");
            scanf("%f", &inventory[i].price);
            printf("Quantity: ");
            scanf("%d", &inventory[i].quantity);
        }
    }

    int choice;
    do {
        printf("--- Inventory Management System ---\n");
        printf("Enter your choice:\n");
        printf("1. Add New Item\n");
        printf("2. Update Existing Item\n");
        printf("3. Delete Item\n");
        printf("4. Display All Inventory Items\n");
        printf("5. Calculate Total Inventory Value\n");
        printf("6. Exit\n");
        
        scanf("%d", &choice);

        switch (choice) {
            case 1:        
                addItem(&inventory, &count);
                break;
            case 2:             
                updateItem(inventory, count);
                break;
            case 3:
                deleteItem(&inventory, &count);
                break;
            case 4:
                displayInventory(inventory, count);
                break;
            case 5:
                printf("\nTotal Inventory Value: $%.2f\n", totalValue(inventory, count));
                break;
            case 6:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } 

   
    if (inventory != NULL) {
        free(inventory);
        inventory = NULL;
    }

    return 0;
}


void addItem(struct Item **inventory, int *count) {
    (*count)++;
    struct Item *temp = (struct Item *)realloc(*inventory, (*count) * sizeof(struct Item));
   
    if (temp == NULL) {
        printf("Memory allocation failed! Could not add item.\n");
        (*count)--; // Revert count increase if realloc fails
        return;
    }
    *inventory = temp;

    int index = *count - 1;
    printf("\nEnter details for the new item:\n");
    printf("Name: ");
    scanf(" %[^\n]s", (*inventory)[index].name);
    printf("Price: ");
    scanf("%f", &(*inventory)[index].price);
    printf("Quantity: ");
    scanf("%d", &(*inventory)[index].quantity);
   
    printf("Item added successfully!\n");
}


void updateItem(struct Item *inventory, int count) {
    if (count == 0 || inventory == NULL) {
        printf("\nInventory is empty. Nothing to update.\n");
        return;
    }

    char searchName[50];
    printf("\nEnter the name of the item to update: ");
    scanf(" %[^\n]s", searchName);

    for (int i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, searchName) == 0) {
            printf("Item found! Enter new details:\n");
            printf("New Price: ");
            scanf("%f", &inventory[i].price);
            printf("New Quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Item updated successfully!\n");
            return;
        }
    }
    printf("Item '%s' not found in inventory.\n", searchName);
}


void deleteItem(struct Item **inventory, int *count) {
    if (*count == 0 || *inventory == NULL) {
        printf("\nInventory is empty. Nothing to delete.\n");
        return;
    }

    char searchName[50];
    printf("\nEnter the name of the item to delete: ");
    scanf(" %[^\n]s", searchName);

    int foundIndex = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp((*inventory)[i].name, searchName) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Item '%s' not found in inventory.\n", searchName);
        return;
    }

    // Shift subsequent items to fill the gap
    for (int i = foundIndex; i < *count - 1; i++) {
        (*inventory)[i] = (*inventory)[i + 1];
    }

    (*count)--;

    if (*count == 0) {
        free(*inventory);
        *inventory = NULL;
    } else {
        // Downsize memory allocation block
        struct Item *temp = (struct Item *)realloc(*inventory, (*count) * sizeof(struct Item));
        if (temp != NULL) {
            *inventory = temp;
        }
    }
    printf("Item deleted successfully!\n");
}


void displayInventory(const struct Item *inventory, int count) {
    if (count == 0 || inventory == NULL) {
        printf("\nInventory is empty.\n");
        return;
    }

    printf("\n--- Current Inventory Items ---\n");
    printf("%-30s %-10s %-10s\n", "Item Name", "Price", "Quantity");
   
    for (int i = 0; i < count; i++) {
        printf("%-30s $%-9.2f %-10d\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}


float totalValue(const struct Item *inventory, int count) {
    float total = 0.0;
    if (inventory == NULL) return total;
   
    for (int i = 0; i < count; i++) {
        total += inventory[i].price * inventory[i].quantity;
    }
    return total;
}
