#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
//int dx[4] = {1,0,-1,0};
//int dy[4] = {0,1,0,-1};
int n, m;
bool isValid(int r, int c) { return r < 0 || r >= n || c < 0 || c >= m; }
int playGame(vector<vector<int>>&board, int curR,int curC, int opR, int opC)
{
	if (board[curR][curC]==0)
		return 0;
	int bestSteps = 0;
	for (int dir = 0; dir < 4; ++dir)
	{
		int nextR = curR + dx[dir];
		int nextC = curC + dy[dir];

		if (isValid(nextR, nextC) || board[nextR][nextC] == 0)
			continue;
		board[curR][curC] = 0;
		int steps = playGame(board, opR, opC, nextR, nextC) + 1;
		board[curR][curC] = 1;

		if (bestSteps % 2 == 0 && steps % 2 == 1)
			bestSteps = steps;
		else if (bestSteps % 2 == 0 && steps % 2 == 0)
			bestSteps = max(bestSteps, steps);
		else if (bestSteps % 2 == 1 && steps % 2 == 1)
			bestSteps = min(bestSteps, steps);
	}
	return bestSteps;
}
int solution(vector<vector<int>>board, vector<int> aloc, vector<int> bloc)
{
	n = board.size();
	m = board[0].size();
	return playGame(board, aloc[0], aloc[1], bloc[0], bloc[1]);
	
}
int main()
{
	cout << solution({ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} }, { 1, 0 }, { 1, 2 }) << endl;//출력값 : 5
	cout << solution({ {1, 1, 1}, {1, 0, 1}, {1, 1, 1} }, { 1, 0 }, { 1, 2 }) << endl;//출력값 : 4
}
// 진짜 어렵다... 겸손하게 만들어주는 문제였다.
// 풀이 영상을 보고 정답 코드를 보고 이해는 했는데, 다시 구현하려고 하니 다시 막혔다.
// 이건 다음에 다시 무조건 풀어봐야겠다.
//