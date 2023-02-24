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

int c0 = 0, c1 = 0, c2 = 0;

void treecount(struct tnode* p) {
  if (p != NULL) {
    if ((p->left != NULL) && (p->right != NULL)) {
        ++c2;
    } else if ((p->left == NULL) && (p->right == NULL)) {
        ++c0;
    } else {
        ++c1;
    }
    treecount(p->left);
    treecount(p->right);
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
  treecount(root);
  printf(" 0 - %d\n", c0);
  printf(" 1 - %d\n", c1);
  printf(" 2 - %d\n", c2);
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