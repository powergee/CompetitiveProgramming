from collections import deque
import sys
input = lambda: sys.stdin.readline().strip()

def DFS(graph, visited, start):
    if visited[start]:
        return
    visited[start] = True
    print(f"{start} ", end="")

    for i in range(1, len(graph)):
        if graph[start][i]:
            DFS(graph, visited, i)

(n, m, s) = list(map(int, input().split()))

graph = [[0 for i in range(n+1)] for j in range(n+1)]
for i in range(m):
    (a, b) = list(map(int, input().split()))
    graph[a][b] = 1
    graph[b][a] = 1
    
visited = [False for i in range(n+1)]
DFS(graph, visited, s)
print()

visited = [False for i in range(n+1)]
d = deque()
d.append(s)

while len(d) > 0:
    now = d.popleft()
    if visited[now]:
        continue
    visited[now] = True

    print(f"{now} ", end="")
    for i in range(1, len(graph)):
        if graph[now][i] and not visited[i]:
            d.append(i)
print()