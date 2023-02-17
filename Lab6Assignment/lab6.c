#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

//Median of Medians Algorithm
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

int partition(int *A, int N, int m) {
    for(int i = 0; i < N; i++) {
	    if(A[i] == m) {
	        A[i] = A[N-1];
	        A[N-1] = m;
        }
    }

    int i = 0;
    for(int j = 0; j < N-1; j++) {
	    if(A[j] <= m) {
	    int temp = A[j];
	    A[j] = A[i];
	    A[i] = temp;
	    i++;
	    }
    }

    A[N-1] = A[i];
    A[i] = m;

    return i;
}

void insertionSort(int *A, int N) {
    for (int i = 1; i < N; i++) {
        int key = A[i];
                
        int j = i-1;
        while(j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}

int selectI(int *A, int i, int N) {
    if(N == 1) return A[0];

    int n_meds = 0;
    for(int j = 0; j < N; j += 5) {
        int l;
        if (N-j < 5) l = N-j;
        else l = 5;
	    insertionSort(A+i, l);
	    
        int temp = A[i/5];
	    A[i/5] = A[i + l/2];
	    A[i + l/2] = temp;

	    n_meds++;
    }

    int median_of_medians;
    if(n_meds > 1) {
        median_of_medians = selectI(A, n_meds/2, n_meds);
    } else {
	    median_of_medians = A[0];
    }

    int k = partition(A, N, median_of_medians);

    if(k == i) {
	    return median_of_medians;
    } else if (i < k) {
	    return selectI(A, i, k);
    } else {
        return selectI(A+k, i-k, N-k);
    }
}

int selectM(int *A, int i, int N) {
    if(N == 1) return A[0];

    int n_meds = 0;
    for(int j = 0; j < N; j += 5) {
        int l;
        if (N-j < 5) l = N-j;
        else l = 5;
        mergeSort(A+i, 0, l-1);
	    
        int temp = A[i/5];
	    A[i/5] = A[i + l/2];
	    A[i + l/2] = temp;

	    n_meds++;
    }

    int median_of_medians;
    if(n_meds > 1) {
        median_of_medians = selectM(A, n_meds/2, n_meds);
    } else {
	    median_of_medians = A[0];
    }

    int k = partition(A, N, median_of_medians);

    if(k == i) {
	    return median_of_medians;
    } else if (i < k) {
	    return selectM(A, i, k);
    } else {
        return selectM(A+k, i-k, N-k);
    }
}

int selectH(int *A, int i, int N) {
    if(N == 1) return A[0];

    int n_meds = 0;
    for(int j = 0; j < N; j += 5) {
        int l;
        if (N-j < 5) l = N-j;
        else l = 5;
        heapSort(A+i, l);
	    
        int temp = A[i/5];
	    A[i/5] = A[i + l/2];
	    A[i + l/2] = temp;

	    n_meds++;
    }

    int median_of_medians;
    if(n_meds > 1) {
        median_of_medians = selectH(A, n_meds/2, n_meds);
    } else {
	    median_of_medians = A[0];
    }

    int k = partition(A, N, median_of_medians);

    if(k == i) {
	    return median_of_medians;
    } else if (i < k) {
	    return selectH(A, i, k);
    } else {
        return selectH(A+k, i-k, N-k);
    }
}

void medianOfMedians() {
    int N;
    printf("Enter the array length: ");
    scanf("%d", &N);
    randomNumberGenerator(N, 0);

    FILE * random = fopen("random.txt", "r");
    int A[N];
    for (int i = 0; i < N; i++) fscanf(random, "%d", &A[i]);
    fclose(random);

    char view = 'a';
    while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
        printf("\nDo you want to view the array of the generated integers? (Y/N): ");
        scanf(" %c", &view);
                
        if (view == 'Y' || view == 'y') {
            printf("\nArray of Integers: \n");
            for (int i = 0; i < N; i++) printf("%d ", A[i]);
            printf("\n");
        } else if (view == 'N' || view == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }

    int median = selectI(A, N/2, N);
    printf("\nThe median is %d.\n", median);

    //Now, let's compare time taken by Merge sort and Heap sort
    clock_t t1, t2;
    double time_taken1, time_taken2;

    t1 = clock();
    selectM(A, N/2, N);
    t1 = clock()-t1;
    time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds

    t2 = clock();
    selectH(A, N/2, N);
    t2 = clock()-t2;
    time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds

    printf("\n");
    printf("Time Taken by Merge Sort: %lf\n", time_taken1);
    printf("Time Taken by Heap Sort: %lf\n", time_taken2);
    if (time_taken1 < time_taken2) printf("Merge Sort is faster in case of N = %d.\n", N);
    else if (time_taken1 == time_taken2) printf("Time taken by both the sorts are comparable in case of N = %d.\n", N);
    else printf("Heap Sort is faster in case of N = %d.\n", N);
}
//

//MatrixMultiplication
void multiplyM(long long int** A, long long int** B, int N, long long int** C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}

void add(long long int **A, long long int **B, int N, long long int **C){       
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            C[i][j] = A[i][j] + B[i][j];   
        }
    }
}

void sub(long long int **A, long long int **B, int N, long long int **C){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            C[i][j]= A[i][j] - B[i][j];
        }
    }
}

void multiply(long long int **A, long long int** B, int N, int n2, long long int** C) {
    if (N == 1) {
        C[0][0] = A[0][0]*B[0][0];
    } else {
        int n = N/2;
        long long int **A11 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            A11[i]= malloc(n*sizeof(long long int));
        }
        long long int **A12 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            A12[i]= malloc(n*sizeof(long long int));
        }
        long long int **A21 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            A21[i]= malloc(n*sizeof(long long int));
        }
        long long int **A22 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            A22[i]= malloc(n*sizeof(long long int));
        }
        long long int **B11 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            B11[i]= malloc(n*sizeof(long long int));
        }
        long long int **B12 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            B12[i]= malloc(n*sizeof(long long int));
        }
        long long int **B21 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            B21[i]= malloc(n*sizeof(long long int));
        }
        long long int **B22 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            B22[i]= malloc(n*sizeof(long long int));
        }

        long long int **P = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            P[i]= malloc(n*sizeof(long long int));
        }
        long long int **Q = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            Q[i]= malloc(n*sizeof(long long int));
        }
        long long int **R = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            R[i]= malloc(n*sizeof(long long int));
        }
        long long int **S = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            S[i]= malloc(n*sizeof(long long int));
        }
        long long int **T = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            T[i]= malloc(n*sizeof(long long int));
        }
        long long int **U = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            U[i]= malloc(n*sizeof(long long int));
        }
        long long int **V = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            V[i]= malloc(n*sizeof(long long int));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][n+j];
                A21[i][j] = A[n+i][j];
                A22[i][j] = A[n+i][n+j];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][n+j];
                B21[i][j] = B[n+i][j];
                B22[i][j] = B[n+i][n+j];
            }
        }

        long long int **temp1 = malloc(n*sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp1[i] = malloc(n*sizeof(long long int));
        }
        long long int **temp2 = malloc(n*sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp2[i] = malloc(n*sizeof(long long int));
        }
        sub(A12, A22, n, temp1);
        add(B21, B22, n, temp2);
        multiply(temp1, temp2, n, N, P);
        free(temp1);
        free(temp2);

        long long int **temp3 = malloc(n*sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp3[i] = malloc(n*sizeof(long long int));
        }
        long long int **temp4 = malloc(n*sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp4[i] = malloc(n*sizeof(long long int));
        }
        add(A11, A22, n, temp3);
        add(B11, B22, n, temp4);
        multiply(temp3, temp4, n, N, Q);
        free(temp3);
        free(temp4);

        long long int **temp5 = malloc(n*sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp5[i] = malloc(n*sizeof(long long int));
        }
        long long int **temp6 = malloc(n*sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp6[i] = malloc(n*sizeof(long long int));
        }
        sub(A11, A21, n, temp5);
        add(B11, B12, n, temp6);
        multiply(temp5, temp6, n, N, R);
        free(temp5);
        free(temp6);

        long long int **temp7 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp7[i]= malloc(n*sizeof(long long int));
        }       
        add(A11, A12, n, temp7);
        multiply(temp7, B22, n, N, S);
        free(temp7);

        long long int **temp8 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp8[i]= malloc(n*sizeof(long long int));
        }       
        add(A21, A22, n, temp8);
        multiply(temp8, B11, n, N, T);
        free(temp8);

        long long int **temp9 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp9[i]= malloc(n*sizeof(long long int));
        }       
        sub(B12, B22, n, temp9);
        multiply(A11, temp9, n, N, U);
        free(temp9);

        long long int **temp10 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            temp10[i]= malloc(n*sizeof(long long int));
        }       
        sub(B21, B11, n, temp10);
        multiply(A22, temp10, n, N, V);
        free(temp10);

        long long int **t1 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            t1[i]= malloc(n*sizeof(long long int));
        }   
        long long int **t2 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            t2[i]= malloc(n*sizeof(long long int));
        } 
        long long int **t3 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            t3[i]= malloc(n*sizeof(long long int));
        } 
        long long int **t4 = malloc(n * sizeof(long long int *));
        for(int i = 0; i < n; i++){
            t4[i]= malloc(n*sizeof(long long int));
        }  

        //alpha
        add(P, Q, n,t1);
        sub(t1, S, n, t1);
        add(t1, V, n, t1);

        //beta
        sub(Q, R, n, t2);
        add(t2, U, n, t2);
        sub(t2, T, n, t2);

        //gamma
        add(V, T, n, t3);

        //delta   
        add(S, U, n, t4);

        //matrix:
        //alpha delta
        //gamma beta

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(j >= 0 && j < n && i >= 0 && i < n){
                    C[i][j] = t1[i][j];
                }
                if(j >= n && j < N && i >= 0 && i < n){
                    int a = j-n;
                    C[i][j] = t4[i][a];
                }
                if(j >= 0 && j < n && i >= n && i < N){
                    int c = i-n;
                    C[i][j] = t3[c][j];
                }
                if(j >= n && j < N && i >= n && i < N){
                    int d = i-n;
                    int e = j-n;
                    C[i][j] = t2[d][e];
                }
            }
        }

        free(P);
        free(Q);
        free(R);
        free(S);
        free(T);
        free(U);
        free(V);
        free(t1);
        free(t2);
        free(t3);
        free(t4);
    }
}
//

void matrix() {
    int k;
    printf("Enter the value of k: ");
    scanf("%d", &k);
    int N = (long long int) pow(2, k);

    srand(time(0));
    long long int **A = malloc(N * sizeof(long long int *));
    for(int i = 0; i < N; i++){
        A[i]= malloc(N*sizeof(long long int));
    } 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand()%100; //0 to 99
        }
    }

    long long int **B = malloc(N * sizeof(long long int *));
    for(int i = 0; i < N; i++){
        B[i]= malloc(N*sizeof(long long int));
    } 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = rand()%100; //0 to 99
        }
    }

    char view = 'a';
    while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
        printf("\nDo you want to view Matrices A and B? (Y/N): ");
        scanf(" %c", &view);
                
        if (view == 'Y' || view == 'y') {
            printf("\nMatrix A: \n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%lld ", A[i][j]);
                }
                printf("\n");
            }
            printf("\nMatrix B: \n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%lld ", B[i][j]);
                }
                printf("\n");
            }
        } else if (view == 'N' || view == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }

    clock_t t1, t2;
    double time_taken1, time_taken2;

    long long int **C1 = malloc(N * sizeof(long long int *));
    for(int i = 0; i < N; i++){
        C1[i]= malloc(N*sizeof(long long int));
    } 
    t1 = clock();
    multiply(A, B, N, N, C1);
    t1 = clock()-t1;
    time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds
    if (time_taken1 > 180) printf("Time exceeds 3 minutes.\n");
    else printf("\nTime Taken: %lf\n", time_taken1);

    view = 'a';
    while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
        printf("\nDo you want to view the result matrix? (Y/N): ");
        scanf(" %c", &view);
                
        if (view == 'Y' || view == 'y') {
            printf("\nResult Matrix: \n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("%lld ", C1[i][j]);
                }
                printf("\n");
            }
        } else if (view == 'N' || view == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }

    printf("\n");
    char choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("Do you want to use the usual matrix multiplication method too? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            long long int **C2 = malloc(N * sizeof(long long int *));
            for(int i = 0; i < N; i++){
                C2[i]= malloc(N*sizeof(long long int));
            } 
            t2 = clock();
            multiplyM(A, B, N, C2);
            t2 = clock()-t2;
            time_taken2 = ((double)t2)/CLOCKS_PER_SEC; // in seconds
            if (time_taken2 > 180) printf("Time exceeds 3 minutes.\n");
            else printf("\nTime Taken: %lf\n", time_taken2);
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }
}

int main() {
    int choice;
    printf("Enter your choice: \n1. Median of Medians Algorithm\n2. Strassen's Algorithm\n3. Exit\n");
    scanf("%d", &choice);

    while(choice != 3) {
        if (choice == 1) medianOfMedians();
        else if (choice == 2) matrix();
        else if (choice == 3) break;
        else printf("Wrong Choice!\n");
        
        printf("\nEnter your choice: \n1. Median of Medians Algorithm\n2. Strassen's Algorithm\n3. Exit\n");
        scanf("%d", &choice);
    }

    printf("\n-----ALL TASKS REVIEWED-----\n");
}