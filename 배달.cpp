#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;
void dikstra(unordered_map<int, vector<pair<int, int>>>&linked,vector<int>& dis,vector<bool>&visited)
{
	int start = 1;
	int weight = 0;
	while (1)
	{
		visited[start] = true;
		for(int i=0;i<linked[start].size();++i)
		{
			if (!visited[linked[start][i].first] && dis[linked[start][i].first] > linked[start][i].second + weight)
				dis[linked[start][i].first] = linked[start][i].second + weight;
		}
		
		weight = 2001;
		for (int i = 1; i < dis.size(); ++i)
		{
			if (!visited[i]&&dis[i] < weight)
			{
				weight = dis[i];
				start = i;
			}
		}
		if (weight == 2001)
			break;
		
	}
}
int solution(int N, vector<vector<int>> road, int K)
{
	int answer(0);
	unordered_map<int, vector<pair<int, int>>>linked(N + 1);
	vector<int>dis(N + 1,2000);
	vector<bool>visited(N + 1, false);
	for (auto r :road)
	{
		int from = r[0], to = r[1], weight = r[2];
		linked[from].push_back({ to,weight });
		linked[to].push_back({ from,weight });

	}
	dis[1] = 0;
	dikstra(linked, dis,visited);
	for (int i = 1; i < dis.size(); ++i)
	{
		if (dis[i] <= K)
			answer++;
	}
	return answer;
}
int main()
{
	cout << solution(5, { {1, 2, 1}, {2, 3, 3}, {5, 2, 2}, {1, 4, 2}, {5, 3, 1}, {5, 4, 2} }, 3) << endl; //출력값 : 4
	cout << solution(6, { {1, 2, 1}, {1, 3, 2}, {2, 3, 2}, {3, 4, 3}, {3, 5, 2}, {3, 5, 3}, {5, 6, 1} }, 4) << endl; //출력값 : 4
	
}
//정답코드
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int solution(int N, vector<vector<int>> road, int K) {
	vector<pair<int, int>> graph[N + 1];
	vector<int> distances(N + 1, numeric_limits<int>::max());
	vector<bool> visited(N + 1, false);
	distances[1] = 0;

	//❶ 방향이 따로 없으므로, 양방향 모두 동일한 가중치 입력
	for (const auto& r : road) {
		int a = r[0], b = r[1], cost = r[2];
		graph[a].push_back({ b, cost });
		graph[b].push_back({ a, cost });
	}

	//❷ 출발점을 heap에 추가
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
	heap.push({ 0, 1 });

	while (!heap.empty()) {
		int dist = heap.top().first;
		int node = heap.top().second;
		heap.pop();

		//❸ 이미 방문한 노드는 무시
		if (visited[node]) continue;
		visited[node] = true;

		for (const auto& next : graph[node]) {
			int next_node = next.first;
			int next_dist = next.second;
			int cost = dist + next_dist;

			//❹ 거쳐가는 노드로 가는 경로의 비용이 더 짧은 경우
			if (cost < distances[next_node]) {
				distances[next_node] = cost;
				heap.push({ cost, next_node });
			}
		}
	}

	int count = 0;

	//❺거리가 K 이하인 장소를 카운트
	for (int i = 1; i <= N; i++) {
		if (distances[i] <= K) count++;
	}

	return count;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{

	cout << solution(5, { {1, 2, 1}, {2, 3, 3}, {5, 2, 2}, {1, 4, 2}, {5, 3, 1}, {5, 4, 2} }, 3) << endl; //출력값 : 4
	cout << solution(6, { {1, 2, 1}, {1, 3, 2}, {2, 3, 2}, {3, 4, 3}, {3, 5, 2}, {3, 5, 3}, {5, 6, 1} }, 4) << endl; //출력값 : 4
	return 0;
}
// 내 코드와 다른점:
// 이번 문제도 어렵고 막혀서 다익스트라 개념과 정답코드를 살짝 보고 구현하였다.
// 나는 매번 가장 가까운 노드를 찾아서 시작노드로 정하고 거리를 갱신했다. O(N^2)
// 하지만 정답코드에서는 우선순위큐라는 자료구조를 이용해 갱신된 노드들을 큐에 넣고 가장 가까운 노드를
// 뽑아 사용하였다 O((N+E)logN) 또한 간선의 최대거리가 2000이라는 문제의 제약 조건을 보고
// 처음 distance를 초기화 할때 2001이라고 했는데, 이는 노드를 타고타고 거리가 2000보다 훨씬 커질 수 있다는 것을
// 간과한 나의 실수였다. 정답코드에서는 numeric_limits<int>::max()로 초기화를 해줬다.
// 
