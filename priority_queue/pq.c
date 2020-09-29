#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pq.h"


void enqueue(pq ** front, pq ** rear,
  char * data, int priority) {

  pq * temp1, * temp2;
  temp1 = (pq * ) malloc(sizeof(pq));
  temp1 -> data = (char * ) malloc(sizeof(char) * STRLEN);
  strcpy(temp1 -> data, data);
  temp1 -> priority = priority;
  temp1 -> next = NULL;

  if ( * rear == NULL) {
    * rear = temp1;
    * front = * rear;

  } else if (( * front) -> priority < priority) {
    temp1 -> next = * front;
    * front = temp1;
  } else {

    if (( * rear) -> priority > priority) {

      ( * rear) -> next = temp1;
      * rear = temp1;

    } else {

      temp2 = * front;

      while ((temp2 -> next) -> priority >= priority) {
        temp2 = temp2 -> next;
      }

      temp1 -> next = temp2 -> next;
      temp2 -> next = temp1;
    }
  }
}

char * execute(pq ** front, pq ** rear) {
  pq * temp;
  char * s = (char * ) malloc(sizeof(char) * STRLEN);
  int p;
  // Empty queue
  if (( * front == * rear) && ( * rear == NULL)) {
    puts("\n\tThe queue is empty\n");
    //exit(0);
    strcpy(s, "");
  } else {

    strcpy(s, ( * front) -> data);

    p = ( * front) -> priority;

    temp = * front;
    * front = ( * front) -> next;

    if ( * rear == temp)
      *
      rear = ( * rear) -> next; // to make *rear NULL
    printf("\n(%s) with priority (%i) has been removed\n",
      s, p);
    free(temp);
  }
  return s;
}

void display(pq * front, pq * rear) {
  if ((front == rear) && (rear == NULL)) {
    puts("\n\tThe queue is Empty\n");
  } else {
    puts("(");
    do {
      printf("\t{%s, %i}\n", front -> data, front -> priority);
      front = front -> next;
    } while (front != rear -> next);
    puts(")");
  }
}