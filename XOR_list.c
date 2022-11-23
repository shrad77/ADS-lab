#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* npx;
};
typedef struct node* NODE;

struct node* XOR(struct node *a, struct node *b) {
    return (struct node*) ((unsigned int) (a) ^ (unsigned int) (b));
}


void insert(struct node **head_ref, int data) {
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->npx = XOR(*head_ref, NULL);
    if (*head_ref != NULL) {
        struct node* next = XOR((*head_ref)->npx, NULL);
        (*head_ref)->npx = XOR(new_node, next);
    }
    *head_ref = new_node;
}

void deleteNODE(struct node **head_ref, int data){
    struct node *curr = *head_ref;
    struct node *prev = NULL;
    struct node *next;
    struct node *temp;
    if(curr == NULL){
        printf("The list is empty!! ");
        return;
    }
    if(curr->data==data){
        next = XOR(prev, curr->npx);
        temp = XOR(curr, next->npx);
        next->npx = XOR(prev, temp);
        printf("\nThe data deleted is: %d",curr->data);
        free(curr);
        *head_ref = next;
        return;
    }
    while (curr != NULL) {
        if(curr->data==data){
            temp = XOR(prev->npx, curr);

            next = XOR(prev, curr->npx);
            prev->npx = XOR(temp,next);
            if(next==NULL){
                printf("\nThe data deleted is : %d",curr->data);
                free(curr);
                return;
            }
            temp = XOR(next->npx, curr);
            next->npx = XOR(prev,temp);

            printf("\nThe data deleted is : %d",curr->data);
            free(curr);
            curr = prev;
            prev = temp;
            return;
        }
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    printf("\nThe element was not found!!");
}

void printList(struct node *head) {
    struct node *curr = head;
    struct node *prev = NULL;
    struct node *next;

    printf("\nFollowing are the nodes of Linked List: \n");

    while (curr != NULL) {
        printf("%d ", curr->data);
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
}

int main() {
    /* Create following Doubly Linked List
     head-->40<-->30<-->20<-->10   */
     int i,n,num,choice,del;
    struct node *head = NULL;
   /* while(1)
    {

        switch(choice)
        {

            case 1:
        }
    }*/
    printf("Enter the number of nodes to be inserted\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the data of the node\n");
        scanf("%d",&num);
         insert(&head, num);
    }

   /* insert(&head 20);
    insert(&head, 30);
    insert(&head, 40);*/
    printList(head);
    printf("\n");
    printf("Enter the node to be deleted\n");
    scanf("%d",&del);
    deleteNODE(&head,del);
    /*deleteNODE(&head,10);*/
    printList(head);
    return (0);
}
