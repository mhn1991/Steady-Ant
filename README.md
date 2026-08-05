# Steady Ant Algorithm

An implementation of Tiskin's **Steady Ant** algorithm for merging permutation (unit-Monge) matrices under min-plus multiplication, applied to fast longest-common-subsequence (LCS) computation via the semi-local string comparison / "braid" formulation. Written as an MSc dissertation project.

## Background

Classic min-plus multiplication of two `n x n` distance matrices takes O(n³). When the matrices are *unit-Monge* (as arises from permutation matrices representing string-comparison "braids"), the Steady Ant algorithm merges two halves of the recursion in O(n) instead, giving an overall subcubic algorithm — the basis for fast semi-local LCS/edit-distance computation.

This repository implements both the naive baseline and the Steady Ant approach so their behaviour and performance can be compared directly.

## Layout

```
core/
  core.h            sparse permutation-matrix representation (Cell, Sparse, Ant),
                     red/blue/green colour states used by the merge
  core.c            the Steady Ant algorithm itself, with its own test-harness
                     main():
                       - ant()      O(n) merge of two permutation-matrix halves
                       - multi()    recursive divide-and-conquer driver (2-column,
                                    3-column, and general recursive cases)
                       - permute(), coloring(), rColoring()  supporting matrix ops
                       - testMulti2/3/5(), testAnt2(), testCheck()  hand-built
                         permutation-matrix cases exercising the merge
  main.c            a separate, standalone LCS demo built on the "braid group"
                     match-matrix idea (shares the Cell type from core.h, but
                     does not call into core.c's ant()/multi() merge — it finds
                     the LCS length directly via a diagonal-run scan)
  algorithm.txt     worked-through notes on the divide/merge steps

naive_multipication/
  naive_multipication.c   baseline implementation used for comparison:
                             - dominanceSum()        O(n^4) permutation -> dominance matrix
                             - minPlusMultiplication() O(n^3) naive min-plus multiply
                             - crossDifference()      O(n^2) dominance -> permutation matrix

steady_ant_rust/    early-stage Rust port — scaffolding only, the algorithm
                    itself has not been ported yet (see Status below)

documentation/      dissertation report (LaTeX source + PDF)
```

## Status

- **Steady Ant merge/recursion** (`core/core.c`): implemented and runnable via its built-in test harness against hand-built permutation matrices.
- **Naive baseline** (`naive_multipication/`): implemented and runnable — O(n⁴) dominance-sum, O(n³) min-plus multiplication, O(n²) cross-difference.
- **LCS demo** (`core/main.c`): a separate, simpler diagonal-run LCS routine over a match matrix — not yet wired to call the Steady Ant merge, so it demonstrates the "braid" matrix idea rather than the fast algorithm end-to-end.
- **Rust port** (`steady_ant_rust/`): scaffolding only. The crate compiles but currently contains stub functions, not a working port of the algorithm.
- Test coverage, border-case handling (see `algorithm.txt`), integrating the LCS driver with the actual Steady Ant merge, and a formal performance comparison against the naive baseline are noted as outstanding in the original project notes.

## Building

```sh
# Steady Ant merge (runs the test harness selected in core.c's main())
cd core
gcc -o steady_ant core.c
./steady_ant

# LCS demo (standalone, does not use the Steady Ant merge)
gcc -o lcs main.c
./lcs <string1> <string2>

# naive baseline
cd ../naive_multipication
gcc -o naive naive_multipication.c
./naive
```
