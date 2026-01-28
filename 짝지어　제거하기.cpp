#include<iostream>
#include<stack>
#include<algorithm>
#include<string>
using namespace std;
//내코드
int solution(string s)
{
	stack<char> st;
	for (auto cs : s)
	{
		if (st.empty() || st.top() != cs)
			st.push(cs);
		else
		{
			st.pop();
		}
	}
	if (st.empty())
		return 1;
	else
		return 0;
}
int main()
{
	cout << solution("baabaa");
	cout << solution("cdcd");
}
//시간복잡도 :O(N)