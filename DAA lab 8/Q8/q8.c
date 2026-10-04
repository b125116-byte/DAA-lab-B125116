#include <stdio.h>
#include <stdlib.h>
#include <float.h>
static int N, W;           
static int *root;
#define R(i,j) root[(i)*W+(j)]
static void show(int i, int j, int parent, const char *side){
    if (i > j) {
        printf("  d%d is the %s child of k%d\n", j, side, parent);
        return;
    }
    int r = R(i,j);
    if (parent == 0) printf("  k%d is the root\n", r);
    else printf("  k%d is the %s child of k%d\n", r, side, parent);
    show(i, r - 1, r, "left");
    show(r + 1, j, r, "right");
}
int main(){
    int n;
    if (scanf("%d", &n) != 1) return 1;
    N = n; W = n + 2;
    double *p = calloc(n + 2, sizeof(double)), *q = calloc(n + 2, sizeof(double));
    for (int i = 1; i <= n; i++) scanf("%lf", &p[i]);
    for (int i = 0; i <= n; i++) scanf("%lf", &q[i]);
    double *e = calloc(W * W, sizeof(double)), *w = calloc(W * W, sizeof(double));
    root = calloc(W * W, sizeof(int));
    #define E(i,j) e[(i)*W+(j)]
    #define Wt(i,j) w[(i)*W+(j)]
    for (int i = 1; i <= n + 1; i++) { E(i,i-1) = q[i-1]; Wt(i,i-1) = q[i-1]; }
    for (int len = 1; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            E(i,j) = DBL_MAX;
            Wt(i,j) = Wt(i,j-1) + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = E(i,r-1) + E(r+1,j) + Wt(i,j);
                if (t < E(i,j)) { E(i,j) = t; R(i,j) = r; }
            }
        }
    printf("Minimum expected search cost = %.4f\nTree structure:\n", E(1,n));
    show(1, n, 0, "");
    free(p); 
  free(q); 
  free(e); 
  free(w); 
  free(root);
    return 0;
}
