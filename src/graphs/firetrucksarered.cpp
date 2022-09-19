#include<bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
 * PROBLEM LINK: https://open.kattis.com/problems/firetrucksarered
 *
 * Algorithm explanation:
 * First, we iterate over all of the input lines, and put them all into a HashMap (for O(1) lookup)\
 * for all of the "numbers" for which they are connected. This means we end up with a HashMap
 * of each number and all of the individuals it links together.
 *
 * We then iterate over this HashMap, and using a union-find / disjoint set data structure, we can
 * join every single element in each "number connection" with the first element in that list, and if
 * this results in a new connection being made in the UnionFind, we add it to the proof.
 *
 * Every time a new element is added to the union-find, we check if it's been
 *
 * Using a union-find makes this very efficient, especially with something as large as a limit of n < 200,000.
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

struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
__gnu_pbds::gp_hash_table<ll,int,chash> h({},{},{},{},{1<<16});

int n;
// vector<vi> people;
unordered_map<int, vi> sets;
vector<pair<int, pii>> proof;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	rep(i, 0, n) {
		int m;
		cin >> m;

		// people.push_back(vi(m));

		rep(j, 0, m) {
			int cur;
			cin >> cur;
			// people[i].push_back(cur);

			if(sets.find(cur) == sets.end()) {
				sets[cur] = vi();
			}

			sets[cur].push_back(i);
		}
	}

	UF forest(n);
	bool possible = false;

	for(auto const& x : sets) {
		vi nums = x.second;

		rep(i, 1, sz(nums)) {
			if(!forest.sameSet(nums[0], nums[i])) {
				forest.join( nums[0], nums[i]);
				proof.push_back({x.first, {nums[0], nums[i]}});

				if(forest.size(nums[0]) == n) {
					possible = true;
					break;
				}
			}
		}
	}

	if(possible) {
		rep(i, 0, sz(proof)) {
			cout << proof[i].second.first + 1 << " " << proof[i].second.second + 1 << " " << proof[i].first << "\n";
		}
	} else {
		cout << "impossible\n";
	}
}
