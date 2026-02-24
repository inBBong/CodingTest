#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
int visited[201] = { 0 };
int answer(0);
void dfs(int node,vector<vector<int>>network)
{
	visited[node] = 1;
	for(int i=0;i<network[node].size();++i)
	{
		if(visited[network[node][i]]==0)
		{
			answer--;
			dfs(network[node][i], network);
		}
	}
		answer++;
}
int solution(int n, vector<vector<int>> computers)
{	
	vector<vector<int>> network(n);

	for (int i = 0; i < computers.size(); ++i)
	{
		for (int j = 0; j < computers[0].size(); ++j)
		{
			if (i != j && computers[i][j] == 1)
				network[i].push_back(j);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if(visited[i]==0)
		dfs(i,network);
	}

	return answer;
}
void init()
{
	answer = 0;
	for(int i=0;i<201;++i)
		visited[i] = 0;
}
int main()
{
	cout << solution(3, { {1, 1, 0}, {1, 1, 0}, {0, 0, 1} }) << endl; //출력값 : 2	
	init();
	cout << solution(3, { {1, 1, 0}, {1, 1, 1}, {0, 1, 1} }) << endl; //출력값 : 1

}
// 정답코드
#include <string>
#include <vector>

using namespace std;

vector<bool> visited;

//❶ 깊이 우선 탐색(DFS)을 수행하는 함수
void dfs(const vector<vector<int>>& network, int node) {
	visited[node] = true;

	for (int i = 0; i < network[node].size(); i++) {
		if (network[node][i] && !visited[i]) {
			dfs(network, i);
		}
	}
}

int solution(int n, vector<vector<int>> computers) {
	visited = vector<bool>(computers.size(), false);

	int networkCount = 0;

	//❷ 네트워크의 수를 확인
	for (int i = 0; i < computers.size(); i++) {
		if (!visited[i]) {
			dfs(computers, i);
			networkCount++;
		}
	}

	return networkCount;
}



//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

void init()
{
	visited.clear();
}
int main()
{

	cout << solution(3, { {1, 1, 0}, {1, 1, 0}, {0, 0, 1} }) << endl; //출력값 : 2
	init();
	cout << solution(3, { {1, 1, 0}, {1, 1, 1}, {0, 1, 1} }) << endl; //출력값 : 1

	return 0;
}
//내 코드와 다른점:
// 로직은 정답 코드와 같다.
// 하지만 answer을 ++ 해주는 부분이, 나는 연결된 노드를 재귀함수로 돌 때 answer을 빼주고,
// 함수가 끝날때 answer을 더해줬다. 그럼 재귀로 들어갈때 -1씩 되고 연결된 모든 함수가 끝날때 +1씩 되면
// 결국 answer은 네트워크당 하나씩 +1이 된다. 글로 설명하니 더 복잡하군...
// 근데 정답코드에서는 그냥 solution 함수에서 첫 dfs함수를 실행하고 나서
// networkCount++;를 해주었다. 이렇게 간결할 수가.... 
// 그리고 나는 network라는 새로운 자료구조를 만들었는데 정답코드에서는
// 입력으로 주어진 computers를 그대로 사용했다. 
// 어차피 visited로 방문했던 노드를 체크하기때문에 network라는 새로운 자료구조를 만들 필요는 없었던것 같다.
// 
// 시간복잡도:O(N^2)
//