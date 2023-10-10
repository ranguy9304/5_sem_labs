
#include <stdio.h>
#include <stdlib.h>
// w  ww .ja  v  a2s  . c  o  m
#define MAX 10


void insert(int queue[], int *rear, int value)
{
   if(*rear < MAX-1)
   {
      *rear= *rear +1;
      queue[*rear] = value;
   }
   else
   {
      printf("The queue is full can not insert a value\n");
      exit(0);
   }
}

void delete(int queue[], int *front, int rear, int * value)
{
   if(*front == rear)
   {
      printf("The queue is empty can not delete a value\n");
      exit(0);
   }
   *front = *front + 1;
   *value = queue[*front];
}

void main()
{
   int queue[MAX];
   int front,rear;
   int n,value;
   front = rear = -1;

   insert(queue,&rear,1);
   insert(queue,&rear,2);

   delete(queue,&front,rear,&value);
   printf("The value deleted is %d\n",value);
   insert(queue,&rear,1);
   insert(queue,&rear,2);

   delete(queue,&front,rear,&value);
   printf("The value deleted is %d\n",value);
}