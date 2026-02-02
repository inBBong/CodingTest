#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//내코드 (정답코드와 동일 : sort()하는 아이디어만 얻음)
bool solution(vector<string> phoneBook)
{
	sort(phoneBook.begin(), phoneBook.end());
	for (int i = 1; i < phoneBook.size(); ++i)
	{
		if (phoneBook[i].substr(0, phoneBook[i - 1].size()) == phoneBook[i - 1])
			return false;
	}
	return true;
}
int main()
{
	cout << solution({ "119", "97674223", "1195524421" }) << endl; //출력값 : 0
	cout << solution({ "123", "456", "789" }) << endl; //출력값 : 1
	cout << solution({ "12", "123", "1235", "567", "88" }) << endl; //출력값 : 0
}
//시간복잡도 : O(NlogN)