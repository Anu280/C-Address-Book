#include <stdio.h>
#include "contact.h" //include the user defined 'header' file
#include "populate.h"
#include <string.h>
#include <ctype.h>
#include "file.h"
#include <stdlib.h>

void checkName(AddressBook *);
void checkPhone(AddressBook *);
void checkMail(AddressBook *);
int check_string(AddressBook *);
int compare_str(char *, char *);
int delete_by_name(AddressBook *);
int delete_by_phone(AddressBook *);
int delete_by_mail(AddressBook *);
void editName(AddressBook *, int);
void editPhone(AddressBook *, int);
void editMail(AddressBook *, int);

// //////////////////////////////////function definitions////////////////
void listContacts(AddressBook *addressBook)
{ // print the list of data
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",
               addressBook->contact[i].index,
               addressBook->contact[i].name,
               addressBook->contact[i].phone,
               addressBook->contact[i].mail);
    }
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0; // make it 0 initially
                                   // populateAddressBook(addressBook); // funtion call, passing address of 'addressBook' which is held by the pointer addressBook

    loadContactsFromFile(addressBook);
}

void createContact(AddressBook *addressBook)
{ // firstly, assign index proper value
    addressBook->contact[addressBook->contactCount].index = addressBook->contactCount;
    // call functions
    checkName(addressBook);

    checkPhone(addressBook);

    checkMail(addressBook);

    addressBook->contactCount++; // now increase the count
}
void checkName(AddressBook *addressBook)
{
    while (1) // make user to enter the name again and agin till its valid.
    {
        int flag = 1;
        printf("Enter the name: ");
        scanf(" %49[^\n]", addressBook->contact[addressBook->contactCount].name);

        for (int i = 0; addressBook->contact[addressBook->contactCount].name[i] != '\0'; i++)
        {
            if (addressBook->contact[addressBook->contactCount].name[i] >= '0' && addressBook->contact[addressBook->contactCount].name[i] <= '9')
            {
                printf("Invalid name! Enter the name again.\n");
                flag = 0; // make flag 0
                break;    // this will break from for loop
            }
        }
        if (flag == 1)
        {
            printf("----- Name entered successfully! -----\n");
            break;
        }
    }
}
void checkPhone(AddressBook *addressBook)
{
    while (1)
    {
        int flag1 = 1; // set the flag1
        printf("Enter phone number: ");
        scanf(" %19[^\n]", addressBook->contact[addressBook->contactCount].phone);

        if ((strlen(addressBook->contact[addressBook->contactCount].phone) > 10) || (strlen(addressBook->contact[addressBook->contactCount].phone) < 10))
        {
            flag1 = 0;
        }
        for (int i = 0; addressBook->contact[addressBook->contactCount].phone[i] != '\0'; i++)
        {
            if (addressBook->contact[addressBook->contactCount].phone[i] < '0' || addressBook->contact[addressBook->contactCount].phone[i] > '9')
            {
                flag1 = 0; // here also reset flag1
                break;
            }
        }

        int same = 0;
        if (flag1 == 1)
        {
            for (int i = 0; i < (addressBook->contactCount); i++)
            {
                if (compare_str(addressBook->contact[addressBook->contactCount].phone, addressBook->contact[i].phone) == 0)
                {
                    same = 1; // same! --- iisue
                    break;
                }
            }

            if (same == 1)
            {
                printf("Phone numbers cannot be same.\n");
                continue;
            }
            else
            {
                printf("----- Phone number entered successfully! -----\n");
                break;
            }
        }
        else if (flag1 == 0)
        {
            printf("Inavlid phone number! Enter a 10-digit phone number. Try again.\n");
            continue;
        }
    }
}
void checkMail(AddressBook *addressBook)
{
    while (1)
    {
        int index = -1;

        printf("Enter the mail address: ");
        scanf(" %29[^\n]", addressBook->contact[addressBook->contactCount].mail);

        for (int i = 0; addressBook->contact[addressBook->contactCount].mail[i] != '\0'; i++) // Find '@'
        {
            if (addressBook->contact[addressBook->contactCount].mail[i] == '@')
            {
                index = i; // got @
                break;
            }
        }
        if (index == -1) // No '@'--> index not changed
        {
            printf("Invalid name mail address! Try again.\n");
            continue;
        }

        char *x = strstr(addressBook->contact[addressBook->contactCount].mail + index + 1, ".com"); // Find ".com" after '@'

        if (x != NULL) // ".com" found after @
        {
            if (addressBook->contact[addressBook->contactCount].mail[index + 1] == '.')
            {
                printf("invalid mail address!\n");
                continue;
            }

            int s = index + 1, sflag = 0;
            while (addressBook->contact[addressBook->contactCount].mail[s] != '.')
            {
                if (addressBook->contact[addressBook->contactCount].mail[s] >= '0' && addressBook->contact[addressBook->contactCount].mail[s] <= '9')
                {
                    sflag = 1; // when number found
                    break;
                }
                s++;
            }
            if (sflag == 0)
            {
                printf("Mail entered successfully\n");
                break;
            }

            else if (sflag == 1)
            {
                printf("Invalid name mail address! Try again.\n");
                continue;
            }
        }
        else if (x == NULL)
        {
            printf("Invalid name mail address! Try again.\n");
            continue;
        }
    }
}
// ----------------------------------------------------------------------------------
int searchContact(AddressBook *addressBook, char *prompt)
{
    while (1)
    {
        char search[50];
        printf("%s", prompt);
        scanf(" %49[^\n]", search);
        int foundCount = 0;
        int foundIndex = -1;

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (compare_str(addressBook->contact[i].name, search) == 0 || compare_str(addressBook->contact[i].phone, search) == 0 || compare_str(addressBook->contact[i].mail, search) == 0)
            {
                foundCount++;
                foundIndex = i;
            }
        }
        if (foundCount == 0)
        {
            printf("Contact not found!\n");
            return -1; // return completely
        }

        else if (foundCount > 1)
        {
            printf("Contact found multiple times! Please re-define which contact you want to search.\n");
            continue; // it will skip next lines of code and ask again.
        }

        else
        {
            printf("------- Contact found! ------\n ");
            printf("Index: %d\n", addressBook->contact[foundIndex].index);
            printf("Name: %s\n", addressBook->contact[foundIndex].name);
            printf("Phone Number: %s\n", addressBook->contact[foundIndex].phone);
            printf("Mail: %s\n", addressBook->contact[foundIndex].mail);
            return foundIndex; // IMP //return completely
        }
    }
}

//////////////////////////  I   M   P
int compare_str(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        char ca = tolower(*str1);
        char cb = tolower(*str2);
        if (ca != cb)
            return ca - cb;
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}
///////////////////////
void deleteContact(AddressBook *addressbook)
{
    while (1)
    {
        int choose, ret;
        printf("1. Delete by name.\n");
        printf("2. Delete by phone.\n");
        printf("3. Delete by mail.\n");
        printf("Enter the choice by which you want to search: ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ret = delete_by_name(addressbook);
            break;
        case 2:
            ret = delete_by_phone(addressbook);
            break;
        case 3:
            ret = delete_by_mail(addressbook);
            break;
        default:
            printf("Wrong choice entered!\n");
            continue; // continue as wrong choice entered
        }

        if (ret == 1 || ret == 0)
            break; // break from while loop if contact deleted suceesfully.
        else if (ret == -1)
            continue; // keep searching if found > once
    }
}
int delete_by_name(AddressBook *addressbook)
{
    char search[50];
    printf("Enter name to delete: ");
    scanf(" %49[^\n]", search);
    int foundCount = 0;  // contains the number of times the conatact is found based on search choice
    int foundIndex = -1; // stores the index where that contact is found
    for (int i = 0; i < addressbook->contactCount; i++)
    {
        if (compare_str(addressbook->contact[i].name, search) == 0)
        {
            foundCount++; // increase the foundCount
            foundIndex = i;
        }
    }
    if (foundCount == 1) // contact found once
    {
        printf("Contact found!\n");
        for (int j = foundIndex; j < addressbook->contactCount; j++)
        {
            addressbook->contact[j].index = addressbook->contact[j + 1].index;
            strcpy(addressbook->contact[j].name, addressbook->contact[j + 1].name);
            strcpy(addressbook->contact[j].phone, addressbook->contact[j + 1].phone);
            strcpy(addressbook->contact[j].mail, addressbook->contact[j + 1].mail);
        }
        printf("----- Contact deleted! -----\n");
        addressbook->contactCount--;
        return 1; // 1 for success
    }
    else if (foundCount > 1)
    {
        printf("Conatct found more than once. Kindly re-define your choice.\n");
        return -1;
    }

    else if (foundCount == 0)
    {
        printf("Conatct not found!\n");
        return 0; // 0 for not found
    }
} //---------------------------------

int delete_by_phone(AddressBook *addressbook) // phone number is unique. So,
{
    int founfflag = 0, foundindex = -1;
    char search[50];
    printf("Enter phone number to delete: ");
    scanf(" %49[^\n]", search);
    for (int i = 0; i < addressbook->contactCount; i++)
    {
        if (compare_str(addressbook->contact[i].phone, search) == 0)
        {
            founfflag = 1;
            foundindex = i;
            break;
        }
    }
    if (founfflag == 1)
    {
        printf("Contact found!\n");
        for (int j = foundindex; j < addressbook->contactCount; j++)
        {
            addressbook->contact[j].index = addressbook->contact[j + 1].index;
            strcpy(addressbook->contact[j].name, addressbook->contact[j + 1].name);
            strcpy(addressbook->contact[j].phone, addressbook->contact[j + 1].phone);
            strcpy(addressbook->contact[j].mail, addressbook->contact[j + 1].mail);
        }
        addressbook->contactCount--;
        printf("----- Contact deleted! -----\n");
        return 1;
    }
    else
    {
        printf("Contact not found.\n");
        return 0;
    }
}
int delete_by_mail(AddressBook *addressbook) // phone number is unique. So,
{
    int founfflag = 0, foundindex = -1;
    char search[50];
    printf("Enter mail address to delete: ");
    scanf(" %49[^\n]", search);
    for (int i = 0; i < addressbook->contactCount; i++)
    {
        if (compare_str(addressbook->contact[i].mail, search) == 0)
        {
            founfflag = 1;
            foundindex = i;
            break;
        }
    }
    if (founfflag == 1)
    {
        printf("Contact found!\n");
        for (int j = foundindex; j < addressbook->contactCount; j++)
        {
            addressbook->contact[j].index = addressbook->contact[j + 1].index;
            strcpy(addressbook->contact[j].name, addressbook->contact[j + 1].name);
            strcpy(addressbook->contact[j].phone, addressbook->contact[j + 1].phone);
            strcpy(addressbook->contact[j].mail, addressbook->contact[j + 1].mail);
        }
        addressbook->contactCount--;
        printf("----- Contact deleted! -----\n");
        return 1;
    }
    else
    {
        printf("Contact not found. Re-define your choice\n");
        return 0;
    }
}
////-----------------------
void editContact(AddressBook *addressBook)
{
    int choice, x;

    x = searchContact(addressBook, "Enter name/phone/mail to search for the contact you want to edit: "); // call search function
    if (x == -1)
        return;
    printf("1. Edit Name.\n2. Edit Phone Number.\n3. Edit Mail.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        editName(addressBook, x); // call
        break;
    case 2:
        editPhone(addressBook, x);
        break;
    case 3:
        editMail(addressBook, x);
        break;
    default:
        printf("You entered wrong choice.\n");
    }
}
void editName(AddressBook *addressBook, int x)
{
    char newName[50];
    while (1)
    {
        int flag = 1;
        printf("Enter the new name: ");
        scanf(" %49[^\n]", newName);
        for (int i = 0; newName[i] != '\0'; i++) // traverse through the name
        {
            if (newName[i] >= '0' && newName[i] <= '9')
            {
                flag = 0; // make flag 0
                break;
            }
        }
        if (flag == 1) // if flag is unchanged,
        {
            strcpy(addressBook->contact[x].name, newName);
            printf("----- Contact edited. -----\n");
            printf("Index: %d\n Name: %s\n Phone Number: %s\n Mail: %s\n", addressBook->contact[x].index, addressBook->contact[x].name, addressBook->contact[x].phone, addressBook->contact[x].mail);
            return;
        }
        else
            printf("Invalid name entered! Contact cannot be edited.\n");
    }
}

void editPhone(AddressBook *addressBook, int x)
{
    char newPhone[50];
    while (1)
    {
        int flag = 1;
        printf("Enter the new phone number: ");
        scanf(" %49[^\n]", newPhone);
        if (strlen(newPhone) > 10 || (strlen(newPhone) < 10))
        {
            flag = 0;
        }

        for (int i = 0; newPhone[i] != '\0'; i++)
        {
            if (newPhone[i] < '0' || newPhone[i] > '9')
            {
                flag = 0; // here also reset flag1
                break;
            }
        }

        int same = 0;
        if (flag == 1)
        {
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i == x)
                    continue; // skip current contact
                if (compare_str(newPhone, addressBook->contact[i].phone) == 0)
                {
                    same = 1;
                    break;
                }
            }

            if (same == 1)
            {
                printf("Phone numbers cannot be same.\n");
                continue;
            }
            else
            {
                strcpy(addressBook->contact[x].phone, newPhone);
                printf("----- Phone number edited successfully! -----\n");
                printf("Index: %d\n Name: %s\n Phone Number: %s\n Mail: %s\n", addressBook->contact[x].index, addressBook->contact[x].name, addressBook->contact[x].phone, addressBook->contact[x].mail);
                break;
            }
        }
        else if (flag == 0)
        {
            printf("Inavlid phone number! Enter a 10-digit phone number. Try again.\n");
            continue;
        }
    }
}

void editMail(AddressBook *addressBook, int x)
{
    char newMail[50];
    while (1)
    {
        int flag = 1, index = -1;
        printf("Enter the new mail: ");
        scanf(" %49[^\n]", newMail);
        for (int i = 0; newMail[i] != '\0'; i++) // Find '@'
        {
            if (newMail[i] == '@')
            {
                index = i;
                break;
            }
        }
        if (index == -1) // No '@'
        {
            printf("Invalid name mail address! Contact cannot be edited.\n");
            continue;
        }
        char *y = strstr(newMail + index + 1, ".com"); // Find ".com" after '@'

        if (newMail[index + 1] == '.')
        {
            printf("Invalid email address.\n");
            continue;
        }

        int s = index + 1, sflag = 0;
        if (y != NULL) // ".com" found
        {
            while (newMail[s] != '.')
            {
                if (newMail[s] >= '0' && newMail[s] <= '9')
                {
                    sflag = 1;
                    break;
                }
                s++;
            }

            if (sflag == 0)
            {
                strcpy(addressBook->contact[x].mail, newMail);
                printf("Index: %d\n Name: %s\n Phone Number: %s\n Mail: %s\n", addressBook->contact[x].index, addressBook->contact[x].name, addressBook->contact[x].phone, addressBook->contact[x].mail);
                printf("----- Contact edited. -----\n");
                break;
            }

            else if (sflag == 1)
            {
                printf("Invalid name mail address! Try again.\n");
                continue;
            }
        }
        else
        {
            printf("Invalid name mail address! Contact cannot be edited.\n");
            continue;
        }
    }
}
// SAVE AND EXIT

void saveAndExit(AddressBook *addressbook)
{
    saveContactsToFile(addressbook); // call save function

    exit(EXIT_SUCCESS);
}