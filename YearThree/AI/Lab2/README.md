# Lab 2
Topic: Min-max alghoritm with alpha–beta pruning

Student: Stanisalv Ciobanu

Group: I2302

Github: https://github.com/Rengeka/USMUniversity/tree/main/YearThree/AI

Teacher: V.Trebes

# Structure

My project contains core node strcture
```rust
struct Node {
    value: i32,
    children: Vec<Node>,
}
```

A method to generate and print tree
```rust
fn generate_tree(depth: usize, width: usize) -> Node
```

And a method for minmax based on [pseudocode][1] algorithm from 

```rust
fn minimax(node: &Node,
           depth: usize,
           alpha: i32,
           beta: i32,
           maximizing: bool,
           nodes_checked: &mut u32) -> i32 {

    *nodes_checked += 1;

    if depth == 0 || node.children.is_empty() {
        return node.value;
    }

    let mut alpha = alpha;
    let mut beta = beta;

    if maximizing {
        let mut max_eval = i32::MIN;
        for child in &node.children {
            let eval = minimax(child, depth - 1, alpha, beta, false, nodes_checked);
            max_eval = max_eval.max(eval);
            alpha = alpha.max(eval);

            if beta <= alpha {
                break;
            }
        }
        max_eval
    }
    else
    {
        let mut min_eval = i32::MAX;
        for child in &node.children {
            let eval = minimax(child, depth - 1, alpha, beta, true, nodes_checked);
            min_eval = min_eval.min(eval);
            beta = beta.min(eval);
            if beta <= alpha {
                break;
            }
        }
        min_eval
    }
}
```

[1]:https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning


# How to run

Use ```cargo run``` to run application