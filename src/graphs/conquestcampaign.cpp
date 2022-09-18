#include<bits/stdc++.h>

using namespace std;

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
