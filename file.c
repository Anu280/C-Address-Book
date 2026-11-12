#include <stdio.h>
#include "file.h" //used
#include <stdlib.h>
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr = fopen("contacts.txt", "w");

    if (fptr == NULL)
    {
        printf("Error opening the file!\n");
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount); // \n new line used for printing contacts on new line after the contact count.

    for (int i = 0; i < addressBook->contactCount; i++) // print or copy contents into the file
    {
        fprintf(fptr, "%d %s,%s,%s\n", addressBook->contact[i].index, addressBook->contact[i].name, addressBook->contact[i].phone, addressBook->contact[i].mail);
    }

    fclose(fptr); // close the file

    printf("Contacts saved! --------------\n"); // just to check!
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;

    fptr = fopen("contacts.txt", "r");

    if (fptr == NULL)
    {
        printf("Error opening file for saving!\n");
        return;
    }

    char store_string[10]; // reads contact count

    if (fgets(store_string, sizeof(store_string), fptr) != NULL)
    {
        addressBook->contactCount = atoi(store_string); // convert string to integer n store //store the count
    }
    else
    {
        printf("Cannot read contact count!------\n");
        fclose(fptr);
        return; // return
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%d %[^,],%[^,],%[^\n]\n", &addressBook->contact[i].index, addressBook->contact[i].name, addressBook->contact[i].phone, addressBook->contact[i].mail);
    }

    fclose(fptr);

    printf("Contacts loaded to structure! --------------\n"); // just to check!
}
