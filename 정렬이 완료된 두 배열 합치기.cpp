#include<iostream>
#include<vector>

using namespace std;
vector<int>solution(vector<int> arr1, vector<int> arr2)
{
	vector<int>answer;
	int p1(0);
	int p2(0);
	for (int i = 0; i < arr1.size() + arr2.size(); ++i)
	{
		
		if (p1 == arr1.size()||arr1[p1] > arr2[p2])
		{
			answer.push_back(arr2[p2]);
			p2++;
		}
		else
		{
			answer.push_back(arr1[p1]);
			p1++;
		}
	}
	return answer;
}
int main()
{
	vector<int> a=solution({ 1, 3, 5 }, { 2, 4, 6 }); // 출력값 : 1 2 3 4 5 6
	vector<int> b = solution({ 1, 2, 3 }, { 4, 5, 6 }); // 출력값 : 1 2 3 4 5 6
	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
	cout << endl;
}
//정답코드
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr1, vector<int> arr2) {
	//❶ 두 배열을 정렬된 상태로 병합하는 배열
	vector<int> merged;
	int i = 0, j = 0;

	//❷ 두 배열을 순회하면서 정렬된 배열을 생성
	while (i < arr1.size() && j < arr2.size()) {
		if (arr1[i] <= arr2[j]) {
			merged.push_back(arr1[i]);
			i++;
		}
		else {
			merged.push_back(arr2[j]);
			j++;
		}
	}

	//❸ arr1이나 arr2 중 남아있는 원소들을 정렬된 배열 뒤에 추가
	while (i < arr1.size()) {
		merged.push_back(arr1[i]);
		i++;
	}
	while (j < arr2.size()) {
		merged.push_back(arr2[j]);
		j++;
	}

	return merged;
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
	print(solution({ 1, 3, 5 }, { 2, 4, 6 })); // 출력값 : 1 2 3 4 5 6
	print(solution({ 1, 2, 3 }, { 4, 5, 6 })); // 출력값 : 1 2 3 4 5 6

	return 0;
}

// 내 코드와 다른 점:
// 이번 문제는 병합정렬의 합병부분을 구현하는 문제였다. 단순한 문제였어서 이번에도 로직은 같지만,
// 굳이 뽑자면 반복문이 달랐다. 나는 각 배열의 size를 합한 만큼 반복하는 for문을, 정답코드에서는
// 포인터가 하나의 배열의 size에 도달할때까지 while문을 사용한 뒤 남은 배열의 원소들을 추가했다.
// 시간복잡도: O(N+M)