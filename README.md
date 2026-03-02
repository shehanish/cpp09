# 🪙 C++ Module 09 — STL

> **42 Network | C++ Series — Module 09**
> The final C++ module, focused entirely on the **Standard Template Library (STL)**. Each exercise enforces deliberate container selection, robust input handling, and rigorous adherence to the **C++98** standard.

---

## � Project Structure

```
cpp09/
├── ex00/   Bitcoin Exchange           — std::map + CSV parsing
├── ex01/   Reverse Polish Notation    — std::stack + expression evaluation
└── ex02/   PmergeMe (Ford-Johnson)    — std::vector + std::deque benchmarking
```

---

## ⚡ Quick Build & Run

```bash
# Exercise 00
cd ex00 && make && ./btc input.txt

# Exercise 01
cd ex01 && make && ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"

# Exercise 02
cd ex02 && make && ./PmergeMe 3 5 9 7 4 1 8 2
```

---

## 0️⃣ Exercise 00 — Bitcoin Exchange

### Goal
Given a CSV database of historical BTC exchange rates and an input file of `date | amount` pairs, output the computed value of each entry using the closest available past date.

### Container Used
```cpp
std::map<std::string, float> _database;
```
`std::map` provides **O(log n)** lookup via a balanced BST. `lower_bound(date)` efficiently finds the closest prior date when an exact match doesn't exist.

### How It Works
1. **`loadDatabase()`** — Reads `data.csv`, parses `date,rate` pairs and populates the map.
2. **`processInput()`** — Reads `input.txt`, validates each `date | value` line, then calls `_database.lower_bound(date)` to find the nearest matching rate and prints the result.

### Input Format
```
date | value
2011-01-03 | 3
2015-01-01 | 10
```

### Error Handling
| Condition | Error Output |
|---|---|
| Negative value | `Error: not a positive number.` |
| Value > 1000 | `Error: too large a number.` |
| Invalid/malformed date | `Error: bad input => <date>` |
| Date before earliest DB entry | `Error: date too early => <date>` |
| Missing `\|` separator | `Error: bad input => <line>` |
| Leap year edge cases | Validated (e.g. `2011-02-29` is rejected) |
| Overflow / non-numeric value | `Error: bad input => <value>` |

### Sample Output
```
2011-01-03 => 3 = 0.9
2015-01-01 => 10 = 2790.6
```

---

## 1️⃣ Exercise 01 — Reverse Polish Notation (RPN)

### Goal
Evaluate a mathematical expression in **Postfix (RPN)** notation passed as a single command-line argument, printing the final result.

### Container Used
```cpp
std::stack<double> _stack;
```
A stack is the natural structure for RPN — numbers are **pushed**, operators **pop** two operands, compute, and **push** the result back.

### How It Works
`myCalculator()` tokenizes the input string with `std::stringstream`, then for each token:
- **Number** → validated as a single digit (`0`–`9`), then pushed onto `_stack`
- **Operator** → pops two values, applies the operation via `cCalculation()`, pushes result

```
Input:  "8 9 * 9 - 9 - 9 - 4 - 1 +"
  push 8  → [8]
  push 9  → [8, 9]
  *       → [72]
  push 9  → [72, 9]
  -       → [63]
  ... continues ...
  Result  → 42
```

### Supported Operators
| Operator | Operation |
|---|---|
| `+` | Addition |
| `-` | Subtraction |
| `*` | Multiplication |
| `/` | Division (throws on zero divisor) |

### Error Handling
| Condition | Thrown Exception |
|---|---|
| Multi-digit number | `Only single digit numbers (0 - 9) are allowed!` |
| Insufficient operands on stack | `Invalid Input: Not enough operands` |
| Division by zero | `Division by zero.` |
| Stack doesn't resolve to 1 value | `Invalid Inputs.` |

### Sample Usage
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
# Output: 42

./RPN "9 8 * 9 -"
# Output: 63
```

---

## 2️⃣ Exercise 02 — PmergeMe (Ford-Johnson Algorithm)

### Goal
Sort a sequence of positive integers from the command-line using the **Ford-Johnson Merge-Insertion Sort**, implemented independently for both **`std::vector`** and **`std::deque`**, then display the time taken by each.

### Containers Used
```cpp
std::vector<int> _vector;
std::deque<int>  _deque;
```

### Algorithm Breakdown (Ford-Johnson)

This algorithm is designed to minimise the **total number of comparisons** required to sort a sequence:

**Step 1 — Pairing:**
Elements are grouped into pairs. Each pair is sorted: the larger becomes the "winner" (main chain candidate), the smaller becomes the "loser" (pend element).

**Step 2 — Recursive Sort:**
All winners are recursively sorted using the same algorithm, forming the sorted **main chain**.

**Step 3 — Jacobsthal Insertion:**
Losers are reinserted into the main chain via `std::lower_bound` (binary search). The **order of insertion follows Jacobsthal numbers** `(0, 1, 1, 3, 5, 11, 21, 43…)` to ensure each binary search operates over the smallest possible prefix of the chain — minimising total comparisons.

**Step 4 — Struggler:**
If the original sequence had an **odd number** of elements, the leftover "struggler" is binary-searched into the final sorted chain last.

### Jacobsthal Sequence
```cpp
// Formula:  J(n) = J(n-1) + 2 * J(n-2)
// Sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171 ...
size_t next = jacobsthal[i-1] + 2 * jacobsthal[i-2];
```

### Time Measurement
Uses `gettimeofday()` for **microsecond-precision** benchmarking of both containers:
```cpp
gettimeofday(&start, NULL);
std::vector<int> sortedVec = recursiveSortVec(vecCopy);
gettimeofday(&end, NULL);
double vecTime = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
```

### Input Validation
| Condition | Error Thrown |
|---|---|
| Non-digit characters in argument | `Error: invalid input (only positive integers allowed)` |
| Value exceeds `INT_MAX` | `Error: number too large (exceeds INT_MAX)` |
| Duplicate values | `Error: duplicate value found` |

### Sample Output
```bash
./PmergeMe 3 5 9 7 4 1 8 2

Before: 3 5 9 7 [...]
After:  1 2 3 4 [...]
Time to process a range of 8 elements with std::vector : 9 us
Time to process a range of 8 elements with std::deque  : 14 us
```

### `std::vector` vs `std::deque` — Why the Difference?
| Feature | `std::vector` | `std::deque` |
|---|---|---|
| Memory layout | Single contiguous block | Segmented fixed-size blocks |
| Random access | O(1), highly cache-friendly | O(1), slightly slower |
| Insert at middle | O(n) — shifts elements | O(n) — slightly more overhead |
| Cache performance | ✅ Excellent | ⚠️ Moderate (pointer indirection) |
| Best for | Read-heavy, random access | Front/back insertions |

---

## 🛠️ Build Requirements

- **Standard:** C++98 (`-std=c++98`)
- **Flags:** `-Wall -Wextra -Werror`
- **Memory check:**
  ```bash
  valgrind --leak-check=full ./btc input.txt
  ```

---

## 📚 Key Takeaways

| Concept | What Was Learnt |
|---|---|
| **Container Selection** | Choosing `map`, `stack`, `vector`, `deque` based on access patterns |
| **Algorithm Design** | Implementing Ford-Johnson from scratch; understanding *why* Jacobsthal ordering minimises comparisons |
| **Robust Parsing** | Handling every edge case: whitespace, overflow, bad formats, leap years, invalid dates |
| **Performance Benchmarking** | Using `gettimeofday()` to measure real-world STL container differences in microseconds |
| **C++98 Constraints** | Working without `auto`, lambdas, range-based loops, or any C++11+ features |

---

*Developed by **shkaruna** as part of the 42 Network C++ curriculum.*
