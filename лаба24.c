#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct tnode {         // узел дерева
  char word;                   // указатель на строку
  struct tnode* left;          // левый потомок
  struct tnode* right;         // правый потомок
}tnode;

#define MAX 50
 
typedef struct stack {
    int data[MAX];
    int top;
}stack;

typedef struct nodestack {
    tnode* data[MAX];
    int top;
}nodestack;
 
int precedence(char);
void init(stack *);
int empty(stack *);
int full(stack *);
int pop(stack *);
void push(stack *,int);
int top(stack *); 
void infixToPostfix(char infix[],char postfix[]);
 
void infixToPostfix(char infix[],char postfix[]) {
    stack s;
    char x,token;
    int i,j;    //i-index of infix,j-index of postfix
    init(&s);
    j=0;
    for(i=0;infix[i]!='\0';i++) {
        token=infix[i];
        if(isalnum(token))
            postfix[j++]=token;
        else
            if(token=='(')
               push(&s,'(');
        else
            if(token==')')
                while((x=pop(&s))!='(')
                      postfix[j++]=x;
                else {
                    while(precedence(token)<=precedence(top(&s))&&!empty(&s)) {
                        x=pop(&s);
                        postfix[j++]=x;
                    }
                    push(&s,token);
                }
    }
    while(!empty(&s)) {
        x=pop(&s);
        postfix[j++]=x;
    }
    postfix[j]='\0';
}
 
int precedence(char x) {
    if(x=='(')
        return(0);
    if(x=='+'||x=='-')
        return(1);
    if(x=='*'||x=='/'||x=='%')
        return(2);
    return(3);
}
 
void init(stack *s) {
    s->top=-1;
}
 
int empty(stack *s) {
    if(s->top==-1)
        return(1);
    return(0);
}
 
int full(stack *s) {
    if(s->top==MAX-1)
        return(1);
    return(0);
}
 
void push(stack *s,int x) {
    s->top=s->top+1;
    s->data[s->top]=x;
}
 
int pop(stack *s) {
    int x;
    x=s->data[s->top];
    s->top=s->top-1;
    return(x);
}
 
int top(stack *p) {
    return (p->data[p->top]);
}

void nPush(nodestack *s,tnode* x) {
    s->top=s->top+1;
    s->data[s->top] = x;
}
 
void nPop(nodestack *s) {
    tnode* x;
    x=s->data[s->top];
    s->top=s->top-1;
}
 
tnode* nTop(nodestack *p) {
    return (p->data[p->top]);
}

tnode* nPrint(nodestack *p) {
    return (p->data[0]);
}

void nInit(nodestack *s) {
    s->top=-1;
}

tnode* constract(char postfix[]) {
    nodestack s;
    nInit(&s);
    int n = sizeof(&postfix)/sizeof(postfix[0]);
    for (int i = 0; i < n; ++i) {
        char c = postfix[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' ) {
            tnode* x = nTop(&s);
            nPop(&s);
            tnode* y = nTop(&s);
            nPop(&s);
            tnode* node = (struct tnode*)malloc(sizeof(struct tnode));
            node->word = c;
            node->left = y;
            node->right = x;
            nPush(&s, node);
        } else {
            tnode* node = (struct tnode*)malloc(sizeof(struct tnode));
            node->word = c;
            node->left = NULL;
            node->right = NULL;
            nPush(&s, node);
        }
    }
    return nPrint(&s);
}

tnode* multiReduce(tnode* tree, int l) {
    tnode* knode = (struct tnode*)malloc(sizeof(struct tnode));
    knode->word = '+';
    knode->left = tree;
    knode->right = tree;
    for (int i = 2; i < l; ++i) {
        tnode* nnode = (struct tnode*)malloc(sizeof(struct tnode));
        nnode->word = '+';
        nnode->right = tree;
        nnode->left = knode;
        knode = nnode;
    }
    return knode;
}

void treeprint(tnode *tree) {
    if (tree!=NULL) { //Пока не встретится пустой узел
        treeprint(tree->left); //Рекурсивная функция для левого поддерева
        treeprint(tree->right); //Рекурсивная функция для правого поддерева
        printf("%c ",tree->word); //Отображаем корень дерева
    }
}

void nodeReduce(tnode* tree) {
    if (tree != NULL) {
        if (tree->word == '*') {
            if (isdigit(tree->left->word)) {
                tnode* x = tree->right;
                int l = tree->left->word - '0';
                tree = multiReduce(tree->right, l);
            } else if (isdigit(tree->right->word)) {
                tnode* x = tree->left;
                int l = tree->right->word  - '0';
                tree = multiReduce(tree->left, l);
            }
        }
        if (tree->word != '*') {
            printf("%c ",tree->word); //Отображаем корень дерева
        }
        nodeReduce(tree->left);
        nodeReduce(tree->right);
    }
}

int main() {
    char infix[30],postfix[30];
    printf("Enter an infix expression(eg: 5+2*4): ");
    scanf("%s", infix);
    infixToPostfix(infix,postfix);
    printf("\nPostfix expression: %s\n",postfix);
    tnode* node = constract(postfix);
    nodeReduce(node);
    free(node);
    return 0;
}
