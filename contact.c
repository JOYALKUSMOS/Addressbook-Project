#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void clearInputBuffer()
{
    int c;
    while((c=getchar()) != '\n' && c!=EOF);
}

int checkDuplicateDetails(AddressBook *addressBook, const char *name, const char *phone, const char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            if (phone != NULL && strcmp(addressBook->contacts[i].phone, phone) == 0) {
                printf("This phone number already exists for this name. Please enter a different number.\n");
                return 1;
            }
            if (email != NULL && strcmp(addressBook->contacts[i].email, email) == 0) {
                printf("This email address already exists for this name. Please enter a different email.\n");
                return 1;
            }
        }
    }
    return 0;
}

void initialize(AddressBook *addressBook) {
    addressBook->contacts = NULL;
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void listContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("*******************************************************\n");
    printf("                     Address Book                      \n");
    printf("*******************************************************\n");
    printf("%-20s %-15s %-20s\n", "Name", "Phone", "Email");
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-20s %-15s %-20s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("********************************************************\n");
}


void createContact(AddressBook *addressBook) {
    Contact *temp = realloc(addressBook->contacts, (addressBook->contactCount + 1) * sizeof(Contact));
    if (!temp) {
        printf("Memory allocation failed.\n");
        return;
    }
    addressBook->contacts = temp;
    printf("Enter name:");
    clearInputBuffer();
    char name[50];
    scanf("%[^\n]",name);
    char phone[15];
    do {
        printf("Enter phone number:");
        clearInputBuffer();
        scanf("%[^\n]",phone);
    }while(checkDuplicateDetails(addressBook,name,phone,NULL));
    char email[50];
    do {
        printf("Enter email id:");
        clearInputBuffer();
        scanf("%[^\n]",email);
    }while(checkDuplicateDetails(addressBook,name,NULL,email));
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;
    printf("Contact created successfully.\n");
}


void searchContact(AddressBook *addressBook) {
    char name[50];
    printf("Enter the name/phone number/email to search: ");
    clearInputBuffer();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';
    int found = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if((strcmp(addressBook->contacts[i].name, name) == 0) ||(strcmp(addressBook->contacts[i].phone, name) == 0) ||(strcmp(addressBook->contacts[i].email, name) == 0))
        {
            if (!found) 
            {
                printf("Contact(s) found:\n");
                found = 1;
            }
            printf("%-20s %-15s %-20s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (!found)
    {
        printf("Contact not found\n");

    }
}


void editContact(AddressBook *addressBook) 
{
    char name[50];
    printf("Enter the name to edit: ");
    clearInputBuffer();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';
    int indices[100];
    int count = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            indices[count++] = i;
        }
    }
    if (count == 0) {
        printf("No contacts found with the name '%s'.\n", name);
        return;
    }
    printf("Found %d contact(s) with the name '%s':\n", count, name);
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        printf("%d. %-20s %-15s %-20s\n", i + 1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
    }
    int choice;
    printf("Enter the number of the contact you want to edit (1-%d): ", count);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    int selectedIndex = indices[choice - 1];
    printf("Editing contact %d:\n", choice);
    printf("Enter new name: ");
    scanf("%[^\n]", addressBook->contacts[selectedIndex].name);
    clearInputBuffer();
    printf("Enter new phone: ");
    scanf("%[^\n]", addressBook->contacts[selectedIndex].phone);
    clearInputBuffer();
    printf("Enter new email: ");
    scanf("%[^\n]", addressBook->contacts[selectedIndex].email);
    clearInputBuffer();
    printf("Contact updated successfully.\n");
}

void deleteContact(AddressBook *addressBook) 
{
    char name[50];
    printf("Enter the name to delete:");
    clearInputBuffer();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0'; 
    int indices[100];
    int count = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            indices[count++] = i;
        }
    }
    if (count == 0) {
        printf("No contacts found with the name '%s'.\n", name);
        return;
    }
    printf("Found %d contact(s) with the name '%s':\n", count, name);
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        printf("%d. %-20s %-15s %-20s\n", i + 1, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
    }
    int choice;
    printf("Enter the number of the contact you want to delete (1-%d): ", count);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    int selectedIndex = indices[choice - 1];
    for (int i = selectedIndex; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    addressBook->contacts = realloc(addressBook->contacts, addressBook->contactCount * sizeof(Contact));
    printf("Contact deleted successfully.\n");
}
