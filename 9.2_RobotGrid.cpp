// Robot sits on (0,0) of a X by Y grid. robot can only move right or down. how many ways for it move from left right corner to right down corner?
// FOLLOW UP: if there are some points in grid cannot step on them ("off limit")
// 1. find one path for robot  move from left right corner to right down corner
// 2. find all the paths

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

struct point {
	point(int m = 0, int n = 0) : x(m), y(n) {}
	int x;
	int y;

	void print() {
		cout << " [" << x << "," << y << "] ";
	}

	bool operator == (const point& other) const {
		return (x == other.x && y == other.y);
	}
};

class hashFcn {
public:
	int operator()(const point& p) const {
		return (3 * hash<int>()(p.x) + 5 * hash<int>()(p.y));
	}
};

typedef long long ll;
typedef unordered_map<point, ll, hashFcn> HASH;

/*
f(x, y) = f(x, y-1) + f(x-1, y)
f(0, ...) = 1
f(...,0) = 1
use memorization to avoid duplicat efforts
*/
ll pathCountR(int x, int y, HASH& hash) {
	if (x == 0 || y == 0)
		return 1;
	point p(x, y);
	if (hash.find(p) != hash.end())
		return hash[p];
	else {
		ll count = pathCountR(x, y - 1, hash) + pathCountR(x - 1, y, hash);
		hash[p] = count;
		return count;
	}
}

ll pathCount(int x, int y) {
	HASH h;
	return pathCountR(x, y, h);
}

/*
c(x+y, x) = (x+y)/(x!*y!)
*/
// no need memorization, as no duplicate calculation
ll factor(int x) {
	if (x == 0)
		return 1;
	return x*factor(x - 1);
}

ll pathCount2(int x, int y) {
	return factor(x + y) / factor(x) / factor(y);
}

/*
FOLLOW UP 1
*/
typedef stack<point> PATH;
typedef vector<vector<int>> GRID;

// check point is in bound and can be "stepped on"
bool valid(const GRID& g, int m, int n) {
	int R = g.size();
	int C = g[0].size();	

	return (m >= 0 && m < R) &&
		(n >= 0 && n < C) &&
		(g[m][n] != 0);
}

/*
Get one path
- once get to [0 0] print out path & return true
- check up/down first and only failed, check left/right
- if failed, pop the point inserted at the begining

Staring backword =>from right down corner to left up corner

DFS
*/ 
bool getPathR(const GRID& g, int m, int n, PATH& path) {
	if (!valid(g, m, n))
		return false;
	path.push(point(m, n));

	if (m == 0 && n == 0) {
		while (!path.empty()) {
			path.top().print();
			path.pop();
		}
		cout << endl;
		return true;
	}		

	bool success = getPathR(g, m, n - 1, path);
	if (!success)
		success = getPathR(g, m - 1, n, path);	
	if (!success)
		path.pop();

	return success;
}

/*
Get one path
- once get to [RR-1 CC-1] print out path & return true (one path)
- check down first and only failed, check right ==> (one path)
- no pop, but keep len, overwrite invalid part (nodes) on a path

Staring forward =>from left up corner to right down corner

DFS
*/
bool getPathR2(const GRID& g, int m, int n, vector<point>& path, int len) {
	if (!valid(g, m, n))
		return false;
	path[len++] = point(m,n);

	if (m == g.size()-1 && n == g[0].size()-1) {
		for (size_t i = 0; i < path.size(); i++) {
			path[i].print();
		}
		cout << endl;
		return true;
	}

	bool success = getPathR2(g, m+1, n, path, len);
	if (!success)
		success = getPathR2(g, m, n+1, path, len);
	
	return success;
}

/*
Get all the paths
- once get to [RR-1 CC-1] print out a path
- check down first , check right always (all paths)
- no pop, but keep len, overwrite invalid part (nodes) on a path

Staring forward =>from left up corner to right down corner

DFS
*/
void getAllPaths(const GRID& g, int m, int n, vector<point>& path, int len) {
	if (!valid(g, m, n))
		return;
	path[len++] = point(m, n);

	if (m == (g.size()-1) && n == (g[0].size()-1)) {
		for (size_t i = 0; i< path.size(); i++) {
			path[i].print();
		}
		cout << endl;
	}
	else {
		getAllPaths(g, m+1, n, path, len);
		getAllPaths(g, m, n+1, path, len);
	}
}

int main() {

	GRID g(3, vector<int>(4, 1));
	g[0][3] = 0; g[1][0] = 0;
	int CC = g[0].size();
	int RR = g.size();
	

	cout << pathCount(RR-1, CC-1) << endl;
	cout << pathCount2(RR-1, CC-1) << endl;

	PATH p;
	getPathR(g, RR-1, CC-1, p);

	cout << "2nd approach" << endl;
	vector<point> p2;
	p2.resize(RR+CC-1);
	getPathR2(g, 0, 0, p2, 0);

	cout << "get all paths" << endl;
	vector<point> p3;
	p3.resize(RR + CC-1);
	getAllPaths(g, 0, 0, p3, 0);
}