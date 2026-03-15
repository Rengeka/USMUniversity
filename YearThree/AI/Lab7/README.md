# **Laboratory Work №7 — Constraint Search: The 8 Queens Problem**

## **1. Objective**

The goal of this laboratory work is to study search algorithms for constraint satisfaction problems (CSP), using the classic **8 Queens Problem** as an example.
The task includes implementing:

* Depth-First Search (DFS) with pruning
* A* Search using a conflict-based heuristic

Each algorithm must find a configuration of 8 queens on an 8×8 chessboard such that none of them attack each other.

---

## **2. Problem Description**

The **8 Queens Problem** requires placing eight queens on a chessboard so that:

* No two queens share the same row
* No two queens share the same column
* No two queens share the same diagonal

### **State Representation**

A state is an array of length 8:

```
state[i] = column of the queen in row i
```

A value of `-1` means the queen in that row has not been placed yet.

Example:

```
[-1, -1, 4, -1, 2, -1, -1, -1]
```

---

## **3. Conflict Function**

The `conflicts(state)` function computes how many pairs of queens threaten each other.

A conflict occurs if:

* Two queens are in the same column
* Two queens lie on the same diagonal

This function is both:

* A pruning tool for DFS
* A heuristic for A* search

---

## **4. Goal Test**

A state is a goal when:

1. All queens are placed (`-1 not in state`)
2. The number of conflicts is zero

```
return -1 not in state and conflicts(state) == 0
```

---

## **5. Generating Neighbors**

To expand a state:

* Find the first unassigned row (`-1`)
* Try placing a queen in each of the 8 columns
* Only keep states that do **not** introduce any conflicts

This implements *forward checking*, reducing the search space.

---

## **6. Implemented Algorithms**

### **6.1. Depth-First Search (DFS)**

DFS recursively tries all valid placements, backtracking whenever a conflict occurs.
Pruning ensures that invalid partial configurations are never expanded further.

**Characteristics:**

* No heuristic
* May explore deeply before finding a solution
* Very memory-efficient
* Speed depends heavily on pruning

---

### **6.2. A* Search**

A* uses a priority queue ordered by:

```
f(n) = g(n) + h(n)
```

Where:

* `g(n)` = number of queens already placed
* `h(n)` = number of conflicts
* `f(n)` = estimated cost to reach goal

A* expands the most promising valid partial board first.

**Characteristics:**

* Informed search
* More efficient exploration
* Guarantees finding a solution if heuristic is admissible (here: conflict count is admissible)

---

## **7. Experimental Results**

The program prints:

```
DFS: <solution_state>
A* : <solution_state>
```

Both algorithms successfully find valid solutions, though speed differs significantly:

* DFS may take longer in worst-case scenarios
* A* typically finds a solution quickly because the conflict heuristic reduces search depth

The exact solution differs depending on runtime ordering, but valid output resembles:

```
[0, 4, 7, 5, 2, 6, 1, 3]
```

---

## **8. Conclusions**

This laboratory work demonstrates two different strategies for solving constraint satisfaction problems:

### **DFS**

* Simple and memory-efficient
* Relies heavily on pruning
* Can be slow without heuristics

### **A* Search**

* Uses heuristics to guide the search
* Explores fewer states
* Faster and more informed
* Finds a solution more efficiently than DFS

### **Overall Conclusion**

Heuristic-guided search (A*) is significantly more efficient than uninformed DFS for CSP tasks.
Conflict-based heuristics greatly reduce the branching factor and search depth.

---