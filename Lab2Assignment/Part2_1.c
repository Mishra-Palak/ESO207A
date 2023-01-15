#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;
struct Node* tail = NULL;
int length = 0;

//insertItem - any position, by default, the end
//append - to initiate - No need of this now
//deleteItem - by value
//searchItem
//printItems
//reversePrintItems

void insertItem(int item, int pos) {
    if (head == NULL) {
        struct Node* new = (struct Node*)malloc(sizeof(struct Node));
        new->data = item;
        new->next = NULL;
        new->prev = NULL;
        head = new;
        tail = head;
    } else if (pos <= 1) {
        struct Node* new = (struct Node*)malloc(sizeof(struct Node));
        new->data = item;
        new->next = head;
        new->prev = NULL;
        head->prev = new;
        head = new;
    } else if (pos >= length+1) {
        struct Node* new = (struct Node*)malloc(sizeof(struct Node));
        new->data = item;
        new->next = NULL;
        tail->next = new;
        new->prev = tail;
        tail = new;
    } else {
        struct Node* temp = head;
        for (int i = 0; i < pos-1; i++) {
            temp = temp->next;
        }
        struct Node* new = (struct Node*)malloc(sizeof(struct Node));
        new->data = item;
        new->next = temp;
        new->prev = temp->prev;
        temp->prev->next = new;
        temp->prev = new;
    }
    printf("Node inserted.\n");
    length++;
}

void deleteItem(int item) {
    if (head == NULL) {
        printf("Stack Underflow!\n");
        return;
    }
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp = head;
    while(temp->data != item) {
        temp = temp->next;
        if (temp == NULL) break;
    }
    if (temp == NULL) {
        printf("Isn't present in the stack. Can't be deleted.\n");
        return;
    } else if (length == 1) {
        head = NULL;
        tail = NULL;
    } else if (temp == head) {
        head = head->next;
        head->prev = NULL;
    } else if (temp == tail) {
        tail = temp->prev;
        tail->next = NULL;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    printf("Node deleted.\n");
    length--;
}

void printItems() {
    if (head == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack: \n");
    struct Node* current = head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void reversePrintItems() {
    if (tail == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Reversed Stack: \n");
    struct Node* current = tail;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

//STACK
//pop - fetch the last item, and pass it to deleteItem
//push - insertItem, default

void push(int item) {
    insertItem(item, length+1);
}

void pop() {
    if (head == NULL) {
        printf("Stack Underflow!\n");
        return;
    }
    deleteItem(tail->data);
}

int main() {
    int choice;
    printf("Enter your choice: \n1. Push\n2. Pop\n3. Display\n4. Exit\n");
    scanf("%d", &choice);
    
    while(choice != 4) {
        if (choice == 1) {
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            push(item);
        } else if (choice == 2) {
            pop();
        } else if (choice == 3) {
            printItems();
        } else if (choice == 4) break;
        else printf("Wrong Choice!\n");
        
        printf("\nEnter your choice: \n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        scanf("%d", &choice);
    }
}
