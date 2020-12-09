#include "headers.h"

//structing a message 
struct processData
{
    int arrivaltime;
    int priority;
    int runningtime;
    int id;
};
struct message
{
long mtype;
struct processData pData;
};

int msgqid;

void clearResources(int);
void initateClock();
void sendData(struct processData p);




int main(int argc, char * argv[])
{
    signal(SIGINT, clearResources);
    // TODO Initialization
    // 1. Read the input files.
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


void sendData(struct processData p)
{
    struct message msg;
    msg.mtype=5;
    /////////////////////////////make this 4 lines a function later  ///////////////////////
    msg.pData.arrivaltime=p.arrivaltime;
    msg.pData.priority=p.priority;
    msg.pData.runningtime=p.runningtime;
    msg.pData.id=p.id;
    ////////////////////////////////////////////////////////////////////////////////////////

    // now I want to send 
    int sndval= msgsnd(msgqid, &msg,sizeof(struct message)-sizeof(long), !IPC_NOWAIT);
    if(sndval==-1)
        perror("error in sending process");

}


