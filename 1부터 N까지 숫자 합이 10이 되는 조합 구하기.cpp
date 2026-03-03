#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>>answer;
vector<int>selected_num;
void backtrack(int N,int sum,int start)
{
	if (sum == 10)
	{
		answer.push_back(selected_num);
		return;
	}

	for (int i = start; i < N + 1; ++i)
	{
		if (sum+i > 10)
			return;
		selected_num.push_back(i);
		backtrack(N, sum + i, i + 1);
		selected_num.pop_back();
	}
}
vector<vector<int>> solution(int N)
{
	backtrack(N, 0, 1);
	return answer;
}
void init()
{
	answer.clear();
	selected_num.clear();
}
int main()
{
	vector<vector<int>> a = solution(5);
	init();
	vector<vector<int>> b = solution(2);
	init();
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
// 이번 문제는 너무 어려웠다. 머리를 계속 굴려도 어떻게 구현해야하는지 감이 안왔다.
// 그래서 그냥 정답코드를 보고 생각 나는 대로 코딩을 했다.
// 나중에 다시 풀어봐야겠다 ㅠㅠ.
// 시간 복잡도 : O(N!)