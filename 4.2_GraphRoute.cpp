// Given a directed graph, design an algorithm to find out whether there is a route between two nodes.

#include <iostream>
#include <queue>

const int maxn = 100;
bool g[maxn][maxn];
bool visited[maxn];
int n;
std::queue<int> q;

void init()
{
	memset(g, false, sizeof(g));
	memset(visited, false, sizeof(visited));
}

bool route(int src, int dst)
{
	q.push(src);
	visited[src] = true;

	while (!q.empty()) {
		int t = q.front();
		q.pop();
		if (t == dst)
			return true;
		for (int i = 0; i < n; i++) {
			if (g[t][i] && !visited[i]) {
				q.push(i);
				visited[i] = true;			
			}
		}
	}
	return false;
}

int main() {
	freopen("4.2.in", "r", stdin);
	init();
	int n, m, u, v;
	std::cin >> n >> m;
	for (int i = 0; i < m; i++) {
		std::cin >> u >> v;
		g[u][v] = true;
	}
	std::cout << route(0, 6) << std::endl;
	fclose(stdin);
	return 0;
}