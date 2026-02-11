#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
#include<string>
using namespace std;
vector<int>parent;

int find(int x)
{
	if (x == parent[x]) return x;
	return find(parent[x]);
}
int solution(int n, vector<vector<int>>costs)
{
	set<int> bridgecost;
	parent.resize(n);
	for (int i = 0; i < n; ++i)
		parent[i] = i;
	int cost(0);
	for (auto cc : costs)
	{
		bridgecost.insert(cc[2]);
	}
	for (auto cb : bridgecost)
	{
		for(auto cc:costs)
		{
			if (cc[2] == cb)
			{
				if (parent[cc[0]] == cc[0])
					parent[cc[0]] = cc[1];
				else if (parent[cc[1]] == cc[1])
					parent[cc[1]] = cc[0];
				cost+=cc[2];
			}
		}
		int standard = find(0);
		bool linkCheck;
		for(int i=0;i<n;++i)
		{
			if (find(i) != standard)
			{
				linkCheck = false;
				break;
			}
			linkCheck = true;
		}
		if(linkCheck)
		break;
		
	}


	return cost;
}
int main()
{
	cout << solution(4, { {0, 1, 1}, {0, 2, 2}, {1, 2, 5}, {1, 3, 1}, {2, 3, 8} }) << endl; //출력값 : 4
}
//정답코드
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 상호베타적 집합 정의
class DisjointSet {
private:
	vector<int> parent, rank;

public:
	DisjointSet(int size) : parent(size, -1), rank(size, 0) {}

	int find(int node) {
		if (parent[node] == -1)
			return node;

		//❶ 경로 압축을 하면서 루트노드 찾기  
		return parent[node] = find(parent[node]);
	}

	void merge(int node1, int node2) {
		int root1 = find(node1);
		int root2 = find(node2);

		if (root1 != root2) {

			//❷ 랭크 기반으로 합치기
			if (rank[root1] > rank[root2]) {
				parent[root2] = root1;
			}
			else if (rank[root1] < rank[root2]) {
				parent[root1] = root2;
			}
			else {
				parent[root2] = root1;
				rank[root1]++;
			}
		}
	}

	//❸ 같은 집합에 있는지 확인  
	bool isCycle(int node1, int node2) {
		return find(node1) == find(node2);
	}
};

int solution(int n, vector<vector<int>> costs) {

	//❹ 비용을 기준으로 간선 정렬
	sort(costs.begin(), costs.end(), [](const vector<int>& a, const vector<int>& b) {
		return a[2] < b[2];
		});

	DisjointSet disjointSet(n);
	int totalCost = 0;

	for (const auto& edge : costs) {
		int cost = edge[2];
		int node1 = edge[0];
		int node2 = edge[1];

		//❺ 사이클 확인 후 없을 경우 합병
		if (!disjointSet.isCycle(node1, node2)) {
			disjointSet.merge(node1, node2);
			totalCost += cost;
		}
	}

	return totalCost;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	//bool 반환할 때 true는 1, false는 0 입니다.
	cout << solution(4, { {0, 1, 1}, {0, 2, 2}, {1, 2, 5}, {1, 3, 1}, {2, 3, 8} }) << endl; //출력값 : 4

	return 0;
}
// 내 코드와 다른점:
// 우선 각 비용 오름차순으로 정렬하는 아이디어는 같지만, 나는 set에 입력 비용을 저장했고, 정답코드에서는
// sort 함수를 사용했다. 
// 나는 set의 비용 데이터를 사용해서, 낮은 비용의 다리부터 연결하여
// 각 노드의 부모가 모두 같아질 때 까지 반복문을 수행했다.
// 
// 반면 정답코드에서는 DisjointSet라는 클래스를 정의하여, 멤버변수로 parent와 rank를 선언하고, find, merge, isCycle 함수를
// 정의 해서 costs 입력데이터를 정렬하고, 낮은 비용의 다리부터 순회하여 사이클이 생기는지 여부를 사용해서
// 노드들을 연결했다.
// 
// 시간복잡도 : O(NlogN)
// 
//