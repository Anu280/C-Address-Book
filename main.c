#include <stdio.h>
#include "contact.h" //include header-file.
#include "file.h"

int main()
{
    AddressBook addressBook;
    initialize(&addressBook); // pass address of variable addressbook of type AddressBook //function call

    int choice; // variable to choose the operation

    do
    {
        printf("----- Address Book Menu -----\n");

        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List All Contact\n");
        printf("6. Save Contact\n");
        printf("7. Exit\n");

        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;

        case 2:
            searchContact(&addressBook, "Enter name/phone/mail to search: "); // function call, based on user choice
            break;

        case 3:
            editContact(&addressBook);
            break;

        case 4:
            deleteContact(&addressBook); // function call.
            break;

        case 5:
            listContacts(&addressBook);
            break;

        case 6:
            saveContactsToFile(&addressBook);
            break;

        case 7:
            saveAndExit(&addressBook);
            break;

        defualt:
            printf("Invalid choice! Please try again\n");
        }

    } while (choice != 7); // stopping condition // check for while(1)
    return 0;
}