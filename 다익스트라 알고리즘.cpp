#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

vector<int>findLeastCost(int start, unordered_map<int, vector<pair<int, int>>>& link, int nodes)
{
	vector<int>answer;
	answer.resize(nodes,100);
	answer[start] = 0;	
	for (int i = 0; i < nodes; ++i)
	{
		int weight;		
		if (i == start)
		{
			weight = 0;
		}
		else
		{
			weight = answer[i];
		}
		for (int j = 0; j < link[i].size(); ++j)
		{
			if (answer[link[i][j].first] >weight + link[i][j].second)
				answer[link[i][j].first] = weight + link[i][j].second;
		}
	}
	return answer;
}
vector<int> solution(int start, int numNodes, vector<tuple<int, int, int>>edges)
{
	unordered_map<int, vector<pair<int,int>>> link;
	for (auto& [s, a, w] : edges)
	{		
		link[s].push_back({ a,w });
	}
	return findLeastCost(start, link,numNodes);
}
int main()
{
	vector<int> a=solution(0, 3, { {0, 1, 9},{0, 2, 3},{1, 0, 5},{2, 1, 1} }); //출력값 : 0 4 3
	vector<int> b = solution(0, 4, {
	{0, 2, 1},
	{2, 1, 1},
	{1, 3, 1},
	{0, 3, 10}
		});
	for (auto ca : a)
		cout<<ca<<" ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
}
//정답코드
#include <vector>
#include <tuple>

using namespace std;

const int INF = 99999;
const int MAX_NODES = 100;
int graph[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];

vector<int> solution(int start, int numNodes, const vector<tuple<int, int, int>> edges) {
	//❶ 그래프 및 방문 여부 초기화
	for (int i = 0; i < MAX_NODES; ++i) {
		fill_n(graph[i], MAX_NODES, INF);
		visited[i] = false;
	}

	//❷ 입력받은 간선 정보를 그래프로 표현
	for (const auto& [from, to, weight] : edges) {
		graph[from][to] = weight;
	}

	//❸ 시작 노드를 제외한 모든 노드의 최소 비용을 INF로 초기화
	vector<int> distances(numNodes, INF);
	distances[start] = 0;

	for (int i = 0; i < numNodes - 1; ++i) {
		int minDistance = INF;
		int closestNode = -1;

		//❹ 최소 거리 노드 찾기
		for (int j = 0; j < numNodes; ++j) {
			if (!visited[j] && distances[j] < minDistance) {
				minDistance = distances[j];
				closestNode = j;
			}
		}

		//❺ 찾은 노드를 방문 처리
		visited[closestNode] = true;

		//❻ 인접 노드에 대한 거리 업데이트
		for (int j = 0; j < numNodes; ++j) {
			int newDistance = distances[closestNode] + graph[closestNode][j];
			if (!visited[j] && graph[closestNode][j] != INF && newDistance < distances[j]) {
				distances[j] = newDistance;
			}
		}
	}

	return distances;
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

	print(solution(0, 3, { {0, 1, 9},{0, 2, 3},{1, 0, 5},{2, 1, 1} })); //출력값 : 0 4 3
	print(solution(0, 4, { {0, 1, 1}, {1, 2, 5}, {2, 3, 1} })); //출력값 : 0 1 6 7
	return 0;
}
// 내 코드와 다른점:
// 우선 나는 인접리스트 그래프를, 정답코드에서는 인접행렬그래프를 사용하였다.
// 나는 그래프를 순회하면서, 노드 간 거리를 비교하여 더 짧은 거리를 발견하면 answer을 갱신해주었다.
// 정답코드에서는, 시작노드에서 가장 가까운 노드를 찾아, 해당 노드의 인접노드의 경로를 비교해서 갱신했다.
// 반면 나는 문제에서 주어진 edges의 순서대로 비교해서 갱신했다.
// Chat GPT의 피드백
// 네 코드는 구조적으로
//
//closestNode(최소 거리 노드 선택) + visited 확정이 없고
//노드 반복 기준을 link.size()로 잘못 잡았고
//link[i]가 맵을 변경하는 접근이라 불안정하며
//INF도 부적절
//이라서 다익스트라로서 정답을 보장하지 못한다.
// 지피티가 준 반례를 실행해봤는데 실패. 나는 각 노드의 최단 거리를 구하는 작업을 1번만 해서 확정이 안됨
// 다익스트라는 가장 짧은 인접 노드를 확정함으로써 각 노드까지의 최단거리를 구해야 함
// 시간복잡도 : O(N^2)