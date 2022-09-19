#include<bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
 * PROBLEM LINK: https://open.kattis.com/problems/treehouses
 *
 * Algorithm explanation:
 * First, we iterate over the input, and put all of the treehouse locations into a vector.
 *
 * We then iterate over every single treehouse location, and construct a vector of edges
 * (consisting of the two edge vertices and the weight of that edge).
 *
 * Then, we start with a union-find / disjoint set, and we first join every single cable provided and every single
 * treehouse within walking distance of each other (the first e) because they all have a weight of 0.
 *
 * Then, we need to SORT the edges to make use of Kruskal's Algorithm to generate a minimum-weight spanning tree
 * for all of the treehouses in the rainforest. After that, we just run Kruskal's algorithm, iterating over all
 * of the edges in ascending weight order, and if the two edges aren't already connected, we add the weight
 * of that new edge to the total weight. We then output the total weight.
 *
 * Using a union-find makes this very efficient, allowing Kruskal's Algorithm to run quickly.
 */

// union find
struct UF {
	vi e;

	UF(int n) : e(n, -1) {}

	bool sameSet(int a, int b) { return find(a) == find(b); }

	int size(int x) { return -e[find(x)]; }

	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }

	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b];
		e[b] = a;
		return true;
	}
};

vector<pair<pii, double>> edges;
vector<pair<double, double>> treehouses;

int n, e, p;

double edgeWeight(double x, double y, double x2, double y2) {
	return (sqrt(abs(x - x2) * abs(x - x2) + abs(y - y2) * abs(y - y2)));
}
bool compareWeight(pair<pii, double> a, pair<pii, double> b) {
	return (a.second < b.second);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> e >> p;

	UF forest(n);

	rep(i, 0, n) {
		double x, y;
		cin >> x >> y;

		treehouses.push_back({x, y});
	}

	// load all actually weighted edge weights
	rep(i, 0, n) {
		rep(j, i + 1, n) {
			edges.push_back({{i, j}, edgeWeight(treehouses[i].first, treehouses[i].second, treehouses[j].first,
			                                    treehouses[j].second)});
		}
	}

	// load all cables
	rep(i, 0, p) {
		int a, b;
		cin >> a >> b;

		forest.join(a - 1, b - 1);
	}

	// first e treehouses are walkable
	rep(i, 0, e - 1) {
		forest.join(i, i + 1);
	}

	sort(all(edges), compareWeight);

	double weight = 0;
	rep(i, 0, sz(edges)) {
		// cout << edges[i].first.first << " " << edges[i].first.second << " " << edges[i].second << "\n";
		if(forest.find(edges[i].first.first) != forest.find(edges[i].first.second)) {
			forest.join(edges[i].first.first, edges[i].first.second);
			weight += edges[i].second;

			if(forest.size(edges[i].first.first) == n) {
				break;
			}
		}
	}

	cout << weight << "\n";
}
