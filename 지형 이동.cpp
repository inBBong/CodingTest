#include<iostream>
#include<vector>
using namespace std;
bool visited[301][301];
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
struct pos
{
	int x;
	int y;
	int h;
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
	pos* p = new pos(0, 0, land[0][0]);
	visited[0][0] = true;
	while (AllVisited(N))
	{

		for (int i = 0; i < 4; ++i)
		{
			int newx = p->x + dx[i], newy = p->y + dy[i];
			int newh = land[newy][newx];
			if (!isValid(N, newx, newy)&&abs(p->h-newh)<=height)
				continue;
			else
			{
				p->x = newx;
				p->y = newy;
				p->h = newh;
				visited[newy][newx] = true;
			}
		}
	}
}
void init()
{

}
int main()
{
	cout << solution({ {1, 4, 8, 10}, {5, 5, 5, 5}, {10, 10, 10, 10}, {10, 10, 10, 20} }, 3) << endl; //출력값 : 15
	init();
	cout << solution({ {10, 11, 10, 11}, {2, 21, 20, 10}, {1, 20, 21, 11}, {2, 1, 2, 1} }, 1) << endl; //출력값 : 18

}