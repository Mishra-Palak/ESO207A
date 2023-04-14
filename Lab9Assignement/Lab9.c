#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int key;
    int rank;
    struct node* left;
    struct node* right;
} Node;

Node* createNode(int key, int rank) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->rank = rank;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int rankOf(Node* node) {
    if (node == NULL)
        return 0;
    return node->rank;
}

void updateRank(Node* node) {
    node->rank = rankOf(node->left) + 1;
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    Node* z = y->right;
    y->right = x;
    x->left = z;
    updateRank(x);
    updateRank(y);
    return y;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* z = y->left;
    y->left = x;
    x->right = z;
    updateRank(x);
    updateRank(y);
    return y;
}

Node* balanceNode(Node* node) {
    if (rankOf(node->left) - rankOf(node->right) > 1) {
        if (rankOf(node->left->left) >= rankOf(node->left->right))
            node = rightRotate(node);
        else {
            node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
    }
    else if (rankOf(node->right) - rankOf(node->left) > 1) {
        if (rankOf(node->right->right) >= rankOf(node->right->left))
            node = leftRotate(node);
        else {
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }
    }
    return node;
}

Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key, 1);
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    updateRank(root);
    return balanceNode(root);
}

Node* findMinNode(Node* node) {
    if (node->left == NULL)
        return node;
    return findMinNode(node->left);
}

Node* deleteMinNode(Node* node) {
    if (node->left == NULL)
        return node->right;
    node->left = deleteMinNode(node->left);
    updateRank(node);
    return balanceNode(node);
}

Node* delete(Node* root, int key) {
    if (root == NULL)
        return NULL;
    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        Node* leftChild = root->left;
        Node* rightChild = root->right;
        free(root);
        if (rightChild == NULL)
            return leftChild;
        Node* minNode = findMinNode(rightChild);
        minNode->right = deleteMinNode(rightChild);
        minNode->left = leftChild;
        updateRank(minNode);
        return balanceNode(minNode);
    }
    updateRank(root);
    return balanceNode(root);
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

void insertRandomNumbers(Node** root) {
    srand(time(0));
    for (int i = 0; i < 500; i++) {
        int num = 1 + rand() % 10000; //1 to 10000
        *root = insert(*root, num);
    }
}

void findAndDeleteMin(Node** root) {
    for (int i = 0; i < 100; i++) {
        Node* minNode = findMinNode(*root);
        printf("Minimum item: %d\n", minNode->key);
        *root = delete(*root, minNode->key);
    }
}

void inorder(Node* root) {
    if(root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice;
    printf("-----RB TREE-----\n");
    printf("Enter your choice: \n1. Insert\n2. Search\n3. Delete\n4. Inorder\n5. Exit\n");
    scanf("%d", &choice);
    
    while(choice != 5) {
        if (choice == 1) {
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            root = insert(root, item);
        } else if (choice == 2) {
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            Node* t = search(root, item);
            if (t != NULL) {
                printf("Item found.\n");
            } else printf("Item not found!\n");
        } else if (choice == 3) {
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            Node* t = search(root, item);
            if (t != NULL) {
                root = delete(root, item);
            } else printf("Item not found!\n");
        }
        else if (choice == 4) {
            inorder(root);
            printf("\n");
        }
        else if (choice == 5) break;
        else printf("Wrong Choice!\n");
        
        printf("\nEnter your choice: \n1. Insert\n2. Search\n3. Delete\n4. Inorder\n5. Exit\n");
        scanf("%d", &choice);
    }

    printf("\n-----SECOND TASK-----\n");
    root = NULL;
    insertRandomNumbers(&root);
    inorder(root);
    findAndDeleteMin(&root);
    inorder(root);
}
