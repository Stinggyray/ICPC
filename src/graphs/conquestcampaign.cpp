#include<bits/stdc++.h>

using namespace std;

/*
 * PROBLEM LINK: https://open.kattis.com/problems/conquestcampaign
 *
 * Algorithm explanation:
 * It's literally just brute force. With only 10,000 cells total and 1 <= R, C <= 100, this is very easy to brute force.
 *
 * We go day by day, and just push all of the newly added squares to a queue, to check the next day. We make sure to
 * respect boundaries and mark things as visited as we go.
 */

bool inbounds(int x, int y, int xbound, int ybound) {
	return x >= 0 && y >= 0 && x < xbound && y < ybound;
}

int r, c, n;
vector<vector<int>> board;

bool unvisited(int x, int y) {
	return inbounds(x, y, r, c) && board[x][y] == 69420;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	cin >> r >> c >> n;

	board = vector<vector<int>>(r, vector<int>(c, 69420));

	queue<pair<int, int>> pts;
	for(int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		board[x][y] = 1;
		pts.push({x, y});
	}

	int days = 1;

	while(!pts.empty()) {
		int x = pts.front().first;
		int y = pts.front().second;

		pts.pop();

		if(unvisited(x - 1, y)) {
			pts.push({x - 1, y});
			board[x - 1][y] = board[x][y] + 1;
			days = board[x - 1][y];
		}
		if(unvisited(x + 1, y)) {
			pts.push({x + 1, y});
			board[x + 1][y] = board[x][y] + 1;
			days = board[x + 1][y];
		}
		if(unvisited(x, y - 1)) {
			pts.push({x, y - 1});
			board[x][y - 1] = board[x][y] + 1;
			days = board[x][y - 1];
		}
		if(unvisited(x, y + 1)) {
			pts.push({x, y + 1});
			board[x][y + 1] = board[x][y] + 1;
			days = board[x][y + 1];
		}
	}

	cout << days << "\n";
}
