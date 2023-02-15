#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Linear time selection algorithm
//Merge and Heap Sort
//Strassen's algorithm

void display(int A[], int N) {
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
}

void randomNumberGenerator(int N, int need) {
    FILE * random = fopen("random.txt", "w");
    
    srand(time(0));
    if (need == 0) {
        for (int i = 0; i < N; i++) {
            int x = rand()%1000000; //0 to 999999
            fprintf(random, "%d ", x);
        }
    } else {
        for (int i = 0; i < N; i++) {
            int x = rand()%100; //0 to 99
            fprintf(random, "%d ", x);
        }
    }
    
    fclose(random);
}

void strassensAlgorithm();

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
//

void mergeVsHeap() {
    int N;
    printf("Enter the array length: ");
    scanf("%d", &N);

    double t1_avg, t2_avg;
    for (int i = 0; i < 1000; i++) {
        randomNumberGenerator(N, 0);

        FILE * random = fopen("random.txt", "r");
        int A[N];
        for (int i = 0; i < N; i++) fscanf(random, "%d", &A[i]);
        fclose(random);

        clock_t t1, t2;
        double time_taken1, time_taken2;

        int * B = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) B[i] = A[i];
        t1 = clock();
        mergeSort(B, 0, N-1);
        t1 = clock()-t1;
        time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds
        t1_avg += time_taken1;

        int * C = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) C[i] = A[i];
        t2 = clock();
        heapSort(C, N);
        t2 = clock()-t2;
        time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
        t2_avg += time_taken2;
    }

    t1_avg /= 1000;
    t2_avg /= 1000;

    printf("Merge sort: Average Time Taken: %lf", t1_avg);
    printf("Heap sort: Average Time Taken: %lf", t2_avg);
}

//Recursive Heap Sort - Max Heap
void heapify(int A[], int N, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
 
    if (left < N && A[left] > A[largest]) largest = left;
    if (right < N && A[right] > A[largest]) largest = right;
 
    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        heapify(A, N, largest);
    }
}

void heapSort(int A[], int N) {
    for (int i = N/2-1; i >= 0; i--) heapify(A, N, i);

    for (int i = N-1; i >= 0; i--) {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        heapify(A, i, 0);
    }
}
//

// int kthSmallest(int A[], int l, int r, int k) {
//     if (k > 0 && k < l-r) {
//         int n = r-l+1;
//         int i, median[(n+4)/5];

//         for (int i = 0; i < n/5; i++) {
//             median[i] = findMedian(A+l);
//         }
//     }
// }

void medianOfMedians() {
    int N;
    printf("Enter the array length: ");
    scanf("%d", &N);
    randomNumberGenerator(N, 0);

    FILE * random = fopen("random.txt", "r");
    int A[N];
    for (int i = 0; i < N; i++) fscanf(random, "%d", &A[i]);
    fclose(random);

    //kthSmallest(A, l, r, 3);
}

int main() {
    int choice;
    printf("Enter your choice: \n1. Median of Medians Algorithm\n2. Merge vs Heap Sort\n3. Strassen's Algorithm\n4. Exit\n");
    scanf("%d", &choice);

    while(choice != 4) {
        if (choice == 1) medianOfMedians();
        else if (choice == 2) mergeVsHeap();
        else if (choice == 3) strassensAlgorithm();
        else if (choice == 4) break;
        else printf("Wrong Choice!\n");
        
        printf("\nEnter your choice: \n1. Median of Medians Algorithm\n2. Merge vs Heap Sort\n3. Strassen's Algorithm\n4. Exit\n");
        scanf("%d", &choice);
    }

    printf("\n-----ALL TASKS REVIEWED-----\n");
}
