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

void recvdata(struct message msg);
 int msgqid;

int main(int argc, char * argv[])
{
    initClk();
    
    //TODO implement the scheduler :)
    //upon termination release the clock resources
    //connecting to the message queue
    msgqid = msgget(100,0);
    if(msgqid==-1)
        perror("error in connecting to the queue");





    destroyClk(true);
}

void recvdata(struct message msg)
{

// message has to be struct 

// now I want to recive 
printf("waiting a messsage\n");
int recval=msgrcv(msgqid, &msg,sizeof(struct message)-sizeof(long), 0,IPC_NOWAIT);

if(recval==-1)
    perror("error in receiveing");

printf("message recieved is: \n");

}

