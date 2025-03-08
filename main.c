#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() 
{
    int choice;
    AddressBook book;
    initialize(&book);
   do
   {
    printf("Address Book Menu:\n 1.Create Contact \n 2.Search Contact \n 3.Edit Contact \n 4.Delete Contact \n 5.List all contacts \n 6.Exit\n");
    printf("Enter your choice:\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        createContact(&book);
        break;
        case 2:
        searchContact(&book);
        break;
        case 3:
        editContact(&book);
        break;
        case 4:
        deleteContact(&book);
        break;
        case 5:
        listContacts(&book);
        break;
        case 6:{
            char savechoice;
            printf("Do you want to save the contacts before exiting?(y/n):");
            clearInputBuffer();
            scanf("%c",&savechoice);
            if(savechoice=='y'||savechoice=='Y')
            {
                saveContactsToFile(&book);
            }
                printf("Exiting the address book\n");
                return 0;
        }

        break;
        default:
        printf("Invalid Choice!\n");
        break;
    }

   } while (1);
   return 0;
}
