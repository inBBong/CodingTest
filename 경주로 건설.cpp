#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct Point
{
	int x;
	int y;
	int cost;
	int direction;//0이면 세로 1이면 가로
};
bool isValid(int x, int y,int N)
{
	if (x >= 0 && x < N && y >= 0 && y < N)
		return true;
	else
		return false;
}
int solution(vector<vector<int>> board)
{
	Point* start = new Point(0, 0, 0, 0);//세로이동으로 시작	
	queue<Point*> q;
	bool visited[25][25] = {false};
	int dx[4] = { 0,1,0,-1 };//1,3 가로 이동
	int dy[4] = { 1,0,-1,0 };
	q.push(start);
	priority_queue<int, vector<int>, greater<int>> answer;
	while (!q.empty())
	{
		Point* curNode = q.front();
		q.pop();
		visited[curNode->y][curNode->x] = true;
		if (curNode->x == board.size() - 1 && curNode->y == board.size() - 1)
		{			
			answer.push(curNode->cost);
		}
		for (int i = 0; i < 4; ++i)
		{
			int nx = curNode->x + dx[i], ny = curNode->y + dy[i];
			if (!isValid(nx, ny, board.size())) continue;
			if (board[ny][nx] != 1 && !visited[ny][nx])
			{
				if(i%2== curNode->direction)//i를 2로 나눈 나머지가 direction과 같으면 직진도로
				{
					q.push(new Point{ nx,ny,curNode->cost + 100,curNode->direction });
				}
				else
				{
					q.push(new Point{ nx,ny,curNode->cost + 600,1-curNode->direction });
				}
			}
		}
	}

	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			visited[i][j] = false;
		}
	}

	start->direction = 1;//가로이동으로 출발
	q.push(start);
	while (!q.empty())
	{
		Point* curNode = q.front();
		q.pop();
		visited[curNode->y][curNode->x] = true;
		if (curNode->x == board.size() - 1 && curNode->y == board.size() - 1)
		{
			answer.push(curNode->cost);
		}
		for (int i = 0; i < 4; ++i)
		{
			int nx = curNode->x + dx[i], ny = curNode->y + dy[i];
			if (!isValid(nx, ny, board.size())) continue;
			if (board[ny][nx] != 1 && !visited[ny][nx])
			{
				if (i % 2 == curNode->direction)//i를 2로 나눈 나머지가 direction과 같으면 직진도로
				{
					q.push(new Point{ nx,ny,curNode->cost + 100,curNode->direction });
				}
				else
				{
					q.push(new Point{ nx,ny,curNode->cost + 600,1 - curNode->direction });
				}
			}
		}
	}



	return answer.top();
}

int main()
{
	cout << solution({ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }) << endl; //출력값 : 900
	cout << solution({ {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0},{0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 1, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0} }
	) << endl; //출력값 : 3800
	cout << solution({ {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 1, 0, 1}, {1, 0, 0, 0} }) << endl; //출력값 : 2100
	cout << solution({ {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 1}, {0, 1, 0, 0, 0, 1},{0, 0, 0, 0, 0, 0} }) << endl; //출력값 : 3200

}
//정답코드
#include <vector>
#include <queue>
#include <cstring>
#include <limits>

using namespace std;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };
const int STRAIGHT_COST = 100;
const int CORNER_COST = 600;
const int MAX_SIZE = 26;
const int INF = numeric_limits<int>::max();

struct Path {
	int y, x, direction;
};

bool isValid(int y, int x, int size) {
	return y >= 0 && y < size && x >= 0 && x < size;
}

int solution(vector<vector<int>> board) {
	int boardSize = static_cast<int>(board.size());
	int dist[MAX_SIZE][MAX_SIZE][4];
	memset(dist, -1, sizeof(dist));
	queue<Path> q;

	//❶ 시작 지점의 방향에 따라 비용이 달라질수 있으므로 모든 경우의 수 고려  
	q.push({ 0, 0, 1 });
	q.push({ 0, 0, 3 });

	dist[0][0][1] = 0;
	dist[0][0][3] = 0;

	while (!q.empty()) {
		auto [y, x, dir] = q.front();
		q.pop();

		int lastCost = dist[y][x][dir];

		//❷ 현재 지점을 기준으로 이동가능한 지점 확인  
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			//❸ 다음 이동할 후보 지점이 board안에 있는 좌표이고, 도려가 연결되 있는 경우
			if (!isValid(ny, nx, boardSize) || board[ny][nx]) continue;

			int newCost = lastCost + (i == dir ? STRAIGHT_COST : CORNER_COST);

			//❹ 아직 후보 지점을 방문하지 않았거나, 이전에 구했던 비용보다 더 적은 비용인 경우
			if (dist[ny][nx][i] == -1 || dist[ny][nx][i] > newCost) {
				dist[ny][nx][i] = newCost;
				q.push({ ny, nx, i });
			}
		}
	}

	//❺ 도착 지점까지 가는 모든 경로 중 최소를 선택
	int answer = INF;
	for (int i = 0; i < 4; i++) {
		if (dist[boardSize - 1][boardSize - 1][i] != -1) {
			answer = min(answer, dist[boardSize - 1][boardSize - 1][i]);
		}
	}

	return answer == INF ? -1 : answer;
}



//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{

	cout << solution({ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }) << endl; //출력값 : 900
	cout << solution({ {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0},{0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 1, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0} }
	) << endl; //출력값 : 3800
	cout << solution({ {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 1, 0, 1}, {1, 0, 0, 0} }) << endl; //출력값 : 2100
	cout << solution({ {0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0}, {0, 0, 1, 0, 0, 0}, {1, 0, 0, 1, 0, 1}, {0, 1, 0, 0, 0, 1},{0, 0, 0, 0, 0, 0} }) << endl; //출력값 : 3200

	return 0;
}
// 내 코드와 다른점:
// 정답코드와 내 코드 모두 너비우선탐색을 이용했다.
// 그러나 나의 코드는 visited 2차원 배열을 사용해서, 방문한 노드들을 체크했다. 이게 패착이었다.
// 너비우선 탐색은 모든 경로를 순회하는데, 가장 짧은 경로로 목적지에 도착 할 시 그 경로의 노드들의 
// visited가 모두 true가 되어 해당 경로와 겹치는데 더 저렴한 경로를 추가 할 수 없었다.
// 때문에 testcase 4는 더 비싸지만 경로가 더 짧은 3500원이 나와버렸다.
// 
// 반면 정답코드에서는 visited를 아예 사용하지 않았다. 해당 노드까지의 비용을 구조체 멤버 변수로 선언한 나와 달리
// 정답코드에서는 방향정보를 포함한 3차원 배열을 이용해 모든 노드마다 비용을 저장했다.
// 이는 중복된 경로를 가는 경우를 포함시킬 수 있게 했다.
// (=❹ 아직 후보 지점을 방문하지 않았거나, "이전에 구했던 비용보다 더 적은 비용인 경우"를 체크할 수 있게 함.)
// 
//
