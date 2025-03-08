#ifndef CONTACT_H
#define CONTACT_H
//#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[50];
    char email[50];
} Contact;

typedef struct {
    Contact *contacts;
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
int checkDuplicateDetails(AddressBook *addressBook, const char *name, const char *phone, const char *email);
void clearInputBuffer();
void displayLoadingBar();

#endif
