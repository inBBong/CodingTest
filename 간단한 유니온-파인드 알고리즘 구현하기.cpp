#include<iostream>
#include<vector>
using namespace std;
vector<int> parent;
vector<int> rankof;
void union_set(int x,int y)
{
	if (rankof[x] > rankof[y])
		parent[y] = x;
	else if (rankof[x] < rankof[y])
		parent[x] = y;
	else
	{
		parent[x] = y;
		rankof[y]++;
	}
}
int find(int x)
{
	if (parent[x] == x)
		return x;
	else
		parent[x]=find(parent[x]);

	return parent[x];
}
vector<bool> solution(int k, vector<vector<char>> operations)
{
	parent.resize(k);
	rankof.resize(k,0);
	vector<bool> answer;
	for (int i = 0; i < parent.size(); ++i)
	{
		parent[i] = i;
	}
	for (auto ca : operations)
	{
		if (ca[0] == 'u')
			union_set(ca[1] - '0', ca[2] - '0');
		else
			answer.push_back(find(ca[1] - '0') == find(ca[2] - '0'));
	}
	return answer;
}
void init()
{
	parent.clear();
	rankof.clear();
}
int main()
{
	vector<bool> a1=solution(3, { {'u', '0', '1'}, {'u', '1', '2'}, {'f', '0', '2'} }); // 결과값 : 1
	for (auto ca : a1)
		cout << ca;
	init();
	vector<bool> a2=solution(4, { {'u', '0', '1'}, {'u', '2', '3'}, {'f', '0', '1'}, {'f', '0', '2'} }); // 결과값 : 1 0
	for (auto ca : a2)
		cout << ca;
}
//정답코드
//#include <vector>
//
//using namespace std;
//
//vector<int> parents;
//vector<int> rankData;
//
//// 문자를 숫자로 변환
//int charToInt(char c) {
//    return c - '0';
//}
//
//int find(int x) {
//    // x의 부모가 자신인 경우 루트노드를 찾았으므로 반환    
//    if (parents[x] == x) {
//        return x;
//    }
//
//    // 파인드 연산 시, 경로압축 사용
//    parents[x] = find(parents[x]);
//
//    return parents[x];
//}
//
//void unionSet(int x, int y) {
//    int root1 = find(x);
//    int root2 = find(y);
//
//    // 루트 노드가 같을 경우 유니온 연산을 할 필요가 없음
//    if (root1 != root2) {
//        // 랭크기반 알고리즘으로 유니온 연산 수행  
//        if (rankData[root1] < rankData[root2]) {
//            parents[root1] = root2;
//        }
//        else if (rankData[root1] > rankData[root2]) {
//            parents[root2] = root1;
//        }
//        else {
//            parents[root2] = root1;
//            rankData[root1]++;
//        }
//    }
//}
//
//vector<bool> solution(int k, vector<vector<char>> operations) {
//    parents.resize(k);
//    rankData.resize(k, 0);
//
//    // 초기에 각 노드는 자신을 부모로 설정
//    for (int i = 0; i < k; ++i) {
//        parents[i] = i;
//    }
//
//    vector<bool> results;
//    for (const auto& op : operations) {
//        if (op[0] == 'u') {
//            int x = charToInt(op[1]);
//            int y = charToInt(op[2]);
//            unionSet(x, y);
//        }
//        else if (op[0] == 'f') {
//            int x = charToInt(op[1]);
//            int y = charToInt(op[2]);
//            // 파인드 연산을 통화 x,y의 루트노드가 같은지 확인해서 결과 저장
//            results.push_back(find(x) == find(y));
//        }
//    }
//
//    return results;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//#include <iterator>
//
//using namespace std;
//
//void init()
//{
//    parents.clear();
//    rankData.clear();
//}
//void print(vector<bool> vec)
//{
//    copy(vec.begin(), vec.end(), std::ostream_iterator<bool>(cout, " "));
//    cout << endl;
//}
//
//int main()
//{
//    print(solution(3, { {'u', '0', '1'}, {'u', '1', '2'}, {'f', '0', '2'} })); // 결과값 : 1
//    init();
//    print(solution(4, { {'u', '0', '1'}, {'u', '2', '3'}, {'f', '0', '1'}, {'f', '0', '2'} })); // 결과값 : 1 0
//
//    return 0;
//}
//
// 문제를 이해도 못하고 어떻게 짜야할지 몰라서 정답코드를 먼저 본 후 스스로 구현해보았다.
// 정답을 보고 풀었으니 내 코드와 정답코드의 다른점은 없다.
// 시간복잡도 : O(N)