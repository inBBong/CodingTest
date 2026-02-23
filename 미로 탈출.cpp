#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
bool visited[100][100] = { false };
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
struct Point
{
	int x;
	int y;
	int cnt;
	bool visitedLever;
};
void init()
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			visited[i][j] = false;
		}
	}
}
int solution(vector<string> maps)
{
	queue<Point> q;
	
	for (int i = 0; i < maps.size(); ++i)
	{
		for (int j = 0; j < maps[i].size(); ++j)
		{
			if (maps[i][j] == 'S')
			{
				Point start(j, i, 0,false);
				q.push(start);
				break;
			}
		}
	}
	while (!q.empty())
	{
		Point currentNode = q.front();
		q.pop();
		int CantMove(0);
		for(int i=0;i<4;++i)
		{
			if (currentNode.y + dy[i] >= maps.size() || currentNode.x + dx[i] >= maps[0].size())
			{
				CantMove++;
				if (CantMove == 4)
					return -1;
				continue;
			}
			if (maps[currentNode.y+dy[i]][currentNode.x+dx[i]] == 'O' && !visited[currentNode.y+dy[i]][currentNode.x+dx[i]])
			{
				Point newNode(currentNode.x + dx[i], currentNode.y + dy[i], currentNode.cnt + 1,currentNode.visitedLever);
				q.push(newNode);
				visited[newNode.y][newNode.x] = true;
			}
			else if (maps[currentNode.y + dy[i]][currentNode.x + dx[i]] == 'L' && !visited[currentNode.y + dy[i]][currentNode.x + dx[i]])
			{
				Point newNode(currentNode.x + dx[i], currentNode.y + dy[i], currentNode.cnt + 1, true);
				q.push(newNode);
				visited[newNode.y][newNode.x] = true;
			}
			else if (maps[currentNode.y + dy[i]][currentNode.x + dx[i]] == 'E' && !visited[currentNode.y + dy[i]][currentNode.x + dx[i]] &&currentNode.visitedLever)
			{
				return currentNode.cnt + 1;
			}
			else if (maps[currentNode.y + dy[i]][currentNode.x + dx[i]] == 'X' && !visited[currentNode.y + dy[i]][currentNode.x + dx[i]])
			{
				CantMove++;
				if (CantMove == 4)
					return -1;
			}

		}
	}
	
}
int main()
{
	cout << solution({ "SOOOL", "XXXXO", "OOOOO", "OXXXX", "OOOOE" }) << endl; //출력값 : 16
	init();
	cout << solution({ "LOOXS", "OOOOX", "OOOOO", "OOOOO", "EOOOO" }) << endl; //출력값 : -1
}
//정답코드
#include <string>
#include <vector>
#include <queue>

using namespace std;

// 현재 좌표와, 해당 좌표까지 이동횟수
struct Point {
	int y, x, cnt;
};

// 상하좌우로 이동하기 위한 오프셋
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int n, m;

// 현재 좌표가 유효한 좌표인이 확인
bool isWithinRange(int y, int x) {
	return 0 <= y && y < n && 0 <= x && x < m;
}

// 시작 좌표를 확인
Point findStartPoint(char start, vector<string>& maze) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (maze[i][j] == start) {
				return { i, j, 0 };
			}
		}
	}
	return { -1, -1, -1 }; // 시작점을 찾지 못한 경우
}

int bfs(char start, char end, vector<string>& maze) {

	//❶ 방문여부를 체크하는 배열
	bool visited[101][101] = { false };
	queue<Point> q;

	//❷ 시작노드부터 너비우선 탐색하도록 추가
	q.push(findStartPoint(start, maze));

	while (!q.empty()) {
		Point current = q.front();
		q.pop();

		//❸ 목적지에 도달했으면 해당 목적지 까지 이동횟수를 반환
		if (maze[current.y][current.x] == end) {
			return current.cnt;
		}
		//❹ 현재위치 기준 상하좌우를 확인 
		for (int i = 0; i < 4; i++) {
			int ny = current.y + dy[i];
			int nx = current.x + dx[i];

			if (isWithinRange(ny, nx) && !visited[ny][nx] && maze[ny][nx] != 'X') {
				//❺ 후보좌표가 미로 범위내에 있고, 아직 방문하지 않았으면 탐색대상으로 추가
				q.push({ ny, nx, current.cnt + 1 });
				visited[ny][nx] = true;
			}
		}
	}
	return -1;
}

int solution(vector<string> maps) {
	n = maps.size();
	m = maps[0].size();

	//❻ 시작지점부터 L까지 최단거리를 구함 
	int distanceToL = bfs('S', 'L', maps);
	if (distanceToL == -1) return -1;

	//❼ L부터 도착지점까지 최단거리를 구함
	int distanceToE = bfs('L', 'E', maps);
	return distanceToE == -1 ? -1 : distanceToL + distanceToE;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution({ "SOOOL", "XXXXO", "OOOOO", "OXXXX", "OOOOE" }) << endl; //출력값 : 16
	cout << solution({ "LOOXS", "OOOOX", "OOOOO", "OOOOO", "EOOOO" }) << endl; //출력값 : -1

	return 0;
}
// 내 코드와 다른점 :
// 우선 너비우선 탐색을 이용한다는 아이디어는 동일하다.
// 하지만, 정답코드에서는 유효한 좌표인지를 확인하는 함수를 따로 만들었고,
// 나는 너비우선탐색을 하다가 L을 만나면 visitedLever를 true로 만들어서,
// E를 만났을때 visitedLever이 true일때만 리턴을 했다. 하지만 정답코드에서는
// bfs 함수에서 start와 end를 정해주고, 시작지점에서부터 레버까지의 거리, 레버부터 종료지점까지의 거리를
// 구해서 더해주었다. 이렇게 하면 구조체에 멤버 visitedLever를 뺄 수 있기때문에 메모리가 절약된다.
// 또한 주요 로직에서 나는 newNode의 위치에 O,X,L,E 모든 경우를 고려해서 구현하였는데 
// 정답코드에서는 X일때만 따로 구현, 나머지는 동일하게 push했다. 이렇게 하면 코드가 훨씬 간결해진다.
// 그리고 나는 E를 만나자마자 return 했고, 정답코드에서는 우선 push 한 뒤, 해당 Point를 pop 하고 나서
// 매개변수 end와 비교해서 return을 했다.
// 또한 나는 dx,dy를 4번 순회했을때 갈 곳이 없을때만 -1을 리턴했는데,
// 정답코드에서는 갈 수 있는 모든 경로를 순회했지만 유의미한 리턴값이 없을때 -1을 리턴한다.
// 예외가 없는 훌륭한 방식이다. 내가 한 방식대로 하면 레버를 들렀다가 종료지점에 도착하지 않았을때 -1을 리턴할 수 없다.
// 
// 시간복잡도 : O(N^2)
// 