#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<pii> edges;
vector<pair<string, vector<string>>> chars;

vector<bool> visited;
stack<int> s;

vector<vi> connections;

void visit(int n) {
	if(!visited[n]) {
		visited[n] = true;
		rep(i, 0, sz(edges)) {
			if(edges[i].first == n) {
				visit(edges[i].second);
			}
		}
		s.push(n);
	}
}

void assign(int u, int root) {
	rep(i, 0, sz(connections)) {
		rep(j, 0, sz(connections[i])) {
			if(connections[i][j] == u) {
				return;
			}
		}
	}
	connections[root].push_back(u);
	rep(i, 0, sz(edges)) {
		if(edges[i].second == u) {
			assign(edges[i].first, root);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	// read input
	rep(i, 0, n) {
		string name;
		cin >> name;

		string line;
		getline(cin, line);

		istringstream f(line);
		vector<string> langs;
		string curl;
		while(getline(f, curl, ' ')) {
			langs.push_back(curl);
		}

		// chop off langs whitespace
		langs.erase(langs.begin());

		string lang = langs[0];

		chars.push_back({lang, langs});
	}

	// assemble language graph
	rep(i, 0, sz(chars)) {
		rep(j, 0, sz(chars[i].second)) {
			rep(k, 0, sz(chars)) {
				if (i == k) {
					continue;
				}
				string curlang = chars[i].second[j];
				if (curlang == chars[k].first) {
					// cout << i << " <-- " << k << " with " << curlang << "\n";
					edges.push_back({k, i});
				}
			}
		}
	}

	// run kosaraju's algorithm, get all strongly connected vertices
	visited = vector<bool>(n, false);
	connections = vector<vi>(n, vi());

	rep(i, 0, n) {
		visit(i);
	}

	while(!s.empty()) {
		int i = s.top();
		s.pop();

		assign(i, i);
	}

	// find the largest set of strongly connected vertices
	int maxSize = 0;
	rep(i, 0, sz(connections)) {
		if (sz(connections[i]) > maxSize) {
			maxSize = sz(connections[i]);
		}
	}

	cout << (n - maxSize) << "\n";
}

