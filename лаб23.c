#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
struct tnode {                // узел дерева
  char* word;                  // указатель на строку (слово)
  int count;                   // число вхождений
  struct tnode* left;          // левый потомок
  struct tnode* right;         // правый потомок
};

struct tnode* addtree(struct tnode* p, char* w) {
  int cond;
  if (p == NULL) {
    p = (struct tnode*)malloc(sizeof(struct tnode));
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  }
  else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);
  
  return p;
}

void treecount(struct tnode* p, int *nul, int *one, int *two) {
  if (p != NULL) {
    if ((p->left != NULL) && (p->right != NULL)) {
        ++*two;
    } else if ((p->left == NULL) && (p->right == NULL)) {
        ++*nul;
    } else {
        ++*one;
    }
    treecount(p->left, nul, one, two);
    treecount(p->right, nul, one, two);
  }
}

int main() {
  struct tnode* root;
  char word[MAXWORD];
  root = NULL;
  do {
    scanf("%s", word);
    if (isalpha(word[0]))
      root = addtree(root, word);
  } while (word[0] != '0');    // условие выхода – ввод символа '0'
  int nul = 0, one = 0, two = 0;
  treecount(root, &nul, &one, &two);
  printf(" 0 - %d\n", nul);
  printf(" 1 - %d\n", one);
  printf(" 2 - %d\n", two);
  getchar();
  getchar();
  return 0;
}
/*now is the time for all good men to come to the aid of their party
0
 0 - 7
 1 - 1
 2 - 6
*/
