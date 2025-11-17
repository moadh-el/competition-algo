from collections import deque, defaultdict
import os

def reader():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(base_dir, "../kingdom_input.txt")

    try:
        with open(file_path, "r") as f:
            data = f.read().split()
            data = [int(x) for x in data]

        idx = 0
        n = data[idx]; idx += 1
        m = data[idx]; idx += 1

        edges = []
        for _ in range(m):
            u = data[idx]; idx += 1
            v = data[idx]; idx += 1
            edges.append((u, v))

        A = data[idx]; idx += 1
        B = data[idx]; idx += 1

        return n, m, edges, A, B

    except FileNotFoundError:
        print(f"Erreur d'ouverture du fichier : {file_path}")
        return None
    except Exception as e:
        print(f"Erreur inattendue : {e}")
        return None

def aladdins_kingdom():
    result = reader()
    if not result:
        return

    n, m, edges, A, B = result

    adj = defaultdict(list)
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)

    # Count the kingdoms
    visited = [False] * (n + 1)
    kingdoms = 0

    def bfs(start):
        q = deque([start])
        visited[start] = True
        while q:
            node = q.popleft()
            for k in adj[node]:
                if not visited[k]:
                    visited[k] = True
                    q.append(k)

    for i in range(1, n + 1):
        if not visited[i]:
            kingdoms += 1
            bfs(i)

    # Find the shortest path between A and B
    dist = [-1] * (n + 1)
    q = deque([A])
    dist[A] = 0

    while q:
        node = q.popleft()
        for k in adj[node]:
            if dist[k] == -1:
                dist[k] = dist[node] + 1
                q.append(k)

    shortest = dist[B]

    #print(kingdoms)
    #print(shortest)
    print(f"{kingdoms}\n{shortest}")

if __name__ == "__main__":
    aladdins_kingdom()
