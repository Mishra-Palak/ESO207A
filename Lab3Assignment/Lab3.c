#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
        int x = rand()%1000;
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
            printf("\n-----INSERTION SORT-----\n");
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
            
            if (wish == 'y' || wish == 'Y') {
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
            printf("\n-----HEAP SORT-----\n");
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
            //Map Heap - Ascending order, Min Heap - Descending order
            
            //heapify
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
            
            //sort
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
            
            if (wish == 'y' || wish == 'Y') {
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
    
    printf("\n-----TASK DONE-----\n");
}
