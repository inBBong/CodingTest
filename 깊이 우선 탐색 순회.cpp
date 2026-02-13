#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

void dfs(unordered_map<char, vector<char>>list, char currentNode, vector<char>& result)
{
	for (int i = 0; i < list[currentNode].size(); ++i)
	{
		if (find(result.begin(), result.end(), list[currentNode][i]) == result.end())
			result.push_back(list[currentNode][i]);
		dfs(list, list[currentNode][i], result);
	}
}
vector<char> solution(vector<pair<char, char>>graph, char start)
{
	unordered_map<char, vector<char>>list;
	vector<char> answer;
	for (auto cg : graph)
	{
		list[cg.first].push_back(cg.second);
	}
	answer.push_back(start);
	dfs(list, start, answer);
	return answer;
}
int main()
{
	vector<char> a1 = solution({ {'A', 'B'}, {'B', 'C'}, {'C', 'D'}, {'D', 'E'} }, 'A'); //출력값 : A B C D E

	vector<char> a2 = solution({ {'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'B', 'E'}, {'C', 'F'}, {'E', 'F'} }, 'A'); //출력값 : A B D E F C

	for (auto ca : a1)
		cout << ca << " ";
	for (auto ca : a2)
		cout << ca << " ";
}
//정답코드 :
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<char, vector<char>> adjList;
vector<char> result;
unordered_set<char> visited;

void dfs(char node) {
	//❶ 현재 node를 방문한 목록 및 방문한 경로 추가
	visited.insert(node);
	result.push_back(node);

	//❷ 현재 node와 인접한 노드 중, 방문하지 않은 node들에 대해 깊이우선탐색을 계속 진행
	for (char neighbor : adjList[node]) {
		if (visited.find(neighbor) == visited.end()) {
			dfs(neighbor);
		}
	}
}

vector<char> solution(vector<pair<char, char>> graph, char start) {
	//❸ 인접 리스트 생성
	for (auto& edge : graph) {
		char u = edge.first;
		char v = edge.second;
		adjList[u].push_back(v);
	}

	//❹ 시작 노드부터 깊이우선탐색 시작
	dfs(start);
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
	visited.clear();
}
void print(vector<char> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<char>(cout, " "));
	cout << endl;

}

int main()
{
	//bool 반환할 때 true는 1, false는 0 입니다.
	print(solution({ {'A', 'B'}, {'B', 'C'}, {'C', 'D'}, {'D', 'E'} }, 'A')); //출력값 : A B C D E
	init();
	print(solution({ {'A', 'B'}, {'A', 'C'}, {'B', 'D'}, {'B', 'E'}, {'C', 'F'}, {'E', 'F'} }, 'A')); //출력값 : A B D E F C

	return 0;
}
// 내 코드와 다른점 :
// 우선 내코드와 정답코드 모두 인접리스트를 사용해서 각 노드와 인접한 노드를 저장하였다.
// 나는 result에 방문한 노드들을 result에 있는지를 체크한 후에 push하며 깊이우선탐색을 하였다.
// 반면 정답코드에서는 visited라는 unordered_set의 구조를 사용해서 방문한 적이 있는지를 체크하였다.
// 그리고 result, visited, adjlist를 전역으로 선언하여, solution 함수를 호출하기 전에 clear 해주었다.
// 시간복잡도 : O(N+E)
//