// Created by Gardo on 13/11/23

#include "stdio.h"
#include "stdlib.h"

typedef struct node{
    int a;
    struct node *next;
}node;

node *add_node_to_tail(node *tail){
    tail->next = (node*) malloc(sizeof(node));

    printf("Aggiungi nodo: ");
    scanf("%d", &tail->next->a);
    tail->next->next = NULL;

    return tail->next;
}

void print_list(node *list_node){
    printf("%d\n", list_node->a);

    if(list_node->next != NULL){
        print_list(list_node->next);
    }
    else
        printf("EXIT");
}

int main(){
    node *head, *tail;

    head = tail = (node*) malloc(sizeof(node));
    head->next = NULL;
    head->a = 42;

    tail = add_node_to_tail(tail);

    print_list(head);
}
