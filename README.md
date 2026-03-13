# DSA — Find Unique (Non-Duplicate) Elements in an Array

A focused C++ implementation that identifies and prints all elements in an array that appear **exactly once** — removing every element that has a duplicate anywhere in the array. This problem is a foundational exercise in **frequency counting**, **nested traversal**, and understanding the trade-off between a simple O(n²) approach and an optimal O(n) hash-based solution. It appears in various forms across DSA interview problems under names like "find unique elements", "remove duplicates", and "single number".

---

## Problem Statement

Given an array of integers, print all elements that appear **exactly once** in the array, in the order they appear.

**Hardcoded Input:**
```cpp
int arr[5] = {10, 20, 30, 20, 40};
```

**Output:**
```
10 30 40
```

*(20 appears twice — it is excluded. 10, 30, and 40 each appear once — they are printed.)*

---

## The Code

```cpp
#include <iostream>
using namespace std;

int main()
{
    int arr[5] = {10, 20, 30, 20, 40};
    int n = 5;
    int newArr[5];
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }
        if (count == 1)
        {
            newArr[newSize] = arr[i];
            newSize++;
        }
    }

    for (int i = 0; i < newSize; i++)
    {
        cout << newArr[i] << " ";
    }
    cout << endl;

    return 0;
}
```

---

## How It Works

The algorithm uses a **nested loop frequency count** strategy:

1. **Outer loop** — picks each element `arr[i]` as the candidate to evaluate.
2. **Inner loop** — scans the entire array counting how many times `arr[i]` appears.
3. **Count check** — if the count is exactly `1`, the element is unique and gets copied into `newArr`.
4. **Output loop** — prints all elements collected in `newArr` up to `newSize`.

The result is a filtered array containing only the elements that have no duplicates, preserving their original order.

---

## The Manual Dynamic Array Pattern

The code manages its output collection using two variables:

```cpp
int newArr[5];   // pre-allocated output buffer (same size as input — safe upper bound)
int newSize = 0; // tracks how many elements have been added
```

This is a classic **manual dynamic array** pattern — a fixed-size array paired with an explicit size counter. Elements are appended by writing to `newArr[newSize]` and incrementing `newSize`. It avoids `std::vector` while correctly managing a variable-length result within a statically allocated buffer.

The upper bound of `5` (same as input size `n`) is safe because in the worst case, every element is unique — the output can never be larger than the input.

---

## Algorithm (Pseudocode)

```
arr    ← {10, 20, 30, 20, 40}
n      ← 5
newArr ← []
newSize ← 0

for i from 0 to n-1:
    count ← 0

    for j from 0 to n-1:
        if arr[j] == arr[i]:
            count ← count + 1

    if count == 1:
        newArr[newSize] ← arr[i]
        newSize ← newSize + 1

print newArr[0..newSize-1]
```

---

## Dry Run

**Array:** `{10, 20, 30, 20, 40}`

| `i` | `arr[i]` | Full scan count | `count == 1`? | Added to `newArr`? |
|-----|----------|-----------------|---------------|--------------------|
| 0   | 10       | appears 1 time  | ✅            | ✅ `newArr = {10}` |
| 1   | 20       | appears 2 times | ❌            | ❌                 |
| 2   | 30       | appears 1 time  | ✅            | ✅ `newArr = {10, 30}` |
| 3   | 20       | appears 2 times | ❌            | ❌                 |
| 4   | 40       | appears 1 time  | ✅            | ✅ `newArr = {10, 30, 40}` |

**Output:** `10 30 40`

---

## Complexity Analysis

| Metric | Complexity |
|--------|------------|
| Time   | **O(n²)** — for every element, the entire array is scanned to count occurrences |
| Space  | **O(n)** — `newArr` is a second array of the same size as the input |

> For `n = 5` this is entirely fine. For large arrays (`n = 10⁶`), the nested loop would perform 10¹² comparisons — the hash map approach is the correct tool at scale.

---

## The Hardcoded Array — A Scope Note

The input array is fixed in the source code:

```cpp
int arr[5] = {10, 20, 30, 20, 40};
```

There is no `cin` prompt. This is a deliberate scope choice — the code focuses purely on demonstrating the algorithm without input-handling overhead. To make it interactive:

```cpp
int n;
cout << "Enter number of elements: ";
cin >> n;
int arr[n];
cout << "Enter elements: ";
for (int i = 0; i < n; i++) cin >> arr[i];
```

The algorithm itself requires no changes — only the input section needs replacing.

---

## No Output Label — A Minor Readability Note

The output loop prints raw numbers with spaces:

```cpp
cout << newArr[i] << " ";
```

There is no label like `"Unique elements: "` before the values. Adding one is a one-line change that significantly improves readability when the program is run:

```cpp
cout << "Unique elements: ";
for (int i = 0; i < newSize; i++)
    cout << newArr[i] << " ";
```

---

## Edge Cases

| Scenario | Behavior |
|----------|----------|
| All elements unique `{1, 2, 3, 4, 5}` | All 5 printed — `newSize = n` |
| All elements identical `{5, 5, 5, 5, 5}` | Nothing printed — `newSize = 0`, only `endl` output |
| One unique, rest duplicates `{1, 2, 2, 3, 3}` | Only `1` printed |
| Alternating `{1, 2, 1, 2, 1}` | Nothing printed — both `1` and `2` appear multiple times |
| Single element `{7}` | `7` printed — count = 1, added to `newArr` |

---

## The O(n) Optimization — Hash Map Approach

The nested loop counts every element from scratch on every outer iteration. A hash map can build the full frequency table in one pass, then filter in a second pass:

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
    int arr[] = {10, 20, 30, 20, 40};
    int n = 5;

    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++)
        freq[arr[i]]++;

    cout << "Unique elements: ";
    for (int i = 0; i < n; i++)
        if (freq[arr[i]] == 1)
            cout << arr[i] << " ";

    cout << endl;
    return 0;
}
```

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Nested loop (this repo) | O(n²) | O(n) | Simple, no STL dependencies |
| Hash map | O(n) | O(n) | Faster, uses `unordered_map` |
| Sorting-based | O(n log n) | O(1) extra | In-place but changes element order |

The nested loop approach is the right starting point — it makes the counting logic explicit and transparent before abstracting it into a hash map.

---

## Comparison with Related Problems

This problem is part of a family of "find special elements" problems:

| Problem | Condition | Key Difference |
|---------|-----------|----------------|
| **This repo** | Count == 1 | Finds all elements appearing exactly once |
| Find Duplicates | Count > 1 | Finds all elements appearing more than once |
| Single Number (LeetCode #136) | One unique among pairs | Every other element appears exactly twice — XOR trick applies |
| Single Number II (LeetCode #137) | One unique among triplets | Every other element appears exactly three times |
| Find All Duplicates (LeetCode #442) | Count == 2 | In-place using negative marking trick |
| First Unique Character (#387) | Count == 1, first only | Same frequency idea applied to characters in a string |

The frequency counting pattern — count occurrences, then filter by a threshold — is the common thread across all of them.

---

## Repository Structure

```
DSA-Unique-Elements/
│
├── unique_elements.cpp     # Main C++ implementation
└── README.md               # Project documentation
```

---

## How to Compile and Run

**Prerequisites:** GCC / G++

```bash
# Clone the repository
git clone https://github.com/rishita-ops/DSA-Unique-Elements.git
cd DSA-Unique-Elements

# Compile
g++ unique_elements.cpp -o unique_elements

# Run
./unique_elements
```

**On Windows:**
```bash
g++ unique_elements.cpp -o unique_elements.exe
unique_elements.exe
```

---

## Key Concepts Covered

- **Nested loop frequency counting** — counting occurrences of each element by scanning the full array
- **Manual dynamic array pattern** — using a fixed buffer + size counter instead of `std::vector`
- **Order preservation** — unique elements appear in the output in their original array order
- **`count == 1` as the uniqueness condition** — filtering on exact frequency, not just presence
- **Hardcoded vs. interactive input** — understanding the scope of a demonstration implementation
- **O(n²) vs O(n) trade-off** — nested loops vs. hash map for frequency problems

---

## Contributing

Contributions are welcome. Consider adding:
- An **interactive input version** using `cin`
- An **O(n) hash map version** for large-input performance
- A version that also **counts and prints the duplicates**
- A version using `std::vector` instead of a manual buffer
- Implementations in Python, Java, or JavaScript

```bash
git checkout -b feature/your-feature
git commit -m "Add: your feature description"
git push origin feature/your-feature
# Then open a Pull Request
```

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

*Part of a structured DSA practice series — fundamentals, done right.*
