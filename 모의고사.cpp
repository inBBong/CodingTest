#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
//1,2,3번수포자는 다음과 같이 찍는다.
// 1: 1,2,3,4,5,1,2,3,4,5....
// 2: 2,1,2,3,2,4,2,5,2,1...
// 3: 3,3,1,1,2,2,4,4,5,5...
// 1번부터 마지막 문제까지의 정답이 순서대로 저장된 배열 answers가 주어졌을 때 가장 많은 문제를 맞힌 사람이 누구인지 배열에 담아 반환하도록 solution()함수를 작성.

//#제약조건
// 1. 시험은 최대 10,000문제
// 2. 문제의 정답은 1~5
// 3. 가장 높은 점수를 받은 사람이 여럿이면 반환하는 값을 오름차순으로 정렬

//아래는 내 코드
vector<int> solution(vector<int>& answer)
{
	vector<int>result;
	vector<int> v1 = { 1,2,3,4,5 };
	vector<int> v2 = { 2,1,2,3,2,4,2,5};
	vector<int> v3 = { 3,3,1,1,2,2,4,4,5,5 };
	int sum1(0);
	int sum2(0);
	int sum3(0);
	for (int i=0;i<answer.size();++i)
	{		
		sum1 += (answer[i] == v1[i%v1.size()]);
		sum2 += (answer[i] == v2[i % v2.size()]);
		sum3 += (answer[i] == v3[i % v3.size()]);
	}
	if (sum1 > sum2 && sum1 > sum3)
		result.push_back(1);
	else if (sum2 > sum1 && sum2 > sum3)
		result.push_back(2);
	else if (sum3 > sum2 && sum3 > sum1)
		result.push_back(3);
	else if (sum1 == sum2&&sum1>sum3)
	{
		result.push_back(1); result.push_back(2);
	}
	else if (sum2 == sum3 && sum3 > sum1)
	{
		result.push_back(2);
		result.push_back(3);
	}
	else if (sum1 == sum3 && sum1 > sum2)
	{
		result.push_back(1);
		result.push_back(3);
	}
	else
	{
		result.push_back(1); result.push_back(2); result.push_back(3);
	}



	return result;
}
int main()
{
	vector<int>v = { 1,3,2,4,2 };
	vector<int>r;
	r=solution(v);
	for (auto cr : r)
		cout << cr << endl;
}

//아래는 정답 코드
// ❶ 각 수포자가 찍는 패턴을 정의
//vector<int> firstPattern = { 1,2,3,4,5 };
//vector<int> secondPattern = { 2,1,2,3,2,4,2,5 };
//vector<int> thirdPattern = { 3,3,1,1,2,2,4,4,5,5 };
//
//vector<int> solution(vector<int> answers) {
//	// ❷ 최종적으로 가장 많이 문제를 맞힌 사람이 저장될 벡터
//	vector<int> answer;
//
//	// ❸ 각 수포자들의 패턴대로 답안을 작성할때 문제를 맞힌 갯수가 저장될 벡터
//	vector<int> matchCnt(3);
//
//	// ❹ 실제 정답과 각 수포자들의 패턴을 비교해서 맞춘 갯수
//	for (int i = 0; i < answers.size(); i++) {
//		if (answers[i] == firstPattern[i % firstPattern.size()]) matchCnt[0]++;
//		if (answers[i] == secondPattern[i % secondPattern.size()]) matchCnt[1]++;
//		if (answers[i] == thirdPattern[i % thirdPattern.size()]) matchCnt[2]++;
//	}
//	// ❺ 가장 많이 맞춘 수포자가 얻은 점수
//	int max_score = *max_element(matchCnt.begin(), matchCnt.end());
//
//	// ❻ 가장 많이 맞춘 수포자의 번호를 저장
//	for (int i = 0; i < 3; i++) {
//		if (matchCnt[i] == max_score) answer.push_back(i + 1);
//	}
//
//	return answer;
//}
//
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
//	print(solution({ 1, 2, 3, 4, 5 }));     // 1 
//	print(solution({ 1, 3, 2, 4, 2 }));     // 1 2 3 
//
//	return 0;
//}
//시간복잡도 : O(N)