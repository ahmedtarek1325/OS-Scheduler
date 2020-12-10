#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define FULL 10

// this ode was intially retrieved from: https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
// nd we have made major changes on it 

struct processData
{
    int arrivaltime;
    int priority;
    int runningtime;
    int id;
};

struct PCB
{
   struct processData pData;
   int state;
   int remaining_time;
   int pid;
};


struct node
{
   // struct processData P_Data;
    struct PCB pcb;
    struct node *next;
};
typedef struct node node;

struct queue
{
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;

void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}
void PDcpy(struct processData* dest, struct processData* src)
{
    dest->arrivaltime=src->arrivaltime;
    dest->priority=src->priority;
    dest->runningtime=src->runningtime;
    dest->id=src->id;
}
void PCBCOMP(struct PCB* first ,struct PCB* second ) 
{
     PDcpy(&first->pData,&second->pData);
     first->state=second->state;
     first->pid=second->pid;
     first->remaining_time=second->remaining_time;
}
//NOT COMPLETE
void enqueue(queue *q, struct PCB* PCB1)
{
    if (q->count < FULL)
    {
        node *tmp;
        tmp = malloc(sizeof(node));
        PCBCOMP(&tmp->pcb,PCB1);
        tmp->next = NULL;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
    }
    else
    {
        printf("List is full\n");
    }
}

void dequeue(queue *q,struct PCB* PCB1)
{
    node *tmp;
    PCBCOMP (PCB1,&q->front->pcb);    
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
}


void display(node *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", head->pcb.pData.priority);
        printf("%d\n", head->pcb.state);

        display(head->next);
    }
}

int peakAR(node *head)
{

    if(head == NULL)
    {
        return(0);
    }
    else
    {
        return(head->pcb.state);
    }
}

/*
int main()
{
    queue *test;
    test = malloc(sizeof(queue));
    
    initialize(test);
    struct PCB OMAR;
    struct processData A;
    A.arrivaltime=1;
    A.id=1111;
    A.priority=1;
    A.runningtime=1;
    PDcpy(&OMAR.pData,&A);
    OMAR.state=12333;
    OMAR.pid=1;
    OMAR.remaining_time=1;

    struct PCB OMAR2;
    struct processData B;
    B.arrivaltime=2;
    B.id=2222;
    B.priority=3;
    B.runningtime=2;
    PDcpy(&OMAR2.pData,&B);
    OMAR2.state=12332; 
    OMAR2.pid=2;
    OMAR2.remaining_time=2;

    struct PCB OMAR3;
    struct processData C;
    C.arrivaltime=3;
    C.id=3333;
    C.priority=2;
    C.runningtime=3;
    PDcpy(&OMAR3.pData,&C);
    OMAR3.state=12334;
    OMAR3.pid=3;
    OMAR3.remaining_time=3;

    struct PCB dumb;
    printf("Is queue empyty? %d\n",isempty(test));
    enqueue(test,&OMAR);
    enqueue(test,&OMAR2);
    enqueue(test,&OMAR3);
    printf("Queue before dequeue\n");
    display(test->front);
    dequeue(test,&dumb);
    printf("Queue after dequeue\n");
    display(test->front);
    printf("Is queue empyty? %d\n",isempty(test));
    printf("peaking\n");
    //peakAR(test->front);
    printf("Queue after peaking\n");
    display(test->front);
    return 0;
}
*/