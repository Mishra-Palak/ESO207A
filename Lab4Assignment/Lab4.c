#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Recursive Quick Sort
int rearrange(int A[], int start, int end) {
    int p = A[end];
    int i = start-1;
    for (int j = start; j < end; j++) {
        if (A[j] <= p) {
            i++;
            
            if (i < j) {
                int temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
        }
    }
    
    if (i < end-1) {
        int temp = A[i+1];
        A[i+1] = A[end];
        A[end] = temp;
    }
    return (i+1);
}

int pivotGeneration(int A[], int low, int high) {
    srand(time(0));
    int pivot = low + rand()%(high-low+1);
    if (pivot < high) {
        int temp = A[pivot];
        A[pivot] = A[high];
        A[high] = temp;
    }
    return rearrange(A, low, high);
}

void quickSort(int A[], int start, int end) {
    if (start < end) {
        int pivot = pivotGeneration(A, start, end);
        quickSort(A, start, pivot-1);
        quickSort(A, pivot+1, end);
    }
}

//Recursive Merge Sort
void merge(int A[], int l, int m, int r) {
    int N1 = m-l+1;
    int N2 = r-m;
    int L[N1], R[N2];
    for (int i = 0; i < N1; i++) L[i] = A[l+i];
    for (int i = 0; i < N2; i++) R[i] = A[m+i+1];
                    
    //merge
    int i = 0, j = 0, k = l;
    while(i < N1 && j < N2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
                    
    while(i < N1) {
        A[k] = L[i];
        i++;
        k++;
    }
                    
    while(j < N2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int A[], int l, int r) {
    if (l < r) {
        int m = (l+r)/2;
        
        mergeSort(A, l, m);
        mergeSort(A, m+1, r);
        
        merge(A, l, m, r);
    }
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
    printf("-----ARRAY GENERATION-----\n");
    int N = -1;
    while(N < 0) {
        printf("Enter the array length: ");
        scanf("%d", &N);
        
        if (N >= 0) randomNumberGenerator(N);
        else printf("Kindly re-enter the number.\n");
        printf("\n");
    }
    
    FILE * random = fopen("random.txt", "r");
    int A[N];
    for (int i = 0; i < N; i++) fscanf(random, "%d", &A[i]);
    fclose(random);
    
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
        printf("Do you want to sort using RECURSIVE QUICK SORT? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            clock_t t;
            double time_taken;
            printf("\n-----RECURSIVE QUICK SORT-----\n"); //Best - O(nlogn), Avg - O(nlogn), Worst - O(n^2)
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
            
            //Recursive Quick Sort Commencement
            quickSort(B, 0, N-1);
            //Recursive Quick Sort Conclusion
            
            if (wish == 'Y' || wish == 'y') {
                t = clock() - t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                if (time_taken > 180) printf("Time exceeds 3 minutes.\n");
                else printf("Time Taken: %lf\n", time_taken);
            }
            
            printf("\n");
            view = 'a';
            while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
                printf("Do you want to view the sorted array? (Y/N): ");
                scanf(" %c", &view);
                
                if (view == 'Y' || view == 'y') {
                    printf("\nRecursive Quick Sort -> Sorted Array: \n");
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
        printf("Do you want to sort using ITERATIVE MERGE SORT? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            clock_t t;
            double time_taken;
            printf("\n-----ITERATIVE MERGE SORT-----\n"); //Best - O(nlogn), Avg - O(nlogn), Worst - O(nlogn)
            int* B = (int*)malloc(N*sizeof(int));
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
            
            //Iterative Merge Sort Commencement
            for (int n = 1; n < N; n*=2) {
                for (int i = 0; i < N-1; i+=2*n) {
                    int l = i;
                    int m;
                    if (N <= i+n) m = N-1;
                    else m = i+n-1;
                    int r;
                    if (N <= i+2*n) r = N-1;
                    else r = i+2*n-1;
                    
                    int N1 = m-l+1;
                    int N2 = r-m;
                    int L[N1], R[N2];
                    for (int j = 0; j < N1; j++) L[j] = B[l+j];
                    for (int j = 0; j < N2; j++) R[j] = B[m+j+1];
                    
                    //merge
                    int i1 = 0, i2 = 0, i3 = l;
                    while(i1 < N1 && i2 < N2) {
                        if (L[i1] <= R[i2]) {
                            B[i3] = L[i1];
                            i1++;
                        } else {
                            B[i3] = R[i2];
                            i2++;
                        }
                        i3++;
                    }
                    
                    while(i1 < N1) {
                        B[i3] = L[i1];
                        i1++;
                        i3++;
                    }
                    
                    while(i2 < N2) {
                        B[i3] = R[i2];
                        i2++;
                        i3++;
                    }
                }
            }
            //Iterative Merge Sort Conclusion
            
            if (wish == 'Y' || wish == 'y') {
                t = clock() - t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                if (time_taken > 180) printf("Time exceeds 3 minutes.\n");
                else printf("Time Taken: %lf\n", time_taken);
            }
            
            printf("\n");
            view = 'a';
            while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
                printf("Do you want to view the sorted array? (Y/N): ");
                scanf(" %c", &view);
                
                if (view == 'Y' || view == 'y') {
                    printf("\nIterative Merge Sort -> Sorted Array: \n");
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
        printf("Do you want to sort using RECURSIVE MERGE SORT? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            clock_t t;
            double time_taken;
            printf("\n-----RECURSIVE MERGE SORT-----\n"); //Best - O(nlogn), Avg - O(nlogn), Worst - O(nlogn)
            int* B = (int*)malloc(N*sizeof(int));
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
            
            //Recursive Merge Sort Commencement
            mergeSort(B, 0, N-1);
            //Recursive Merge Sort Conclusion
            
            if (wish == 'Y' || wish == 'y') {
                t = clock() - t;
                time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                if (time_taken > 180) printf("Time exceeds 3 minutes.\n");
                else printf("Time Taken: %lf\n", time_taken);
            }
            
            printf("\n");
            view = 'a';
            while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
                printf("Do you want to view the sorted array? (Y/N): ");
                scanf(" %c", &view);
                
                if (view == 'Y' || view == 'y') {
                    printf("\nRecursive Merge Sort -> Sorted Array: \n");
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
