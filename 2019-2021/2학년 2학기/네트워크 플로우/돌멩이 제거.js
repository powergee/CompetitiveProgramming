const { match } = require("assert");

const LEFT_MAX = 501;
const RIGHT_MAX = 501;

const connected = Array.from(Array(LEFT_MAX), () => Array());
const visited = Array.from(Array(LEFT_MAX), () => false);
const matching = Array.from(Array(RIGHT_MAX), () => 0);

function DFS(start) {
    if (visited[start])
        return 0;
    
    visited[start] = true;

    for (let opposite of connected[start]) {
        if (matching[opposite] === 0 || DFS(matching[opposite])) {
            matching[opposite] = start;
            return 1;
        }
    }

    return 0;
}

function bipartite(n) {
    let result = 0;

    for (let i = 1; i <= n; ++i) {
        visited.fill(false, 0, n+1);
        result += DFS(i);
    }

    return result;
}

const fs = require("fs");

let lines = fs.readFileSync("/dev/stdin", "utf-8").split('\n');
let [n, k] = lines[0].split(" ").map(v => Number(v));
for (let i = 1; i <= k; ++i) {
    let [r, c] = lines[i].split(" ").map(v => Number(v));
    connected[r].push(c);
}

console.log(bipartite(n));