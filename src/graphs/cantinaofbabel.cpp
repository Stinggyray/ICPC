#include<bits/stdc++.h>
using namespace std;

/*
 * PROBLEM LINK: https://open.kattis.com/problems/cantinaofbabel
 *
 * Algorithm explanation:
 * First, we iterate over all of the input lines, and put them all in a vector of characters.
 *
 * Then, using that character vector, we iterate over all of the languages to construct every single edge
 * between two characters.
 * This would normally be pretty expensive, but thankfully, there's only up to 100 characters in the cantina.
 *
 * This graph is *directed*, because at least 1 character needs to have speaking ability for two characters to communicate,
 * and that connection only goes one way. (We can represent two characters who speak the same language with two connections
 * in either direction.)
 *
 * The notion of "conversing" in this problem means that node A and B on the graph need to have a connection to each
 * other. So, as a result, this problem can be boiled down to "what is the largest group of STRONGLY CONNECTED vertices
 * in this directed graph?" Strongly connected vertices are vertices that all have a path to each other, in any direction.
 *
 * We can now find an algorithm for this: Kosaraju's algorithm. We run it on our graph, and immediately, we get
 * the largest amount of characters that can all converse with each other. We subtract that from the total amount
 * of characters, and we get the number of people we need to kick out.
 */

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

