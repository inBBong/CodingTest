#include<iostream>
#include<vector>
using namespace std;

vector<int> findLeastCost(int num_vertices,int start, vector < vector<pair<int, int>>>&link)
{
	vector<int>answer;
	answer.resize(num_vertices, 200);
	answer[0] = 0;
	for(int k=0;k<num_vertices-1;++k)
	{
		for (int i = 0; i < num_vertices; ++i)
		{
			int weight=answer[i];
			for (int j = 0; j < link[i].size(); ++j)
			{
				if (answer[link[i][j].first] > link[i][j].second + weight)
					answer[link[i][j].first] = link[i][j].second + weight;
			}
		}
	}
	for (int i = 0; i < num_vertices; ++i)
	{
		int weight = answer[i];
		for (int j = 0; j < link[i].size(); ++j)
		{
			if (answer[link[i][j].first] > link[i][j].second + weight)
				return { -1 };
		}
	}
	return answer;
}
vector<int> solution(int num_vertices, vector<tuple<int, int, int>>edges, int source)
{
	vector< vector<pair<int, int>>>link;
	link.resize(num_vertices);
	for (auto& [from, to, weight] : edges)
	{
		link[from].push_back({ to,weight });
	}
	return findLeastCost(num_vertices,source, link);
}
int main()
{
	vector<int>a = solution(5, { {0, 1, 4}, {0, 2, 3}, {0, 4, -6}, {1, 3, 5}, {2, 1, 2}, {3, 0, 7}, {3, 2, 4},{4, 2, 2} }, 0); //출력값 : 0 -2 -4 3 -6
	vector<int>b = solution(4, { {0, 1, 5}, {0, 2, -1}, {1, 2, 2}, {2, 3,-2}, {3, 0, 2}, {3, 1, 6} }, 0); //
	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
}
// 정답코드
#include <vector>
#include <limits>
#include <tuple>

using namespace std;

const int INF = numeric_limits<int>::max();

vector<int> solution(int num_vertices, vector<tuple<int, int, int>> edges, int source) {
    vector<vector<pair<int, int>>> graph(num_vertices);

    //❶ 간선정보를 활용해서 인접리스트를 생성
    for (auto& edge : edges) {
        int from, to, weight;
        tie(from, to, weight) = edge;
        graph[from].emplace_back(to, weight);
    }

    //❷ 현재까지 구한 최소비용을 INF로 설정(시작노드는 제외)
    vector<int> distance(num_vertices, INF);
    distance[source] = 0;

    //❸ 정점의 개수 -1 만큼 최소비용을 갱신
    for (int i = 0; i < num_vertices - 1; ++i) {
        for (int u = 0; u < num_vertices; ++u) {
            for (const auto& [v, weight] : graph[u]) {
                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }
    }

    //❹ 음의 순환이 있는지 확인
    for (int u = 0; u < num_vertices; ++u) {
        for (const auto& [v, weight] : graph[u]) {
            if (distance[u] + weight < distance[v]) {
                return vector<int>(1, -1);
            }
        }
    }

    return distance;
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

    print(solution(5, { {0, 1, 4}, {0, 2, 3}, {0, 4, -6}, {1, 3, 5}, {2, 1, 2}, {3, 0, 7}, {3, 2, 4},{4, 2, 2} }, 0)); //출력값 : 0 -2 -4 3 -6
    print(solution(4, { {0, 1, 5}, {0, 2, -1}, {1, 2, 2}, {2, 3,-2}, {3, 0, 2}, {3, 1, 6} }, 0)); //출력값 : -1

    return 0;
}
//내 코드와 다른 점:
// 우선 로직자체는 똑같다. 나는 answer 자체에서 최단거리를 비교했지만 정답코드에서는 distance라는 
// 벡터를 하나 더 선언했다. 정답코드가 좀 더 간결한 것 같다.
// 시간복잡도 : O(N*E)
//