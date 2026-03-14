#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
int solution(vector<int> topping)
{
	int answer(0);
	unordered_set<int>me;
	unordered_set<int>brother;
	for (auto ct : topping)
	{
		me.insert(ct);
	}
	int total,mytoppingCnt = me.size();
	if (total % 2 == 1)return 0;

	int mytoppingCnt = me.size();
	for (auto ct : topping)
	{
		brother.insert(ct);

	}
}
int main()
{
	cout << solution({ 1,2,1,3,1,4,1,2 });
	cout << solution({ 1,2,3,1,4});
}