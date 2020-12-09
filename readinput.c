#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
   int num;
   FILE *fptr;
   char str[255];
   char* piece;

   fptr = fopen("/home/ahmed/Downloads/OS Labs/Project/code/processes.txt","r");

   if(fptr == NULL)
   {
      printf("Error in oppening the file!");   
      exit(1);             
   }

   while(fgets (str, 255, fptr) !=NULL)
   {
      
       if (str[0]=='#')
            {
                printf("skipped\n");
                continue;
            }
        piece=strtok(str,"\t");
        num=atoi(piece);
        printf("integer value= %d\n",num);
        // read the first value     
        piece=strtok(NULL,"\t");
        num=atoi(piece);
        printf("integer value= %d\n",num);
        piece=strtok(NULL,"\t");
        num=atoi(piece);
        printf("integer value= %d\n",num);
        
        piece=strtok(NULL,"\t");
        num=atoi(piece);
        printf("integer value= %d\n",num);



   }


   fclose(fptr);

   return 0;
}