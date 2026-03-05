#include<iostream>
#include<vector>
using namespace std;
vector<bool>visited;

bool allVisited()
{
	for (int i = 0; i < visited.size(); ++i)
	{
		if (visited[i] == false)
			return false;
	}
	return true;
}
bool isIn(int start, int target, int speed, int n)
{
	if (start + speed > n)
	{
		if ((target >= start && target < n) || (target > 0 && target <= start + speed - n))
			return true;
	}
	if (target >= start && target <= start + speed)
	{
		return true;
	}
	return false;
}
int solution(int n, vector<int> weak, vector<int>dist)
{
	vector<int>d = dist;
	vector<int>w = weak;
	visited.resize(weak.size(),false);
	
	int answer = 8; //계속 갱신 될 정답
	int start = 0;// 이번 친구의 시작지점
	int firststart = 0;//가장 빠른놈을 배치하는 시작지점
	int distIndex = dist.size() - 1;//친구 인ㄷ덱스
	int fast = dist[distIndex];	//가용병력중 가장 빠른 친구
	int friendNum(1); //가용한 친구
	while (firststart != weak.size())
	{
		int nextStart(0);
		for(int i=0;i<weak.size();++i)
		{
			if (!visited[i] && isIn(weak[start], weak[i], fast, n))
			{
				visited[i] = true;
				nextStart++;
			}
		}
		start+=nextStart;
		start %= weak.size();
		fast = dist[--distIndex];

		if (allVisited())//한바퀴 끝
		{
			if (answer > friendNum)
				answer = friendNum;
			start = ++firststart;
			friendNum = 0;
			distIndex = dist.size()-1;
			fast = dist[distIndex];
			for (int i = 0; i < visited.size(); ++i)
			{
				visited[i] = false;
			}
		}
		friendNum++;

	}
	return answer;
	
}

int main()
{
	cout << solution(12, { 1, 5, 6, 10 }, { 1, 2, 3, 4 }) << endl; //출력값 : 2
	cout << solution(12, { 1, 3, 4, 9, 10 }, { 3, 5, 7 }) << endl; //출력값 : 1   
}
//정답코드
#include <vector>
#include <algorithm>
using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
	int length = weak.size();
	//❶  weak 리스트 확장
	for (int i = 0; i < length; ++i) {
		weak.push_back(weak[i] + n);
	}

	//❷ 초기화
	int answer = dist.size() + 1;

	//❸ 시작점 설정 및 친구 순열 생성
	for (int start = 0; start < length; ++start) {
		do {
			//❹ 친구 배치 및 수 계산
			int cnt = 1;
			int position = weak[start] + dist[cnt - 1];

			//❺ 다음 weak 지점 확인
			for (int index = start; index < start + length; ++index) {
				if (position < weak[index]) {
					cnt += 1;
					//❻ 친구 수 초과 확인
					if (cnt > dist.size()) break;
					position = weak[index] + dist[cnt - 1];
				}
			}

			//❼ 최소 친구 수 업데이트
			answer = min(answer, cnt);
		} while (next_permutation(dist.begin(), dist.end())); // 순열 생성
	}

	//❽ 결과 반환
	return answer > dist.size() ? -1 : answer;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution(12, { 1, 5, 6, 10 }, { 1, 2, 3, 4 }) << endl; //출력값 : 2
	cout << solution(12, { 1, 3, 4, 9, 10 }, { 3, 5, 7 }) << endl; //출력값 : 1   

	return 0;
}

//내 코드와 다른 점:
// 이번 문제도 여느 백트래킹과 같이 너무 어려워서 혼자서는 도저히 아이디어를 떠올릴 수 없었다.
// 그래서 지피티로도 찾아보고, 유튜브에서 강의를 봤다. 유튜브 강의를 보고 아이디어를 얻어 비록 하드코딩을
// 했지만 정답을 도출해낼 수 있었다. 핵심 아이디어는 가장 빠른 친구를 선발해서, 시작지점을 달리하면서
// 커버할 수 있는 범위 내에 weak를 방문하는 것이었다. 모든 weak를 방문하면 다시 가용친구는 1로 초기화,
// 시작지점을 한칸 옮긴다. 이렇게 모든 경우의 수를 탐색해 가용친구가 answer보다 작으면 갱신해줬다.
// 
// 반면 정답코드에서는 next_permutation함수를 사용해서 속도에 상관 없이 친구의 모든 순열을 구하고 
// 같은 코드를 적용하여 모든 경우의수를 구했다. 또한 원형구조에서 범위를 탐색한 내 코드와 달리, 
// 정답코드에서는 weak + (weak+n)을 해서 선형적인 구조로 만들었음.
// ex) n=12 : 1,5,6,10,'13,17,18,22'
// 
// 시간복잡도 : O(M^2*N!)