//#include<iostream>
//#include<stack>
//#include<vector>
//using namespace std;
////초 단위로 기록된 주식 가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를
////반환하도록 solution()함수를 완성하세요.
//// 제약 조건
//// 1. prices의 각 가격은 1 이상 10,000이하인 자연수 입니다.
//// 2. prices의 길이는 2 이상 100,000 이하입니다.
//// 입출력 예 : 
////  prices			result
////[1,2,3,2,3]      [4,3,1,1,0]
////내 코드
//vector<int> solution(vector<int> prices)
//{
//	int standard = 0;
//	vector<int> answer;
//	for (int i = 0; i < prices.size()-1; ++i)
//	{
//		standard = prices[i];
//		int sec = 0;
//		for (int j = i+1; j < prices.size(); ++j)
//		{
//			sec++;
//			if (prices[j] < standard)
//			{
//				answer.push_back(sec); break;
//			}
//			else if (j == prices.size() - 1)
//				answer.push_back(prices.size() - i - 1);
//
//		}
//	}
//	answer.push_back(0);
//	return answer;
//}
//int main()
//{
//	vector<int> v = { 1,2,3,2,3 };
//	vector<int> answer;
//	answer=solution(v);
//	cout << "[";
//	for (auto ca : answer)
//		cout<< ca << " ";
//	cout << "]"<<endl;
//
//}
//정답코드 ㅈㄴ어렵노 ㅋㅋㅋ
//#include <string>
//#include <vector>
//#include <stack>
//
//using namespace std;

//vector<int> solution(vector<int> prices) {
//	//❶ 가격이 떨어지지 않은 기간을 저장한 벡터    
//	vector<int> answer(prices.size());
//	// 스택에는 prices의 인덱스가 들어감, 이전 가격과 현재 가격을 비교하기 위한 용도로 사용됨  
//	stack<int> s;
//
//	int priceNum = prices.size();
//
//	for (int i = 0; i < priceNum; i++) {
//		while (!s.empty() && prices[s.top()] > prices[i]) {
//			//❷ 가격이 떨어졌으므로 이전 가격의 기간 계산 
//			answer[s.top()] = i - s.top();
//			s.pop();
//		}
//		s.push(i);
//	}
//	//❸ 스택에 남아있는 가격들은 가격이 떨어지지 않은 경우
//	while (!s.empty()) {
//		answer[s.top()] = priceNum - s.top() - 1;
//		s.pop();
//	}
//	return answer;
//}
//
//
//
//
////아래 코드는 테스트 코드 입니다.
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
//	print(solution({ 1, 2, 3, 2, 3 })); // 4 3 1 1 0
//	return 0;
//
//}
//다시 짜보기
#include<iostream>
#include<vector>
#include<stack>
using namespace std;
vector<int> solution(vector<int>prices)
{
	stack<int> s;
	vector<int> answer(prices.size());
	for (int i = 0; i < prices.size(); ++i)
	{
		while (!s.empty() && prices[s.top()] > prices[i])
		{
			answer[s.top()] = i - s.top();
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty())
	{
		answer[s.top()] = prices.size() - 1 - s.top();
		s.pop();
	}
	return answer;
}
int main()
{
	vector<int> v = { 1,2,3,2,3 };
	vector<int> answer;
	answer=solution(v);
	for (auto ca : answer)
		cout << ca << " ";
}
//시간복잡도 : O(N)