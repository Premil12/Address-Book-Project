# include <stdio.h>
# include "file.h"
# include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt","w");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp,"%15s,%15s,%35s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}

void load_data_from_file(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");
    if(fp == NULL)
    {
        perror("file is not present\n");
        return;
    }
    for(int i = 0; ; i++)
    {
       int res = fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
       if(res == 3)
       {
        addressBook->contactCount++;
       }
       else
       {
        break;
       }
    }
    fclose(fp);

}