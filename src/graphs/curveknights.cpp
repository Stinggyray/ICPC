#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
