#include "contact.h"
#include <string.h>
#include <stdio.h>
#include "populate.h"
#include "file.h"

void sort_name(AddressBook *addressBook)
{
    Contact temp;
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcmp(addressBook->contacts[j].name , addressBook->contacts[j + 1].name) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

void sort_phone(AddressBook *addressBook)
{
    Contact temp;
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcmp(addressBook->contacts[j].phone , addressBook->contacts[j + 1].phone) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

void sort_email(AddressBook *addressBook)
{
    Contact temp;
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcmp(addressBook->contacts[j].email , addressBook->contacts[j + 1].email) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // populateAddressBook(addressBook);
    load_data_from_file(addressBook);
}



void listContacts(AddressBook *addressBook)
{
    int option;
    printf("List based on :\n1.Name\n2.Phone Number\n3.Email.id\n");
    printf("Enter your option : ");
    scanf("%d", &option);

    switch(option)
    {
        case 1:
        sort_name(addressBook);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            printf("%20s,%15s,%35s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        break;
        case 2:
        sort_phone(addressBook);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            printf("%20s,%15s,%35s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        break;
        case 3:
        sort_email(addressBook);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            printf("%20s,%15s,%35s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        break;
        default:
        printf("Invalid option\n");
        break;
    }
    
}




void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount <= 100)
    {
        Contact new;
        int flag_name = 1;
        int flag_phone = 1;
        int flag_email = 1;

        printf("Enter the name : ");
        scanf(" %[^\n]",new.name); // check number should not come;

        for(int i = 0; i < strlen(new.name); i++)
        {
            if(!((new.name[i] >= 'A' && new.name[i] <= 'Z') || (new.name[i] >= 'a' && new.name[i] <= 'z') || (new.name[i] == ' ')))
            {
                flag_name = 0;
                break;
            }
            
        }
        if(flag_name == 0)
        {
            printf("Invalid name!\n");
            return;
        }

        printf("Enter the phone number : ");
        scanf(" %[^\n]",new.phone);// check alphabet not come and only 10 digits should be there;

        if(strlen(new.phone) != 10)
        {
            flag_phone = 0;
        }

        for(int i = 0; i < strlen(new.phone); i++)
        {
            if(!(new.phone[i]>= '0' && new.phone[i] <= '9'))
            {
                flag_phone = 0;
                return;
            }
            
        }

        if(flag_phone == 0)
        {
            printf("Invalid Phone Number\n");
            return;
        }

        printf("Enter the email .ID : ");
        scanf(" %[^\n]",new.email);// @ and . should be present;

        int count = 0;
        int position = 0;
        int dot = 0;

        for(int i = 0; i < strlen(new.email); i++)
        {
            if(new.email[i] == ' ')
            {
                flag_email = 0;
            }
        }

        for(int i = 0; i < strlen(new.email); i++)
        {
            if(new.email[i] == '@')
            {
                count++;
                position += i;
            }
        }
        for(int i = 0; i < strlen(new.email); i++)
        {
            if(new.email[i] == '.')
            {
                dot++;
            }
        }

        if((count != 1) || (position == 0 || position >= strlen(new.email)) || (!dot))
        {
            flag_email = 0;
        }

        if (!(strstr(new.email, ".com") || strstr(new.email, ".in")  || strstr(new.email, ".yahoo")))
        {
            flag_email = 0;
        }
        
        if(flag_email == 0)
        {
            printf("Invalid Email Entry\n");
            return;
        }

        addressBook->contacts[addressBook->contactCount] =  new;
        addressBook->contactCount++;
          
        printf("Contact Added\n");
        printf("Number of contacts is %d\n", addressBook->contactCount);

    }
    else
    {
        printf("List is full\n");
    }
}




void searchContact(AddressBook *addressBook)
{
    char buffer[50];
    int option;

    printf("How do you want to seach\n");
    printf("1. Search by name\n2. Search by phone number\n3. Search by eamil\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("Enter the name you want to search : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, buffer))
            {
                printf("Contact found\n");
                printf("%20s%15s%35s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                return;
            }
        } 
        printf("Contact doesn't found!");
        break;

        case 2:
        printf("Enter the phone number you want to search : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].phone, buffer))
            {
                printf("Contact found\n");
                printf("%20s%15s%35s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                return;
            }

        } 
        printf("Contact doesn't found!");
        break;

        case 3:
        printf("Enter the email you want to search : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email, buffer))
            {
                printf("Contact found\n");
                printf("%20s%15s%35s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                return;
            }
        } 
        printf("Contact doesn't found!");
        break;
    
    default:
        printf("Invalid choice");
        break;
    }
}


void editContact(AddressBook *addressBook)
{

    char buffer[50];
    int option;

    printf("How do you want to seach\n");
    printf("1. Search by name\n2. Search by phone number\n3. Search by eamil\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("Enter the name you want to edit : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, buffer))
            {
                printf("Contact found\n");
                printf("Editing contact : %s\n", buffer);
                printf("%s%15s%15s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("Enter the new name : ");
                scanf(" %[^\n]",addressBook->contacts[i].name);
                printf("Enter the new phone number : ");
                scanf(" %[^\n]",addressBook->contacts[i].phone);
                printf("Enter the new email : ");
                scanf(" %[^\n]",addressBook->contacts[i].email);
                printf("Contact is successfully edited\n");
                return;
            }
        } 
        printf("Contact doesn't found!");
        break;

        case 2:
        printf("Enter the phone number you want to edit : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].phone, buffer))
            {
                printf("Contact found\n");
                printf("Editing contact : %s\n", buffer);
                printf("%s%15s%15s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("Enter the new name : ");
                scanf(" %[^\n]",addressBook->contacts[i].name);
                printf("Enter the new phone number : ");
                scanf(" %[^\n]",addressBook->contacts[i].phone);
                printf("Enter the new email : ");
                scanf(" %[^\n]",addressBook->contacts[i].email);
                printf("Contact is successfully edited\n");
                return;
            }
        }
        printf("Contact doesn't found!"); 
        break;

        case 3:
        printf("Enter the email you want to edit : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email, buffer))
            {
                printf("Contact found\n");
                printf("Editing contact : %s\n", buffer);
                printf("%s%15s%15s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("Enter the new name : ");
                scanf(" %[^\n]",addressBook->contacts[i].name);
                printf("Enter the new phone number : ");
                scanf(" %[^\n]",addressBook->contacts[i].phone);
                printf("Enter the new email : ");
                scanf(" %[^\n]",addressBook->contacts[i].email);
                printf("Contact is successfully edited\n");
                return;
            }
        } 
        printf("Contact doesn't found!");
        break;
    
    default:
        printf("Invalid choice");
        break;
    }
}

void deleteContact(AddressBook *addressBook)
{
    char buffer[50];
    int option;

    printf("How do you want to seach the contact you want to delete\n");
    printf("1. Search by name\n2. Search by phone number\n3. Search by eamil\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("Enter the name you want to delete : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, buffer))
            {
                printf("Contact found\n");
                for(int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("Contact deleted\n");
                return;
            }
        }
        printf("Contact doesn't found\n");
        break;

    case 2:
        printf("Enter the phone number you want to delete : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].phone, buffer))
            {
                printf("Contact found\n");
                for(int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("Contact deleted\n");
                return;
            }
        } 
        printf("Contact doesn't found\n");
        break;  
    
    case 3:
        printf("Enter the email.id you want to delete : ");
        scanf(" %[^\n]", buffer);
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email, buffer))
            {
                printf("Contact found\n");
                for(int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("Contact deleted\n");
                return;
            }
        }
        printf("Contact doesn't found\n");
        break;
    
    default:
    printf("Invalid option\n");
    break;
    }

}