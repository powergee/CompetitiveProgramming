from collections import deque
import sys
input = lambda: sys.stdin.readline().strip()

def DFS(graph, visited, start):
    if visited[start]:
        return
    visited[start] = True
    print(f"{start} ", end="")

    for dest in graph[start]:
        DFS(graph, visited, dest)

(n, m, s) = list(map(int, input().split()))

graph = [[] for j in range(n+1)]
for i in range(m):
    (a, b) = list(map(int, input().split()))
    graph[a].append(b)
    graph[b].append(a)

for i in range(1, n+1):
    graph[i].sort()
    
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
    for dest in graph[now]:
        if not visited[dest]:
            d.append(dest)
print()