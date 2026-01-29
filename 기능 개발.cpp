#include<iostream>
#include<queue>
#include<vector>
using namespace std;
//내 코드
vector<int> solution(vector<int> progresses, vector<int> speeds)
{
	queue<int> q;
	vector<int> answer;	
	int projects = progresses.size();
	for (int i = 0; i < projects; ++i)
	{
		q.push(i);		
	}
	while (!q.empty())
	{
		int cnt(0);
		for (int i = 0; i < projects; ++i)
		{
			progresses[i] += speeds[i];
		}
		while (!q.empty()&&progresses[q.front()] >= 100)
		{
			cnt++;
			q.pop();
		}
		if(cnt)
		{
			answer.push_back(cnt);
		}
	}
	return answer;
}
int main()
{
	vector<int> p = { 93,30,55 };
	vector<int> p2 = { 95,90,99,99,80,99};
	vector<int> s = { 1,30,5 };
	vector<int> s2 = {1,1,1,1,1,1};
	vector<int> answer;
	answer = solution(p, s);
	for (auto ca : answer)
		cout << ca << " ";
	cout << endl;
	answer = solution(p2, s2);
	for (auto ca : answer)
		cout << ca << " ";
}
//정답코드
//#include <vector>
//#include <cmath>
//using namespace std;
//
//vector<int> solution(vector<int> progresses, vector<int> speeds) {
//	vector<int> answer;
//	int n = progresses.size();
//	vector<int> days_left(n);
//
//	//❶ 각 작업에 대한 완료까지 남은 일수 계산
//	for (int i = 0; i < n; ++i) {
//		days_left[i] = ceil((100.0 - progresses[i]) / speeds[i]);
//	}
//
//	int count = 0; //❷ 배포 될 작업의 수
//	int max_day = days_left[0]; // ❸ 현재 배포될 작업 중 가장 늦게 배포될 작업의 가능일
//
//
//	for (int i = 0; i < n; ++i) {
//		if (days_left[i] <= max_day) { //❹ 배포 가능일이 가장 늦은 배포일보다 빠르면
//			count++;
//		}
//		else { //❺ 배포 예정일이 기준 배포일보다 느리면
//			answer.push_back(count);
//			count = 1;
//			max_day = days_left[i];
//		}
//	}
//
//	answer.push_back(count); //❻ 마지막으로 카운트된 작업들을 함께 배포
//	return answer;
//}
//
//
//
//
//
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//#include <iterator>
//
//void print(vector<int> vec)
//{
//	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
//	cout << endl;
//}
//
//int main()
//{
//
//	print(solution({ 93, 30, 55 }, { 1, 30, 5 })); // 2 1
//	print(solution({ 95, 90, 99, 99, 80, 99 }, { 1, 1, 1, 1, 1, 1 })); // 1 3 2
//
//	return 0;
//
//}
//내코드와 정답코드의 다른점
// 내코드는 progresses와 speeds의 인덱스 큐 q를 만들어서, progresses[q.front()] 가 100보다 커지면 while문을
// 사용해서 progresses[q.front()]와 그 뒤에 100보다 커진 작업이 있는지 탐색후 answer에 추가될 cnt를 조정했다.
// 반면 정답코드는 처음에 progresses와 speeds를 이용해서 남은 일수를 저장한 벡터days_left를 사용했고,
// 
// 남은일수 days_left의 앞쪽에서부터 기준 maxdays을 정하여 기준일이 지나면, 그 뒤의 완료된 작업의 수까지 계산하고, 
// answer에 추가한 뒤 maxdays를 다시 지정해주었다. 
// 정답코드 : 시간복잡도 : O(N)
// 내코드 : 시간복잡도 : O(TN) T: 마지막 작업이 완료될 때까지의 일 수 (while(!q.empty()) 라는게 더이상 작업할게 없을때
// 까지라는 의미기 때문에, 최소 속도가 1이고 최소 progresses가 0일때 T는 100까지 가능.)
// 
// 
//
