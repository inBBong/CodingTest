#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
//내코드
// 실제 주문의 조합을 구하는 함수
map<string, int>courseCnt;
void combination(string src, string dst, int depth) {
	if (dst.size() == depth)
		courseCnt[dst]++;
	else for (int i = 0; i < src.size(); i++)
		combination(src.substr(i + 1), dst + src[i], depth);
}
vector<string> solution(vector<string> orders, vector<int> course)
{
	vector<string> answer;
	for (string& order : orders)
		sort(order.begin(), order.end());
	for (int j = 0; j < course.size(); ++j)
	{
		for (int i = 0; i < orders.size(); ++i)		
			combination(orders[i], "", course[j]);

			int maxOrder = 0;
			for (auto it : courseCnt)
				maxOrder = max(maxOrder, it.second);
			for (auto it : courseCnt)
				if (maxOrder >= 2 && it.second == maxOrder)
					answer.push_back(it.first);
			courseCnt.clear();
		
	}
		sort(answer.begin(), answer.end());
		return answer;
}
int main()
{
	//combination("abc", "", 2);
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
// 직접 짜보려고 했는데 진짜 너무 어렵고 이해가 잘 안돼서 결국 정답코드를 보고 작성해버렸다.
// 일단 combine 함수를 보고 이해가 너무 안됐다. 하지만 그림을 보고, src에서 문자 하나씩 뽑고, 뒤 문자들을 붙이는
// 식으로 조합을 생성하고 depth와 길이가 같아지면 리턴한다는 것을 이해했다.
// 또한 각 조합을 키로 하고 횟수를 값으로 하는 맵을 선언하는 아이디어는 떠올리긴 했는데 그 이후로 어떻게 해야할지 감이 아예 안왔다.
// 정답코드에서는 algorithm의 max 함수를 이용해서 가장 많이 주문된 코스를 저장한다.
// answer을 반환하기 전에 정렬을 한다.
// 더 공부해보고 반드시 한번 더 풀어보는게 좋을 것 같다.
// 
//시간복잡도 :O(M*N^2)