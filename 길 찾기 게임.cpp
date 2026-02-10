#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;
class Node
{
private:
	int x, y, num;
public:
	Node* left;
	Node* right;
	int GetX() { return x; }
	int GetY() { return y; }
	int GetNum() { return num; }
	Node(int _x, int _y, int _num) :x(_x), y(_y),num(_num), left(nullptr), right(nullptr){}
};
class Tree
{
private:
	Node* root;
public:
	Tree(Node*_root):root(_root){}
	Tree():root(nullptr){}
	Node* insert(Node* node, int _x, int _y, int _num)
	{
		if (!node)
			return new Node(_x, _y,_num);
		if (_x < node->GetX())
			node->left = insert(node->left, _x, _y, _num);
		else 
			node->right = insert(node->right, _x, _y, _num);
		return node;
	}
	vector<int>firstCycle(Node* node, vector<int> fc)
	{
		if (!node)
			return fc;
		fc.push_back(node->GetNum());
		fc=firstCycle(node->left, fc);
		fc=firstCycle(node->right, fc);
		return fc;
	}
	vector<int>lastCycle(Node* node, vector<int> fc)
	{
		if (!node)
			return fc;
		fc=lastCycle(node->left, fc);
		fc=lastCycle(node->right, fc);
		fc.push_back(node->GetNum());
		return fc;
	}
};
bool compare(vector<int>a,vector<int>b)
{
	return a[1] > b[1];
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo)
{
	vector<int> team1; //전위순회
	vector<int> team2; //후위순회
	vector<vector<int>> answer;
	unordered_map<int, int> idx;
	for (int i = 0; i < nodeinfo.size(); ++i)
	{
		idx[nodeinfo[i][0]] = i + 1;
	}

	sort(nodeinfo.begin(), nodeinfo.end(), compare);
	Node* root = new Node(nodeinfo[0][0],nodeinfo[0][1], idx[nodeinfo[0][0]]);
	Tree* T = new Tree(root);
	for (int i=1;i<nodeinfo.size();++i)
		T->insert(root, nodeinfo[i][0], nodeinfo[i][1], idx[nodeinfo[i][0]]);

	//순회 시작
	team1=T->firstCycle(root, team1);
	team2=T->lastCycle(root, team2);
	answer.push_back(team1);
	answer.push_back(team2);
	return answer;
}
int main()
{
	vector<vector<int>> answer;
	answer = solution({ {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} });
	
	for (auto ca : answer[0])
		cout << ca<<" ";
	cout << endl;
	for (auto ca : answer[1])
		cout << ca << " ";
}
// 정답코드:
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
////❶ 이진트리에서 사용할 노드 정의 
//struct Node {
//	int id, x, y;
//	Node* left = nullptr;
//	Node* right = nullptr;
//
//	Node(int id, int x, int y) : id(id), x(x), y(y) {}
//
//};
//
////❷ 이진트리 정의
//class BinaryTree {
//private:
//	Node* root = nullptr;
//	//❸ 노드 좌표를 기준으로 정렬할 때 기준이 되는 함수
//	static bool compareNodes(Node* a, Node* b) {
//		if (a->y != b->y) return a->y > b->y;
//
//		return a->x < b->x;
//	}
//
//	//❹ 새 노드를 추가하는 함수
//	Node* addNode(Node* current, Node* newNode) {
//		if (current == nullptr) return newNode;
//		//❺ 추가하려고 하는 노드의  좌표를 기준으로 현재노드의 왼쪽 혹은 오른쪽 자식 여부를 판단하고 추가
//		if (newNode->x < current->x) current->left = addNode(current->left, newNode);
//		else current->right = addNode(current->right, newNode);
//
//		return current;
//	}
//
//	// 전위 순회를 진행하며 경로를 저장하는 함수
//	void preOrder(Node* node, vector<int>& traversal) {
//		if (node == nullptr) return;
//		traversal.push_back(node->id);
//		preOrder(node->left, traversal);
//		preOrder(node->right, traversal);
//	}
//
//	// 후위 순회를 진행하며 경로를 저장하는 함수
//	void postOrder(Node* node, vector<int>& traversal) {
//		if (node == nullptr) return;
//		postOrder(node->left, traversal);
//		postOrder(node->right, traversal);
//		traversal.push_back(node->id);
//	}
//
//public:
//	BinaryTree() : root(nullptr) {}
//
//	//❻ nodeinfo를 기준으로 이진트리를 구축하는 함수
//	void buildTree(const vector<vector<int>>& nodeInfo) {
//		vector<Node*> nodes;
//		//❼ 각 노드의 (인덱스,x좌표,y좌표) 정보를 nodes에 저장 
//		for (int i = 0; i < nodeInfo.size(); ++i) {
//			nodes.push_back(new Node(i + 1, nodeInfo[i][0], nodeInfo[i][1]));
//		}
//
//		//❽ 이진트리를 구축하기 위해 노드를 정렬
//		sort(nodes.begin(), nodes.end(), compareNodes);
//		//❾ 이진트리 구축
//		for (Node* node : nodes) {
//			root = addNode(root, node);
//		}
//	}
//
//	// 전위순회 후 경로를 반환하는 함수  
//	vector<int> getPreOrderTraversal() {
//		vector<int> traversal;
//		preOrder(root, traversal);
//
//		return traversal;
//	}
//
//	// 후위순회 후 경로를 반환하는 함수
//	vector<int> getPostOrderTraversal() {
//		vector<int> traversal;
//		postOrder(root, traversal);
//
//		return traversal;
//	}
//};
//
//vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
//	BinaryTree tree;
//
//	//❿ 이진트리를 구축하고 순회결과를 반환
//	tree.buildTree(nodeinfo);
//	vector<int> preOrder = tree.getPreOrderTraversal();
//	vector<int> postOrder = tree.getPostOrderTraversal();
//
//	return { preOrder, postOrder };
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iterator>
//#include <iostream>
//void print(vector<vector<int>> vec)
//{
//	for (auto& vec_elem : vec)
//	{
//		copy(vec_elem.begin(), vec_elem.end(), std::ostream_iterator<int>(cout, " "));
//		cout << endl;
//	}
//}
//
//int main()
//{
//	print(solution({ {5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2} }));
//
//	/**
//	 출력값
//	 7 4 6 9 1 8 5 2 3
//	 9 6 5 8 1 4 3 2 7
//	**/
//
//	return 0;
//}
// 내 코드와 다른 점:
// 나는 노드와 트리 클래스를 정의하고 트리 클래스 내부에서 노드 삽입과, 트리의 전위순회와 후위순회를 할 수 있게 하였다.
// nodeInfo를 정렬할때, sort의 compare 함수에서 나는 y 기준으로만 정렬을 하고, y가 같을때 x 조건은 놓쳤다.
// 또한 나는 root 노드는 미리 생성을 하고, 그 다음 노드부터 insert를 했는데, 정답코드를 보니 그럴필요 없이
// 루트노드부터 insert를 할 수 있었다. 그리고 정답코드에서는 buildTree라는 함수를 만들어서
// 우선 노드들을 먼저 생성 한 후에 addNode 함수를 통해연결을 해주었고, 나는 연결을 하면서 생성했다.
// 시간복잡도 : O(N)