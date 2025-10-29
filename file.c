#include <stdio.h>
#include "file.h"
#include "contact.h"  
  
void saveContactsToFile(AddressBook *addressBook) 
{

    FILE *fp = fopen("addressbook.csv","w");
    if(fp==NULL)
    {
       printf("error opening file for writing\n");
        return; 
    }
    
    fprintf(fp,"%d\n",addressBook->contactCount);   //it will stores how many contacts are saved in the file

     //write contact to file
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}
  //.............LOAD CONTACTS FROM FILE..................
void loadContactsFromFile(AddressBook *addressBook)
{
    
    FILE *fp = fopen("addressbook.csv","r");
    if(fp==NULL)
    {
        addressBook->contactCount=0;
        return; 
    }
    

    fscanf(fp,"%d\n",&addressBook->contactCount);  //it will tells how many contacts are their in the file
    
    //read contact
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",
        addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    
}
