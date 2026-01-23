#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> solution(vector<int>&lst)
{
	sort(lst.rbegin(), lst.rend());
	lst.erase(unique(lst.begin(), lst.end()), lst.end());
	return lst;
}
int main()
{
	vector<int> v = { 2,1,1,3,2,5,4 };
	solution(v);
	for (auto cv : v)
	{
		cout << cv << endl;
	}
}




