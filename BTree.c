#include <stdio.h>
  #include <stdlib.h>

  #define MAX 4
  #define MIN 2

  struct btreeNode {
        int val[MAX + 1], count;
        struct btreeNode *link[MAX + 1];
  };

  struct btreeNode *root;

 
  struct btreeNode * createNode(int val, struct btreeNode *child) {
        struct btreeNode *newNode;
        newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        newNode->val[1] = val;
        newNode->count = 1;
        newNode->link[0] = root;
        newNode->link[1] = child;
        return newNode;
  }


  void addValToNode(int val, int pos, struct btreeNode *node,
                        struct btreeNode *child) {
        int j = node->count;
        while (j > pos) {
                node->val[j + 1] = node->val[j];
                node->link[j + 1] = node->link[j];
                j--;
        }
        node->val[j + 1] = val;
        node->link[j + 1] = child;
        node->count++;
  }

  void splitNode (int val, int *pval, int pos, struct btreeNode *node,
     struct btreeNode *child, struct btreeNode **newNode) {
        int median, j;

        if (pos > MIN)
                median = MIN + 1;
        else
                median = MIN;

        *newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
        j = median + 1;
        while (j <= MAX) {
                (*newNode)->val[j - median] = node->val[j];
                (*newNode)->link[j - median] = node->link[j];
                j++;
        }
        node->count = median;
        (*newNode)->count = MAX - median;

        if (pos <= MIN) {
                addValToNode(val, pos, node, child);
        } else {
                addValToNode(val, pos - median, *newNode, child);
        }
        *pval = node->val[node->count];
        (*newNode)->link[0] = node->link[node->count];
        node->count--;
  }

  
  int setValueInNode(int val, int *pval,
     struct btreeNode *node, struct btreeNode **child) {

        int pos;
        if (!node) {
                *pval = val;
                *child = NULL;
                return 1;
        }

        if (val < node->val[1]) {
                pos = 0;
        } else {
                for (pos = node->count;
                        (val < node->val[pos] && pos > 1); pos--);
                if (val == node->val[pos]) {
                        printf("Duplicates not allowed\n");
                        return 0;
                }
        }
        if (setValueInNode(val, pval, node->link[pos], child)) {
                if (node->count < MAX) {
                        addValToNode(*pval, pos, node, *child);
                } else {
                        splitNode(*pval, pval, pos, node, *child, child);
                        return 1;
                }
        }
        return 0;
  }

 
  void insertion(int val) {
        int flag, i;
        struct btreeNode *child;

        flag = setValueInNode(val, &i, root, &child);
        if (flag)
                root = createNode(i, child);
  }



  void traversal(struct btreeNode *myNode) {
        int i;
        if (myNode) {
                for (i = 0; i < myNode->count; i++) {
                        traversal(myNode->link[i]);
                        printf("%d ", myNode->val[i + 1]);
                }
                traversal(myNode->link[i]);
        }
  }

  int main() {
        int val, ch;
        while (1) {
                printf("1. Insertion\t");
                printf("2. traversal\n");
                printf("3. Exit\nEnter your choice:");
                scanf("%d", &ch);
                switch (ch) {
                        case 1:
                                printf("Enter your input:");
                                scanf("%d", &val);
                                insertion(val);
                                break;
                        case 2:
                                traversal(root);
                                break;

                        case 3:
                                exit(0);
                        default:
                                printf("U have entered wrong option!!\n");
                                break;
                }
                printf("\n");
        }
  }
