#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

vector<int> solution(vector<pair<int, int>> graph, int start)
{
	vector<vector<int>> adjlist;
	vector<int>answer;
	queue<int> visited;
	for (auto p : graph)
	{
		if(p.first+1>adjlist.size())
			adjlist.resize(p.first+1);
		adjlist[p.first].push_back(p.second);
	}
	visited.push(start);
	while (1)
	{
		if (visited.empty())
			break;
		int current = visited.front();
		visited.pop();
		if(find(answer.begin(),answer.end(),current)==answer.end())
		answer.push_back(current);
		if(current<adjlist.size())
		for(int i=0;i<adjlist[current].size();++i)
		{
			if (find(answer.begin(), answer.end(), adjlist[current][i]) == answer.end())
			visited.push(adjlist[current][i]);
		}
	}

	return answer;
}
int main()
{
	vector<int> a=solution({ {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 8}, {6, 9}, {7, 9} }, 1); //출력값 : 1 2 3 4 5 6 7 8 9
	
	vector<int> b=solution({ {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0} }, 1); //출력값 : 1 2 3 4 5 0
	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
}
//정답코드 :
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<int, vector<int>> adjList;
vector<int> result;

void bfs(int start) {
	unordered_set<int> visited;
	queue<int> q;

	// ❶ 시작 노드 방문
	q.push(start);
	visited.insert(start);
	result.push_back(start);

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		// ❷ 현재 노드와 인접한 노드 중 아직 방문하지 않는 노드 방문
		for (int neighbor : adjList[node]) {
			if (visited.find(neighbor) == visited.end()) {
				q.push(neighbor);
				visited.insert(neighbor);
				result.push_back(neighbor);
			}
		}
	}
}

vector<int> solution(vector<pair<int, int>> graph, int start) {
	// ❸ 인접 리스트 생성
	for (auto& edge : graph) {
		int u = edge.first;
		int v = edge.second;
		adjList[u].push_back(v);
	}

	// ❹ 시작 노드부터 너비 우선 탐색 시작
	bfs(start);

	return result;
}

//아래 코드는 테스트 코드 입니다.
#include <iterator>
#include <iostream>

using namespace std;


void init()
{
	adjList.clear();
	result.clear();

}
void print(vector<int> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;

}

int main()
{

	print(solution({ {1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 8}, {6, 9}, {7, 9} }, 1)); //출력값 : 1 2 3 4 5 6 7 8 9
	init();
	print(solution({ {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0} }, 1)); //출력값 : 1 2 3 4 5 0
	return 0;
}
// 내 코드와 다른 점:
// 사실 이번 문제의 내 코드는 엉망으로 짠 것 같다. 너비우선 탐색에서 큐를 사용하긴 하지만, 엄밀히 말하면 visited라고 이름을
// 지은것은 문제가 있다. 큐에 들어가는 노드들은 방문을 한 노드가 아니기 때문이다. 그리고 이번 문제에서 정답코드처럼
// visited라는 unordered_set 자료구조를 사용하지 않은 한계가 드러났다. 전 문제인 깊이우선 탐색에서는
// 그냥 result 안에 없으면 데이터를 추가하는 식으로 중복체크를 했는데 너비우선탐색에서는 통하지 않았다.
// unordered_set으로 노드에 방문할 때 마다 visited라고 체크를 해주는것은 훌륭한 방식인 것 같다.
// 시간복잡도 : O(N+E)