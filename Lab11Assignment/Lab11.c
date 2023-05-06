#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomNumberGenerator(int N) {
    FILE * random = fopen("random.txt", "w");
    
    srand(time(0));
    for (int i = 0; i < N; i++) {
        int x = 1 + rand()%1000; //1 to 1000
        fprintf(random, "%d ", x);
    }
    
    fclose(random);
}

typedef struct Node {
	int val;
	struct Node * right;
	struct Node * left;
	int height;
} Node;

#ifndef max
#define max(a,b) (((a) >= (b)) ? (a) : (b))
#endif

Node* new_node(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val= val;
    n->right = NULL;
    n->left = NULL;
    n->height = 1;
    return n;
}

int height(Node* root) {
    if(root == NULL) return 0;
    return root->height;
}

Node* left_rotate(Node* root) {
    Node* right = root->right;
    Node* right_child = right->left;

    root->right = right_child;
    right->left = root;

    root->height = max(height(root->right), height(root->left)) + 1;
    right->height = max(height(right->right), height(right->left)) + 1;

    return right;
}

Node* right_rotate(Node* root) {
    Node* left = root->left;
    Node* left_child = left->right;

    left->right = root;
    root->left = left_child;

    root->height = max(height(root->right), height(root->left)) + 1;
    left->height = max(height(left->right), height(left->left)) + 1;

    return left;
}

int balance_factor(Node* root) {
    int balance_factor = height(root->left) - height(root->right);
    return balance_factor;
}

Node* insert(Node *root, int val) {  
    if (root == NULL) return new_node(val);
    int currVal = root->val;
    if (val < currVal) root->left = insert(root->left, val);
    else if ( val > currVal) root->right = insert(root->right, val);
    else return root;

    root->height = max(height(root->right), height(root->left)) + 1;

    int bf = balance_factor(root);
    if(bf > 1 && val < root->left->val) return right_rotate(root);
    if (bf < -1 && val > root->right->val ) return left_rotate(root);
    if(bf > 1 && val > root->left->val) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (bf < -1 && val < root->right->val) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

Node* inorder_successor(Node* root){
    Node* temp = root->right;
    while(temp->left) temp = temp->left;
    return temp;
}

Node* delete_node(Node* root, int val){
    if (root == NULL) return root;
    if(val < root->val) root->left = delete_node(root->left, val);
    else if (val > root->val) root->right = delete_node(root->right, val);
    else {
        if((root->left == NULL || root->right == NULL)){
            Node* temp = root->left ? root->left: root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            free(temp);
        } else {
            Node* temp = inorder_successor(root);
            root->val = temp->val;
            root->right  = delete_node(root->right, temp->val);
        }
    }

    if (root == NULL) return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balance_factor(root);

    if(bf > 1 && balance_factor(root->left) >= 0){
        return right_rotate(root);
    }
    if(bf < -1 && balance_factor(root->right) <= 0){
        return left_rotate(root);
    }
    if(bf > 1 && balance_factor(root->left) < 0){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if(bf < -1 && balance_factor(root->right) > 0){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

Node* search_node(Node* root, int val){
    if (root == NULL || root->val == val){
        return root;
    }
    else if (val < root->val){ 
        return search_node(root->left, val);
    }
    else{
        return search_node(root->right, val);
    }
}

void display_tree(Node* root){
    if(root == NULL){
        return;
    }
    display_tree(root->left);
    printf("%d ",root->val);
    display_tree(root->right);
}

void display(Node* root){
    display_tree(root);
    printf("\n");
}

//join 
Node* joinLeft(Node* T1, Node* T2) {
    if(T1 == NULL)
        return T2;
    if(T2 == NULL)
        return T1;
    
    int h1 = height(T1);
    int h2 = height(T2);
    
    Node* temp = T2;
    while(temp->left) temp=temp->left;
    int x = temp->val;

    T2 = delete_node(T2, x);
    int h = T2->height;
    
    Node* v = T1, *u = T1;
    int h_prime = h1;
    if(h == 0) h++;
    while (h_prime > h+1) {
        if(balance_factor(v) == -1) h_prime -= 2;
        else h_prime -=1;
        u = v;
        v = v->right;
    }
    
    Node* new_tree = new_node(x);
    new_tree->left = v;
    new_tree->right= T2;
    new_tree->height = 1 + max(height(new_tree->left),height(new_tree->right));

    if(u == v)
        T1 = new_tree;
    else
        u->right = new_tree;

    T1 = insert(T1, v->val);
    return T1;
}

Node* joinRight(Node* T1, Node* T2) {
    if(T1==NULL)
        return T2;
    if(T2==NULL)
        return T1;
    int h1 = height(T1);
    int h2 = height(T2);

    Node* temp = T1;
    
    while(temp->right) temp=temp->right;
    int x = temp->val;

    T1 = delete_node(T1, x);
    int h = T1->height;
    Node* v = T2, *u = T2;
    int h_prime = h2;
    if(h == 0) h++;
    while (h_prime > h+1) {
        if(balance_factor(v)==-1) h_prime -= 2;
        else h_prime -=1; u = v;
        v = v->left;
    }
 
    Node* new_tree = new_node(x);
    new_tree->right = v;
    new_tree->left= T1;
    new_tree->height = 1 + max(height(new_tree->left),height(new_tree->right));

        
    if(u == v) T2 = new_tree;
    else u->left = new_tree;

    int bf = balance_factor(new_tree);
    T2 = insert(T2, v->val);
    return T2;
}

Node* join(Node* T1, Node* T2){
    if(height(T1) > height(T2)) {
        return joinLeft(T1, T2);
    } else {
        return joinRight(T1,T2);
    }
}

//split
Node* split(Node* t, int k) {
    if (t == NULL) {
        return new_node(0);
    }

    if (t->val == k) {
        Node* temp = new_node(0);
        temp->left = t->left;
        temp->right = t->right;
        temp->height = max(height(temp->left), height(temp->right)) +1;
        return temp;    
    } else if (k < t->val) {
        Node* temp = split(t->left, k);
        temp->right = join(temp->right, t->right);
        temp->right = insert(temp->right, t->val);
        return temp;
    } else {
        Node* temp = split(t->right, k);
        temp->left = join(t->left, temp->left);
        temp->left = insert(temp->left, t->val);
        return temp;
    }
}

int main() {
    int N;
    printf("Enter the number of nodes: ");
    scanf("%d",&N);
    
    int values[N];
    randomNumberGenerator(N);
    FILE * random = fopen("random.txt", "r");
    for (int i = 0; i < N; i++) fscanf(random, "%d", &values[i]);
    fclose(random);
    
    Node *T = NULL;
    for(int i = 0; i < N; i++) T = insert(T, values[i]);
    printf("\nTree: \n");
    display(T);
    
    int splitter;
    printf("\nEnter the item where you want to split the tree (NOTE - This node will not be present in the final tree anymore): ");
    scanf("%d", &splitter);
    T = insert(T, splitter);
    
    Node* dummy = split(T, splitter);
    printf("\nLeft Tree:\n");
    display(dummy->left);
    printf("Right Tree:\n");
    display(dummy->right);
    
    Node* new_tree = join(dummy->left, dummy->right);
    printf("\nFinal Tree: \n");
    display(new_tree);
}
