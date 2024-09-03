#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void removeDuplicates(Node* head) {
    Node *current = head;
    Node *prev, *temp;

    while (current != NULL && current->next != NULL) {
        prev = current;
        
        while (prev->next != NULL) {
            if (current->data == prev->next->data) {
                temp = prev->next;
                prev->next = prev->next->next;
                free(temp);
            } else {
                prev = prev->next;
            }
        }
        current = current->next;
    }
}

Node* buildListFromInput() {
    Node* head = NULL;
    Node* tail = NULL;
    int value;
    char buffer[10];

    printf("Enter values for the linked list (end with non-numeric input):\n");
    while (1) {
        printf("Enter a number: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            break;
        }

        if (sscanf(buffer, "%d", &value) != 1) {
            break;
        }

        Node* newNode = createNode(value);
        if (head == NULL) {
            head = newNode;
            tail = head;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}

int main() {
    Node* head = buildListFromInput();

    printf("Original list:\n");
    printList(head);

    removeDuplicates(head);

    printf("List after removing duplicates:\n");
    printList(head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
