#include "contact.h"

Contact contactList[] = {{0, "John Doe", "1234567890", "john@example.com"}, // dummy contact list of type 'Contact'
                         {1, "Alice Smith", "0987654321", "alice@example.com"},
                         {2, "Bob Johnson", "1112223333", "bob@company.com"},
                         {3, "Carol White", "4445556666", "carol@company.com"},
                         {4, "David Brown", "7778889999", "david@example.com"},
                         {5, "Eve Davis", "6665554444", "eve@example.com"},
                         {6, "Frank Miller", "3334445555", "frank@example.com"},
                         {7, "Grace Wilson", "2223334444", "grace@example.com"},
                         {8, "Hannah Clark", "5556667777", "hannah@example.com"},
                         {9, "Ian Lewis", "8889990000", "ian@example.com"}};

// add the dummy conacts to the address book, one-by-one
void populateAddressBook(AddressBook *addressBook) // function call
{
    int size = sizeof(contactList) / sizeof(contactList[0]);

    for (int i = 0; i < size; i++) // later --> i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS
    {
        addressBook->contact[addressBook->contactCount++] = contactList[i];
    }
}
// its like arr1[j] = arr[i] //i iterates from 0 to size
// AND j starts from 0, increments itself
