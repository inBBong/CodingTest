#include<iostream>
#include<vector>
using namespace std;
vector<int>lionInfo(11,0);
int ScoreGap(vector<int>appeach, vector<int>lion,int maxAppeach)
{
	int lionScore(0);
	int appeachScore(maxAppeach);

	for (int i = 0; i < 11; ++i)
	{
		if (appeach[i] < lion[i])
		{
			lionScore += 10 - i;
			appeachScore -= 10 - i;
		}
		
	}
	if (appeachScore < lionScore)
		return lionScore - appeachScore;
	else
		return -1;
}
void backTrack(int n)
{
	
	for (int i = 0; i < n; ++i)
	{
		lionInfo[]
	}
}
vector<int> solution(int n, vector<int> info)
{
	vector<int>lionInfo(11, 0);
	int maxAppeachScore(0);
	for (int i = 0; i < 11; ++i)
	{
		if (info[i] != 0)
			maxAppeachScore += 10 - i;
	}
	backTrack(n);
}
void init()
{
	for (int i = 0; i < 11; ++i)
	{
		lionInfo[i] = 0;
	}
}
int main()
{
	vector<int>a, b, c;
	a=solution(5, { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }); //출력값 : 0 2 2 0 1 0 0 0 0 0 0 
	init();
	b=solution(1, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }); //출력값 : -1
	init();
	c=solution(9, { 0, 0, 1, 2, 0, 1, 1, 1, 1, 1, 1 }); //출력값 : 1 1 2 0 1 2 2 0 0 0 0 

	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
	for (auto cc : c)
		cout << cc << " ";
}