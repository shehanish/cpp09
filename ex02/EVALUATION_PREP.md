# PmergeMe - Evaluation Preparation Guide

## Overview
This program implements the **Ford-Johnson merge-insertion sort algorithm** (also known as merge-insertion sort) to sort positive integers using two different STL containers: `std::vector` and `std::deque`.

---

## Algorithm Explanation

### What is Ford-Johnson (Merge-Insert Sort)?

The Ford-Johnson algorithm is a comparison-based sorting algorithm that **minimizes the number of comparisons** needed to sort a sequence. It was proven optimal for small sequences.

### Key Steps:

#### 1. **Pairing Phase**
   - Group elements into pairs
   - Compare each pair and identify "winner" (larger) and "loser" (smaller)
   - If odd number of elements, the last one is a "struggler" (handled separately)
   
   Example: `[3, 5, 9, 7, 4]`
   - Pairs: (3,5), (9,7), struggler: 4
   - After comparison: (5,3), (9,7), struggler: 4
   - Winners: [5, 9], Losers: [3, 7]

#### 2. **Recursive Sort**
   - Recursively sort the **winners** using the same algorithm
   - This creates the "main chain" (sorted sequence of winners)

#### 3. **Insertion Phase (The Critical Part!)**
   
   This is where **Jacobsthal sequence** comes in:
   
   **Jacobsthal Numbers:** 0, 1, 1, 3, 5, 11, 21, 43, 85, 171...
   - Formula: `J(n) = J(n-1) + 2*J(n-2)`
   
   **Why Jacobsthal?**
   - It determines the **optimal insertion order** for the losers
   - Minimizes the maximum number of comparisons during binary insertion
   
   **Insertion Order:**
   - First: Insert b₁ (first loser) at the beginning (always smaller than first winner)
   - Then insert in Jacobsthal groups:
     - Group 1: b₃, b₂
     - Group 2: b₅, b₄
     - Group 3: b₁₁, b₁₀, b₉, b₈, b₇, b₆
     - etc. (backwards within each group)
   
   Each element is inserted using **binary search** to find its position.

#### 4. **Handle Struggler**
   - If there was an odd element, insert it at the end using binary search

---

## Implementation Details

### Two Separate Implementations
- **Vector version**: Uses `std::vector` container
- **Deque version**: Uses `std::deque` container
- **Why separate?** Subject requires non-generic implementation to see performance differences

### Key Functions:

1. **`generateJacobsthalOrder(n)`**
   - Generates the optimal insertion order based on Jacobsthal sequence
   - Returns indices in the order they should be inserted

2. **`recursiveSortVec/Deque(container)`**
   - Main recursive sorting function
   - Creates pairs, extracts winners, recurses, then inserts losers

3. **`insertionPhaseVec/Deque(mainChain, pairs, struggler, hasStruggler)`**
   - Inserts losers into sorted main chain
   - Uses Jacobsthal order for optimal performance
   - Uses binary search (`std::lower_bound`) for each insertion

4. **`sortAndDisplay()`**
   - Orchestrates the sorting with timing
   - Displays before/after sequences
   - Shows timing for both containers

---

## Common Evaluation Questions & Answers

### Q1: "Why two containers? What's the difference?"
**A:** The subject requires using two different containers to compare performance:
- **`std::vector`**: Contiguous memory, fast random access, slower insertions in middle
- **`std::deque`**: Double-ended queue, faster insertions at both ends, slightly slower random access
- In our tests, vector is typically faster despite more insertions because of better cache locality

### Q2: "Explain the Jacobsthal sequence and why you use it"
**A:** Jacobsthal numbers (0, 1, 1, 3, 5, 11, 21...) define the optimal insertion order that minimizes the maximum number of comparisons. Each element can be found within a guaranteed number of binary search steps based on its position in the sequence. Without it, we'd just insert sequentially which would be less efficient.

### Q3: "What's the time complexity?"
**A:** 
- Best/Average: **O(n log n)** comparisons
- Worst case: **O(n log n)** comparisons
- **Space**: O(n) for storing pairs and main chain
- **Note**: Ford-Johnson minimizes comparisons but not necessarily time (due to insertions)

### Q4: "Why use binary search for insertion?"
**A:** Since the main chain is already sorted, binary search finds the insertion position in O(log n) comparisons. This is more efficient than linear search O(n).

### Q5: "What if there are duplicates?"
**A:** Current implementation detects and rejects duplicates during input parsing with error message: "Error: duplicate value found"

### Q6: "How do you handle the 'struggler' (odd element)?"
**A:** When the sequence has an odd number of elements, the last unpaired element is saved and inserted at the end using binary search, after all other elements are sorted.

### Q7: "Can you handle 3000+ elements?"
**A:** Yes, tested successfully with up to 3000 elements. Example timing: ~700μs for vector, ~1800μs for deque.

### Q8: "What containers from previous exercises can't be used?"
**A:** Subject says containers from previous exercises are forbidden. In Module 09, we likely used:
- ex00: `std::map` (Bitcoin prices)
- ex01: `std::stack` (RPN calculator)
So those are forbidden here. We use `std::vector` and `std::deque`.

### Q9: "Show me where Ford-Johnson is different from regular merge-insert"
**A:** The key difference is in `insertionPhaseVec/Deque()`:
- Line ~155-165: Uses `generateJacobsthalOrder()` 
- Inserts elements in Jacobsthal order (b₃, b₂, b₅, b₄...) instead of sequential (b₂, b₃, b₄, b₅...)
- This is the optimization that makes it Ford-Johnson

### Q10: "How do you measure timing?"
**A:** Using `gettimeofday()` from `<sys/time.h>`:
- Start timer before sorting
- Stop timer after sorting
- Calculate difference in microseconds
- Display with precision to show differences between containers

---

## Testing Checklist During Evaluation

- [ ] **Compilation**: `make` and `make re` work without errors
- [ ] **No memory leaks**: Can check with valgrind if evaluator asks
- [ ] **Basic test**: `./PmergeMe 3 5 9 7 4` works correctly
- [ ] **Large test**: `./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")` handles 3000 elements
- [ ] **Error handling**: Negative numbers, invalid input, duplicates all show errors
- [ ] **Output format**: Shows Before, After, and timing for both containers
- [ ] **Orthodox Canonical Form**: Copy constructor, assignment operator, destructor implemented

---

## Quick Demo Commands

```bash
# Clean build
make re

# Basic example
./PmergeMe 3 5 9 7 4

# Large test
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")

# Error cases
./PmergeMe -1 2          # Negative
./PmergeMe abc           # Invalid
./PmergeMe 5 3 5         # Duplicate

# Run full test suite
bash test_evaluation.sh
```

---

## Code Structure Summary

```
PmergeMe.hpp
├── Private members: _vector, _deque
└── Public methods:
    ├── Orthodox Canonical Form (constructor, copy, assignment, destructor)
    ├── parseInput()          // Validates and stores input
    ├── sortAndDisplay()      // Main orchestrator with timing
    ├── generateJacobsthalOrder()  // Generates optimal insertion order
    ├── recursiveSortVec/Deque()   // Main sorting recursion
    └── insertionPhaseVec/Deque()  // Inserts using Jacobsthal order

main.cpp
└── Calls parseInput() and sortAndDisplay(), handles exceptions
```

---

## Tips for Evaluation

1. **Be ready to explain Jacobsthal**: This is the key distinguishing feature
2. **Show the test script**: Demonstrates thorough testing
3. **Explain why you chose vector and deque**: Different performance characteristics
4. **Be prepared to trace through a small example**: Show pairing, recursion, insertion order
5. **Know your complexity**: O(n log n) comparisons, minimizing maximum comparisons
6. **Memory management**: Using STL containers (automatic), Orthodox Canonical Form implemented

---

## References

- Knuth, Donald E. "The Art of Computer Programming, Volume 3: Sorting and Searching" (Page 184)
- Ford-Johnson algorithm paper: "Selecting the t largest using binary errorless comparisons" (1959)
