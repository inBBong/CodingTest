#include<iostream>
#include<vector>

using namespace std;
struct node
{
	int value = 0;
	node* left=nullptr;
	node* right=nullptr;
};
vector<bool> solution(vector<int> lst, vector<int> search_lst)
{
	node* root = new node;
	root->value = lst[0];
	vector<bool>answer;
	for (int i = 1; i < lst.size(); ++i)
	{
		node* currentNode = root;
		node* n = new node;
		n->value = lst[i];
		while (1)
		{
			if (n->value < currentNode->value)
			{
				if(!currentNode->left)
				{
					currentNode->left = n;
					break;
				}
				currentNode = currentNode->left;
			}
			else if (n->value > currentNode->value)
			{
				if (!currentNode->right)
				{
					currentNode->right = n;
					break;
				}
				currentNode = currentNode->right;
			}
		}
	}
	for (int i = 0; i < search_lst.size(); ++i)
	{
		node* currentNode = root;
		while (1)
		{
			if (currentNode->value == search_lst[i])
			{
				answer.push_back(true);
				break;
			}
			else if (search_lst[i] < currentNode->value && currentNode->left)
				currentNode = currentNode->left;
			else if (search_lst[i] > currentNode->value && currentNode->right)
				currentNode = currentNode->right;
			else
			{
				answer.push_back(false);
				break;
			}
		}
	}
	return answer;
}
int main()
{
	vector<bool> a1=solution({ 5, 3, 8, 4, 2, 1, 7, 10 }, { 1, 2, 5, 6 }); //출력값 : 1 1 1 0
	vector<bool> a2=solution({ 1, 3, 5, 7, 9 }, { 2, 4, 6, 8, 10 });
	for (auto ca1 : a1)
		cout << ca1 << " ";
	cout << endl;
	for (auto ca2 : a2)
		cout << ca2 << " ";
}
//정답코드
#include <vector>
using namespace std;

// ❶ 노드를 정의
class Node {
public:
	int val;
	Node* left, * right;

	Node(int key) : val(key), left(nullptr), right(nullptr) {}
};

//❷ 이진 탐색 트리 정의
class BST {
private:
	Node* root;


	Node* insertNode(Node* node, int key) {
		if (!node) {
			return new Node(key);
		}
		//❸ 키 값과 현재 노드의 값을 비교해서 이진탐색트리 규칙에 맞는 위치로 이동
		if (key < node->val) {
			node->left = insertNode(node->left, key);
		}
		else {
			node->right = insertNode(node->right, key);
		}
		return node;
	}

	bool searchNode(Node* node, int key) {
		//❹ 찾는 키 값이 없는 경우 
		if (!node) {
			return false;
		}
		//❺ 이진탐색트리에서 키 값을 찾은 경우
		if (key == node->val) {
			return true;
		}
		//❻ 아직 값을 찾지 못한 경우, 현재 노드값과 key 값을 비교해서, 어느 노드에서 탐색할지 결정
		return key < node->val ?
			searchNode(node->left, key) :
			searchNode(node->right, key);
	}

public:
	BST() : root(nullptr) {}

	void insert(int key) {
		root = insertNode(root, key);
	}

	bool search(int key) {
		return searchNode(root, key);
	}
};

vector<bool> solution(vector<int> lst, vector<int> search_lst) {
	BST bst;
	// 이진 탐색 트리에 노드 삽입
	for (int key : lst) {
		bst.insert(key);
	}

	vector<bool> result;
	// 이진 탐색 트리에서 찾는 값이 있는지 확인하고 탐색결과를 result에 추가
	for (int search_val : search_lst) {
		result.push_back(bst.search(search_val));
	}

	return result;
}

//아래 코드는 테스트 코드 입니다.
#include <iterator>
#include <iostream>
void print(vector<bool> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<bool>(cout, " "));
	cout << endl;
}

int main()
{
	// bool을 출력할 때 true는 1 false는 0 입니다.
	print(solution({ 5, 3, 8, 4, 2, 1, 7, 10 }, { 1, 2, 5, 6 })); //출력값 : 1 1 1 0
	print(solution({ 1, 3, 5, 7, 9 }, { 2, 4, 6, 8, 10 })); //출력값 : 0 0 0 0 0    
	return 0;
}
// 내 코드와 다른점:
//		정답코드와 로직은 똑같은데, 정답 코드에서는 class를, 나는 struct를 사용했다.
//		정답코드가 내 코드보다 간결하고 세련된 코드인것같다.
//		나는 solution 함수에다가 트리 생성과, 탐색하는 코드를 모두 넣었는데
//		정답코드에서는 클래스 멤버함수로 구현해놓았다.
// 시간복잡도 : O(N)