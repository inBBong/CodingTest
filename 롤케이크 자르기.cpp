#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;
int solution(vector<int> topping)
{
	int answer(0);
	vector<int>me(topping.size());
	unordered_set<int>brother;
	int myTopping(0);
	for (auto ct : topping)
	{
		me[ct]++;
		if (me[ct] == 1)
			myTopping++;
	}	
	
	for (auto cut : topping)
	{
		brother.insert(cut);
		me[cut]--;
		if (me[cut] == 0)
			myTopping--;
		if (myTopping == brother.size())
			answer++;
	}
	return answer;
}
int main()
{
	cout << solution({ 1,2,1,3,1,4,1,2 });
	cout << solution({ 1,2,3,1,4});
}
//정답코드 :
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int solution(vector<int> topping) {
	int answer = 0;

	//❶ 남아있는 각 토핑의 개수
	unordered_map<int, int> topping_cnt;
	//❷ 절반에 속한 토핑의 종류
	unordered_set<int> half_topping;

	//❸ 카운터에 각 토핑의 개수를 저장
	for (auto top : topping) {
		if (topping_cnt.find(top) == topping_cnt.end()) {
			topping_cnt[top] = 1;
		}
		else {
			topping_cnt[top]++;
		}
	}

	//❹ 앞에서 부터 토핑을 순서대로 순회
	for (int i = 0; i < topping.size(); i++) {
		//❺ 절반에 속하는 토핑에 추가하고, 남은 토핑개수에서 제외
		half_topping.insert(topping[i]);
		topping_cnt[topping[i]]--;
		//❻ 현재 토핑이 남아있지 않은 경우 남은 토핑 목록에서 삭제
		if (topping_cnt[topping[i]] == 0) {
			topping_cnt.erase(topping[i]);
		}
		//❼ 공평한 경우 카운팅
		if (topping_cnt.size() == half_topping.size()) {
			answer++;
		}
	}

	return answer;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;


int main()
{
	cout << solution({ 1, 2, 1, 3, 1, 4, 1, 2 }) << endl; // 출력값 : 2
	cout << solution({ 1, 2, 3, 1, 4 }) << endl; // 출력값 : 0

	return 0;
}
// 내 코드와 다른 점:
// 나의 토핑을 모든토핑으로 시작해서 앞에서부터 하나씩 잘라 공평해질때 answer을 추가하는 로직은 나와 같다.
// 한 가지 다른 점이 있는데, 그것은 나는 나의 토핑을 vector로, 정답코드에서는 unordered_map으로 선언했다는 것이다.
// 나의 토핑을 vector로 선언했을때 문제점은, 나의 토핑의 공간에 0을 값으로 갖는 부분이 있어 공간의 낭비가
// 생길 수 있고, 나의 토핑의 size로 내 토핑의 종류의 수를 판단 할 수 없다는 점이다. 이 문제점을 정답코드에서는
// unordered_map을 사용함으로써 보완했다.
// 
// 시간복잡도 : O(N)
//