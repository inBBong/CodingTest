#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>>answer;
vector<int>selected_num;
vector<vector<int>> solution(int N)
{
	int sum(0);
	for (int i = 1; i < N; ++i)
	{
		selected_num.push_back(i);
		sum += i;
		if (sum == 10)
			answer.push_back(selected_num);
	}
}
int main()
{
	vector<vector<int>> a = solution(5);
	vector<vector<int>> b = solution(2);
	vector<vector<int>> c = solution(7);

	for (auto ca : a)
	{
		for (auto cca : ca)
			cout << cca << " ";
		cout << endl;
	}
	for (auto cb : b)
	{
		for (auto ccb : cb)
			cout << ccb << " ";
		cout << endl;
	}
	for (auto cc : c)
	{
		for (auto ccc : cc)
			cout << ccc << " ";
		cout << endl;
	}
}