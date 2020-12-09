#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define FULL 1000

// this ode was intially retrieved from: https://www.codesdope.com/blog/article/making-a-queue-using-linked-list-in-c/
// nd we have made major changes on it 

struct processData
{
    int arrivaltime;
    int priority;
    int runningtime;
    int id;
};

struct node
{
    struct processData P_Data;
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

void enqueue(queue *q, struct processData* P_D)
{
    if (q->count < FULL)
    {
        node *tmp;
        tmp = malloc(sizeof(node));
        PDcpy(&tmp->P_Data,P_D);
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

void dequeue(queue *q,struct processData* TEMP)
{
    node *tmp;
    PDcpy (TEMP,&q->front->P_Data);    
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
        printf("%d\n", head->P_Data.arrivaltime);

        display(head->next);
    }
}

int peakAR(node *head)
{

    if(head == NULL)
    {
        printf("NUll\n");
    }
    else
    {
        printf("%d\n",head->P_Data.arrivaltime);
    }
}


int main()
{
    queue *test;
    test = malloc(sizeof(queue));
    
    initialize(test);
    
    struct processData A;
    A.arrivaltime=1;
    A.id=1111;
    A.priority=1;
    A.runningtime=1;
    
    struct processData B;
    B.arrivaltime=2;
    B.id=2222;
    B.priority=2;
    B.runningtime=2;
    
    struct processData C;
    C.arrivaltime=3;
    C.id=3333;
    C.priority=3;
    C.runningtime=3;
    
    printf("Is queue empyty? %d\n",isempty(test));
    enqueue(test,&A);
    enqueue(test,&B);
    enqueue(test,&C);
    printf("Queue before dequeue\n");
    display(test->front);
    dequeue(test,&dumb);
    printf("Queue after dequeue\n");
    display(test->front);
    printf("Is queue empyty? %d\n",isempty(test));
    printf("peaking\n");
    peakAR(test->front);
    printf("Queue after peaking\n");
    display(test->front);
    return 0;
}
