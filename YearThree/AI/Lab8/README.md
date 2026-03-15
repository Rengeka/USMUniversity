# **Laboratory Work №8 — State Space Search Methods**

**Direct, Reverse, and Bidirectional Search**

## **1. Objective**

The purpose of this laboratory work is to study search algorithms in state-space planning problems for intelligent agents.
The task includes implementing:

* Forward Breadth-First Search (BFS)
* Forward Greedy Search using a heuristic
* Backward Greedy Search using a heuristic
* Bidirectional Breadth-First Search

Each algorithm must return:

* The resulting path
* Number of visited nodes
* Number of generated states
* Effective branching factor
* Execution time

---

## **2. Problem Description**

The environment is a 2×2 grid.
The agent starts at position `(0, 0)` without the item.
The goal is to return to the same position **with** the item.

### **Initial and Goal States**

* **Start state:** `(0, 0, False)`
* **Goal state:** `(0, 0, True)`
* An item is located at `(1, 1)`.

The agent can:

* Move in four directions: up, down, left, right (when inside the grid)
* Pick up an item when reaching `(1,1)` (only once)

---

## **3. Implemented Functions**

### **Successor Functions**

* **Forward expansion:** generates valid next states + "pickup" action
* **Backward expansion:** generates previous states + "unpickup" action

### **Heuristic**

The heuristic estimates remaining effort:

* If no item: Manhattan distance to item + distance from item to base
* If item already taken: Manhattan distance to base

The heuristic is **admissible, consistent**, and suitable for greedy best-first search.

### **Path Reconstruction**

Parents are stored during search to reconstruct the final path.

---

## **4. Implemented Algorithms**

### **4.1. Forward BFS**

* Expands frontier level-by-level.
* Guarantees shortest path in number of steps.
* No heuristic used.

### **4.2. Forward Greedy Search**

* Expands state with the minimum heuristic value.
* Does not guarantee optimality.
* Fast in practice for small spaces.

### **4.3. Backward Greedy Search**

* Starts from the goal and expands backwards.
* Uses predecessor function.
* Finds a reverse path which is later reversed.

### **4.4. Bidirectional BFS**

* Expands from both start and goal simultaneously.
* Stops when two search frontiers meet.
* Very efficient when branching factor is small.

---

## **5. Experimental Results**

*(The exact results depend on execution time, but the structure below is what the program outputs.)*

For each algorithm, results include:

* **Path**
* **Solution length**
* **Visited vertices**
* **Generated states**
* **Branching factor** *(generated / visited)*
* **Execution time**

Example output format:

```
Forward BFS
Path: [...]
Solution length: N
Visited vertices: V
Generated states: G
Branching factor: B
Time: T s
```

---

## **6. Conclusions**

This laboratory work demonstrates several key ideas in search algorithms:

1. **BFS** guarantees the shortest path but may explore many unnecessary states.
2. **Greedy search** significantly reduces explored states using a heuristic, but optimality is not guaranteed.
3. **Backward greedy** shows that reverse reasoning can also be efficient when the goal state is well-defined.
4. **Bidirectional BFS** is the most effective approach for small state spaces with well-defined start and goal states, drastically reducing the search depth.

Thus, choosing the correct search strategy depends on:

* State space size
* Branching factor
* Whether a good heuristic is available
* Whether both start and goal states are explicitly known

---

## **7. Summary**

This work provides practical experience with fundamental search strategies used in AI planning.
By comparing forward, backward, greedy, and bidirectional search, we better understand their strengths, limitations, and suitable applications.