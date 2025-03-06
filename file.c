#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "contact.h"

// Save contacts to CSV file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "%d\n", addressBook->contactCount);  // Write contact count at the beginning
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(file);
}

// Load contacts from CSV file
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "r");
    if (!file) {
        printf("No contact data found. Starting with an empty address book.\n");
        return;
    }

    fscanf(file, "%d\n", &addressBook->contactCount);  // Read the contact count
    addressBook->contacts = malloc(addressBook->contactCount * sizeof(Contact));
    if (!addressBook->contacts) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fscanf(file, "%[^,],%[^,],%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(file);
}
