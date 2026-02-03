#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<string> solution(vector<string> orders, vector<int> course)
{

}
int main()
{
	vector<string> v = solution({ "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" }, { 2, 3, 4 });
	vector<string> v2 = solution({ "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" }, { 2, 3, 5 });
	vector<string> v3 = solution({ "XYZ", "XWY", "WXA" }, { 2, 3, 4 });
	for (auto cv : v)
		cout << cv << " ";
	for (auto cv : v2)
		cout << cv << " ";
	for (auto cv : v3)
		cout << cv << " ";
}