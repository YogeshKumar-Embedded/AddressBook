#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    printf("-----------------------------------------------------\n");
    printf("                    Contacts List                    \n");
    printf("-----------------------------------------------------\n");
    // Sort contacts based on the chosen criteria
    // list of All contact saved in file
    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
    for(int i=0; i<addressBook ->contactCount;i++)
    {
        printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("-----------------------------------------------------\n");
    printf("                    Create contact                   \n");
    printf("-----------------------------------------------------\n");    
    int flag1;
    int count = addressBook->contactCount;
    printf("Enter the name :- ");
    do 
    {
        flag1 = 0;
        scanf(" %49[^\n]",addressBook->contacts[count].name);
        // logic for Name not contain special cherecter or number
        for (int j = 0; addressBook->contacts[count].name[j] != '\0'; j++) 
        {
            char ch = addressBook->contacts[count].name[j];
            if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == ' '))) 
            {
                flag1=1;
                printf("Special Characters not allow\n");
                printf("Please Try Again\n");
                break;
            }
        }
    }
    while(flag1==1);
    printf("Enter phone No. :- ");
    do 
    {
        flag1 = 0;
        scanf(" %19[^\n]",addressBook->contacts[count].phone);
        int length = strlen(addressBook->contacts[count].phone);

        // logic for Phone Number not contain special cherecter uther then number and number must b 10

        for (int j = 0; addressBook->contacts[count].phone[j] != '\0'; j++) 
        {
            char ch = addressBook->contacts[count].phone[j];
            if (!(ch >= '0' && ch <= '9') || (length != 10)) 
            {
                flag1=1;
                printf("Enter a valid phone no. of 10 digit \n");
                printf("Please Try Again\n");
                break;
            }
        }
        // check if the Phon Number is already exist or not
        if(flag1==0)
        {
            for(int k=0; k < addressBook->contactCount; k++)
            {
                if(strcmp(addressBook->contacts[count].phone,addressBook->contacts[k].phone)==0)
                {
                    flag1=1;
                    printf("Phone No. already exists \n");
                    printf("Please Try Again\n");
                    break;
                }
            }
        }
    }while(flag1==1);
    printf("Enter Email ID :- ");
    do 
    {
        flag1 = 0;
        scanf(" %49[^\n]",addressBook->contacts[count].email);
        int hastag =0;
        int dot = 0;
        int validchar = 0;
        // email should be in lower case and must include "@" and "."
        for (int j = 0; addressBook->contacts[count].email[j] != '\0'; j++) 
        {
            char ch = addressBook->contacts[count].email[j];
            if (!((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == '@') || (ch == '.'))) 
            {
                validchar = 1;
                break;
            }
            if(ch == '@')
            hastag = 1;
            if(ch == '.')
            dot = 1;
        }
        // if email is not in given criteria then error messege will print
        if(validchar || !hastag || !dot)
        {
            flag1=1;
            printf("Enter a valid Email ID \n");
            printf("Please Try Again\n");
        }
        // if email is already exist then messege will print and re-enter new email 
        if(flag1==0)
        {
            for(int k=0; k < addressBook->contactCount; k++)
            {
                if(strcmp(addressBook->contacts[count].email,addressBook->contacts[k].email)==0)
                {
                    flag1=1;
                    printf("Email ID already exists \n");
                    printf("Please Try Again\n");
                    break;
                }
            }
        }
    }while(flag1==1);
    // if all input are valid then contect will display
    printf("\ncontact saved as : \n");
    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[count].name,addressBook ->contacts[count].phone,addressBook ->contacts[count].email);
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    printf("-----------------------------------------------------\n");
    printf("                    Search contact                   \n");
    printf("-----------------------------------------------------\n");
    /* Define the logic for search */
    int search_choice;
    int flag, header = 0;
    char NPI_choice[30];
    char add_contact;
    // sub memu for serch by name or phon number or email
    printf("Search By:\n");
    printf("1. Name\n");
    printf("2. Phon Number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");
    scanf("%d",&search_choice);
    printf("\n");
    switch(search_choice)
    {
        case 1 : // name
            printf("Enter the Name you want to search : ");
            scanf(" %29[^\n]",NPI_choice);
            flag=0;
            // if same name or part of name is entered then display full name
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if((strcmp(NPI_choice, addressBook->contacts[i].name)==0) || (strstr(addressBook->contacts[i].name, NPI_choice)!= NULL))
                {
                    if (header == 0)
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    flag++;header++;
                }
            }
            // if contect not found then if user want he or she can create that contect
            if(flag == 0)
            {
                printf("Contact Not Found\n");
                printf("Do you want to Add this contact (Y/N) : ");
                scanf(" %c",&add_contact);
                if(add_contact == 'Y')
                {
                    createContact(addressBook);
                }
            }

            break;
        case 2 : 
            printf("Enter the Phone number you want to search : ");
            scanf(" %29[^\n]",NPI_choice);
            // logic for phon number search
            flag=0;
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if(strcmp(NPI_choice, addressBook->contacts[i].phone)==0)
                {
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");                    
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    flag++;
                    break;
                }
            }
            // if phon number not found then new contect can be created
            if(flag == 0)
            {
                printf("Contact Not Found\n");
                printf("Do you want to Add this contact (Y/N) : ");
                scanf(" %c",&add_contact);
                if(add_contact == 'Y')
                {
                    createContact(addressBook);
                }
            }
            break;
        case 3 : 
            printf("Enter the Email ID you want to search : ");
            scanf(" %29[^\n]",NPI_choice);
            // logic for Email search  
            flag=0;
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if(strcmp(NPI_choice, addressBook->contacts[i].email)==0)
                {
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    flag++;
                    break;
                }
            }
            // if email not found now email can be created
            if(flag == 0)
            {
                printf("Contact Not Found\n");
                printf("Do you want to Add this contact (Y/N) : ");
                scanf(" %c",&add_contact);
                if(add_contact == 'Y')
                {
                    createContact(addressBook);
                }
            }
            break;
        default:
            printf("Invalid Input.\n");
    }
}

void editContact(AddressBook *addressBook)
{
    printf("-----------------------------------------------------\n");
    printf("                     Edit contact                    \n");
    printf("-----------------------------------------------------\n");
    /* Define the logic for Editcontact */
    int search_choice, j=0;
    int flag=0,flag1;
    char NPI_choice[30];
    char Edited_text[30];
    // Sub menu
    printf("Edit contact By:\n");
    printf("1. Name\n");
    printf("2. Phon Number\n");
    printf("3. Email ID\n\n");
    printf("Enter your choice: ");
    scanf("%d",&search_choice);
    printf("\n\n");
    switch(search_choice)
    {
        case 1 : 
            printf("Enter the name you want to edit : ");
            // while((getchar()) != '\n');
            scanf(" %29[^\n]",NPI_choice);
            int match_indexes[100];
            int match_count=0;
            // check if the multiple name of contact is in list or not
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if(strcmp(NPI_choice, addressBook->contacts[i].name)==0 || strstr(addressBook->contacts[i].name, NPI_choice)!=NULL)
                {
                    match_indexes[match_count++] = i;
                }
            }
            // if contect not found in list error message
            if (match_count == 0)
            {
                printf("contact not found\n");
                break;
            }
            // if only one contact is found
            int selectedindex;
            if(match_count == 1)
            {
                selectedindex = match_indexes[0];
                printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[selectedindex].name,addressBook ->contacts[selectedindex].phone,addressBook ->contacts[selectedindex].email);
            }
            else // if multiple contact is found
            {
                printf("Matchings contacts: \n");
                printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                for(int i =0; i<match_count; i++)
                {
                    // list of all found contact
                    int idx = match_indexes[i];
                    printf("%d.|  %s\t\t|\t%s\t|\t%s\n", i+1, addressBook ->contacts[idx].name,addressBook ->contacts[idx].phone,addressBook ->contacts[idx].email);
                }
                int selection;
                // in multiple contect select one contect you want to edit
                printf("\nEnter the number of contact you want to edit: ");
                scanf("%d", &selection);
                // if selection was wrong
                if (selection<1||selection>match_count)
                {
                    printf("Invalid Selection.\n");
                    break;
                }
                selectedindex = match_indexes[selection-1];
            }
            // logic for new name
            printf("\nEnter new name\n");
            do 
            {
                flag1 = 0;
                while((getchar())!='\n');
                scanf(" %29[^\n]",Edited_text);
                for (int j = 0; Edited_text[j] != '\0'; j++) 
                {
                    // check for valid name
                    char ch = Edited_text[j];
                    if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == ' '))) 
                    {
                        flag1=1;
                        printf("Special Characters not allow\n");
                        printf("Please Try Again\n");
                        break;
                    }
                }
            }while(flag1==1); 
            strcpy(addressBook->contacts[selectedindex].name, Edited_text);
            printf("-----------------------------------------------------\n");
            // after edit is sucessfull print message
            printf("Contact Update Sucessfully:\n");
            printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
            printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[selectedindex].name,addressBook ->contacts[selectedindex].phone,addressBook ->contacts[selectedindex].email);
            break;
        case 2 : 
            // logic for edit Phon number
            printf("Enter the Phone number you want to edit : ");
            scanf(" %29[^\n]",NPI_choice);
            for(int i=0; i< addressBook->contactCount; i++)
            {
                // check for the entered phon number is in the list or not
                if(strcmp(NPI_choice, addressBook->contacts[i].phone)==0)
                {
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    printf("\nEnter new Phon No. \n");
                    // if phon number found in the list then enter new number
                    do 
                    {
                        flag1 = 0;
                        while((getchar())!='\n');
                        scanf(" %29[^\n]",Edited_text);
                        int length = strlen(Edited_text);
                        // check for number is of 10 digit and it is valid phon number
                        for (int j = 0; Edited_text[j] != '\0'; j++) 
                        {
                            char ch = Edited_text[j];
                            if (!((ch >= '0' && ch <= '9') || (length !=10))) 
                            {
                                flag1=1;
                                printf("Enter a valid phone no. of 10 digit \n");
                                printf("Please Try Again\n");
                                break;
                            }
                        }
                        // if nummber is already exist then print message
                        if(flag1==0)
                        {
                            for(int k=0; k < addressBook->contactCount; k++)
                            {
                                if(strcmp(Edited_text,addressBook->contacts[k].phone)==0)
                                {
                                    flag1=1;
                                    printf("Phone No. already exists \n");
                                    printf("Please Try Again\n");
                                    break;
                                }
                            }
                        }
                    }while(flag1==1);
                    strcpy(addressBook->contacts[i].phone, Edited_text);
                    printf("-----------------------------------------------------\n");
                    printf("Contact Update Sucessfully:\n");
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    flag++;
                }
            }
            // if phon number not found print this message
            if(flag == 0)
            {
                printf("Contact Not Found\n");
            }
            break;
        case 3 : 
            printf("Enter the Email ID you want to edit : ");
            scanf(" %29[^\n]",NPI_choice);
            // Logic to edit Email
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if(strcmp(NPI_choice, addressBook->contacts[i].email)==0)
                {
                    // check for entered Email present or Not
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    printf("Enter new Email ID \n");
                    do 
                    {
                        // Logic for enter a valid Email.com
                        flag1 = 0;
                        while((getchar())!='\n');
                        scanf(" %29[^\n]",Edited_text);
                        int hastag =0;
                        int dot = 0;
                        int validchar = 0;
                        for (int j = 0; Edited_text[j] != '\0'; j++) 
                        {
                            // check that email must contain lower case alphabet "@" and "."
                            char ch = Edited_text[j];
                            if (!((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == '@') || (ch == '.'))) 
                            {
                                validchar = 1;
                                break;
                            }
                            if(ch == '@')
                            hastag = 1;
                            if(ch == '.')
                            dot = 1;
                        }
                        // if entered email is not a valid email print this messeage
                        if(validchar || !hastag || !dot)
                        {
                            flag1=1;
                            printf("Enter a valid Email ID \n");
                            printf("Please Try Again\n");
                        }
                        // if Entered email is already exist then print this message
                        if(flag1==0)
                        {
                            for(int k=0; k<addressBook->contactCount;k++)
                            {
                                if(strcmp(Edited_text,addressBook->contacts[k].email)==0)
                                {
                                    flag1=1;
                                    printf("Email already exists \n");
                                    printf("Please Try Again\n");
                                    break;
                                }
                            }
                        }
                    }while(flag1==1);
                    strcpy(addressBook->contacts[i].email, Edited_text);
                    printf("-----------------------------------------------------\n");
                    printf("Contact Update Sucessfully:\n");
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    flag++;
                }
            }
            // if email is not found in the list
            if(flag == 0)
            {
                printf("Contact Not Found\n");
            }
            break;
        default:
            printf("Invalid Input.\n");
    }
	

    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("-----------------------------------------------------\n");
    printf("                    Delete contact                   \n");
    printf("-----------------------------------------------------\n");
    /* Define the logic for search */
    int search_choice;
    int flag;
    char NPI_choice[30];
    char delete_choice;
    // sub manu for choice
    printf("Delete contact By:\n");
    printf("1. Name\n");
    printf("2. Phon Number\n");
    printf("3. Email ID\n\n");
    printf("Enter your choice: ");
    scanf("%d",&search_choice);
    printf("\n");
    switch(search_choice)
    {
        case 1 :
            printf("Enter the Name of contact you want to delete: ");
            // delete contect with respect to name
            scanf(" %29[^\n]",NPI_choice);
            int match_indexes[100];
            int match_count=0;
            // check for same name or similar name
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if(strcmp(NPI_choice, addressBook->contacts[i].name)==0 || strstr(addressBook->contacts[i].name, NPI_choice)!=NULL)
                {
                    match_indexes[match_count++] = i;
                }
            }
            // if no same contect found
            if (match_count == 0)
            {
                printf("contact not found\n");
                break;
            }
            int selectedindex;
            // if 1 contect found
            if (match_count ==1)
            {
                selectedindex = match_indexes[0];
                printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[selectedindex].name,addressBook ->contacts[selectedindex].phone,addressBook ->contacts[selectedindex].email);
            }
            else //if multiple contect found
            {
                printf("Matchings contacts: \n");
                printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                for(int i =0; i<match_count; i++)
                {
                    int idx = match_indexes[i];
                    printf("%d.|  %s\t\t|\t%s\t|\t%s\n", i+1, addressBook ->contacts[idx].name,addressBook ->contacts[idx].phone,addressBook ->contacts[idx].email);
                }
                int selection;
                // select 1 contect in multiple contact
                printf("\nEnter the number of contact you want to delete: ");
                scanf("%d", &selection);
                // if selected contact is not in list
                if (selection<1||selection>match_count)
                {
                    printf("Invalid Selection.\n");
                    break;
                }
                selectedindex = match_indexes[selection-1];
            }
            // velidation message
            printf("Are you sure you want to delete \"%s\" ? :- (Y/N)",addressBook->contacts[selectedindex].name);
            scanf(" %c",&delete_choice);
            // if Yes then Contect delete
            if(delete_choice=='Y')
            {
                for(int j=selectedindex; j<addressBook->contactCount-1;j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                }
                addressBook->contactCount-- ;
                printf("Contact Deleted Successfully \n");
            }
            // if other then Yes then contect not delete
            else
            {
                printf("contact Not Deleted\n");
            }
            break;
        case 2 : 
            printf("Enter the Phone number you want to delete : ");
            scanf(" %29[^\n]",NPI_choice);
            // delete contect via phon number
            flag=0;
            for(int i=0; i< addressBook->contactCount; i++)
            {
                // check for phon number is prasent in the list or not
                if(strcmp(NPI_choice, addressBook->contacts[i].phone)==0)
                {
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");                    
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    // phon number is present in the list now velidation for deleting the contect
                    printf("Are you sure you want to delete \"%s\" ? :- (Y/N)",addressBook->contacts[i].name);
                    scanf(" %c",&delete_choice);
                    if(delete_choice=='Y')
                    {
                        for(int j=i; j<addressBook->contactCount-1;j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j+1];
                        }
                        addressBook->contactCount-- ;
                        printf("Contact Deleted Successfully \n");
                    }
                    // if N is selected then contect not deleded
                    else if (delete_choice=='N')
                    {
                        printf("contact Not Deleted\n");
                    }
                    flag++;
                    break;
                }
            }
            // if phon number not found
            if(flag == 0)
            {
                printf("Contact Not Found\n");
            }
            break;
        case 3 : 
            printf("Enter the Email ID you want to Delete : ");
            scanf(" %29[^\n]",NPI_choice);
            // Deleting contect via email
            flag=0;
            for(int i=0; i< addressBook->contactCount; i++)
            {
                if(strcmp(NPI_choice, addressBook->contacts[i].email)==0)
                {
                    // check wether email is present in the list of not
                    printf("|  NAME\t\t\t|\tPHONE NO.\t|\tEMAIL-ID\n");
                    printf("|  %s\t\t|\t%s\t|\t%s\n", addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
                    printf("Are you sure you want to delete \"%s\" ? :- (Y/N)",addressBook->contacts[i].name);
                    scanf(" %c",&delete_choice);
                    // if email found then velidation for deleting contact
                    if(delete_choice=='Y')
                    {
                        for(int j=i; j<addressBook->contactCount-1;j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j+1];
                        }
                        addressBook->contactCount-- ;
                        printf("Contact Deleted Successfully \n");
                    }
                    // If N is pressed then contect not deleted
                    else if (delete_choice=='N')
                    {
                        printf("contact Not Deleted\n");
                    }
                    flag++;
                    break;
                }
            }
            // if entered email not found in the list
            if(flag == 0)
            {
                printf("Contact Not Found\n");
            }
            break;
        default:
            printf("Invalid Input.\n");
    }
}


