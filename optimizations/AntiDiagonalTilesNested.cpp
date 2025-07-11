// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "helper.h"
#define loop(i, k, n) for (int i = k; i < n; i++)
using namespace std;

void Needleman_Wunsch_optv7(string &A, string &B, int match, int mismatch, int gap) {
    int szseq1 = A.size();
    int szseq2 = B.size();
    int **dp = new int *[szseq1 + 1];
    for (int i = 0; i <= szseq1; i++) {
        dp[i] = new int[szseq2 + 1];
    }
    double gflops = 6 * szseq1 * szseq2;
    struct timeval t;
    tick(&t);
    if (szseq1 > szseq2) {
        swap(szseq1, szseq2);
        swap(A, B);
    }
#pragma omp parallel for
    loop(i, 0, szseq1 + 1) {
        dp[i][0] = i * gap;
    }
#pragma omp parallel for
    loop(i, 0, szseq2 + 1) {
        dp[0][i] = i * gap;
    }
    // columns more than rows
    int tilesize = min(szseq1 + 1, szseq2 + 1)/omp_get_max_threads() + 1;
    int ntiles = (szseq1 + 1) / tilesize;
    int ntiles2 = (szseq2 + 1) / tilesize;
    // cout << tilesize << "\n";
    loop(i, 0, ntiles2) {
        int iters = min(i + 1, ntiles);
        int start_col_tile = i;
        int start_row_tile = 0;
#pragma omp parallel for
        for (int j = 0; j < iters; j++) {
            for (int col = (start_col_tile - j) * tilesize; col < (start_col_tile - j + 1) * tilesize; col++) {
                int iters2 = min(col - ((start_col_tile - j) * tilesize) + 1, tilesize);
                int curr_row = (start_row_tile + j) * tilesize;
#pragma omp parallel for
                for (int l = 0; l < iters2; l++) {
                    if (((col - l) == 0 or (curr_row + l) == 0)) continue;
                    // computing dp[start_row+l][start_col-l]
                    char seqAati = A[curr_row + l - 1];
                    char seqBatj = B[col - l - 1];
                    int matchdiag = dp[curr_row + l - 1][col - l - 1] + (seqAati == seqBatj ? match : mismatch);
                    int gapA = dp[curr_row + l - 1][col - l] + gap;
                    int gapB = dp[curr_row + l][col - l - 1] + gap;
                    dp[curr_row + l][col - l] = max(max(gapA, gapB), matchdiag);
                }
            }
            for (int row = (start_row_tile + j) * tilesize + 1; row < (start_row_tile + j + 1) * tilesize; row++) {
                int iters2 = (start_row_tile + j + 1) * tilesize - row;
                int curr_col = (start_col_tile - j + 1) * tilesize - 1;
#pragma omp parallel for
                for (int l = 0; l < iters2; l++) {
                    if (((curr_col - l) == 0 or (row + l) == 0)) continue;
                    // computing dp[start_row+l][start_col-l]
                    char seqAati = A[row + l - 1];
                    char seqBatj = B[curr_col - l - 1];
                    int matchdiag = dp[row + l - 1][curr_col - l - 1] + (seqAati == seqBatj ? match : mismatch);
                    int gapA = dp[row + l - 1][curr_col - l] + gap;
                    int gapB = dp[row + l][curr_col - l - 1] + gap;
                    dp[row + l][curr_col - l] = max(max(gapA, gapB), matchdiag);
                }
            }
        }
    }
    loop(i, 1, ntiles) {
        int iters = ntiles - i;
        int start_col_tile = ntiles2 - 1;
        int start_row_tile = i;
#pragma omp parallel for
        for (int j = 0; j < iters; j++) {
            for (int col = (start_col_tile - j) * tilesize; col < (start_col_tile - j + 1) * tilesize; col++) {
                int iters2 = min(col - ((start_col_tile - j) * tilesize) + 1, tilesize);
                int curr_row = (start_row_tile + j) * tilesize;
#pragma omp parallel for
                for (int l = 0; l < iters2; l++) {
                    if (((col - l) == 0 or (curr_row + l) == 0)) continue;
                    // computing dp[start_row+l][start_col-l]
                    char seqAati = A[curr_row + l - 1];
                    char seqBatj = B[col - l - 1];
                    int matchdiag = dp[curr_row + l - 1][col - l - 1] + (seqAati == seqBatj ? match : mismatch);
                    int gapA = dp[curr_row + l - 1][col - l] + gap;
                    int gapB = dp[curr_row + l][col - l - 1] + gap;
                    dp[curr_row + l][col - l] = max(max(gapA, gapB), matchdiag);
                }
            }
            for (int row = (start_row_tile + j) * tilesize + 1; row < (start_row_tile + j + 1) * tilesize; row++) {
                int iters2 = (start_row_tile + j + 1) * tilesize - row;
                int curr_col = (start_col_tile - j + 1) * tilesize - 1;
#pragma omp parallel for
                for (int l = 0; l < iters2; l++) {
                    if (((curr_col - l) == 0 or (row + l) == 0)) continue;
                    // computing dp[start_row+l][start_col-l]
                    char seqAati = A[row + l - 1];
                    char seqBatj = B[curr_col - l - 1];
                    int matchdiag = dp[row + l - 1][curr_col - l - 1] + (seqAati == seqBatj ? match : mismatch);
                    int gapA = dp[row + l - 1][curr_col - l] + gap;
                    int gapB = dp[row + l][curr_col - l - 1] + gap;
                    dp[row + l][curr_col - l] = max(max(gapA, gapB), matchdiag);
                }
            }
        }
    }
    for (int i = 1; i < ntiles * tilesize; i++) {
        for (int j = ntiles2 * tilesize; j < szseq2 + 1; j++) {
            char seqAati = A[i - 1];
            char seqBatj = B[j - 1];
            int matchdiag = dp[i - 1][j - 1] + (seqAati == seqBatj ? match : mismatch);
            int gapA = dp[i][j - 1] + gap;
            int gapB = dp[i - 1][j] + gap;
            dp[i][j] = max(max(gapA, gapB), matchdiag);
        }
    }
    for (int i = ntiles * tilesize; i < szseq1 + 1; i++) {
        for (int j = 1; j < szseq2 + 1; j++) {
            // i,j th tile
            char seqAati = A[i - 1];
            char seqBatj = B[j - 1];
            int matchdiag = dp[i - 1][j - 1] + (seqAati == seqBatj ? match : mismatch);
            int gapA = dp[i][j - 1] + gap;
            int gapB = dp[i - 1][j] + gap;
            dp[i][j] = max(max(gapA, gapB), matchdiag);
        }
    }
    // i , j th tile
    double time = tock(&t);
    cout << "Exec Time: " << time * 1000 << "\n";
    cout << "GIPS: " << gflops / time / 1e9 << "\n";
}
