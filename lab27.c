#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "lab26.h"


void qu_bubble_sort(struct queue *q) {
    int tmp, sw;
    for (int i = q->first; i <= q->last; i++) {
        sw = 1;
        for (int j = q->first; j < q->last; j++) {
            if (q->qu[j] > q->qu[j+1]) {
                tmp = q->qu[j+1];
                q->qu[j+1] = q->qu[j];
                q->qu[j] = tmp;
                sw = 0;
            }
        }
        if (sw) {
            break;
        }
    }
    return;
}

int main() {
    int n, x;
    scanf("%d", &n);
    struct queue q;
    init(&q);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        insert(&q, x);
    }
    qu_bubble_sort(&q);
    print(&q);
}