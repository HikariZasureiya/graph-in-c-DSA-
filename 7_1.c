#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node* left;
    struct node* right;
    struct node* next;
} tree;

tree* create(char data) {
    tree* new = (tree*)malloc(sizeof(tree));
    new->left = NULL;
    new->right = NULL;
    new->next = NULL;
    new->data = data;
    return new;
}

void push(tree* x, tree** head) {
    if (*head == NULL)
        *head = x;
    else {
        x->next = *head;
        *head = x;
    }
}

tree* pop(tree** head) {
    tree* popele = *head;
    *head = (*head)->next;
    return popele;
}

void print(struct node* node) {
    if (node == NULL)
        return;
    else {
        print(node->left);
        printf("%c ", node->data);
        print(node->right);
    }
}

int main() {
    char s[100];
    int l, i;
    tree *x, *y, *z;
    tree* head = NULL; // head node
    printf("Enter length of the operation: ");
    scanf("%d", &l);

    for (i = 0; i < l; i++) {
        printf("Enter operator or operand: ");
        scanf(" %c", &s[i]); 
    }

    for (i = 0; i < l; i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
            z = create(s[i]);
            x = pop(&head);
            y = pop(&head);
            z->left = y;
            z->right = x;
            push(z, &head);
        } 
        
        else {
            z = create(s[i]);
            push(z, &head);
        }
    }

    printf("The Inorder Traversal of Expression Tree: ");
    print(head);

    return 0;
}
