#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <float.h>

typedef struct Point Point;

struct Point {
    int x, y;
};

void randomNumberGenerator(int N) {
    FILE * random = fopen("random.txt", "w");
    
    srand(time(0));
    for (int i = 0; i < N; i++) {
        int x = 2*(rand()%1000001) - 1000000; //-1000000 to 1000000
        fprintf(random, "%d ", x);
    }
    
    fclose(random);
}

int compareX(const void* a, const void* b) {
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

double dist(Point p1, Point p2) {
    return sqrt(((double) (p1.x - p2.x)*(p1.x - p2.x)) + ((double) (p1.y - p2.y)*(p1.y - p2.y)));
}

double bruteForce(Point* P, int n, Point* ans) {
    double m = DBL_MAX;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (dist(P[i], P[j]) < m) {
                m = dist(P[i], P[j]);
                ans[0] = P[i];
                ans[1] = P[j];
            }
        }
    }

    return m;
}

double stripClosest(Point* strip, int n, double d, Point* ans) {
    double m = d;

    qsort(strip, n, sizeof(Point), compareY);

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n && (strip[j].y - strip[i].y) < m; j++) {
            if (dist(strip[i], strip[j]) < m) {
                m = dist(strip[i], strip[j]);
                ans[0] = strip[i];
                ans[1] = strip[j];
            }
        }
    }

    return m;
}

double closestUtil(Point* P, int n, Point* ans) {
    if (n <= 3) return bruteForce(P, n, ans);

    int mid = n/2;
    Point midPoint = P[mid];

    Point* ans1 = (Point *)malloc(2*sizeof(Point));
    ans1[0].x = 0;
    ans1[0].y = 0;
    ans1[1].x = 0;
    ans1[1].y = 0;
    double dl = closestUtil(P, mid, ans1);

    Point* ans2 = (Point *)malloc(2*sizeof(Point));
    ans2[0].x = 0;
    ans2[0].y = 0;
    ans2[1].x = 0;
    ans2[1].y = 0;
    double dr = closestUtil(P+mid, n-mid, ans2);

    double d;
    if (dl < dr) {
        d = dl;
        ans[0].x = ans1[0].x;
        ans[0].y = ans1[0].y;
        ans[1].x = ans1[1].x;
        ans[1].y = ans1[1].y;
    } else {
        d = dr;
        ans[0].x = ans2[0].x;
        ans[0].y = ans2[0].y;
        ans[1].x = ans2[1].x;
        ans[1].y = ans2[1].y;
    }

    free(ans1);
    free(ans2);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (abs(P[i].x - midPoint.x) < d) {
            strip[j] = P[i];
            j++;
        }
    }

    Point* ans3 = (Point *)malloc(2*sizeof(Point));
    ans3[0].x = 0;
    ans3[0].y = 0;
    ans3[1].x = 0;
    ans3[1].y = 0;

    double res = stripClosest(strip, j, d, ans3);
    if (res < d) {
        ans[0].x = ans3[0].x;
        ans[0].y = ans3[0].y;
        ans[1].x = ans3[1].x;
        ans[1].y = ans3[1].y;
        return res;
    } else return d;
}

double closest(Point* P, int n, Point* ans) {
    qsort(P, n, sizeof(Point), compareX);

    return closestUtil(P, n, ans);
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    randomNumberGenerator(2*n);

    FILE * random = fopen("random.txt", "r");
    Point P[n];
    for (int i = 0; i < n; i++) {
        fscanf(random, "%d", &P[i].x);
        fscanf(random, "%d", &P[i].y);
    }
    fclose(random);

    char view = 'a';
    while(view != 'Y' && view != 'y' && view != 'N' && view != 'n') {
        printf("\nDo you want to view points? (Y/N): ");
        scanf(" %c", &view);
                
        if (view == 'Y' || view == 'y') {
            printf("\nPoints: \n");
            for (int i = 0; i < n; i++) {
                printf("Point #%d: (%d, %d)\n", i+1, P[i].x, P[i].y);
            }
        } else if (view == 'N' || view == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }

    printf("\n");
    char choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("Do you want to use O(n^2) method? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            //O(n^2)
            clock_t t;
            double time_taken;

            Point* ans = (Point *)malloc(2*sizeof(Point));
            ans[0].x = 0;
            ans[0].y = 0;
            ans[1].x = 0;
            ans[1].y = 0;

            printf("\n-----O(n^2) METHOD-----\n");
            t = clock();
            printf("The distance between the closest pair(s) is: %lf.\n", bruteForce(P, n, ans));
            printf("The closest pair is: (%d, %d) and (%d, %d).\n", ans[0].x, ans[0].y, ans[1].x, ans[1].y);
            t = clock()-t;
            time_taken = ((double)t)/CLOCKS_PER_SEC;
            if (time_taken <= 180) printf("Time Taken: %lf seconds.\n", time_taken);
            else printf("Time exceeds 3 minutes.\n");
            //
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }

    printf("\n");
    choice = 'a';
    while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
        printf("Do you want to use O(nlogn) method? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            //O(nlogn)
            clock_t t;
            double time_taken;

            Point* ans = (Point *)malloc(2*sizeof(Point));
            ans[0].x = 0;
            ans[0].y = 0;
            ans[1].x = 0;
            ans[1].y = 0;

            printf("\n-----O(nlogn) METHOD-----\n");
            t = clock();
            printf("The distance between the closest pair(s) is: %lf.\n", closest(P, n, ans));
            printf("The closest pair is: (%d, %d) and (%d, %d).\n", ans[0].x, ans[0].y, ans[1].x, ans[1].y);
            t = clock()-t;
            time_taken = ((double)t)/CLOCKS_PER_SEC;
            if (time_taken <= 180) printf("Time Taken: %lf seconds.\n", time_taken);
            else printf("Time exceeds 3 minutes.\n");
            //
        } else if (choice == 'N' || choice == 'n') break;
        else printf("Wrong Input! Enter again.\n\n");
    }

    printf("\n-----ALL TASKS REVIEWED-----\n");
}
