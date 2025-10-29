#include <stdio.h>
#include "contact.h"
#include"file.h"

int main() {
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    loadContactsFromFile(&addressBook);  // to read the privious contacts 
    int flag=0;
    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and exit contacts\n");	
        	
        while(1)
        {
            printf("Enter your choice: ");	
           
            if(scanf(" %d", &choice)!=1)
            {
                printf("enter only numbers\n");
                while(getchar()!='\n')   //if you enter non digits then  first clear whatver it stored in buffer
                {
                continue;
                }
                continue;
            }
            else
            {
                break;
            }
        }

        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:   
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);  //saving the contacts into the file before exiting
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}
