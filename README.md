# Optimizing Needleman–Wunsch Algorithm

This project explores various optimization techniques applied to the well-known Needleman–Wunsch algorithm.  
The Needleman–Wunsch algorithm is a dynamic programming method used to compute the optimal global alignment of two biological sequences (DNA, RNA, or proteins). It works by constructing a scoring matrix based on match, mismatch, and gap penalties, filling that matrix, and then tracing back to find the best alignment.

---

## Scoring Scheme

- **Match:** +1  
- **Mismatch:** −1  
- **Gap:** −2  

A match between characters is rewarded with +1, a mismatch costs −1, and introducing a gap (insertion/deletion) costs −2. This balances similarity against the cost of edits.

---

## 1. Matrix Initialization

We create an `(A+1) × (B+1)` matrix (where `A` and `B` are the lengths of the two sequences), initialize the top‑left cell to `0`, and fill the first row and column with cumulative gap penalties:

| Initial (0,0) = 0                                | First row & column with gap penalties        |
|--------------------------------------------------|----------------------------------------------|
| <img src="https://github.com/user-attachments/assets/0dbc59cb-2050-4334-9c8f-32d608ecdbb8" alt="Initial matrix" width="300"/> | <img src="https://github.com/user-attachments/assets/21dcb25a-0398-4a1b-9003-7d9907dd9b7f" alt="Row/column init" width="300"/> |

---

## 2. Matrix Filling

Starting from the **top‑left**, for each cell `(i,j)` compute three candidate scores:

1. **Diagonal (↖):**  `dp[i-1][j-1] + (match ? +1 : −1)`  
2. **Up (↑):**        `dp[i-1][j] − 2`  
3. **Left (←):**      `dp[i][j-1] − 2`  

Take the **maximum** of those three and store it in `dp[i][j]`. Also record a **back‑pointer** (↖, ↑, or ←) indicating which choice gave the max.

> **Visualization**  
> <img src="https://github.com/user-attachments/assets/9c61238d-efc5-4ae5-8da5-60eb6fc9e770" alt="Matrix filling" width="300"/>

---

## 3. Traceback

Once the matrix is full, start at the **bottom‑right** cell and follow your back‑pointers back to the **top‑left**. Each pointer tells you whether to align a character from both sequences (↖) or introduce a gap in one of them (↑ or ←). If two directions tie, there are multiple equally‐optimal alignments.

> **Traceback example**  
> <img src="https://github.com/user-attachments/assets/850a89f5-2cb0-40c4-90f1-62ccad2bcbf7" alt="Traceback" width="300"/>

---

Now we will look into methods of optimising the algorithm to find the minimum penalty or maximum score i.e the best alignment.
> **Note:** All benchmarks and performance measurements above were conducted on a sample dataset where both input sequences have length **10,000**.

## Program 1: Column‑Traversal Benchmark

In **column.cpp**, we implement the Needleman–Wunsch DP matrix fill using **column‑traversal** over a row‑major layout. This stresses memory access patterns and lets us compare compiler/runtime performance:

- **Execution Time  (average of 10 runs)**  
  - g++: 750 ms  

- **Throughput**  
  0.865 GIPS (Giga Integer Operations Per Second)

You can view the full source code here:  
[📄column.cpp](./optimizations/column.cpp)

## Program 2: Row‑Major Traversal Benchmark

In **row.cpp**, we implement the Needleman–Wunsch DP matrix fill using **row‑traversal** over a row‑major layout. This change boosts spatial locality and cache hits.

- **Execution Time (average of 10 runs)**  
  - g++: 210 ms

- **Throughput**  
  2.862 GIPS  

You can view the full source and build instructions here:  
[📄 row.cpp](./optimizations/row.cpp)

## Program 3: Anti‑Diagonal Traversal Benchmark

In **Anti-Diagonal.cpp**, we compute the scoring matrix by iterating along anti‑diagonals (from the top edge toward the left edge). This approach isn’t parallelized and has poor spatial locality, so it runs slower.

- **Execution Time (average of 10 runs)**  
  - g++: 730 ms

- **Throughput**  
  0.822 GIPS

<img src="https://github.com/user-attachments/assets/da61acdf-0ac8-47ce-b908-90be6fcff79a" alt="Initial matrix" width="200"/>


You can view the full source here:  
[📄 Anti-Diagonal.cpp](./optimizations/Anti-Diagonal.cpp)

## Program 4: Parallelized Anti‑Diagonal + Loop Unrolling

In **unroll.cpp**, we parallelized the anti‑diagonal traversal (since elements on the same anti‑diagonal are independent) and added loop unrolling.

- **Execution Time (average of 10 runs)**  
  - g++: 142 ms

- **Throughput**  
  4.225 GIPS  

- **Using `#pragma unroll` for** inner‑loop unrolling to increase instruction‑level parallelism.

You can view the full source here:  
[📄 unroll.cpp](./optimizations/unroll.cpp)

## Program 5: Tiled Matrix Traversal

Tiling (or blocking) breaks the DP matrix into cache‑sized sub‑matrices (“tiles”) and processes one tile at a time, maximizing cache hits and minimizing main‑memory accesses.

In **tiling.cpp**, we explored tiling the DP matrix to improve spatial locality, boost cache hits, and reduce memory access time.

- **Execution Time (average of 10 runs)**  
  - g++: 350 ms

- **Throughput**  
  1.714 GIPS  

You can view the full source here:  
[📄 tiling.cpp](./optimizations/tiling.cpp)

### Program 6: Parallelized Anti‑Diagonal Within Tiles

In **Anti-DiagonalTiling.cpp**, we apply the anti‑diagonal computation **inside each cache‑sized tile** and parallelize across anti‑diagonals as in Program 4.

- **Execution Time (average of 10 runs)**  
  - g++: 363 ms

- **Throughput**  
  1.652 GIPS  

[📄 Anti-DiagonalTiling.cpp](./optimizations/Anti-DiagonalTiling.cpp)

### Program 7: Anti‑Diagonal Across Tiles

In **AntiDiagonalTiles.cpp**, we apply anti‑diagonal computation at the tile level: each tile’s DP matrix is filled with the naive row‑major method, but tiles on the same anti‑diagonal are processed in parallel. This yields our best performance yet.

- **Execution Time (average of 10 runs)**  
  - g++: 112 ms (tile size 1000)  
  - g++: 64.5 ms  (tile size 15–30)

- **Throughput**  
  - 5.358 GIPS
  - 9.302 GIPS 

[📄 AntiDiagonalTiles.cpp](./optimizations/AntiDiagonalTiles.cpp)

### Program 8: Nested Parallel Anti‑Diagonal

In **AntiDiagonalTilesNested.cpp**, we apply the anti‑diagonal approach both **across tiles** and **within each tile**, parallelizing every anti‑diagonal of tiles and every anti‑diagonal of cells inside those tiles. While this yields a solid improvement over the baseline, it doesn’t outperform the previous tiled anti‑diagonal strategy.

- **Execution Time (average of 10 runs)**  
  - g++: 162 ms  

- **Throughput**  
  3.704 GIPS  

[📄 AntiDiagonalTilesNested.cpp](./optimizations/AntiDiagonalTilesNested.cpp)


---

> **For final observations and conclusions, see [OBSERVATIONS.md](./OBSERVATIONS.md).**









