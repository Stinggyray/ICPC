#include<bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

	sort(edges.begin(), edges.end(), compareWeight);

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
