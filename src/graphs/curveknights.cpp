#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
 * PROBLEM LINK: https://open.kattis.com/problems/curveknights
 *
 * Algorithm explanation:
 * This contains two attempts at solutions, because I didn't realize this program needed longs. I hate everything.
 *
 * My first attempt (which works with longs) involved the following approach:
 * Parse the input, and while parsing it, maintain a dependency count for every single material for every time it's
 * a dependency. It would mess up our total material count if we multiplied a material down the material tree BEFORE
 * its upstream materials were all "paid out".
 *
 * So, we iterate over all of the dependency relationships provided in the input, and only take action on them if
 * they don't have any dependencies themselves. We continue doing this until the list of dependency relationships is
 * completely empty.
 *
 * This approach initially didn't work, so after doing some more experimentation, I recognized this data structure as
 * a "directed acyclical graph" (DAG) (because cycles would break everything regarding dependencies). I then also
 * realized that if we sorted the DAG *topologically* (which definitionally, every single DAG has a topological sort),
 * we could just iterate through the DAG in order, because then nothing would depend on something upstream (because
 * that's what a topological sort is by definition). I then found the existence of Kahn's Algorithm, and sorted the
 * dependency list topologically using that. After that, I still... experienced the exact same error.
 *
 * After asking for some help, I realized why the dependencies could only be 1 through 3. It was to avoid overflowing
 * longs, because turns out, 3^10000 is a very high number.
 *
 * So, I switched to longs and it worked. I kinda wanna die.
 *
 * At least it wasn't all bad. I learned about DAGs, topological sort, and Kahn's Algorithm.
 */

// there is quite simply no shot
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;

	cin >> n >> m;

	vector<ll> mats(n, 0ll);
	vi depCount(n, 0);

	vector<vi> depRels(m, vi(3, 0));

	rep(i, 0, n) {
		cin >> mats[i];
	}

	rep(i, 0, m) {
		int dep, mat, amt;
		cin >> dep >> mat >> amt;
		depCount[dep]++;
		depRels[i] = vi{dep, mat, amt};
	}

//	// Kahn's Algorithm
//	queue<int> noDeps;
//	vi sortedDeps;
//
//	rep(i, 0, sz(depCount)) {
//		if(depCount[i] == 0) {
//			noDeps.push(i);
//		}
//	}
//	while(!noDeps.empty()) {
//		int v = noDeps.front();
//		noDeps.pop();
//		sortedDeps.push_back(v);
//
//		rep(i, 0, sz(depRels)) {
//			vi curRel = depRels[i];
//
//			int dep = curRel[0];
//			int mat = curRel[1];
//			int amt = curRel[2];
//
//			if(mat == v) {
//				depCount[dep]--;
//
//				if(depCount[dep] == 0) {
//					noDeps.push(dep);
//				}
//			}
//		}
//	}
//
//	rep(i, 0, sz(sortedDeps)) {
//		// cout << sortedDeps[i] << " ";
//		rep(j, 0, sz(depRels)) {
//			vi curRel = depRels[j];
//
//			int dep = curRel[0];
//			int mat = curRel[1];
//			int amt = curRel[2];
//
//			if(mat == sortedDeps[i]) {
//				mats[dep] += mats[mat] * amt;
//			}
//		}
//	}
//	// cout << "\n\n";

	while(!depRels.empty()) {
//		cout << "\nBeginning pass\n";
		for(int i = sz(depRels) - 1; i >= 0; i--) {
			vi curRel = depRels[i];
			int dep = curRel[0];
			int mat = curRel[1];
			int amt = curRel[2];

//			cout << "Need " << amt << " of " << dep << " to make " << mat << "\n";
//			cout << "depCount: " << depCount[mat] << "\n";

			if(depCount[mat] > 0) {
				continue;
			}

			mats[dep] += mats[mat] * amt;
			depCount[dep]--;
			depRels.erase(depRels.begin() + i);
		}
	}

	rep(i, 0, sz(mats) - 1) {
		cout << mats[i] << " ";
	}
	cout << mats[sz(mats) - 1] << "\n";
}
