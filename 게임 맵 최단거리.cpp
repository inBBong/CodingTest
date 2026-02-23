#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
bool visited[101][101] = { false };
int n, m;
struct Point
{
	int x;
	int y;
	int cnt;
};
void init()
{
	for (int i = 0; i < 101; ++i)
	{
		for (int j = 0; j < 101; ++j)
		{
			visited[i][j] = false;
		}
	}
}
bool isValid(int x, int y)
{
	if (x < m && y < n &&x>=0&&y>=0)
		return true;
	else
		return false;
}
int solution(vector<vector<int>>maps)
{
	n = maps.size();
	m = maps[0].size();
	
	queue<Point> q;
	q.push({0,0,1});
	while (!q.empty())
	{
		Point currentNode = q.front();
		q.pop();
		if (currentNode.x == m - 1 && currentNode.y == n - 1)
			return currentNode.cnt;
		for (int i = 0; i < 4; ++i)
		{
			int ny = currentNode.y + dy[i];
			int nx = currentNode.x + dx[i];

			if (isValid(nx,ny) && maps[ny][nx] == 1 && !visited[ny][nx])
			{
				q.push({ nx,ny,currentNode.cnt + 1 });
				visited[ny][nx] = true;
			}
		}
	}
	return -1;
}
int main()
{
	cout << solution({ {1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1} }) << endl; //출력값 : 11
	init();
	cout << solution({ {1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 0}, {0, 0, 0, 0, 1} }) << endl; //출력값 : -1

}
// 정답코드
#include <vector>
#include <queue>
using namespace std;

const int MAX_SIZE = 100;
const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };
int check[MAX_SIZE][MAX_SIZE];

//❶ 좌표 정보 및 관련 연산을 하기 위한 구조체
struct Point {
	int y, x;

	Point(int y, int x) : y(y), x(x) {}

	bool isValid(int width, int height) const {
		return y >= 0 && y < height && x >= 0 && x < width;
	}

	Point move(int i) const {
		return Point(y + dy[i], x + dx[i]);
	}

	bool canMoveTo(const vector<vector<int>>& maps) const {
		return maps[y][x] == 1 && check[y][x] == 0;
	}
};

queue<Point> q; // BFS를 위한 큐

int solution(vector<vector<int>> maps) {
	int width = maps[0].size(), height = maps.size();
	q.push({ 0, 0 });
	check[0][0] = 1;

	// ❷ 너비우선탐색 진행
	while (!q.empty()) {
		Point current = q.front();
		q.pop();
		//❸ 현재좌표 기준으로 상하좌우를 확인
		for (int i = 0; i < 4; i++) {
			Point next = current.move(i);
			//❹ 범위나 좌표이고 벽이 아닌 경우
			if (next.isValid(width, height) && next.canMoveTo(maps)) {
				check[next.y][next.x] = check[current.y][current.x] + 1;
				q.push({ next.y, next.x });
			}
		}
	}

	//❺ 목적지에 도달가능 여부를 확인 
	int destinationX = width - 1, destinationY = height - 1;
	if (check[destinationY][destinationX] == 0) {
		return -1; // 도착 지점에 도달할 수 없음
	}

	return check[destinationY][destinationX]; // 도착 지점까지의 최단 거리 반환
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

void init()
{
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			check[i][j] = false;
}
int main()
{

	cout << solution({ {1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1} }) << endl; //출력값 : 11
	init();
	cout << solution({ {1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 0}, {0, 0, 0, 0, 1} }) << endl; //출력값 : -1

	return 0;
}
// 내 코드와 다른점 :
// 이번 문제는 전 문제와 유사해서 전 문제의 해답을 떠올리며 구현했다.
// 이번 문제의 정답코드는 check라는 이차원 int형 배열을 선언하고, point의 이동경로마다 check 값을 +1 해줘서,
// check[n-1][m-1]을 리턴한다.
// 또한 구조체의 멤버함수 isValid, move, CanmoveTo를 선언해서 사용했다.
// 시간복잡도 : O(M*N)
//