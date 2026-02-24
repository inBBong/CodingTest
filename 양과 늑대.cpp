#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
vector<bool>visited;
unordered_map<string, int>Cnt;

class Node
{
private:
    vector<Node*>Sons;
    int WhoAmI;
    int num;
public:
    Node(int who,int n):Sons(NULL), WhoAmI(who),num(n) {}
    void makeSons(Node* n) { Sons.push_back(n); }
    int GetWhoAmI() { return WhoAmI; }
    int GetNum() { return num; }
    vector<Node*>GetSons() { return Sons; }
};
void init()
{
}
void bfs(Node* root)//너비우선탐색
{
    queue<Node*>q;
    q.push(root);
    while (!q.empty())
    {
        
        Node* currentNode = q.front();
        q.pop();       

        visited[currentNode->GetNum()] = true;
        
        vector<Node*>sons = currentNode->GetSons();
        for (int i = 0; i < sons.size(); ++i)
        {
            if (!visited[sons[i]->GetNum()])
            {
                if (sons[i]->GetWhoAmI() == 0)
                {
                    q.push(sons[i]);
                    Cnt["Sheep"]++;
                }
                else
                {
                    if (Cnt["Sheep"] > Cnt["Wolf"] + 1)
                    {
                        q.push(sons[i]);
                        Cnt["Wolf"]++;
                    }
                }
            }
            
        }
    }

}
int solution(vector<int> info, vector<vector<int>>edges)
{
    Cnt["Sheep"] = 1;
    visited.resize(info.size(),false);
    vector<Node*>nodes;
    for (int i = 0; i < info.size(); ++i)
    {
        Node* node = new Node(info[i],i);
        nodes.push_back(node);
    }
    for (int i = 0; i < edges.size(); ++i)
    {
        nodes[edges[i][0]]->makeSons(nodes[edges[i][1]]);
    }
    for (int i = 0; i < nodes.size(); ++i)
    {
        if(!visited[i])
        {

            if (nodes[i]->GetWhoAmI() == 0)
                bfs(nodes[i]);
            else
            {
                if (Cnt["Sheep"] > Cnt["Wolf"] + 1)
                    bfs(nodes[i]);
            }
        }
    }
    return Cnt["Sheep"];
}
int main()
{
    cout << solution({ 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
        { {0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9} }
    ) << endl; //출력값 : 5

    init(); // 전역변수를 초기화 해야함

    cout << solution({ 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0 },
        { {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {6, 9}, {9, 10} }
    ) << endl; //출력값 : 5
}

//정답코드
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> tree;
vector<int> visited, comp;
int n, answer = 0;

// 깊이 우선 탐색 (DFS)를 수행하는 함수
void dfs(vector<int> cur) {
    int sheep = 0, wolf = 0;
    //❶ 현재 방문한 경로를 기준으로 양과늑대의 개수를 셈
    for (int c : cur) {
        if (comp[c] == 1) wolf++;
        else sheep++;
    }

    //❷ 늑대의 수가 양보다 많거나 같으면 종료  
    if (sheep <= wolf) return;

    //❸ 최대 양의 수 갱신
    answer = max(answer, sheep);

    for (int i = 0; i < cur.size(); i++) {
        int node = cur[i];
        //❹ 현재 노드와 인접한 노드를 순회
        for (int g : tree[node]) {

            //❺ 이미 방문한 노드는 재방문하지 않음
            if (visited[g]) continue;
            //❻ 현재노드를 방문한 경우, 하지 않은 경우 모두 확인
            visited[g] = true;
            cur.push_back(g);
            dfs(cur);
            cur.pop_back();
            visited[g] = false;
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    n = info.size();
    tree.resize(n);
    visited.resize(n, false);
    comp = info;

    //❼ 입력값으로 부터 트리 생성
    for (auto e : edges) {
        tree[e[0]].push_back(e[1]);
    }

    visited[0] = true;
    //❽ 방문여부를 체크하고, 시작 노드부터 탐색을 시작합니다.
    dfs({ 0 });
    return answer;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>
using namespace std;

void init()
{
    tree.clear();
    visited.clear();
    comp.clear();
    n = 0;
    answer = 0;

}

int main()
{
    cout << solution({ 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 },
        { {0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9} }
    ) << endl; //출력값 : 5

    init(); // 전역변수를 초기화 해야함

    cout << solution({ 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0 },
        { {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {6, 9}, {9, 10} }
    ) << endl; //출력값 : 5
    return 0;
}
// 내 코드와 다른점:
// 이 문제를 처음 보고 나는 너비우선탐색을 사용해야겠다는 생각이 들었다.
// 양과 늑대의 수를 비교하며, 양의 수가 늑대보다 많은지를 체크하면서 자식 노드를 순회했다.
// 그러나 나의 코드대로 하면, 2번이나 3번 노드같은, 양을 자식으로 갖지 않기때문에
// 방문해도 의미가 없는 노드도 방문을 해버려서 쓸데없는 늑대수가 증가하는 문제가 일어났다.
// 이 문제를 어떻게 해결해야 될지 감이 잡히지 않아서 정답코드를 봤지만
// 정답코드도 이해가 가지 않았다. 난 아직 멀었나보군... 다음에 실력이 향상되고 한번 더 풀어봐야겠다.
// 
// 시간복잡도: O(N^2)
//