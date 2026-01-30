#include<iostream>
#include<vector>
#include<string>
using namespace std;
vector<bool>solution(vector<string> string_list, vector<string> query_list)
{

}
int main()
{
	vector<string> v = { "apple","banana","cherry" };
	vector<string> v2 = { "banana","kiwi","melon","apple" };
	vector<bool>answer;
	answer = solution(v, v2);
	for (auto ca : answer)
		cout << ca<<" ";

}
