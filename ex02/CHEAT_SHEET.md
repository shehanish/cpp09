# Quick Evaluation Cheat Sheet - PmergeMe

## 🎯 MUST KNOW

### 1. What Algorithm?
**Ford-Johnson (Merge-Insert Sort)**
- Minimizes number of comparisons
- Uses Jacobsthal sequence for optimal insertion order
- From Knuth Vol 3, page 184

### 2. Jacobsthal Sequence
```
Formula: J(n) = J(n-1) + 2*J(n-2)
Sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85...
```
**Used for:** Determining optimal order to insert elements

### 3. Two Containers
- **std::vector** - Contiguous memory, typically faster here
- **std::deque** - Double-ended queue, faster insertions at ends

### 4. Algorithm Steps (Quick Version)
```
1. Create pairs → compare → winners/losers
2. Recursively sort winners → main chain
3. Insert first loser at beginning
4. Insert remaining losers in JACOBSTHAL ORDER using binary search
5. Insert struggler (if odd count)
```

### 5. Insertion Order Example
Instead of: b₁, b₂, b₃, b₄, b₅...
Ford-Johnson: b₁, **b₃, b₂**, **b₅, b₄**, **b₁₁, b₁₀, b₉, b₈, b₇, b₆**...
(Groups based on Jacobsthal, backwards within group)

---

## 💻 Key Code Locations

**Jacobsthal generation:** Lines 33-76 in PmergeMe.cpp
**Insertion order used:** Lines 155-165 in insertionPhaseVec()
**Binary search:** `std::lower_bound()` for finding position

---

## ⚙️ Quick Tests

```bash
# Basic
./PmergeMe 3 5 9 7 4

# 3000 elements
./PmergeMe $(shuf -i 1-100000 -n 3000 | tr "\n" " ")

# Errors
./PmergeMe -1 2        # negative
./PmergeMe 5 3 5       # duplicate
./PmergeMe abc         # invalid

# Full suite
bash test_evaluation.sh
```

---

## 📊 Complexity

**Time:** O(n log n) comparisons (optimal for small n)
**Space:** O(n)
**Key point:** Minimizes COMPARISONS, not time

---

## ❗ Common Pitfalls to Avoid

1. ❌ Don't say "it's just merge sort" - it's MERGE-INSERT with Jacobsthal optimization
2. ❌ Don't forget to mention binary search for insertions
3. ❌ Don't claim O(n²) - it's O(n log n)
4. ✅ DO emphasize the Jacobsthal sequence is what makes it Ford-Johnson
5. ✅ DO show you implemented it separately for each container (not generic)

---

## 🎤 If Asked to Explain on Whiteboard

Example with [3, 5, 9, 7, 4]:

```
Step 1: Pair & Compare
(3,5) → winner:5, loser:3
(9,7) → winner:9, loser:7
struggler: 4

Step 2: Recursive Sort Winners
[5, 9] → already sorted
Main chain: [5, 9]

Step 3: Insert First Loser
[5, 9] → [3, 5, 9]  (b₁ goes at beginning)

Step 4: Insert Others (Jacobsthal order)
For 2 elements, order is just [1] (index 1, which is b₂=7)
[3, 5, 9] → binary search for 7 → [3, 5, 7, 9]

Step 5: Insert Struggler
[3, 5, 7, 9] → binary search for 4 → [3, 4, 5, 7, 9]

DONE!
```

---

## 🔍 If They Check Memory Leaks

```bash
valgrind --leak-check=full ./PmergeMe 3 5 9 7 4
```
Should show: "All heap blocks were freed -- no leaks are possible"

---

## ✅ Orthodox Canonical Form

- ✅ Default constructor (line 15)
- ✅ Copy constructor (line 17)
- ✅ Copy assignment operator (line 22)
- ✅ Destructor (line 31)

---

## 🏆 Strengths to Highlight

1. **Complete Ford-Johnson implementation** with Jacobsthal
2. **Separate implementations** for each container (as required)
3. **Comprehensive error handling** (negative, invalid, duplicate)
4. **Handles 3000+ elements** efficiently
5. **Precise timing** in microseconds
6. **Clean, readable code** with good separation of concerns

---

## 🎯 Final Checklist Before Evaluation

- [ ] Code compiles without warnings
- [ ] Norm/style check passed
- [ ] Basic test works (./PmergeMe 3 5 9 7 4)
- [ ] 3000 element test works
- [ ] All error cases handled
- [ ] You can explain Jacobsthal sequence
- [ ] You can explain why it's different from basic merge-insert
- [ ] You know your time complexity
- [ ] Test script runs successfully

---

## 💡 One-Liner Summary

"Ford-Johnson merge-insertion sort that uses the Jacobsthal sequence to determine the optimal insertion order, minimizing the maximum number of comparisons needed during binary search insertion, implemented separately for std::vector and std::deque to compare performance."
