#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

void randomNumberGenerator(int N) {
    FILE * random = fopen("random.txt", "w");
    
    srand(time(0));
    for (int i = 0; i < N; i++) {
        int x = 1 + rand()%10000; //1 to 10000
        fprintf(random, "%d ", x);
    }
    
    fclose(random);
}

void insert(int val) {
    struct Node* newN = (struct Node*)malloc(sizeof(struct Node));
    newN->data = val;
    newN->left = NULL;
    newN->right = NULL;
    
    if (root == NULL) root = newN;
    else {
        struct Node* temp = root;
        struct Node* prev = NULL;
        
        while (temp != NULL) {
            prev = temp;
            if (val > temp->data) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        
        if (val > prev->data) {
            prev->right = newN;
        } else {
            prev->left = newN;
        }
    }
}

int search(int key) {
    struct Node* temp = root;
    
    while (temp != NULL) {
        if (key == temp->data) {
            return 1;
        } else if (key > temp->data) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
    
    return 0;
}

struct Node* minimum(struct Node* root) {
    struct Node* curr = root;
    while (curr != NULL && curr->left != NULL) {
        curr = curr->left;
    }
    
    return curr;
}

struct Node* deleteN(struct Node* root, int key) {
    if (root == NULL) return root;
    
    if (key < root->data) {
        root->left = deleteN(root->left, key);
    } else if (key > root->data) {
        root->right = deleteN(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        struct Node* temp = minimum(root->right);
        root->data = temp->data;
        root->right = deleteN(root->right, temp->data);
    }
    
    return root;
}

void inorder(struct Node* root) {
    if (root == NULL) return;
    
    inorder(root->left);
    printf("%d ",  root->data);
    inorder(root->right);
}

int main() {
    printf("-----BINARY SEARCH TREE-----\n");
    
    int N;
    printf("\n-----Insert-----\n");
    printf("Enter the number of nodes: ");
    scanf("%d", &N);
    randomNumberGenerator(N);
            
    FILE * random = fopen("random.txt", "r");
            
    for (int i = 0; i < N; i++) {
        int val;
        fscanf(random, "%d", &val);
        insert(val);
    }
            
    fclose(random);
    printf("\nNodes inserted.\n");
    printf("\nInorder Traversal: \n");
    inorder(root);
    
    printf("\n\n-----Search-----\n");
    char choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("\nDo you want to search a key? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            int key;
            printf("\nEnter data: ");
            scanf("%d", &key);
            
            if(search(key)) printf("\nData found!\n");
            else printf("\nData not found!\n");
            
            choice = 'a';
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input. Enter again.\n\n");
    }
    
    printf("\n-----Delete-----\n");
    choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("\nDo you want to delete a node? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            int val;
            printf("\nEnter data: ");
            scanf("%d", &val);
            
            if(search(val)) {
                root = deleteN(root, val);
                N--;
                printf("Node deleted.\n");
            } else printf("\nData not found!\n");
            
            choice = 'a';
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input. Enter again.\n\n");
    }
    printf("\nInorder Traversal: \n");
    inorder(root);
    
    printf("\n\n-----Delete Min-----\n");
    int n = 0;
    while(n < 1000 && n < N) {
        int min = (minimum(root))->data;
        printf("%d. Deleted: %d\n", n+1, min);
        deleteN(root, min);
        n++;
    }
    printf("\nInorder Traversal: \n");
    inorder(root);
}
