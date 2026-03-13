#include<iostream>
#include<vector>
#include<queue>
using namespace std;
bool visited[301][301];
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
struct pos
{
	int x;
	int y;
	int h;
	bool operator<(const pos& p) const
	{
		return h > p.h;
	}
};
bool AllVisited(int N)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (visited[i][j] == false)
				return false;
		}
	}
	return true;
}
bool isValid(int N,int x,int y)
{
	if (x >= 0 && x < N && y >= 0 && y < N&&visited[y][x]==false)
		return true;
	else
		return false;
}
int solution(vector<vector<int>> land, int height)
{
	int N = land.size();
	pos start(0, 0, 0);
	priority_queue<pos>pq;
	pq.push(start);
	int totalCost(0);
	while (!pq.empty())
	{
		
		pos current = pq.top();
		pq.pop();
		if (!isValid(N, current.x, current.y))
			continue;
		totalCost += current.h;
		for (int i = 0; i < 4; ++i)
		{
			int newx = current.x + dx[i], newy = current.y + dy[i];			
			if (!isValid(N, newx, newy))
				continue;
			int diff = abs(land[current.y][current.x] - land[newy][newx]);
			if (diff <= height)
			{
				pq.push(pos(newx, newy, 0));
			}
			else
			{
				pq.push(pos(newx, newy, diff));
			}
		}
			visited[current.y][current.x] = true;
	}
	return totalCost;
}
void init()
{
	for (int i = 0; i < 301; ++i)
	{
		for (int j = 0; j < 301; ++j)
			visited[i][j] = false;
	}
}
int main()
{
	cout << solution({ {1, 4, 8, 10}, {5, 5, 5, 5}, {10, 10, 10, 10}, {10, 10, 10, 20} }, 3) << endl; //출력값 : 15
	init();
	cout << solution({ {10, 11, 10, 11}, {2, 21, 20, 10}, {1, 20, 21, 11}, {2, 1, 2, 1} }, 1) << endl; //출력값 : 18

}
//정답코드
//#include <vector>
//#include <queue>
//#include <algorithm>
//
//using namespace std;
//
////❶ 현재칸의 좌표와 이전칸에서 현재칸으로 가는 비용
//struct Pos {
//	int r;
//	int c;
//	int heightDiff;
//	bool operator<(const Pos& p) const {
//		return heightDiff > p.heightDiff;
//	}
//};
//
//int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, 1, 0, -1 };
//bool visited[301][301];
////❷ 다음 이동할 칸이 격자 내에 존재하는 좌표인지 확인
//bool isValid(int nr, int nc, int rows, int cols) {
//	return nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc];
//}
//
//int solution(vector<vector<int>> land, int height) {
//	int totalCost = 0;
//	int rows = land.size(), cols = land[0].size();
//
//	priority_queue<Pos> pq;
//	pq.push({ 0, 0, 0 });
//
//	while (!pq.empty()) {
//		Pos current = pq.top();
//		pq.pop();
//
//		//❸ 이미 방문한 칸은, 또 방문하지 않음
//		if (visited[current.r][current.c])
//			continue;
//		//❹ 현재 칸으로 이동하는 비용을 추가
//		totalCost += current.heightDiff;
//		//❺ 현재칸의 인접 칸을 순회
//		for (int i = 0; i < 4; i++) {
//			int nr = current.r + dy[i], nc = current.c + dx[i];
//			if (isValid(nr, nc, rows, cols)) {
//				//❻ 이동가능한 칸과 현재칸의 높이차를 구함
//				int diff = abs(land[current.r][current.c] - land[nr][nc]);
//				//❼ 높이차가 사다리 설치 기준보다 큰 경우
//				if (diff > height)
//					pq.push({ nr, nc, diff });
//				//❽ 높이차가 사다리 설치 기준보다 크지 않은 경우
//				else
//					pq.push({ nr, nc, 0 });
//			}
//		}
//		//❾ 현재 칸을 방문여부를 표시
//		visited[current.r][current.c] = true;
//	}
//
//	return totalCost;
//}
//
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//
//using namespace std;
//
//void init()
//{
//	for (int i = 0; i <= 300; i++)
//		for (int j = 0; j <= 300; j++)
//			visited[i][j] = 0;
//}
//
//int main()
//{
//	cout << solution({ {1, 4, 8, 10}, {5, 5, 5, 5}, {10, 10, 10, 10}, {10, 10, 10, 20} }, 3) << endl; //출력값 : 15
//	init();
//	cout << solution({ {10, 11, 10, 11}, {2, 21, 20, 10}, {1, 20, 21, 11}, {2, 1, 2, 1} }, 1) << endl; //출력값 : 18
//
//	return 0;
//}
// 내 코드와 다른 점:
// 이번에도 정답률 14퍼짜리 괴물문제였다. 하지만 백트래킹의 괴물문제에 비하면 그나마 풀만 했던 것 같다. 물론 못풀었다.
// 내힘으로는 구현하지 못했고, 정답코드를 분석해서 이해하고 혼자 짜면서 구현을 해냈다.
// priority_queue에 대해서 더 공부했고, Pos 구조체의 operator< 함수를 공부했다.
// priority_queue<Pos>를 선언하면 자동으로 operator<함수의 우선순위대로 우선순위큐가 구성된다는 것을 알았다.
// operator< 함수의 리턴값이 heightDiff < p.heightDiff;면 더 작은 값을 아래로 보내는 최대힙,
// operator< 함수의 리턴값이 heightDiff > p.heightDiff;면 더 큰 값을 아래로 보내는 최소힙 구조라는 것을 알게 됐다.
// 
// 시간복잡도 : O(N^2log(N^2))
//