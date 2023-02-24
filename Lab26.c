#define QMAX 100
#include "lab26.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void init(struct queue *q) {
    q->first = 1;
    q->last = 0;
    return;
}

void insert(struct queue *q, int x) {
    if (q->last < QMAX - 1) {
        q->last++;
        q->qu[q->last] = x;
    } else {
        printf("Queue is full!\n");
    }
    return;
}

int isempty(struct queue *q) {
    if (q->first > q->last) return 1;
    else return 0;
}

void print(struct queue *q) {
    int i;
    if (isempty(q) == 1) {
        printf("Queue is empty!\n");
        return;
    }
    for (i = q->first; i <= q->last; i++) {
        printf("%d ", q->qu[i]);
    }   
    return;
}

int removes(struct queue *q) {
    int x;
    if(isempty(q)==1) {
        printf("Queue is empty!\n");
        return(0);
    }
    x = q->qu[q->first];
    q->first++;
    return x;
}
int qu_size(struct queue *q) {
    return q->last - q->first + 1;
}