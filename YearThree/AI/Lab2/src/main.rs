use rand::Rng;

fn main() {
    //let root = generate_tree(6, 2);
    let root = generate_tree(3, 3);
    root.print(0);

    let mut nodes_checked = 0;
    let best_value = minimax(&root, 6, i32::MIN, i32::MAX, true, &mut nodes_checked);

    println!("Best value at root: {}", best_value);
    println!("Nodes checked: {}", nodes_checked);
}

struct Node {
    value: i32,
    children: Vec<Node>,
}

fn generate_tree(depth: usize, width: usize) -> Node {
    let mut rng = rand::rng();
    if depth == 0 {
        Node { value: rng.random_range(0..100), children: vec![] }
    } else {
        let mut children = Vec::new();
        for _ in 0..width {
            children.push(generate_tree(depth - 1, width));
        }
        Node { value: 0, children }
    }
}

impl Node {
    fn print(&self, level: usize) {
        let indent = "  ".repeat(level);
        println!("{}{}", indent, self.value);

        for child in &self.children {
            child.print(level + 1);
        }
    }
}

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