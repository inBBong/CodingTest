#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
void dikstra(unordered_map<int, vector<int>>&linked,vector<int>& dis)
{
	for (int i = 0; i < linked[1].size(); ++i)
	{
		linked[1][i]
	}
}
int solution(int N, vector<vector<int>> road, int K)
{
	int answer(0);
	unordered_map<int, vector<vector<int>>>linked(N+1);
	vector<int>dis(N + 1,2000);
	for (int i = 0; i < road.size(); ++i)
	{
		linked[road[0][0]].push_back(road[0][1]);
		linked[road[0][0]].push_back(road[0][2]);
	}
	dis[1] = 0;
	dikstra(linked, dis);
	return answer;
}
int main()
{
	cout << solution(5, { {1, 2, 1}, {2, 3, 3}, {5, 2, 2}, {1, 4, 2}, {5, 3, 1}, {5, 4, 2} }, 3) << endl; //출력값 : 4
	cout << solution(6, { {1, 2, 1}, {1, 3, 2}, {2, 3, 2}, {3, 4, 3}, {3, 5, 2}, {3, 5, 3}, {5, 6, 1} }, 4) << endl; //출력값 : 4
	
}