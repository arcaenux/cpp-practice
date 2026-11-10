# LeetCode 1 — Two Sum

**Difficulty:** Easy  
**Topics:** Arrays, Hash Maps, Searching  
**Language:** C++

## 1. Problem Understanding

Given an array of integers `nums` and an integer `target`, return the indices of two numbers whose sum equals the target.

### Example

```text
Input:
nums = [2, 7, 11, 15]
target = 9

Output:
[0, 1]
```

Explanation:

```text
nums[0] + nums[1] = 2 + 7 = 9
```

The answer is `[0, 1]` because the problem requires the **indices**, not the actual numbers.

### Important constraints

- Each input has exactly one valid solution.
- You cannot use the same array element twice.
- You may return the answer in any order.

---

## 2. Understanding the Problem Mathematically

We need to find two different positions, `i` and `j`, such that:

\[
nums[i] + nums[j] = target
\]

Rearranging:

\[
nums[j] = target - nums[i]
\]

This gives us an important idea:

If we know the current number, we can calculate the other number we need.

We call this the **complement**.

```cpp
int complement = target - nums[i];
```

For example:

```text
target = 9
current number = 2

complement = 9 - 2 = 7
```

Now our task becomes finding whether 7 exists somewhere else in the array.

---

## 3. Approach One: Brute Force

### The idea

Try every possible pair of elements until we find two whose sum equals the target.

We use nested loops:

- The outer loop selects the first number.
- The inner loop searches for the second number.

### Algorithm

```text
1. Start with the first array element.
2. Compare it with every element after it.
3. Check whether their sum equals the target.
4. If they do, return their indices.
5. Otherwise, move to the next first element.
6. Continue until a valid pair is found.
```

### C++ implementation

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        for (int i = 0; i < nums.size(); i++) {

            for (int j = i + 1; j < nums.size(); j++) {

                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }

        return {};
    }
};
```

### Understanding the loops

```cpp
for (int i = 0; i < nums.size(); i++)
```

Selects the first element.

```cpp
for (int j = i + 1; j < nums.size(); j++)
```

Selects the second element, starting after the first element.

Why start at `i + 1`?

Because:

1. We must not use the same element twice.
2. We don't need to check the same pair in reverse order.

For example, checking `(0, 1)` makes checking `(1, 0)` unnecessary.

### Time complexity

\[
O(n^2)
\]

In the worst case, we examine approximately every possible pair.

### Space complexity

\[
O(1)
\]

We use only a fixed number of extra variables.

---

## 4. Approach Two: Hash Map Optimization

The brute-force approach works, but it repeatedly searches through the array.

Can we remember numbers we've already encountered?

Yes. We can use a hash map.

In C++, we use:

```cpp
#include <unordered_map>
```

An `unordered_map` stores key-value pairs and provides average constant-time lookup.

For this problem, we store:

```text
number → index
```

Example:

```text
2 → 0
7 → 1
11 → 2
15 → 3
```

This allows us to quickly find whether a required number has already appeared.

### The algorithm

For every element:

1. Calculate its complement.
2. Check whether the complement exists in the hash map.
3. If it exists, return the stored index and the current index.
4. Otherwise, store the current number and its index.
5. Continue.

### Why check before inserting?

Suppose:

```text
nums = [3, 3]
target = 6
```

At the first element, we need another 3.

But we haven't encountered another 3 yet.

We first check the map, then insert the current number.

At the second element, the first 3 is already stored, so we find the pair.

This also prevents accidentally using the same element twice.

---

## 5. Important C++ Concepts

### A. `unordered_map<int, int>`

```cpp
unordered_map<int, int> myMap;
```

This declares a hash map where:

- The first `int` is the key (number).
- The second `int` is the value (index).

Example:

```cpp
myMap[25] = 3;
```

Stores:

```text
25 → 3
```

### B. The subscript operator `[]`

```cpp
myMap[nums[i]] = i;
```

Stores the current number and its index.

The `[]` operator can insert a new key or update an existing key.

### C. `.find()`

```cpp
myMap.find(complement);
```

Searches for a key in the hash map.

It returns an iterator to the matching element if found.

If the key does not exist, it returns:

```cpp
myMap.end()
```

### D. `.end()`

```cpp
myMap.find(complement) != myMap.end()
```

This checks whether the key exists.

The `end()` iterator represents the position just past the last element. It is used as a boundary marker, not an actual element to access.

### E. Iterators

An iterator is an object that allows us to navigate and access elements inside a container.

Example:

```cpp
auto it = myMap.find(complement);
```

Here, `auto` tells the compiler to deduce the iterator's type.

We can access the key and value through:

```cpp
it->first
it->second
```

For an unordered map:

- `first` represents the key.
- `second` represents the value.

The arrow operator `->` accesses a member through a pointer or pointer-like object.

For example:

```cpp
it->second
```

is equivalent to:

```cpp
(*it).second
```

### F. `vector<int>`

```cpp
vector<int>& nums
```

This represents a reference to a vector of integers.

The `&` means the function receives a reference to the original vector rather than making a copy.

### G. Returning `{i, j}`

```cpp
return {i, j};
```

This constructs and returns a vector containing the two indices.

It is different from:

```cpp
return {nums[i], nums[j]};
```

The latter returns the actual values, not their positions.

---

## 6. Optimized C++ Implementation

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int, int> myMap;

        for (int i = 0; i < nums.size(); i++) {

            int complement = target - nums[i];

            auto it = myMap.find(complement);

            if (it != myMap.end()) {
                return {it->second, i};
            }

            myMap[nums[i]] = i;
        }

        return {};
    }
};
```

### Understanding the key section

```cpp
int complement = target - nums[i];
```

Calculate the number we need.

```cpp
auto it = myMap.find(complement);
```

Search for that number among previously encountered elements.

```cpp
if (it != myMap.end()) {
    return {it->second, i};
}
```

If found:

- `it->second` gives us the previous element's index.
- `i` gives us the current element's index.

```cpp
myMap[nums[i]] = i;
```

If no pair was found, remember the current number for future iterations.

---

## 7. Dry Run

Input:

```text
nums = [2, 7, 11, 15]
target = 9
```

| Iteration | Current index | Current value | Complement | Map before lookup | Result |
|---|---:|---:|---:|---|---|
| 1 | 0 | 2 | 7 | Empty | Not found; store 2 → 0 |
| 2 | 1 | 7 | 2 | 2 → 0 | Found! Return [0, 1] |

The algorithm stops after the second iteration.

---

## 8. Complexity Analysis

Let `n` be the number of elements in the input array.

| Approach | Time Complexity | Auxiliary Space |
|---|---|---|
| Brute force | \(O(n^2)\) | \(O(1)\) |
| Hash map | \(O(n)\) average | \(O(n)\) |

### Why is the hash map approach faster?

The brute-force solution repeatedly checks pairs.

The hash map solution processes each element once and performs an average O(1) lookup.

This reduces the average time complexity from quadratic to linear.

**Note:** Hash map operations are average O(1), not guaranteed O(1) in every situation.

---

## 9. Mistakes I Made and Lessons Learned

During implementation, I encountered several errors.

### Mistake 1: Incorrect variable name

Incorrect:

```cpp
num[i]
```

Correct:

```cpp
nums[i]
```

Lesson: Variable names must match their declarations exactly.

### Mistake 2: Comparing values instead of indices

Incorrect:

```cpp
nums[i] != nums[j]
```

Correct:

```cpp
i != j
```

Lesson: The requirement is that we must not reuse the same array position. Two different positions may contain equal values.

### Mistake 3: Incorrect vector return syntax

Incorrect:

```cpp
return [i, j];
```

Correct:

```cpp
return {i, j};
```

Lesson: Braces can be used to construct the returned vector.

### Mistake 4: Returning a value instead of an index

Incorrect:

```cpp
return {myMap[complement], nums[i]};
```

Correct:

```cpp
return {myMap[complement], i};
```

Lesson: Always distinguish between a value and its index.

### Mistake 5: Forgetting the fallback return

```cpp
return {};
```

Lesson: The function must have a return path when no pair is found.

---

## 10. Knowledge Check

Try answering these questions without looking at the implementation.

1. What is the difference between an array element's value and its index?
2. Why does the brute-force approach use nested loops?
3. Why does the inner loop start at `i + 1`?
4. What is a complement in the Two Sum problem?
5. What does `unordered_map<int, int>` represent?
6. What exactly does `.find()` return?
7. What is the purpose of `.end()`?
8. What does `auto` do?
9. Why do we check for the complement before inserting the current number?
10. Why is the hash map approach O(n) on average?
11. What is the difference between `it->first` and `it->second`?
12. Why do we return `{it->second, i}` instead of the actual numbers?

### Independent implementation challenge

Close this document and implement Two Sum again.

Try both approaches:

- Brute force without assistance.
- Hash map optimization without assistance.

If you can explain why every line exists, you understand the solution.

---

## 11. The Real Lesson

Two Sum teaches an important problem-solving pattern:

**Use additional memory to reduce repeated computation.**

The hash map allows us to remember information from previous iterations, making future searches faster.

This idea appears in many algorithms involving:

- Frequency counting.
- Duplicate detection.
- Fast lookups.
- Grouping data.
- Tracking previously encountered elements.

The goal is not simply to memorize the Two Sum solution. It is to recognize when a hash map can transform an inefficient search into a more efficient algorithm.