#include<iostream>
#include<queue>

using namespace std;

int solution(int N, int K)
{
	queue<int> q;
	for (int i = 0; i < N; ++i)
	{
		q.push(i + 1);
	}
	while(q.size()!=1)
	{
		for (int i = 0; i < K - 1; ++i)
		{
			int data = q.front();
			q.pop();
			q.push(data);
		}
		q.pop();
	}
	return q.front();
}

int main()
{
	cout<<solution(5, 3);
}
//시간복잡도 : O(N*K)