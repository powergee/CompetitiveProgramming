const VERTEX_COUNT = 501;

const flow = Array.from(Array(VERTEX_COUNT), () => new Array(VERTEX_COUNT).fill(0));
const capa = Array.from(Array(VERTEX_COUNT), () => new Array(VERTEX_COUNT).fill(0));
const prev = new Array(VERTEX_COUNT).fill(0);

function getSpare(u, v) {
    return capa[u][v] - flow[u][v];
}

function addFlow(u, v, add) {
    flow[u][v] += add;
    flow[v][u] -= add;
}

function findAugPath(source, sink) {
    prev.fill(-1);
    let q = [];
    q.push(source);

    while (q.length && prev[sink] === -1) {
        let now = q[0];
        q.shift();
        
        for (let next = 1; next < VERTEX_COUNT; ++next) {
            if (now !== next && getSpare(now, next) > 0 && prev[next] === -1) {
                q.push(next);
                prev[next] = now;

                if (prev[sink] != -1)
                    break;
            }
        }
    }

    return prev[sink] !== -1;
}

function edmondsKarp(source, sink) {
    let result = 0;

    while (findAugPath(source, sink)) {
        let add = 0x7fffffff;

        for (let i = sink; i != source; i = prev[i])
            add = Math.min(add, getSpare(prev[i], i));
        
        for (let i = sink; i != source; i = prev[i])
            addFlow(prev[i], i, add);
        
        result += add;
    }

    return result;
}

const fs = require("fs");
const lines = fs.readFileSync("/dev/stdin").toString().split("\n");

let [n, m] = lines[0].split(' ').map(num => Number(num));
for (let i = 1; i <= m; ++i) {
    let [a, b, c] = lines[i].split(' ').map(num => Number(num));
    capa[a][b] += c;
    capa[b][a] += c;
}
let [s, t] = lines[m+1].split(' ').map(num => Number(num));
console.log(edmondsKarp(s, t));