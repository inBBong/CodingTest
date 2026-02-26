#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int dfs(vector<vector<int>>graph,int currentNode,int NumSubTreeNodes,vector<bool>&visited)
{
	NumSubTreeNodes++;
	visited[currentNode] = true;
	for (auto n:graph[currentNode])
	{
		if (!visited[n])
			NumSubTreeNodes = dfs(graph, n, NumSubTreeNodes, visited);
	}
	return NumSubTreeNodes;
}

int solution(int n, vector<vector<int>> wires)
{
	vector<int>answers;
	vector<vector<int>>graph(n + 1);
	for (auto w :wires)
	{

		graph[w[0]].push_back(w[1]);
		graph[w[1]].push_back(w[0]);
	}
	for (auto w : wires)
	{
		vector<bool>visited(n + 1,false);
		visited[w[1]] = true;		
		int subSize = dfs(graph, w[0],0,visited);
		answers.push_back(abs((n - subSize)-subSize));
	}
	int min(n);
	for (auto ca : answers)
	{
		if (ca < min)
			min = ca;
	}
	return min;
}
int main()
{
	cout << solution(9, { {1, 3}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {4, 7}, {7, 8}, {7, 9} }) << endl; //출력값 : 3
	cout << solution(4, { {1, 2}, {2, 3}, {3, 4} }) << endl; //출력값 : 0
	cout << solution(7, { {1, 2}, {2, 7}, {3, 7}, {3, 4}, {4, 5}, {6, 7} }) << endl; //출력값 : 1
}
//정답코드
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

int dfs(int node, int parent, const vector<vector<int>>& graph) {
	int cnt = 1;
	//❶ 인접노드에 대해 깊이우선탐색 계속 진행
	for (int child : graph[node]) {
		//❷ 무한탐색을 방지하기 위해 인접한 노드 중, 부모노드는 탐색하지 않음
		if (child != parent) {
			cnt += dfs(child, node, graph);
		}
	}
	return cnt;
}

int solution(int n, vector<vector<int>> wires) {
	vector<vector<int>> graph(n + 1);
	//❸ wire정보를 활용해서 그래프 구축
	for (auto& wire : wires) {
		int a = wire[0];
		int b = wire[1];
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int min_diff = INT_MAX;
	for (auto& wire : wires) {
		int a = wire[0];
		int b = wire[1];

		//❹ 특정 전선을 임시로 삭제
		graph[a].erase(remove(graph[a].begin(), graph[a].end(), b), graph[a].end());
		graph[b].erase(remove(graph[b].begin(), graph[b].end(), a), graph[b].end());

		//❺ 전력망을 단절하고 각 전력망의 송전탑 개수의 차를 구함
		int cnt_a = dfs(a, b, graph);
		int cnt_b = n - cnt_a;

		//❻ 현재까지 구한 송전탑의 차의 절대값의 최소값과 현재 값중 더 적은값을 택함
		min_diff = min(min_diff, abs(cnt_a - cnt_b));

		//❼ 임시로 제거했던 제거했던 전선을 복구
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	return min_diff;
}




//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{

	cout << solution(9, { {1, 3}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {4, 7}, {7, 8}, {7, 9} }) << endl; //출력값 : 3
	cout << solution(4, { {1, 2}, {2, 3}, {3, 4} }) << endl; //출력값 : 0
	cout << solution(7, { {1, 2}, {2, 7}, {3, 7}, {3, 4}, {4, 5}, {6, 7} }) << endl; //출력값 : 1
	return 0;
}
// 내코드와 다른점:
// 정답코드와 로직은 같다. 인접 리스트 그래프를 사용한다는 것도 동일하다.
// 허나 한가지 다른 점은 나는 그래프의 노드들을 순회할때 visited를 사용해서
// 한번 방문한 노드는 가지 않도록했는데, 정답 코드에서는
// 매개변수로 parent를 설정해서 한번 방문한 노드에서는 그 부모를 다시 
// 방문하지 않도록 구현했다.
// 또, 정답 코드에서는 wires 입력에서 간선 정보를 하나씩 삭제하여 두개의 트리로 나누고
// 서브트리의 크기를 구했다. 반면 나는 visited에서 wire에 묶인 노드를 방문 처리하고
// dfs 함수를 실행 하는 식으로 서브트리의 크기를 구했다. 
// 
// 시간복잡도 :O(N^2)
//