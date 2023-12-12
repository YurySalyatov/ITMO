n, m, s, t = map(int, input().split())
edges = []
passes = []

def dfs(i, len):
    if(i == t):
        passes.append(len)
        return
    for a in edges[i - 1]:
        dfs(a[0], len + a[1])

for i in range(n):
    edges.append([])
for i in range(m):
    b, e, w = map(int, input().split())
    edges[b - 1].append([e, w])
dfs(s, 0)
if(len(passes) == 0):
    print("Unreachable")
else:
    mini = passes[0]
    for i in passes:
        mini = min(mini, i)
    print(mini)