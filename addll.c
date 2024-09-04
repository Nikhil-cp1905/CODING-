#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

struct Node* addTwoLists(struct Node* first, struct Node* second) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    struct Node* prev = NULL;
    int carry = 0, sum;
    
    while (first != NULL || second != NULL || carry) {
        sum = carry;
        
        if (first != NULL) {
            sum += first->data;
            first = first->next;
        }
        
        if (second != NULL) {
            sum += second->data;
            second = second->next;
        }
        
        carry = sum / 10;
        sum = sum % 10;
        
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = sum;
        temp->next = NULL;
        
        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
    }
    
    return result;
}

int main() {
    struct Node* first = NULL;
    struct Node* second = NULL;
    struct Node* result = NULL;
    
    push(&first, 7);
    push(&first, 1);
    push(&first, 6); // Represents the number 617
    
    push(&second, 5);
    push(&second, 9);
    push(&second, 2); // Represents the number 295
    
    printf("First list: ");
    printList(first);
    
    printf("Second list: ");
    printList(second);
    
    result = addTwoLists(first, second);
    
    printf("Resultant list: ");
    printList(result);
    
    return 0;
}
