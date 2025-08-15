#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *contact_file = fopen("contacts.txt","w");
    // Print contact to text file contacts.txt
    fprintf(contact_file, "%d\n",addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fprintf(contact_file, "%s,%s,%s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(contact_file);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *contact_file = fopen("contacts.txt","r");
    // Read contact from text file "contacts.txt"
    fscanf(contact_file, "%d\n",&addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fscanf(contact_file, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(contact_file);
}
