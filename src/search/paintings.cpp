#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
 * PROBLEM LINK: https://open.kattis.org/problems/paintings
 *
 * Algorithm explanation:
 * For getPaintings
 */

vector<vi> hideous;
vector<string> colors;

vi best;
int totalcount;

void printVec(vi vec) {
	cout << "[ ";
	rep(i, 0, sz(vec)) {
		cout << vec[i] << " ";
	}
	cout << "]\n";
}

void getPaintings(vi remaining, vi painting) {
	if(sz(remaining) == 0) {
		totalcount++;

		if(totalcount == 1) {
			rep(i, 0, sz(painting)) {
				best[i] = painting[i];
			}
		}
	}

	rep(i, 0, sz(remaining)) {
		if(!painting.empty() && hideous[painting.back()][remaining[i]] == 1) {
			continue;
		}

		vi copyRem;
		copy(all(remaining), back_inserter(copyRem));

		vi copyPaint;
		copy(all(painting), back_inserter(copyPaint));

		int curColor = copyRem[i];
		copyRem.erase(copyRem.begin() + i);
		copyPaint.push_back(curColor);

		getPaintings(copyRem, copyPaint);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	rep(testcase, 0, t) {
		int n;
		cin >> n;

		colors = vector<string>(n);
		hideous = vector<vi>(n, vi(n, 0));
		best = vi(n);
		totalcount = 0;

		vi initial;

		rep(i, 0, n) {
			string cur;
			cin >> cur;

			colors[i] = cur;
			initial.push_back(i);
		}

		int m;
		cin >> m;

		rep(i, 0, m) {
			string col1;
			string col2;

			cin >> col1 >> col2;

			int index1;
			int index2;

			rep(j, 0, n) {
				if(col1 == colors[j]) {
					index1 = j;
				}
				else if(col2 == colors[j]) {
					index2 = j;
				}
			}

			hideous[index1][index2] = 1;
			hideous[index2][index1] = 1;
		}

		getPaintings(initial, vi());

		cout << totalcount << "\n";
		rep(i, 0, n - 1) {
			cout << colors[best[i]] << " ";
		}
		cout << colors[best[n - 1]] << "\n";
	}
}
