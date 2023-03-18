#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct record {
    char name[50];
    char surname[50];
    char midname[50];
    char gender;
    char group[20];
    int discr;
    int matan;
    int informatic;
    int linear;
    int history;
} record;

struct tnode {                // узел дерева
    char* word;                  // указатель на строку (слово)
    int count;                   // число вхождений
    int points;
    struct tnode* left;          // левый потомок
    struct tnode* right;         // правый потомок
};

struct tnode* addtree(struct tnode* p, char* w, int points) {
    int cond;
    if (p == NULL) {
        p = (struct tnode*)malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->points = points;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        p->points += points;
    } else if (cond < 0)
        p->left = addtree(p->left, w, points);
    else
        p->right = addtree(p->right, w, points);
    return p;
}

void treeprint(struct tnode *tree) {
    if (tree!=NULL) { //Пока не встретится пустой узел
        treeprint(tree->left); //Рекурсивная функция для левого поддерева
        treeprint(tree->right); //Рекурсивная функция для правого поддерева
        printf("%s\n %d %d\n",tree->word, tree->count, tree->points); //Отображаем корень дерева
    }
}

void find_max(struct tnode* p, double *maxim) {
    if (p != NULL) {
        if (((double) p->points/p->count) > *maxim) {
            *maxim = ((double) p->points/p->count);
        }
        find_max(p->left, &*maxim);
        find_max(p->right, &*maxim);
    }
}

void find_group(struct tnode* p, double maxim) {
    if (p != NULL) {
        if (((double) p->points/p->count) == maxim) {
            printf("%s\n\n", p->word);
            return;
        }
        find_group(p->left, maxim);
        find_group(p->right, maxim);
    }
}


int main() {
    FILE *file = fopen("data.csv","r");
    struct tnode* root;
    root = NULL;
    char *istr;
    char str[255];
    while (!feof(file)) {
        if (fgets(str, 255, file)) {
            int sum = 0, i = 0, c = 0; 
            while (str[i] != ' ') {
                if (c == 3 && str[i] == 'F') {
                    char s[20];
                    for (int j = 0; j < 11; ++j) {
                        s[j] = str[j + i + 2];
                    }
                    sum = str[i+14] - '0' + str[i+16] - '0' + str[i+18] - '0' + str[i+20] - '0' + str[i+22] - '0';
                    root = addtree(root, s, sum);
                    break;
                }
                if (c == 3 && str[i] != 'F') {
                    break;
                }
                if (str[i] == ';') {
                    ++c;
                }
                ++i;
            }
        }
    }
    double maxim = 0;
    char ans;
    find_max(root, &maxim);
    find_group(root, maxim);
    treeprint(root);
    fclose(file);
    return 0;
}