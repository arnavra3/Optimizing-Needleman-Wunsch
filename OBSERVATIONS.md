<img src="https://github.com/user-attachments/assets/70bb86be-51df-4953-892d-6a77f0d2e58c" alt="Initial matrix" width="500"/>

**Best speed‑up:** 750 ms / 64.5 ms ≈ 12× observed for string lengths upto 10,000.

- Increasing the sequence length also increases the speed‑up.  
  For sequence size 10 000, a speed‑up of ≈ 12× was achieved (750 ms / 64.5 ms). For sequence size 30 000, a speed‑up close to 18× was observed (10.2 s / 0.55 s).
  
- Simply varying the tile size produces significant changes in execution times.

- Contrary to expectations, tiling with only tile‑level parallelization outperformed full parallelization of both tiles and the cells within them.

- Changing the traversal order of the DP table—row‑wise, column‑wise, or anti‑diagonal‑wise—provides a considerable speed‑up due to improved spatial locality.

---

## Future Analysis

- Find the best tile size for the optimizations that use tiling , find the optimal tile size and how it depends on n and generalize a pattern to get the best optimization possible.

- Reduce space complexity to further enhance performance. One promising approach is Hirschberg’s algorithm (O(n) space for the shorter sequence), which is a divide‑and‑conquer, space‑efficient version of Needleman–Wunsch.
