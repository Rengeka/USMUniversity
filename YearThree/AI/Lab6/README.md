# **Laboratory Work №6 — Genetic Algorithm Optimization**

## **1. Objective**

The goal of this laboratory work is to study the principles of **genetic algorithms (GA)** as a method for solving optimization problems.
The task includes implementing a GA to maximize the function:

[
f(x) = \sin^2(4\pi x) + 0.3x, \quad x \in [0, 1]
]

The algorithm uses binary chromosomes, roulette-wheel selection, single-point crossover, and bitwise mutation.

---

## **2. Problem Description**

### **2.1. Chromosome Encoding**

Each individual is represented as a binary list of length **L** (e.g., L = 4).
The binary string is decoded into a real number:

[
x = \frac{\text{binary_value}}{2^L - 1}
]

Example:
Chromosome `1010` → integer 10 → `x = 10 / 15`.

---

## **3. Components of the Genetic Algorithm**

### **3.1. Initial Population**

A population of **N** chromosomes is generated randomly:

```
initialize_population(N, L)
```

### **3.2. Fitness Function**

The fitness of an individual is calculated as:

[
f(x) = \sin^2(4\pi x) + 0.3x
]

### **3.3. Selection — Roulette Wheel**

Two parents are selected with probability proportional to fitness:

```
random.choices(pop, weights=fitness, k=2)
```

This ensures high-fitness individuals have a greater chance of being selected.

---

### **3.4. Crossover**

Single-point crossover is applied with probability **pc**:

* A random split point is chosen
* Two children are created by swapping chromosome segments

This introduces new combinations of genes.

---

### **3.5. Mutation**

Each gene flips with a small probability **pm**:

```
bit = 1 - bit
```

Mutation prevents premature convergence and maintains genetic diversity.

---

## **4. Main Genetic Algorithm Loop**

For each generation:

1. Evaluate fitness
2. Print population and statistics
3. Select parents
4. Apply crossover
5. Apply mutation
6. Form a new population
7. Track the best fitness value

After G generations, the algorithm prints the best found solution.

---

## **5. Results and Observations**

During the run, the algorithm prints:

* Current generation
* Each chromosome
* Its decoded value
* Fitness value
* Max, min, and average fitness

A typical output:

```
--- Generation 10 ---
3: [1, 0, 0, 1] -> x=0.6000, f=0.5431
Max: 0.8120, Min: 0.1023, Avg: 0.4510
```

At the end:

```
Best solution: x* = ..., f(x*) = ...
```

The graph displays how the maximum fitness evolves over generations — typically increasing, then stabilizing as the population converges.

---

## **6. Conclusions**

### **What the experiment shows:**

* Genetic algorithms **do not guarantee** finding the absolute maximum, but with correct parameters they reach near-optimal values.
* Crossover accelerates convergence by mixing genetic material.
* Mutation prevents the algorithm from getting stuck in local maxima.
* Even with a small chromosome length (L = 4) and small population (N = 6), GA improves solutions over generations.

### **Key insights:**

* The balance between exploration (mutation) and exploitation (selection + crossover) strongly affects performance.
* Larger chromosome lengths provide better accuracy when representing real numbers.
* More generations result in better convergence.

---