#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"


/*
Name:Guru
Project Name:Addressbook
Date:19/08/2025
*/

                             //...........List contacts......................

void listContacts(AddressBook *addressBook) 
{
    int i,j;
    Contact temp;
    
    for(i=0;i<addressBook->contactCount-1;i++)
    {
        for(j=0;j<addressBook->contactCount-i-1;j++)
        {
            int cmp=0;
            {
                cmp=strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
            }


            if(cmp>0)

            {
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
            
        }
    }
printf("-------------------------------------------------------------------");
printf("\n%-5s %-20s %-15s %-30s\n","No.", "Name", "Phone", "Email");
printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-5d %-20s %-15s %-30s\n",i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
printf("-------------------------------------------------------------------\n");
printf("Total contacts :%d\n",addressBook->contactCount);
}

     //...........Saving and exiting .................

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
   char  name[200];
	
    int flag=0;
    do
    {
        int i=0;
        while(getchar()!='\n')  //if any privious characters are stored then first clear that buffer 
        {
            continue;
        }
        printf("Enter name : ");
        scanf(" %[^\n]",name);
        flag=0;

        if(name[0]=='\0')
        {
            printf("Error reading name\n");
           flag=1;
           continue;
        }
        while(name[i]!='\0')
        {
            if(name[i]>='A' && name[i]<='Z' || name[i]>='a' && name[i]<='z' || name[i]==' ' || name[i]=='.')
            {
                i++;
            }
            else
            {
                flag=1;
                break;
            }    
        }
        if(flag==1)
            {
                printf("Invalid name , please enter valid name.\n");
            }
    }
    while(flag==1);

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);   // copying the correctly entered name to addressbook
    printf("name ok\n");


    //...............VALIDATION FOR PHONE NUMBER............
    char number[50];
     flag=0;
    do
    {
        int i=0;
        printf("Enter number : ");
        scanf(" %[^\n]",number);
        flag=0;

        if(number[i]=='\0')
        {
            printf("Error reading number.\n");
           flag=1;
           continue;
        }
        if(strlen(number)!=10)
        {
            printf("Phone number should be 10 digits\n");
            flag=1;
        }
        else
        {
            while(number[i]!='\0')
            {
                if(number[i]>='0' && number[i]<='9')
                {
                    i++;
                }
                else
                {
                    flag=1;
                    break;
                }    
            }

            int found=0;

            for(int k=0;k<addressBook->contactCount;k++)   //check for the number is already exist in the addressbook
            {
                if (strcmp(addressBook->contacts[k].phone, number)==0)
                {
                    // printf("Phone number already exist\n");
                    found=1;
                    break;
                }
            }
            if(found)
            {
                printf("Phone number already exist\n");
                flag=1;
                continue;
            }

            if(flag==1)
                {
                    printf("Invalid number , please enter valid number.\n");
                    continue;
                } 
        }
    }
    while(flag==1);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,number);
    printf("number ok\n");

    //.............................VALIDATION FOR EMAIL...........................
    char mail[100];
    do
    {
        flag=0;
        int k=0;
        printf("Enter the mail:");
        scanf(" %[^\n]",mail);
    
            if(mail[k]=='\0')
            {
                flag=1;
                continue;
            }
            while(mail[k]!='\0')
            {
                    if((mail[k]>='a' && mail[k]<='z') || (mail[k]>='0' && mail[k]<='9') ||(mail[k]=='.') || (mail[k]=='_') || (mail[k]=='-') || (mail[k]== '@' ))
                    {
                        k++;
                    }
                    else
                    {
                        flag=1;
                        break;
                    }
            }

            if(flag==1)
            {
                printf("Invalid mail! please enter the valid mail\n");
                continue;
            }

            int count=0;

            for(int i=0;mail[i]!='\0';i++)
            {
                if(mail[i]=='@')      // if more than one @ its not valid
                {
                    count++;
                }
                
            }
            if(count>1)
            {
                printf("email should contain only one @\n");
                flag=1;
                continue;
            }

            for(int i=0;mail[i]!='\0';i++)
            {
                if(mail[i] ==  '.'  && mail[i+1]=='.')
                {
                    printf("two dots at beside is not allowed\n");
                    flag=1;
                    continue;
                }
            }
             
            char*atpos=strchr(mail,'@');
            char * dot_com_pos=strstr(mail,".com");
            
            if(atpos== NULL || *(atpos+1)=='\0')
            {
                printf("Email should contain @ and not end with @\n");
               flag=1;
               continue;  
            }
           
            int len=strlen(mail);
            if(dot_com_pos== NULL || dot_com_pos!=mail+len-4 )
            {
                printf("Email should contain .com\n");
               flag=1;
               continue;  
            }
            if(dot_com_pos<atpos)
            {
                printf(".com should be after @");   //dotcom should come first
                flag=1;
                continue;
            }
            if(dot_com_pos-atpos<=1)
            {
                printf("they should contain atleast one char before\n");
                flag=1;
                continue;
            }
            int found=0;

            for(int k=0;k<addressBook->contactCount;k++)   //check for the mail is already exist in the addressbook
            {
                if (strcmp(addressBook->contacts[k].email, mail)==0)
                {
                    found=1;
                    break;
                }
            }
            if(found)
            {
                printf("mail already exist\n");
                flag=1;
                continue;
            }

            if(flag==1)
                {
                    printf("Invalid mail , please enter valid mail.\n");
                    continue;
                } 
       
              
    }
        while(flag==1);
        strcpy(addressBook->contacts[addressBook->contactCount].email,mail);

        printf("entered email is correct\n");
    addressBook->contactCount++;

    printf("Contact added successfully!\n"); 
}
             //.................search contact....................

void searchContact(AddressBook *addressBook) 
{
   int searchChoice;
   char search[100];
   char  lowercasearray[100];   //for storing the  user searched lower case contacts like gmail,name
   
   while(1)
   {
    printf("search by:\n");
    printf("1.Name\n");
    printf("2.phone\n");
    printf("3.Email\n");
   
    printf("Enter your choice: ");
    if(scanf("%d",&searchChoice)!=1)
    {
        printf("Invalid input!please enter a number 1to3.\n");
        while (getchar() != '\n');  //if you enter wrong inputs like a,b then to clear the privious stored input
        continue;
    }
    if(searchChoice==4)
    {
        return;
    }
    if(searchChoice<1 || searchChoice>3)
    {
        printf("please enter the choice from 1 to 3 :\n");
        continue;
    }
break;
   } 

   printf("Enter what you want to search:\n");
   scanf(" %[^\n]",search);

   strcpy(lowercasearray,search);    //copying the user entered search to lowercasearray 
    
   for(int i=0;lowercasearray[i];i++)
   {
      lowercasearray[i]=tolower(lowercasearray[i]);
   }

    int found=0;  //for how many matches found
    int multiarray[150]; //i am storing indexes into this one, when multiple matches are found
   for(int j=0;j<addressBook->contactCount;j++)
   {
      char lowercasename[100];   //to copy the contacts from the addressbook to this array for converting to lowercase
      char lowercasemail[100];
      int res=0;
     
      switch(searchChoice)
      {
        case 1:    //searching by using name  and i am keeping or convering the user entered and stored mails to lowercase

        strcpy(lowercasename,addressBook->contacts[j].name);   //copy the address book content to lowercasename array
        
        for(int j=0;lowercasename[j];j++)
        {
            lowercasename[j]=tolower(lowercasename[j]);
        }
        res=(strstr(lowercasename,lowercasearray)!=NULL);  //res  will  be 1 or 0
        break;

        case 2:   //for phone
       res=(strcmp(lowercasearray,addressBook->contacts[j].phone)==0);
        break;


        case 3:  //for email
        strcpy(lowercasemail,addressBook->contacts[j].email);  
        for(int j=0;lowercasemail[j];j++)
        {
            lowercasemail[j]=tolower(lowercasemail[j]);  //lowercase convertion
        }
        res=(strstr(lowercasemail,lowercasearray)!=NULL);

        break;
       }

      if(res==1)
      {
        multiarray[found]=j;    //if multiple matches found then i am storing there index to one array
        found++;
      }

    }

    int original_index=0;
    
      if(found==0)
      {
        printf("No matches found\n");
      }
      else if (found==1)
      {
        original_index=multiarray[0];    //if only one contact is found then directly print
        printf("%-20s %-15s %-30s\n",addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
      }
      else if(found>1)
      {
        printf(".............................................................\n");
        printf(" %-5s %-20s %-15s %-30s\n","No.","Name","Phone No","email");
        printf(".............................................................\n");

        for(int i=0;i<found;i++)
        {
            original_index=multiarray[i];  //if multiple found then store that one in one variable 
            printf(" %-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
    
        }
        printf(".............................................................\n");

        int p;
        while(1)
        {
            printf("please search by serial no:");

            if(scanf(" %d",&p)!=1)
            {
                printf("please enter only  numbers\n");
                while(getchar()!='\n')  //if user enters other than numbers then clear the input bufer
                {
                    continue;
                }

                continue;

            }
           
            if( p < 1 || p > found )
            {
                printf("serial should not greater than found\n");
                continue;
            }
            break;
        }

        original_index=multiarray[p-1];
        printf(".....................................................\n");
        printf("%-20s %-15s %-30s\n","Name","Phone No","email");
        printf("....................................................\n");
        printf("%-20s %-15s %-30s\n",addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
        printf(".....................................................\n");


      }


    }
     
         //............Edit contact...................

void editContact(AddressBook *addressBook)
{
    int searchchoice;
    char edit[100];
  
    while(1)
    {
        printf("Edit by:\n");
        printf("1.Name\n");
        printf("2.phone\n");
        printf("3.Email\n");
        printf("Enter your choice: ");

        if(scanf("%d",&searchchoice)!=1)
        {
            printf("Invalid input!please enter a number(1-3).\n");
            while (getchar() != '\n');  //if you enter wrong inputs like a,b then to clear the privious stored input
            continue;
        }

        if(searchchoice<1 || searchchoice>3)
        {
            printf("please enter the choice from 1 to 3 :\n");
            continue;
        }

    break;

    } 

    printf("Enter what you want to edit:\n"); //like name ,email,number
    scanf(" %[^\n]",edit);

    int found=0;  //for how many matches found
    int multiarray[150]; //i am storing indexes into this array , when multiple matches are found
   for(int j=0;j<addressBook->contactCount;j++)
   {
      int res=0;
     
      switch(searchchoice)
        {
            case 1:    //editing by using name 
            
            res=(strstr(addressBook->contacts[j].name,edit)!=NULL);  //the   res will be 1 or 0
            break;

            case 2:   //for phone
            res=(strcmp(edit,addressBook->contacts[j].phone)==0);
            break;

            case 3:  //for email
            res=(strstr(addressBook->contacts[j].email,edit)!=NULL);

            break;

        }

        if(res==1)
        {
            multiarray[found]=j;    //if multiple matches found then i am storing there indexes to one array
            found++;
        }
    }

    int original_index=0;
    int k=0;
        if(found==0)
        {
            printf("No search  found\n");
            return ;
        }

        else if (found==1)
        {
            original_index=multiarray[0];
            printf("%-20s %-15s %-30s\n",addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
            k=original_index;
        }
        
        else if(found>1)
        {
            printf(".............................................................\n");
            printf(" %-5s %-20s %-15s %-30s\n","No.","Name","Phone No","email");
            printf(".............................................................\n");
            
            for(int i=0;i<found;i++)
            {
                original_index=multiarray[i];
                printf(" %-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
            }
            printf(".............................................................\n"); 
            
            int p;
            while(1)
            {
                printf("please edit by serial no:");

                if(scanf(" %d",&p)!=1)
                {
                    printf("please enter numbers\n");
                    while(getchar()!='\n')
                    {
                        continue;
                    }
                    continue;
                }

                if( p > found || p < 1 )
                {
                    printf("serial no always less than matches and only for multiple matches\n ");
                    continue;
                
                }
                break;
            }


            original_index=multiarray[p-1];

            printf(".....................................................\n");
            printf("%-20s %-15s %-30s\n","Name","Phone No","email");
            printf("....................................................\n");
            printf("%-20s %-15s %-30s\n",addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
            printf(".....................................................\n");
            
            k=original_index;  //i am storing to k because i can directly edit by this index 

        }

    int flag=0;
    int fieldchoice;

    while(1)
    {

        printf("editing contact by name or email or number\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.Email\n");

        printf("enter the field choice to edit:");
        if(scanf("%d",&fieldchoice)!=1)
        {

            printf("Invalid input!please enter a number(1-3).\n");
            while (getchar() != '\n')
            {
            continue;
            }
            continue;
        }
        if(fieldchoice<1 || fieldchoice>3)
        {
            printf("invalid choice\n");
           continue;
        }
       
        break;

    }
    
    switch(fieldchoice)
    {

    case 1:

    char  new_name[200];
    
    do
    {
        int i=0;
        printf("Enter name : ");
        scanf(" %[^\n]",new_name);
        flag=0;

        if(new_name[0]=='\0')
        {
            printf("Error reading name.\n");
           flag=1;
           continue;
        }

        while(new_name[i]!='\0')
        {
            if(new_name[i]>='A' && new_name[i]<='Z' || new_name[i]>='a' && new_name[i]<='z' || new_name[i]==' ' || new_name[i]=='.')
            {
                i++;
            }
            else
            {
                flag=1;
                break;
            }    
        }

        if(flag==1)
            {
                printf("Invalid name , please enter valid name.\n");
            }
    }
    while(flag==1);

    strcpy(addressBook->contacts[k].name,new_name);  //copying the new_name into directly addressbook by using index 

    printf("name editied successfully\n");
    break;

    case 2:

    //...............VALIDATION FOR PHONE NUMBER EDITING............
    char new_number[50];
     flag=0;
    do
    {
        int i=0;
        printf("Enter number : ");
        scanf(" %[^\n]",new_number);
        flag=0;

        if(new_number[i]=='\0')
        {
            printf("Error reading number.\n");
           flag=1;
           continue;
        }
        if(strlen(new_number)!=10)
        {
            printf("Phone number should be 10 digits!\n");
            flag=1;
        }
        else
        {
            while(new_number[i]!='\0')
            {
                if(new_number[i]>='0' && new_number[i]<='9')
                {
                    i++;
                }
                else
                {
                    flag=1;
                    break;
                }    
            }
            int found=0;

            for(int k=0;k<addressBook->contactCount;k++)   //check for the number is already exist in the addressbook
            {
                if (strcmp(addressBook->contacts[k].phone, new_number)==0)
                {
                    // printf("Phone number already exist\n");
                    found=1;
                    break;
                }
            }
            if(found)
            {
                printf("Phone number already exist\n");
                flag=1;
                continue;
            }

            if(flag==1)
                {
                    printf("Invalid number , please enter valid number.\n");
                }
        }
    } while(flag==1);
    strcpy(addressBook->contacts[k].phone,new_number);
    printf("number edited successfully\n");
    break;
   
    //.............................VALIDATION FOR EMAIL EDITING...........................
    case 3:

    char new_mail[100];
    do
    {
        flag=0;
        int k=0;
        printf("Enter the mail:");
        scanf(" %[^\n]",new_mail);
    
            if(new_mail[k]=='\0')
            {
                flag=1;
                continue;
            }
            while(new_mail[k]!='\0')
            {
                    if((new_mail[k]>='a' && new_mail[k]<='z') || (new_mail[k]>='0' && new_mail[k]<='9') ||(new_mail[k]=='.') || (new_mail[k]=='_') || (new_mail[k]=='-') || (new_mail[k]== '@' ))
                    {
                        k++;
                    }
                    else
                    {
                        flag=1;
                        break;
                    }
            }

            if(flag==1)
            {
                printf("Invalid mail! please enter the valid mail\n");
                continue;
            }
             
            char*atpos=strchr(new_mail,'@');
            char * dot_com_pos=strstr(new_mail,".com");
            
            if(atpos== NULL || *(atpos+1)=='\0')
            {
                printf("Email should contain @ and not end with @\n");
               flag=1;
               continue;  
            }
            int count=0;
            for(int i=0;new_mail[i]!='\0';i++)
            {
                if(new_mail[i]=='@')      // if more than one @ its not valid
                {
                    count++;
                }
                
            }
            if(count>1)
            {
                printf("email should contain only one @\n");
                flag=1;
                continue;
            }

            for(int i=0;new_mail[i]!='\0';i++)
            {
                if(new_mail[i] ==  '.'  && new_mail[i+1]=='.')
                {
                    printf("two dots at beside is not allowed\n");
                    flag=1;
                    continue;
                }
            }

            int len=strlen(new_mail);
            if(dot_com_pos== NULL || dot_com_pos!=new_mail+len-4 )
            {
                printf("Email should contain .com\n");
               flag=1;
               continue;  
            }
            if(dot_com_pos<atpos)
            {
                printf(".com should be after @\n");
                flag=1;
                continue;
            }
            if(dot_com_pos-atpos<=1)
            {
                printf("they should contain atleast one char before\n");
                flag=1;
                continue;
            }
            int found=0;

            for(int k=0;k<addressBook->contactCount;k++)   //check for the mail is already exist in the addressbook
            {
                if (strcmp(addressBook->contacts[k].email, new_mail)==0)
                {
                    found=1;
                    break;
                }
            }
            if(found)
            {
                printf("mail already exist\n");
                flag=1;
                continue;
            }
            
                
    } while(flag==1);
        strcpy(addressBook->contacts[k].email,new_mail);
        printf("email edited successfully\n");

    break;	

    }  
}
           //....................Delete contact..............

void deleteContact(AddressBook *addressBook)
{
    int searchchoice;
    char delete[100];
  
    while(1)
    {
        printf("Delete  by:\n");
        printf("1.Name\n");
        printf("2.phone\n");
        printf("3.Email\n");
        printf("Enter your choice: ");

        if(scanf("%d",&searchchoice)!=1)
        {
            printf("Invalid input!please enter a number(1-3).\n");
            while (getchar() != '\n');  //if you enter wrong inputs like a,b then to clear the privious stored input
            continue;
        }

        if(searchchoice<1 || searchchoice>3)
        {
            printf("please enter the choice from 1 to 3 :\n");
            continue;
        }

    break;

    } 

    printf("Enter what you want to delete:\n"); //like name ,email,number
    scanf(" %[^\n]",delete);

    int found=0;  //for how many matches found
    int multiarray[150]; //i am storing indexes into this array , when multiple matches are found
    for(int j=0;j<addressBook->contactCount;j++)
    {
        int res=0;
     
        switch(searchchoice)
        {
            case 1:    //editing by using name 
            
            res=(strstr(addressBook->contacts[j].name,delete)!=NULL);  //the   res will be 1 or 0
            break;

            case 2:   //for phone
            res=(strcmp(delete,addressBook->contacts[j].phone)==0);
            break;

            case 3:  //for email
            res=(strstr(addressBook->contacts[j].email,delete)!=NULL);

            break;

        }

        if(res==1)
        {
            multiarray[found]=j;    //if multiple matches found then i am storing there indexes to one array
            found++;
        }
    }

    int original_index=0;
    int k=0;
        if(found==0)
        {
            printf("No search  found\n");
            return ;
        }

        else if (found==1)
        {
            original_index=multiarray[0];   //if single found then in array index starts from zero
            printf("%-20s %-15s %-30s\n",addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
            k=original_index;
        }
        
        else if(found>1)
        {
            printf(".............................................................\n");
            printf(" %-5s %-20s %-15s %-30s\n","No.","Name","Phone No","email");
            printf(".............................................................\n");
            
            for(int i=0;i<found;i++)
            {
                original_index=multiarray[i];   //if multiple matches then i am storing in array and assigning to one variable
                printf(" %-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
            }
            printf(".............................................................\n"); 
            
            int p;
            while(1)       //if user enters wrong serial no then again and again asking until enters correctly
            {

                printf("please delete by serial no:");
                if(scanf(" %d",&p)!=1)    
                {
                    printf("enter only numbers\n");
                    while(getchar()!='\n')   //if char like a ,b,c lke that then scanf will stores that one so we need to clear if they enter wrong choices 
                    {
                        continue;
                    }
                    continue;

                }
                if( p > found || p < 1 )
                {
                    printf("serial no always less than matches and only for multiple matches\n ");
                    continue;
                }

                break;

            }


            original_index=multiarray[p-1];

            printf(".....................................................\n");
            printf("%-20s %-15s %-30s\n","Name","Phone No","email");
            printf("....................................................\n");
            printf("%-20s %-15s %-30s\n",addressBook->contacts[original_index].name,addressBook->contacts[original_index].phone,addressBook->contacts[original_index].email);
            printf(".....................................................\n");
            
            k=original_index;  //i am storing to k because i can directly delete by this index 

        }

        for (int i = k; i < addressBook->contactCount - 1; i++)   //from the holded  index position to the  total contacts
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];  //shifting one index position value
        }
        addressBook->contactCount--;   //decrease the size by 1
        
        printf("\nContact deleted successfully!\n");   
}
