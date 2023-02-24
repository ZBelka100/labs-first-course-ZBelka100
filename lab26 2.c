#include <stdio.h>

#define QMAX 100
struct queue {
  int qu[QMAX];
  int last, first;
};

void qu_bubble_sort(struct queue *q) {
    int tmp, sw;
    for (i = q->first; i <= q->last; i++) {
        sw = 1;
        for (j = j + 1; j <= q->last; j++) {
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
    queue qu;
    init(qu);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        insert(qu, x);
    }
    print(qu);
}
