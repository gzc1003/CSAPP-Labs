/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include "cachelab.h"
#include <stdio.h>

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj;
    int bsize = 8;
    for (i = 0; i < M; i += bsize)
        for (j = 0; j < N; j += bsize)
            for (ii = i; ii < i + bsize; ii++) {
                for (jj = j; jj < j + bsize; jj++) {
                    if (ii != jj)
                        B[jj][ii] = A[ii][jj];
                }
                if (i == j) {
                    B[ii][ii] = A[ii][ii];
                }
            }
}

char transpose_submit_desc64[] = "Transpose submission64";
void transpose_submit64(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj;
    int bsize = 4;
    for (i = 0; i < M; i += bsize)
        for (j = 0; j < N; j += bsize)
            for (ii = i; ii < i + bsize; ii++) {
                for (jj = j; jj < j + bsize; jj++) {
                    if (ii != jj)
                        B[jj][ii] = A[ii][jj];
                }
                if (i == j) {
                    B[ii][ii] = A[ii][ii];
                }
            }
}

char transpose_submit_desc64_2[] = "Transpose submission64_2";
void transpose_submit64_2(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj, iii, jjj;
    int bsize = 8, bbsize = 4;
    for (i = 0; i < M; i += bsize)
        for (j = 0; j < N; j += bsize)
            for (ii = i; ii < i + bsize; ii += bbsize) {
                if (ii == i) {
                    for (jj = j; jj < j + bsize; jj += bbsize)
                        for (iii = ii; iii < ii + bbsize; iii++) {
                            for (jjj = jj; jjj < jj + bbsize; jjj++) {
                                if (iii != jjj)
                                    B[jjj][iii] = A[iii][jjj];
                            }
                            if (ii == jj)
                                B[iii][iii] = A[iii][iii];
                        }
                } else {
                    for (jj = j + bbsize; jj >= j; jj -= bbsize)
                        for (iii = ii; iii < ii + bbsize; iii++) {
                            for (jjj = jj; jjj < jj + bbsize; jjj++) {
                                if (iii != jjj)
                                    B[jjj][iii] = A[iii][jjj];
                            }
                            if (ii == jj)
                                B[iii][iii] = A[iii][iii];
                        }
                }
            }
}

char transpose_submit_desc64_3[] = "Transpose submission64_3";
void transpose_submit64_3(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj, iii, jjj;
    int bsize = 8, bbsize = 4;
    for (i = 0; i < M; i += bsize)
        for (j = 0; j < N; j += bsize)
            for (ii = i; ii < i + bsize; ii += bbsize) {
                if (ii == i) {
                    for (jj = j; jj < j + bsize; jj += bbsize)
                        for (iii = ii; iii < ii + bbsize; iii++) {
                            for (jjj = jj; jjj < jj + bbsize; jjj++) {
                                if ((i != j) || (iii - ii != jjj - jj))
                                    B[jjj][iii] = A[iii][jjj];
                            }
                            if (i == j)
                                B[iii - ii + jj][iii] = A[iii][iii - ii + jj];
                        }
                } else {
                    for (jj = j + bbsize; jj >= j; jj -= bbsize)
                        for (iii = ii; iii < ii + bbsize; iii++) {
                            for (jjj = jj; jjj < jj + bbsize; jjj++) {
                                if ((i != j) || (iii - ii != jjj - jj))
                                    B[jjj][iii] = A[iii][jjj];
                            }
                            if (i == j)
                                B[iii - ii + jj][iii] = A[iii][iii - ii + jj];
                        }
                }
            }
}

char transpose_submit_desc64_4[] = "Transpose submission64_4";
void transpose_submit64_4(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj, iii;
    int bsize = 8, bbsize = 4;
    int a, b, c, d;
    for (i = 0; i < M; i += bsize)
        for (j = 0; j < N; j += bsize)
            for (ii = i; ii < i + bsize; ii += bbsize) {
                if (ii == i) {
                    for (jj = j; jj < j + bsize; jj += bbsize)
                        for (iii = ii; iii < ii + bbsize; iii++) {
                            a = A[iii][jj];
                            b = A[iii][jj + 1];
                            c = A[iii][jj + 2];
                            d = A[iii][jj + 3];

                            B[jj][iii] = a;
                            B[jj + 1][iii] = b;
                            B[jj + 2][iii] = c;
                            B[jj + 3][iii] = d;
                        }
                } else {
                    for (jj = j + bbsize; jj >= j; jj -= bbsize)
                        for (iii = ii; iii < ii + bbsize; iii++) {
                            a = A[iii][jj];
                            b = A[iii][jj + 1];
                            c = A[iii][jj + 2];
                            d = A[iii][jj + 3];

                            B[jj][iii] = a;
                            B[jj + 1][iii] = b;
                            B[jj + 2][iii] = c;
                            B[jj + 3][iii] = d;
                        }
                }
            }
}

char transpose_submit_desc61[] = "Transpose submission61";
void transpose_submit61(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj;
    int bsize = 16;
    for (i = 0; i < N; i += bsize)
        for (j = 0; j < M; j += bsize)
            for (ii = i; ii < i + bsize && ii < N; ii++)
                for (jj = j; jj < j + bsize && jj < M; jj++)
                    B[jj][ii] = A[ii][jj];
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the
 * cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);
    registerTransFunction(transpose_submit64, transpose_submit_desc64);
    registerTransFunction(transpose_submit64_2, transpose_submit_desc64_2);
    registerTransFunction(transpose_submit64_3, transpose_submit_desc64_3);
    registerTransFunction(transpose_submit64_4, transpose_submit_desc64_4);
    registerTransFunction(transpose_submit61, transpose_submit_desc61);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
