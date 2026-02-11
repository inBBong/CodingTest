#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

int solution(vector<int>nums)
{
	int monSize(nums.size() / 2);//가져갈 포켓몬
	unordered_set<int>KindofPoketmon;
	for (auto cn : nums)
		KindofPoketmon.insert(cn);
	int monKindSize = KindofPoketmon.size(); 

	if (monKindSize >= monSize)
		return monSize;
	else
		return monKindSize;
}
int main()
{
	cout << solution({ 3, 1, 2 ,3 }) << endl; //출력값 : 2
	cout << solution({ 3, 3, 3, 2, 2, 4 }) << endl; //출력값 : 3
	cout << solution({ 3, 3, 3, 2, 2, 2 }) << endl; //출력값 : 2
}
// 정답코드
#include <vector>
#include <unordered_set>

using namespace std;

int solution(vector<int> nums) {
	//❶ s는 nums의 중복값을 제거한 집합
	unordered_set<int> s(nums.begin(), nums.end()); //오 이렇게도 초기화가 되는구나

	//❷ 중복을 제거한 개수와 nums의 개수중 작은 값을 반환
	return min(nums.size() / 2, s.size());			
}

//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution({ 3, 1, 2 ,3 }) << endl; //출력값 : 2
	cout << solution({ 3, 3, 3, 2, 2, 4 }) << endl; //출력값 : 3
	cout << solution({ 3, 3, 3, 2, 2, 2 }) << endl; //출력값 : 2

	return 0;
}
//내 코드와 다른점:
// 문제 자체가 쉬워서 알고리즘은 똑같다. 하지만 정답코드는 단 두줄로 끝내버렸다.
// unordered_set을 초기화를 저렇게 할 수도 있다는 걸 처음 알았다.
// 비교할때도 min 함수로 써서 힙하게 비교했군.
//
//시간복잡도 : O(N)
//