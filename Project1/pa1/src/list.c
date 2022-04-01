#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>




typedef struct node

{
       struct node *next;
       int data;

       

} Node;

int contains(Node *head, int n);
Node* insert(Node *head, int n);
Node* delete(Node* head, int n);
int length(Node* head);

void deleteList(Node *head);

void print(Node *head);

int main(void) {

       Node *head = NULL; 

       int data;

       char command;

       do

       {

             fflush(stdout);

             scanf(" %c %d",&command,&data);

             if((tolower(command) != 'i') && (tolower(command) != 'd'))

                    break;
             if(tolower(command) == 'i')

                    head = insert(head,data);

             else 

                    head = delete(head,data);


             printf("%d : ",length(head));

             print(head); 

             printf("\n");

       }while((tolower(command) == 'i') || (tolower(command) == 'd'));

       deleteList(head); 

       return EXIT_SUCCESS;

}

Node* insert(Node *head, int n)

{

       if(contains(head,n) == 1) 

             return head;

       Node *node = (Node*)malloc(sizeof(Node)); 

       if(node != NULL)

       {

             node->data = n;

             node->next = NULL;

             if(head == NULL)

                    head = node;

             else

             {

                    Node *curr = head;

                    Node *prev = NULL;

                    while(curr != NULL)

                    {
                           if(curr->data > node->data)

                           {

                                 if(prev == NULL)

                                 {

                                        node->next = head;

                                        head = node;

                                 }else

                                 {

                                        node->next = curr;

                                        prev->next = node;

                                 }

                                 return head;

                           }

                           prev = curr;

                           curr = curr->next;

                    }

                    prev->next = node;

             }

       }

       return head;

}

Node* delete(Node* head, int n)

{
       if(head != NULL)

       {
             if(head->data == n)

             {

                    Node *temp = head;

                    head = head->next;

                    free(temp); 

             }else

             {

                    Node *curr = head;

                    Node *prev = NULL;

                    while(curr != NULL)

                    {

                           if(curr->data == n)

                           {

                                 prev->next = curr->next;

                                 free(curr);

                                 return head;

                           }

                           prev = curr;

                           curr = curr->next;

                    }

             }

       }

       return head;

}

int length(Node* head)

{

       int count = 0;

       Node *curr = head;

       while(curr != NULL)

       {

             count++;

             curr = curr->next;

       }

       return count;

}

void print(Node *head)

{

       Node *curr = head;

       while(curr != NULL)

       {

             printf("%d ",curr->data);

             curr = curr->next;

       }

}

int contains(Node *head, int n)

{

       Node *curr = head;

       while(curr != NULL)

       {

             if(curr->data == n)

                    return 1;

             curr = curr->next;

       }

       return 0;

}

void deleteList(Node *head)

{

       Node *curr;

       while(head != NULL)

       {

             curr = head;

             head = head->next;

             free(curr);

       }

}