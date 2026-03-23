#include<iostream>
#include<vector>
using namespace std;

vector<int> solution(int amount)
{
	vector<int>answer;
	while (amount)
	{
		if (amount >= 100)
		{
			answer.push_back(100);
			amount -= 100;
		}
		else if (amount >= 50)
		{
			answer.push_back(50);
			amount -= 50;
		}
		else if (amount >= 10)
		{
			answer.push_back(10);
			amount -= 10;
		}
		else
		{
			answer.push_back(1);
			amount -= 1;
		}
	}
	return answer;
}
int main()
{
	vector<int> a=solution(123); //출력값 : 100 10 10 1 1 1
	vector<int> b=solution(350); //출력값 : 100 100 100 50

	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
}
//정답코드
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int amount) {
	vector<int> denominations = { 1, 10, 50, 100 };
	sort(denominations.rbegin(), denominations.rend()); //❶ 화폐 단위를 큰 순서대로 정렬

	vector<int> change; //❷ 거스름돈을 담을 벡터
	for (int coin : denominations) {
		while (amount >= coin) { //❸ 해당 화폐 단위로 거스름돈을 계속 나눠줌
			change.push_back(coin); //❹ 거스름돈 벡터 업데이트
			amount -= coin; //❺ 정산이 완료된 거스름돈 뺌
		}
	}
	return change; //❻ 거스름돈 반환
}



//아래 코드는 테스트 코드 입니다.
#include <iterator>
#include <iostream>

using namespace std;

void print(vector<int> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}


int main()
{
	print(solution(123)); //출력값 : 100 10 10 1 1 1
	print(solution(350)); //출력값 : 100 100 100 50

	return 0;
}
//내 코드와 다른 점:
// 
// 로직은 내 코드와 완전히 같다. 값이 큰 동전부터 검사해서 남은 돈이 해당 값보다 크면 그 동전값을
// 뺀다. 정답코드와 다른점은 나는 if/else 문으로 남은돈이 0이 될 때 까지 검사를 했다.
// 반면 정답코드에서는 denominations라는 벡터를 선언해서, 각 코인으로 거스를수 있을때까지
// for문으로 처리하였다. 연산의 수는 정답코드가 더 적다. 내 코드로는 100원 미만으로 돈이 남아도
// 100원 검사를 하기 때문이다.
// 
// 시간복잡도 : O(N)
//