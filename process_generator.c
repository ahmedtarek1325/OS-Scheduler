#include "headers.h"
#include "queue.h"
#include <string.h>
//structing a message 
struct message
{
long mtype;
struct processData pData;
};

int msgqid;

void readinput(queue* temp);
void clearResources(int);
void initateClock();
void sendData(struct processData p);
void sendData(struct processData p);

/// copy process data function


int main(int argc, char * argv[])
{
    signal(SIGINT, clearResources);
    // TODO Initialization
    // 1. Read the input files.
    queue *temp;
    temp = malloc(sizeof(queue));
    initialize(temp);
    readinput(temp);
    // 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.
    // 3. Initiate and create the scheduler and  clock processes.
    // 4. Use this function after creating the clock process to initialize clock
    initateClock();
    initClk();
    
    // creating a message queue to send processes to scheduler when their time arrive 
    msgqid = msgget(100,IPC_CREAT | 0666);
    if(msgqid==-1)
        perror("error in creating the queue");


    int y=0;
    while(y<10) // I will change this codition to make it dependent on whether there are elements in the queue 
    { 
        int x = getClk();
        printf("current time is %d\n", x);
        y=x+1;
    // TODO Generation Main Loop
    // 5. Create a data structure for processes and provide it with its parameters.
    // 6. Send the information to the scheduler at the appropriate time.



    while(y>getClk())
    {}

    }


    // 7. Clear clock resources
    free(temp);
    destroyClk(true);
}

void clearResources(int signum)
{
    //TODO Clears all resources in case of interruption
    msgctl(msgqid,IPC_RMID,NULL);
    printf("\nResources were cleared");
}

void initateClock()
{
    int pid=fork();
    if (pid==-1)
        perror("error in fork \n");
    
    if (pid==0)
    {
        char name[]="./clk.out";
        char* argv[]={name,NULL};
        execvp(name, &argv[0]);
    }

}

void scheduler()
{
    int pid=fork();
    if (pid==-1)
        perror("error in fork \n");
    
    if (pid==0)
    {
        char name[]="./scheduler.out";
        char* argv[]={name,NULL};
        execvp(name, &argv[0]);
    }

}


void sendData(struct processData p)
{
    struct message msg;
    msg.mtype=5;
    PDcpy(&msg.pData,&p);


    // now I want to send 
    int sndval= msgsnd(msgqid, &msg,sizeof(struct message)-sizeof(long), !IPC_NOWAIT);
    if(sndval==-1)
        perror("error in sending process");

}



void readinput(queue* temp)
{
   int num;
   FILE *fptr;
   char str[255];
   char* piece;
   fptr = fopen("processes.txt","r");
   
   if(fptr == NULL)
   {
      printf("Error in oppening the file!");   
      exit(1);             
   }

   while(fgets (str, 255, fptr) !=NULL)
   {
      struct processData A;
       if (str[0]=='#')
            {
                printf("skipped\n");
                continue;
            }
        piece=strtok(str,"\t");
        num=atoi(piece);
        A.id=num;
        
        piece=strtok(NULL,"\t");
        num=atoi(piece);
        A.arrivaltime=num;
        
        piece=strtok(NULL,"\t");
        num=atoi(piece);
        A.runningtime=num;

        piece=strtok(NULL,"\t");
        num=atoi(piece);
        A.priority=num;

        enqueue(temp,&A);
   }

   fclose(fptr);
}

