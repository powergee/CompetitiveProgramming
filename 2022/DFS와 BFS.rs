use std::collections::VecDeque;
use std::io::{BufWriter, stdout};
use std::io::Write;

fn main() {
    let io = &mut Scanner::default();
    
    let n: usize = io.next();
    let m: usize = io.next();
    let v: usize = io.next();

    let mut graph: Vec<Vec<usize>> = vec![vec![]; n+1];
    for _ in 0..m {
        let u: usize = io.next();
        let v: usize = io.next();
        graph[u].push(v);
        graph[v].push(u);
    }

    for v in 1..=n {
        graph[v].sort_unstable();
    }

    fn explore_dfs(graph: &Vec<Vec<usize>>, visited: &mut Vec<bool>, result: &mut Vec<usize>, start: usize) {
        visited[start] = true;
        result.push(start);
        for &next in &graph[start] {
            if !visited[next] {
                visited[next] = true;
                explore_dfs(graph, visited, result, next);
            }
        }
    }
    let mut visited = vec![false; n+1];
    let mut result = vec![];
    explore_dfs(&graph, &mut visited, &mut result, v);
    
    let mut out = BufWriter::new(stdout());
    for v in result {
        write!(out, "{} ", v).unwrap();
    }
    writeln!(out).unwrap();

    let mut q = VecDeque::new();
    q.push_back(v);
    let mut visited = vec![false; n+1];
    visited[v] = true;
    
    while !q.is_empty() {
        let curr = q.pop_front().unwrap();
        write!(out, "{} ", curr).unwrap();
        
        for &next in &graph[curr] {
            if !visited[next] {
                visited[next] = true;
                q.push_back(next);
            }
        }
    }
    writeln!(out).unwrap();
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}
impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            std::io::stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}