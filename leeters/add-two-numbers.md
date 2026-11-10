# LeetCode 2 — Add Two Numbers

**Difficulty:** Medium  
**Topics:** Linked Lists, Pointers, Mathematics, Data Structures  
**Language:** C++

## 1. Problem Understanding

We are given two non-empty singly linked lists representing two non-negative integers.

Each node contains one digit, and the digits are stored in **reverse order**.

Our task is to add the two numbers and return the result as a linked list, also in reverse order.

### Example 1

```text
Input:
l1 = [2, 4, 3]
l2 = [5, 6, 4]

Output:
[7, 0, 8]
```

Why?

```text
342 + 465 = 807
```

The digits are stored backwards, so the result is:

```text
7 → 0 → 8
```

### Example 2: Different list lengths

```text
Input:
l1 = [9]
l2 = [9, 9]

Output:
[8, 0, 1]
```

Why?

```text
9 + 99 = 108
```

The algorithm must handle lists of different lengths.

---

## 2. Understanding the Data Structure: Linked Lists

A singly linked list consists of individual nodes connected through pointers.

Each node contains:

- `val`: the value stored in the node.
- `next`: a pointer to the next node.

A simplified C++ representation:

```cpp
struct ListNode {
    int val;
    ListNode* next;
};
```

Example:

```text
    ┌─────┐     ┌─────┐     ┌─────┐
    │  2  │ --> │  4  │ --> │  3  │ --> nullptr
    └─────┘     └─────┘     └─────┘
```

Unlike arrays and vectors, linked lists do not support direct indexing.

We cannot simply write:

```cpp
l1[0];
```

Instead, we navigate through the nodes using pointers.

```cpp
l1 = l1->next;
```

This moves `l1` to the next node.

### Understanding `ListNode*`

When we write:

```cpp
ListNode* l1;
```

We declare a pointer that can store the memory address of a `ListNode`.

It does not directly store the node's value.

For example:

```cpp
l1->val
```

Accesses the value inside the node.

```cpp
l1->next
```

Accesses the address of the next node.

### Understanding `nullptr`

`nullptr` represents a pointer that currently points to nothing.

For example:

```cpp
if (l1 != nullptr) {
    int value = l1->val;
}
```

We check whether the pointer is valid before accessing the node.

Trying to access `l1->val` when `l1` is `nullptr` results in undefined behavior.

---

## 3. Understanding the Algorithm

The key insight is that we don't need to reconstruct the original integers.

Because the digits are stored in reverse order, we can perform ordinary column addition by traversing both lists simultaneously.

Consider:

```text
342
465
---
807
```

We process the least significant digits first.

### Step 1: Traverse both lists

We use two pointers:

```cpp
ListNode* l1;
ListNode* l2;
```

Each pointer tracks our current position in its respective list.

### Step 2: Read the current digits

What happens if one list is shorter than the other?

Suppose:

```text
l1 = [9]
l2 = [9, 9]
```

When `l1` finishes, we still need to process the remaining digits of `l2`.

We treat a missing digit as zero.

```cpp
int val1 = l1 != nullptr ? l1->val : 0;
int val2 = l2 != nullptr ? l2->val : 0;
```

This uses the ternary operator:

```cpp
condition ? valueIfTrue : valueIfFalse;
```

### Step 3: Add the digits and incoming carry

We maintain a variable called `carry`.

```cpp
int sum = val1 + val2 + carry;
```

For example:

```text
9 + 9 + 0 = 18
```

### Step 4: Extract the result digit and calculate carry

We use the modulo operator `%` and integer division `/`.

```cpp
int digit = sum % 10;
carry = sum / 10;
```

For `sum = 18`:

```text
digit = 18 % 10 = 8
carry = 18 / 10 = 1
```

The remainder gives us the digit to store.

Integer division gives us the carry for the next addition.

### Step 5: Create a result node

We need to construct a new linked list containing the result.

We use:

```cpp
new ListNode(digit);
```

This dynamically allocates a new node and returns its address.

For example:

```cpp
ListNode* node = new ListNode(7);
```

Creates a node containing 7 and stores its address in `node`.

---

## 4. The Dummy Node and Tail Pointer

This is one of the most important concepts from this problem.

We use:

```cpp
ListNode dummy(0);
ListNode* tail = &dummy;
```

### What is the dummy node?

Think of the dummy node as a temporary starting point for building our answer.

It is not part of the actual answer.

It simply gives us a starting node so we can append every result digit using the same procedure.

### What is the tail pointer?

`tail` always points to the last node in the result list.

Initially:

```text
dummy
  ↓
[0] → nullptr
 ↑
tail
```

When we append a digit:

```cpp
tail->next = new ListNode(digit);
tail = tail->next;
```

The first statement:

- Creates a new node.
- Connects it after the current tail.

The second statement moves `tail` to the newly created node.

### Example: Appending 7 and 8

Initially:

```text
[0] → nullptr
 ↑
tail
```

Append 7:

```text
[0] → [7] → nullptr
        ↑
       tail
```

Append 8:

```text
[0] → [7] → [8] → nullptr
               ↑
              tail
```

Notice that `tail = tail->next` does not make `tail` become `nullptr`.

It moves the pointer to the newly connected node.

### Why do we return `dummy.next`?

At the end:

```cpp
return dummy.next;
```

We return the address of the first actual result node, skipping the temporary dummy node.

For example:

```text
dummy → [0] → [7] → [0] → [8] → nullptr
         ↑
      dummy.next
```

The returned pointer points to the node containing 7.

However, that node links to the next node, which links to the next one.

Therefore, returning one node's address gives us access to the entire linked list.

**Key takeaway:** A pointer to the first node gives us access to the entire chain because every node stores a link to the next node.

---

## 5. Complete Algorithm

```text
1. Create a dummy node.
2. Let tail point to dummy.
3. Initialize carry to zero.

4. Continue while:
   - l1 has nodes, OR
   - l2 has nodes, OR
   - carry is not zero.

5. During each iteration:

   a. Read l1's digit, or use zero if l1 is null.
   b. Read l2's digit, or use zero if l2 is null.
   c. Add both digits and the incoming carry.
   d. Extract the result digit using sum % 10.
   e. Calculate the outgoing carry using sum / 10.
   f. Create a new node containing the result digit.
   g. Connect it to the result list.
   h. Move tail to the new node.
   i. Advance l1 if it exists.
   j. Advance l2 if it exists.

6. Return dummy.next.
```

---

## 6. C++ Implementation

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        // Create the dummy starting node.
        ListNode dummy(0);

        // Tail tracks the last node in our result.
        ListNode* tail = &dummy;

        // Store the carry from each addition.
        int carry = 0;

        // Continue while either list has nodes or carry remains.
        while (l1 != nullptr || l2 != nullptr || carry != 0) {

            // Read the current digits.
            int val1 = l1 != nullptr ? l1->val : 0;
            int val2 = l2 != nullptr ? l2->val : 0;

            // Add both digits and the incoming carry.
            int sum = val1 + val2 + carry;

            // Calculate the result digit and outgoing carry.
            int digit = sum % 10;
            carry = sum / 10;

            // Append a new node to the result.
            tail->next = new ListNode(digit);
            tail = tail->next;

            // Advance the input pointers when possible.
            if (l1 != nullptr) {
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                l2 = l2->next;
            }
        }

        // Return the first actual result node.
        return dummy.next;
    }
};
```

---

## 7. Dry Run

Input:

```text
l1 = [2, 4, 3]
l2 = [5, 6, 4]
```

| Iteration | val1 | val2 | Carry in | Sum | Digit | Carry out |
|---|---:|---:|---:|---:|---:|---:|
| 1 | 2 | 5 | 0 | 7 | 7 | 0 |
| 2 | 4 | 6 | 0 | 10 | 0 | 1 |
| 3 | 3 | 4 | 1 | 8 | 8 | 0 |

Final result:

```text
7 → 0 → 8 → nullptr
```

### Special case: Final carry

Input:

```text
l1 = [9]
l2 = [9]
```

First iteration:

```text
9 + 9 + 0 = 18

digit = 8
carry = 1
```

Both input pointers are now `nullptr`.

But the loop does not stop because `carry` is still 1.

Second iteration:

```text
0 + 0 + 1 = 1

digit = 1
carry = 0
```

Final result:

```text
8 → 1 → nullptr
```

This explains why the loop condition includes:

```cpp
carry != 0
```

---

## 8. Complexity Analysis

Let:

- `m` = number of nodes in the first linked list.
- `n` = number of nodes in the second linked list.

### Time Complexity

\[
O(\max(m,n))
\]

We traverse each input list once.

There can be at most one additional iteration for a final carry.

### Auxiliary Space Complexity

\[
O(1)
\]

We use a fixed number of extra pointers and variables, excluding the output.

### Output Space Complexity

\[
O(\max(m,n))
\]

We construct a new linked list containing the result.

---

## 9. Mistakes I Made and Lessons Learned

My first implementation had two important logical errors.

### Mistake 1: Forgetting to include carry

Incorrect:

```cpp
int sum = val1 + val2;
```

Correct:

```cpp
int sum = val1 + val2 + carry;
```

**Lesson:** Carry from the previous addition must be included in the current addition.

### Mistake 2: Reversing digit and carry calculations

Incorrect:

```cpp
int digit = sum / 10;
carry = sum % 10;
```

Correct:

```cpp
int digit = sum % 10;
carry = sum / 10;
```

**Lesson:** Modulo extracts the last digit, while integer division removes the last digit and gives the carry.

### Concepts I strengthened

- Singly linked lists.
- Pointers and memory addresses.
- Pointer dereferencing.
- The arrow operator `->`.
- `nullptr` and safe pointer access.
- Dynamic memory allocation using `new`.
- Ternary operator.
- Integer division and modulo.
- Dummy node and tail pointer pattern.
- Carry-based arithmetic.
- Linked-list traversal.

---

## 10. Knowledge Check

Try answering without looking at the implementation.

1. What is a linked list?
2. What does `ListNode*` represent?
3. What is the difference between `l1->val` and `l1->next`?
4. Why do we use `nullptr`?
5. Why can't we access `l1->val` when `l1` is `nullptr`?
6. What does `new ListNode(digit)` do?
7. What does `&dummy` return?
8. Why do we need both `dummy` and `tail`?
9. Why does `tail = tail->next` move to the newly created node?
10. Why do we return `dummy.next` instead of `dummy`?
11. Why do we use zero when one list has ended?
12. Why must carry be part of the loop condition?
13. What is the difference between `%` and `/` in this algorithm?
14. What is the time complexity?
15. Can you implement the entire solution again without looking?

---

## 11. The Real Lesson

This challenge was an introduction to manipulating linked data structures using pointers.

The most important ideas are:

- A pointer stores an address.
- A node connects to another node through its `next` pointer.
- We can traverse a linked list by repeatedly following these links.
- A dummy node simplifies linked-list construction.
- A tail pointer makes appending nodes straightforward.
- Returning the first node's address gives us access to the entire linked list.

The dummy-tail pattern is reusable in many other linked-list problems.

**The real objective:** Understand the structure and the pointer operations well enough to build and manipulate linked lists independently, not merely memorize this particular solution.