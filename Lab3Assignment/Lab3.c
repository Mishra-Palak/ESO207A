#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>

struct Node {
    int data;
    struct Node* next;
};

void enQueue(struct Node** head, struct Node** tail, int item) {
    if (*head == NULL) {
        struct Node* newN = (struct Node*)malloc(sizeof(struct Node));
        newN->data = item;
        newN->next = NULL;
        *head = newN;
        *tail = *head;
    } else {
        struct Node* newN = (struct Node*)malloc(sizeof(struct Node));
        newN->data = item;
        newN->next = NULL;
        (*tail)->next = newN;
        *tail = newN;
    }
}

void insertionSort(struct Node** head, struct Node** sorted) {
    struct Node* key = *head;
    
    while(key != NULL) {
        struct Node* nextN = key->next;
        
        if (*sorted == NULL || (*sorted)->data >= key->data) {
            key->next = *sorted;
            *sorted = key;
        } else {
            struct Node* current = *sorted;
            while(current->next != NULL && current->next->data < key->data) {
                current = current->next;
            }
            key->next = current->next;
            current->next = key;
        }
        
        key = nextN;
    }
    
    *head = *sorted;
}

void display(struct Node** head, int i) {
    if (*head == NULL) {
        printf("Queue %d - Empty Queue\n", i+1);
        return;
    }
    printf("Queue %d - ", i+1);
    struct Node* current = *head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void randomNumberGenerator(int N) {
    FILE * random = fopen("random.txt", "w");
    // int lim = 1;
    // while(random == NULL && lim < 100) {
    //     printf("Error in opening the file. Trying again.\n");
    //     lim++;
    //     random = fopen("random.txt", "w");
    // }
    // if (lim == 100) {
    //     printf("Not able to open the file in the moment. Try later.\n");
    //     exit(-1);
    // }
    // printf("File opened.\n");
    
    srand(time(0));
    for (int i = 0; i < N; i++) {
        int x = rand()%1000000; //0 to 999999
        fprintf(random, "%d ", x);
    }
    
    fclose(random);
}

int main() {
    printf("-----RANDOM NUMBER GENERATION-----\n");
    int N;
    printf("Enter the number of random numbers to be generated: ");
    scanf("%d", &N);
    randomNumberGenerator(N);
    
    FILE * random = fopen("random.txt", "r");
    int A[N];
    for (int i = 0; i < N; i++) fscanf(random, "%d", &A[i]);
    fclose(random);
    
    printf("\n");
    char view = 'a';
    while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
        printf("Do you want to view the array of the generated integers? (Y/N): ");
        scanf(" %c", &view);
                
        if (view == 'Y' || view == 'y') {
            printf("\nArray of Integers: \n");
            for (int i = 0; i < N; i++) printf("%d ", A[i]);
            printf("\n");
        } else if (view == 'N' || view == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }
    
    printf("\n");
    char choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("Do you want to sort using INSERTION SORT? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            clock_t t;
            double time_taken;
            printf("\n-----INSERTION SORT-----\n"); //Best - O(n), Avg - O(n^2), Worst - O(n^2)
            int B[N];
            for (int i = 0; i < N; i++) B[i] = A[i];
            
            printf("\n");
            char wish = 'a';
            while(wish != 'Y' && wish != 'y' && wish != 'N' && wish != 'n') {
                printf("Do you wish to calculate the time taken? (Y/N): ");
                scanf(" %c", &wish);
                
                if (wish == 'Y' || wish == 'y') {
                    t = clock();
                } else if (wish == 'N' || wish == 'n') {
                    break;
                } else printf("Wrong Input! Enter again.\n\n");
            }
            
            //Insertion Sort Commencement
            for (int i = 1; i < N; i++) {
                int key = B[i];
                
                int j = i-1;
                while(j >= 0 && B[j] > key) {
                    B[j+1] = B[j];
                    j--;
                }
                B[j+1] = key;
            }
            //Insertion Sort Conclusion
            
            if (wish == 'Y' || wish == 'y') {
                t = clock() - t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("Time Taken: %lf\n", time_taken);
            }
            
            printf("\n");
            view = 'a';
            while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
                printf("Do you want to view the sorted array? (Y/N): ");
                scanf(" %c", &view);
                
                if (view == 'Y' || view == 'y') {
                    printf("\nInsertion Sort -> Sorted Array: \n");
                    for (int i = 0; i < N; i++) printf("%d ", B[i]);
                    printf("\n");
                } else if (view == 'N' || view == 'n') break;
                else printf("Wrong Input! Enter again.\n\n");
            }
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }
    
    printf("\n");
    choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("Do you want to sort using HEAP SORT? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            clock_t t;
            double time_taken;
            printf("\n-----HEAP SORT-----\n"); //Best - O(nlogn), Avg - O(nlogn), Worst - O(nlogn)
            int B[N];
            for (int i = 0; i < N; i++) B[i] = A[i];
            
            printf("\n");
            char wish = 'a';
            while(wish != 'Y' && wish != 'y' && wish != 'N' && wish != 'n') {
                printf("Do you wish to calculate the time taken? (Y/N): ");
                scanf(" %c", &wish);
                
                if (wish == 'Y' || wish == 'y') {
                    t = clock();
                } else if (wish == 'N' || wish == 'n') {
                    break;
                } else printf("Wrong Input! Enter again.\n\n");
            }
            
            //Heap Sort Commencement
            //Max Heap - Ascending order, Min Heap - Descending order
            
            //Heapify
            for (int i = 1; i < N; i++) {
                if (B[i] > B[(i-1)/2]) {
                    int j = i;
                    while(B[j] > B[(j-1)/2]) {
                        int temp = B[j];
                        B[j] = B[(j-1)/2];
                        B[(j-1)/2] = temp;
                        j = (j-1)/2;
                    }
                }
            }
            
            //Sort
            for (int i = N-1; i > 0; i--) {
                int temp = B[0];
                B[0] = B[i];
                B[i] = temp;
                
                int j = 0, idx;
                do {
                    idx = 2*j+1;
                    if (B[idx] < B[idx+1] && idx < (i-1)) idx++;
                    if (B[j] < B[idx] && idx < i) {
                        int temp = B[j];
                        B[j] = B[idx];
                        B[idx] = temp;
                    }
                    j = idx;
                } while(idx < i);
            }
            
            //Heap Sort Conclusion
            
            if (wish == 'Y' || wish == 'y') {
                t = clock() - t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("Time Taken: %lf\n", time_taken);
            }
            
            printf("\n");
            view = 'a';
            while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
                printf("Do you want to view the sorted array? (Y/N): ");
                scanf(" %c", &view);
                
                if (view == 'Y' || view == 'y') {
                    printf("\nHeap Sort -> Sorted Array: \n");
                    for (int i = 0; i < N; i++) printf("%d ", B[i]);
                    printf("\n");
                } else if (view == 'N' || view == 'n') {
                    break;
                } else printf("Wrong Input! Enter again.\n\n");
            }
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }
    
    printf("\n");
    choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("Do you want to sort using BUCKET SORT? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            clock_t t;
            double time_taken;
            printf("\n-----BUCKET SORT-----\n"); //Best - O(n + k), Avg - O(n + k), Worst - O(n^2)
            int B[N];
            for (int i = 0; i < N; i++) B[i] = A[i];
            
            printf("\n");
            char wish = 'a';
            while(wish != 'Y' && wish != 'y' && wish != 'N' && wish != 'n') {
                printf("Do you wish to calculate the time taken? (Y/N): ");
                scanf(" %c", &wish);
                
                if (wish == 'Y' || wish == 'y') {
                    t = clock();
                } else if (wish == 'N' || wish == 'n') {
                    break;
                } else printf("Wrong Input! Enter again.\n\n");
            }
            
            //Bucket Sort Commencement
            //Identifying the number of buckets required
            int nBuckets = (int) ceil(sqrt((double) N)); //optimal number of buckets
            
            //Finding max and min item
            int m = INT_MAX;
            int M = INT_MIN;
            for (int i = 0; i < N; i++) {
                if (B[i] < m) m = B[i];
                if (B[i] > M) M = B[i];
            }
            double range = (double) (M-m)/nBuckets;
            
            //nBuckets queues initialised
            struct Node* head[nBuckets];
            for (int i = 0; i < nBuckets; i++) head[i] = NULL;
            struct Node* tail[nBuckets];
            for (int i = 0; i < nBuckets; i++) tail[i] = NULL;
            
            //If range == 0, the array is already sorted
            if (range) {
                //Scatter
                for (int i = 0; i < N; i++) {
                    double idx = (double) (B[i]-m)/range;
                    int idx_t = (B[i]-m)/range;
                    if (idx == idx_t && B[i] != m) idx_t--;
                
                    enQueue(&head[idx_t], &tail[idx_t], B[i]);
                }
                
                //Sorting the buckets - Insertion Sort
                struct Node* sorted[nBuckets];
                for (int i = 0; i < nBuckets; i++) sorted[i] = NULL;
                for (int i = 0; i < nBuckets; i++) {
                    if (head[i] != NULL) insertionSort(&head[i], &sorted[i]);
                }
                
                //Gather
                int idx = 0;
                for (int i = 0; i < nBuckets; i++) {
                    if (head[i] != NULL) {
                        struct Node* current = head[i];
                        while(current != NULL) {
                            B[idx] = current->data;
                            current = current->next;
                            idx++;
                        }
                    }
                }
            }
            
            //Bucket Sort Conclusion
            
            if (wish == 'Y' || wish == 'y') {
                t = clock() - t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                printf("Time Taken: %lf\n", time_taken);
            }
            
            if (range) {
                printf("\n");
                wish = 'a';
                while(wish != 'Y' && wish != 'y' && wish != 'N' && wish != 'n') {
                    printf("Do you wish to view the sorted bucket queues? (Y/N): ");
                    scanf(" %c", &wish);
                
                    if (wish == 'Y' || wish == 'y') {
                        for (int i = 0; i < nBuckets; i++) display(&head[i], i);
                    } else if (wish == 'N' || wish == 'n') {
                        break;
                    } else printf("Wrong Input! Enter again.\n\n");
                }
            }
            
            printf("\n");
            view = 'a';
            while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
                printf("Do you want to view the sorted array? (Y/N): ");
                scanf(" %c", &view);
                
                if (view == 'Y' || view == 'y') {
                    printf("\nBucket Sort -> Sorted Array: \n");
                    for (int i = 0; i < N; i++) printf("%d ", B[i]);
                    printf("\n");
                } else if (view == 'N' || view == 'n') {
                    break;
                } else printf("Wrong Input! Enter again.\n\n");
            }
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }
    
    printf("\n-----ALL TASKS REVIEWED-----\n");
}
