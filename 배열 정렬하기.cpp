#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> solution(vector<int>& arr);

int main(void)
{
	vector<int>v = { 2,1,1,3,2,5,4};
	solution(v);
	for (auto cv : v)
		cout << cv<<endl;
}

vector<int> solution(vector<int>& arr)
{
	sort(arr.begin(), arr.end());
	return arr;
}
