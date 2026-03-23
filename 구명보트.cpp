#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int solution(vector<int> people, int limit)
{
	int N = people.size();
	int answer(N);
	sort(people.begin(), people.end());
	for (int i = 0; i < N-1; i += 2)
	{
		if (people[i] + people[i + 1] <= limit)
			answer--;
	}
	return answer;
}
int main()
{
	cout << solution({ 70, 50, 80, 50 }, 100) << endl; //출력값 : 3
	cout << solution({ 70, 80, 50 }, 100) << endl; //출력값 : 3

}
//정답코드 :
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
	sort(people.begin(), people.end());  //❶ 몸무게를 오름차순으로 정렬
	int count = 0;  //❷ 필요한 보트 개수
	int i = 0;  //❸ 가장 가벼운 사람을 가리키는 인덱스
	int j = people.size() - 1;  //❹ 가장 무거운 사람을 가리키는 인덱스

	while (i <= j) {
		//❺ 가장 무거운 사람과 가장 가벼운 사람을 같이 태울 수 있으면 두 사람 모두 보트에 태움
		if (people[j] + people[i] <= limit) {
			i++;
		}
		//❻ 무거운 사람만 태울 수 있으면 무거운 사람만 보트에 태움
		j--;
		count++;
	}

	return count;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

int main()
{
	cout << solution({ 70, 50, 80, 50 }, 100) << endl; //출력값 : 3
	cout << solution({ 70, 80, 50 }, 100) << endl; //출력값 : 3

	return 0;
}
// 내 코드와 다른점 :
// 내 코드로 입출력의 예는 통과했지만, 정답코드를 보고 내 코드가 잘못되었다는 것을 알게 되었다.
// 나는 answer을 people.size()로 선언하고, people 벡터를 오름차순으로 정렬해서, 앞에서부터 두명씩 짝지어서
// limit보다 작거나 같으면 answer을 1씩 빼주었다. 그러나, 내 코드대로 하면, 30,30,70,70 같은 people 배열이 있으면,
// 보트를 3번 태워야 한다. 2번만에 갈 수 있어도 말이다. 정답코드에서는 가장 가벼운 사람과 가장 무거운 사람을 한명씩
// 뽑아서 같이 태울수 있으면 같이 태우고, 안되면 무거운사람은 혼자 태우는 식으로 answer을 조절했다.
// 
// 시간복잡도 : O(NlogN)
//
