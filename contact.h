// this is a user-made header file name "contact.h"----------

#ifndef MY_CONTACT_H // just a label

#define MY_CONTACT_H

typedef struct
{
    int index;
    char name[50];
    char phone[20];
    char mail[30];
} Contact; // struct Contact ---> Contact , using typedef

typedef struct
{
    Contact contact[100]; // array of structures, named 'contact' of type 'Contact'
    int contactCount;     // 'contactCount' used to keep the count of number of entries
} AddressBook;

// declare functions
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook, char *);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
#endif