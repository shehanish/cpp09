# C++ Module 09 — STL Containers & Algorithms

> **42 School Project** | Author: **shkaruna** | Standard: **C++98**

This module explores the Standard Template Library (STL) through three independent exercises, each requiring the use of a specific container and demonstrating a real-world or algorithmic use case.

---

## Table of Contents

- [Overview](#overview)
- [Requirements](#requirements)
- [Exercise 00 — Bitcoin Exchange](#exercise-00--bitcoin-exchange)
- [Exercise 01 — Reverse Polish Notation](#exercise-01--reverse-polish-notation)
- [Exercise 02 — PmergeMe (Ford-Johnson Sort)](#exercise-02--pmergeme-ford-johnson-sort)

---

## Overview

| Exercise | Program | Container Used | Concept |
|----------|---------|----------------|---------|
| ex00 | `btc` | `std::map` | Date-keyed price lookup with lower-bound search |
| ex01 | `RPN` | `std::stack` | Stack-based expression evaluation |
| ex02 | `PmergeMe` | `std::vector` & `std::deque` | Ford-Johnson merge-insert sort |

All exercises are compiled with `-Wall -Wextra -Werror -std=c++98`.

---

## Requirements

- A C++98-compatible compiler (e.g. `g++`, `clang++`)
- GNU `make`

---

## Exercise 00 — Bitcoin Exchange

### What it does

`btc` reads a historical Bitcoin price database (`data.csv`) and an input file supplied on the command line. For each valid `date | value` entry in the input, it prints the value of the specified amount of bitcoins on (or closest to) that date.

### Build & Run

```bash
cd ex00
make
./btc input.txt
```

### Input file format

```
date | value
2011-01-03 | 3
2012-03-01 | 1.5
2022-03-29 | 1
```

- **date** must be in `YYYY-MM-DD` format.
- **value** must be a positive floating-point number between **0** and **1000**.

### Database format (`data.csv`)

```
date,exchange_rate
2009-01-02,0
2010-07-17,0.04
...
```

### Key behaviour

- Uses `std::map::lower_bound` to find the closest earlier date when an exact match is not found.
- Rejects negative values, values above 1000, invalid dates, and malformed lines — printing a descriptive error for each.

### Example output

```
2011-01-03 => 3 = 0.9
2012-03-01 => 1.5 = 7.35
2022-03-29 => 1 = 47095.3
```

---

## Exercise 01 — Reverse Polish Notation

### What it does

`RPN` evaluates a mathematical expression given in **Reverse Polish Notation** (postfix notation) and prints the result.

### Build & Run

```bash
cd ex01
make
./RPN "3 4 +"        # → 7
./RPN "5 1 2 + 4 * + 3 -"   # → 14
```

### Supported operators

| Operator | Meaning |
|----------|---------|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division |

### Rules

- Operands must be **single-digit integers** (0–9).
- Tokens must be separated by spaces.
- Division by zero produces an error.
- Invalid expressions (too few operands, unknown tokens) produce an error.

### How RPN works

1. Read tokens left to right.
2. If a token is a number → push it onto the stack.
3. If a token is an operator → pop the top two values, apply the operator, push the result.
4. After all tokens are consumed, the single value on the stack is the answer.

```
Expression: 3 4 + 2 *
Step 1: push 3        → [3]
Step 2: push 4        → [3, 4]
Step 3: + → pop 4,3 → push 7   → [7]
Step 4: push 2        → [7, 2]
Step 5: * → pop 2,7 → push 14  → [14]
Result: 14
```

---

## Exercise 02 — PmergeMe (Ford-Johnson Sort)

### What it does

`PmergeMe` sorts a sequence of positive integers provided as command-line arguments using the **Ford-Johnson merge-insert sort algorithm** (also known as the *binary insertion sort with Jacobsthal ordering*). It runs the sort on both a `std::vector` and a `std::deque`, then reports the time taken for each.

### Build & Run

```bash
cd ex02
make
./PmergeMe 5 3 8 1 9 2 7 4 6
```

### Example output

```
Before: 5 3 8 1 [...]
After:  1 2 3 4 [...]
Time to process a range of 9 elements with std::vector : 42 us
Time to process a range of 9 elements with std::deque  : 51 us
```

### Input rules

- Only positive integers are accepted.
- Duplicates are not allowed — the program throws an error and exits if a duplicate value is found.
- Values must not exceed `INT_MAX`.

### Algorithm — Ford-Johnson (Merge-Insert Sort)

The Ford-Johnson algorithm is designed to minimise the number of comparisons needed to sort a sequence. It outperforms simple insertion sort and approaches the theoretical comparison lower bound.

**High-level steps:**

1. **Pair up** adjacent elements and sort each pair (larger = *winner*, smaller = *loser*).
2. **Recurse** on the winners to produce a sorted *main chain*.
3. **Insert the losers** back into the main chain using binary search (`std::lower_bound`), following the **Jacobsthal insertion order** to minimise comparisons.
4. Handle the **struggler** (unpaired element if the input has odd length) by inserting it last.

**Jacobsthal sequence:** `0, 1, 1, 3, 5, 11, 21, 47, 113, …`

The insertion order derived from this sequence ensures that each binary search covers at most the same bounded range, keeping the total comparison count optimal.

**Complexity:**

| Metric | Value |
|--------|-------|
| Time (average) | O(n log n) |
| Comparisons | ~⌈log₂(n!)⌉ (near-optimal) |

---

## Project Structure

```
cpp09/
├── ex00/
│   ├── main.cpp
│   ├── BitcoinExchange.hpp
│   ├── BitcoinExchange.cpp
│   ├── data.csv          ← historical Bitcoin prices
│   ├── input.txt         ← sample input
│   └── Makefile
├── ex01/
│   ├── main.cpp
│   ├── RPN.hpp
│   ├── RPN.cpp
│   └── Makefile
├── ex02/
│   ├── main.cpp
│   ├── PmergeMe.hpp
│   ├── PmergeMe.cpp
│   └── Makefile
└── docs/
    └── GDB_Guide.md
```
