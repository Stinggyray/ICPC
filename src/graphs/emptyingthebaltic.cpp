#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int (i) = a; (i) < (b); ++(i))
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
 * PROBLEM LINK: https://open.kattis.org/problems/emptyingbaltic
 *
 * Algorithm explanation:
 * This nutcase wants to delete the Baltic.
 *
 * So, what we obviously need to do is a floodfill.
 * Since the maximum drainage for a certain cell can be determined by MORE than just one tile, a DFS
 * flood-fill will not do, because it doesn't set the highest possible drain after 1 visit. We need to let tiles be
 * visited multiple times, and change their drainage if applicable.
 *
 * The maximum drainage is determined by the minimum between the depth of that tile, and the maxdrainage of the
 * neighboring tile. This is run multiple times against each tile to ensure that each of them is selecting the highest
 * drainage available to them.
 *
 * Notably, we have to use a priority queue to prioritize things with a HIGHER max depth. We need to resolve all of those
 * in the queue first, so we don't get the results of the lower depths first.
 */

vector<vi> grid;
vector<vi> maxDrain;
vector<vector<bool>> visited;

const int R_CHANGE[]{0, 0, 1, 1, 1, -1, -1, -1};
const int C_CHANGE[]{1, -1, -1, 0, 1, -1, 0, 1};

int h, w;

struct tile {
	int r, c, maxDepth;
};

// define a custom sort so the priority queue can work
bool operator<(const tile& tile1, const tile& tile2) {
	if(tile1.maxDepth != tile2.maxDepth) {
		return tile1.maxDepth < tile2.maxDepth;
	}
	if(tile1.c != tile2.c) {
		return tile1.c < tile2.c;
	}
	return tile1.r < tile2.r;
};

void floodfill(int r, int c) {
	priority_queue<tile> frontier;
	frontier.push({r, c, maxDrain[r][c]});

	while(!frontier.empty()) {
		r = frontier.top().r;
		c = frontier.top().c;
		frontier.pop();

		if (visited[r][c]) {
			continue;
		}
		visited[r][c] = true;

		rep(i, 0, 8) {
			int nextR = r + R_CHANGE[i];
			int nextC = c + C_CHANGE[i];

			if (nextR < 0 || nextR >= h || nextC < 0 || nextC >= w) { // out of bounds
				continue;
			}

			if (maxDrain[nextR][nextC] < min(maxDrain[r][c], -grid[nextR][nextC])) {
				maxDrain[nextR][nextC] = min(maxDrain[r][c], -grid[nextR][nextC]);
				frontier.push({nextR, nextC, maxDrain[nextR][nextC]});
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> h >> w;

	grid = vector<vi>(h, vi(w));
	maxDrain = vector<vi>(h, vi(w, 0));
	visited = vector<vector<bool>>(h, vector<bool>(w, false));

	rep(i, 0, h) {
		rep(j, 0, w) {
			cin >> grid[i][j];
		}
	}

	int a, b;

	cin >> a >> b;
	a--;
	b--;
	maxDrain[a][b] = -grid[a][b];

	floodfill(a, b);

	ll total = 0;

	rep(i, 0, h) {
		rep(j, 0, w) {
			total += maxDrain[i][j];
		}
	}

	cout << total << "\n";
}
