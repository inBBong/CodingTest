#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 슈퍼게임 개발자 오셀리의 게임 난이도 조절을 위한 실패율을 구하는 코드를 작성하자!
// 실패율 정의 : (스테이지에 도달 했으나 아직 클리어하지 못한 플레이어의 수) / (스테이지에 도달 한 플레이어의 수)
// 전체 스테이지 개수가 N, 게임을 이용하는 사용자가 현재 멈춰 있는 스테이지의 번호가 담긴 배열 stages가 주어질 때 실패율이
// 높은 스테이지부터 내림차순으로 스테이지의 번호가 담겨 있는 배열을 반환하도록 solution() 함수를 작성하세요.
// 제약조건
// 1. 스테이지 개수 N은 1 이상 500 이하의 자연수.
// 2. stages의 길이는 1 이상 200,000 이하
// 3. stages에는 1 이상 N + 1 이하의 자연수가 존재
//		-각 자연수는 사용자가 현재 도전 중인 스테이지 번호를 나타냄
//		-단 N + 1은 마지막 스테이지, 즉 N까지 클리어한 사용자를 나타냄
// 4. 만약 실패율이 같은 스테이지가 있다면 작은 번호의 스테이지가 먼저 오면 됨
// 5. 스테이지에 도달한 유저가 없는 경우 해당 스테이지의 실패율은 0으로 간주

//내 코드 (정답코드에서 pair, compare 함수의 아이디어만 얻음)
bool compare(pair<int, double>& a, pair<int, double>& b)
{
	if (a.second == b.second)
		return a.first < b.first;
	return a.second > b.second;
}
vector<int> solution(int N, vector<int>& stages)
{
	vector<int> PersonPerStage;//(스테이지에 도달 한 플레이어의 수)
	vector<int> NonClearPerStage;//(스테이지에 도달 했으나 아직 클리어하지 못한 플레이어의 수)
	vector<pair<int,double>> failPercent(N);//(스테이지에 도달 했으나 아직 클리어하지 못한 플레이어의 수)

	vector<int> answer;//정답
	PersonPerStage.assign(N, 0);
	NonClearPerStage.assign(N, 0);
	//answer.assign(N, 0);
	//failPercent.assign(N,0);	
	for (int i = 0; i < stages.size(); ++i)
	{
		for (int j = 0; j < stages[i]; j++)
		{
			if (j == N)break;
			PersonPerStage[j]++;
			if (j == stages[i] - 1)
				NonClearPerStage[j]++;
		}
	}
	for(int i=0;i<N;++i)
	{
		failPercent[i].first = i+1;
		failPercent[i].second = static_cast<double>(NonClearPerStage[i]) / static_cast<double>(PersonPerStage[i]);
	}
	sort(failPercent.begin(), failPercent.end(), compare);
	for (int i = 0; i < N; ++i)
	{
		answer.push_back(failPercent[i].first);
	}
	//sort(answer.rbegin(), answer.rend(), failPercent);
	return answer;
}

int main()
{
	vector<int> v = { 2,1,2,6,2,4,3,3 };
	vector<int> a;
	a=solution(5, v);

	for (auto ca : a)
		cout << ca << endl;

}
//정답코드
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//// ❶ 문제에서 요구하는 조건대로 실패율을 정렬하는 함수 
//bool compare(pair<int, float>& a, pair<int, float>& b) {
//	if (a.second == b.second)
//		return a.first < b.first;
//	return a.second > b.second;
//}
//
//vector<int> solution(int N, vector<int> stages) {
//
//	vector<int> answer; // ❷ answer는 최종 답 
//	vector<float> challenger(N + 2, 0.0);  // ❸ challenger는 각 스테이지에 도달한 적이 있는 도전자의 수  
//	vector<float> fail(N + 2, 0.0); // ❹ fail는 특정 스테이지에 실패한 도전자의 수
//
//	// ❺ 각 스테이지의 인원을 기준으로 특정 스테이지에서 실패한 인원수와, 각 스테이지에 도전한 적이 있는 인원수를 구함 
//	for (int i = 0; i < stages.size(); i++) {
//		for (int j = 1; j <= stages[i]; j++)
//			challenger[j]++;
//
//		fail[stages[i]]++;
//	}
//	// ❻ failRatio는 실패율을 저장, first는 stage정보이고 second는 실패율 
//	vector<pair<int, float>> failRatio(N);
//
//	// ❼ 스테이지 정보 및 실패율을 저장  
//	for (int i = 0; i < N; i++) {
//		failRatio[i].first = i + 1;
//
//		if (challenger[i + 1] == 0)
//			failRatio[i].second = 0;
//		else
//			failRatio[i].second = fail[i + 1] / challenger[i + 1];
//	}
//
//	// ➑ 계산한 실패율을 문제에서 제시한 조건에 맞게 정렬
//	sort(failRatio.begin(), failRatio.end(), compare);
//
//	// ❾ 최종 답을 반환하기 위해 실패율을 저장
//	for (int i = 0; i < N; i++) {
//		answer.push_back(failRatio[i].first);
//	}
//
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
//	print(solution(5, { 2, 1, 2, 6, 2, 4, 3, 3 })); // 3 4 2 1 5
//	print(solution(4, { 4, 4, 4, 4, 4 }));          // 4 1 2 3 
//
//	return 0;
//}
//시간복잡도 : O(M*N+NlogN)