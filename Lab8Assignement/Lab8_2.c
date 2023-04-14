#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int r;

void randomNumberGenerator(int N) {
    FILE * random = fopen("random.txt", "w");
    
    srand(time(0));
    for (int i = 0; i < N; i++) {
        int x = 1 + rand()%10000; //1 to 10000
        fprintf(random, "%d ", x);
    }
    
    fclose(random);
}

int parent(int node) {
    if (node%r == 0) return (node-1)/r;
    return node/r;
}

int child(int node, int index) {
    return (r*(node)+index);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void minHeapify(int a[], int i, int size) {
    int largest = i;
    for(int j = 1; j <= r; j++){
        int b = child(i, j);
        if(b <= size-1 && a[b] < a[i]){
            if(a[b] <= a[largest]){
                largest = b;
            }
        }
    }
    if(largest != i) {
        swap(&a[i], &a[largest]);
        minHeapify(a,largest,size);
    }
}

void buildHeap(int a[], int size) {
    int ind = (size/2)-1;
    for(int i = ind; i >= 0; i--){
        minHeapify(a,i,size);
    }
}

void printArray(int a[], int size) {
    for(int i = 0; i < size; i++) printf("%d ", a[i]);
    printf("\n");
}

void insert(int a[], int key, int size) {
    size++;
    a[size-1] = key;
    int i = size-1;
    while(i > 0 && a[parent(i)] < a[i]) {
        swap(&a[i], &a[parent(i)]);
        i = parent(i);
    }
}

void reduceKey(int a[], int key, int i, int size){
    if(key > a[i]) {
        printf("The new key is greater.\n");
        return;
    }
    a[i] = key;
    buildHeap(a, size);
}

void deleteMin(int a[], int size){
    printf("Deleted: %d\n",a[0]);
    size--;
    swap(&a[0], &a[size]);
    buildHeap(a,size);
}

int main() {
    printf("-----MINIMUM PRIORITY QUEUE-----\n");
    printf("Enter the value of r: ");
    scanf("%d", &r);
    
    int a[10000];
    int size;
    printf("\n-----Insert-----\n");
    printf("Enter the number of nodes: ");
    scanf("%d", &size);
    randomNumberGenerator(size);
            
    FILE * random = fopen("random.txt", "r");
            
    for (int i = 0; i < size; i++) {
        int val;
        fscanf(random, "%d", &val);
        insert(a, val, i);
    }
    buildHeap(a, size);
            
    fclose(random);
    printf("\nNodes inserted.\n");
    printf("\nPriority Queue: \n");
    printArray(a, size);
    
    printf("\n-----Reduce Key-----\n");
    char choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("\nDo you want to reduce a key value? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            int i, key;
            printf("Enter the index: ");
            scanf("%d", &i);
            printf("\nEnter the new value: ");
            scanf("%d", &key);
            
            reduceKey(a, key, i, size);
            
            choice = 'a';
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input. Enter again.\n\n");
    }
    printf("\nPriority Queue: \n");
    printArray(a, size);
    
    printf("\n-----Delete Min-----\n");
    int n;
    if (size < 1000) n = size;
    else n = 1000;
    for(int i = 0; i < n; i++){
        printf("%d. ", i+1);
        deleteMin(a, size);
        size--;
    }
    if (size > 0) {
        printf("\nPriority Queue: \n");
        printArray(a, size-1000);
    } else printf("\nEmpty Priority Queue.\n");
}
