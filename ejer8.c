#include "stdio.h"
#include "stdlib.h"
#include "omp.h"

void generarPares(int *serie, int inicio, int fin, int incremento, int N) {
    for (int i = inicio; i <= fin; i += incremento) {
        *serie++ = i;
    }
}

int main() {
    const int M = 4; 
    const int N = 10; 
    int *vectores[M];
    int ini, fin, inc;

    #pragma omp parallel num_threads(M)
    {
        int thread_id = omp_get_thread_num();
        vectores[thread_id] = (int *)malloc(N * sizeof(int));

        ini = (thread_id * 2) + 2;
        fin = ini + (N - 1) * M;
        inc = 2 * M;
        generarPares(vectores[thread_id], ini, fin, inc, N);
    }

    for (int i = 0; i < M; ++i) {
        printf("Vector %d: ", i + 1);
        for (int j = 0; j < N; ++j) {
            if(vectores[i][j]>0 && vectores[i][j]<10000){
                printf("%d ", vectores[i][j]);
            }
        }
        printf("\n");
        free(vectores[i]); 
    }

    return 0;
}
