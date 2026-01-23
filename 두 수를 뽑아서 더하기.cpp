#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//두 수를 뽑아서 더하기.
//정수 배열 numbers에서 서로 다른 인덱스에 있는 2개의 수를 뽑아 더해 만들 수 있는 모든 수를 배열에 오름차순으로 담아 반환하는 solution()함수 완성하기.
//numbers의 길이는 2이상 100이하.
//numbers의 모든 수는 0 이상 100 이하.
//아래는 내 코드
vector<int> solution(vector<int>& numbers)
{
	vector<int> sum;
	for (int i = 0; i < numbers.size(); ++i)
	{
		for (int j = i+1; j < numbers.size(); ++j)
		{
			sum.push_back(numbers[i]+numbers[j]);
		}
	}
	sort(sum.begin(), sum.end());
	sum.erase(unique(sum.begin(), sum.end()), sum.end());
	return sum;
}
int main()
{
	vector<int> v={ 2,1,3,4,1 };
	vector<int> result;
	result=solution(v);
	for (auto r : result)
		cout << r << endl;

}
//아래는 정답코드
//#include <vector>
//#include <set>
//
//using namespace std;
//
//vector<int> solution(vector<int> numbers) {
//	set<int> sum; // 두 수의 합을 저장할 저장공간 선언
//
//	for (int i = 0; i < numbers.size(); ++i)  // ? 반복문을 수행하면서 두 수의 합을 저장
//		for (int j = i + 1; j < numbers.size(); ++j)
//			sum.insert(numbers[i] + numbers[j]);
//
//	vector<int> answer(sum.begin(), sum.end()); // ? 반환타입을 맞추기 위헤 벡터로 변환
//	return answer;
//}
//
//
//
////아래 코드는 테스트 코드 입니다.
//
//#include <iterator>
//#include <iostream>
//void print(vector<int> vec)
//{
//	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
//	cout << endl;
//}
//
//int main()
//{
//	print(solution({ 2, 1, 3, 4, 1 }));     // 2 3 4 5 6 7 
//	print(solution({ 5, 0, 2, 7 }));        // 2 5 7 9 12 
//
//	return 0;
//} 
// 시간복잡도 : O(N^2logN)