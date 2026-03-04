#include<iostream>
#include<vector>
using namespace std;
int answer(0);
	vector<bool>visited;
void backTrack(int currentPower,int currentDungeon, vector<vector<int>>dungeons,int depth)
{
	if (answer < depth)
	{
		answer = depth;
	}
	if(depth!=0)
	currentPower -= dungeons[currentDungeon][1];
	for (int i = 0; i < dungeons.size(); ++i)
	{
		if (visited[(currentDungeon + i) % dungeons.size()] || currentPower < dungeons[(currentDungeon + i) % dungeons.size()][0])
			continue;

		visited[(currentDungeon + i) % dungeons.size()] = true;
		backTrack(currentPower, (currentDungeon + i) % dungeons.size(), dungeons, depth + 1);
		visited[(currentDungeon + i) % dungeons.size()] = false;

	}
}
int solution(int initialPower, vector<vector<int>>dungeons)
{
	visited.resize(dungeons.size());	
	backTrack(initialPower, 0, dungeons,0);
	
	return answer;
}
int main()
{
	cout << solution(80, { {80, 20}, {50, 40}, {30, 10} }) << endl; // 출력값 : 3
}
// 이번에도 한번에 구현하는 것을 실패해서 정답코드를 보면서 구현하였다.
// 백트래킹이 너무 어려워서 지피티에게 백트래킹 잘하는 꿀팁을 물어보니 아래와 같은 체크리스트를 알려줬다.
//////// 
//state가 함수 인자로 명확한가 ? (전역 남발 X)
//
//choice loop가 정확히 어떤 범위를 도는지 설명 가능한가 ?
//
//pruning 조건이 최소 1개 이상 있는가 ? (없으면 대개 시간초과)
//
//do / undo가 완전 대칭인가 ?
//
//답이 “하나만” 필요하면 bool 반환으로 조기 종료하는가 ?
//
// 피로도 문제의 do / undo는 visited를 true로 했다가 false로 원복하는 것이다.
// 나는 아무래도 위 체크리스트의 모든 부분을 제대로 생각하지 못하는 것 같은데 특히 종료조건과 do/undo를 헷갈리는 것 같다.
// 아무래도 백트래킹 문제는 모두 나중에 다시 풀어봐야 할 것 같다.
// 
// 시간복잡도 : O(N!) 하지만 유망함수에 의해 훨씬 적음.
//