#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct node
{
	int value=0;
	node* left=nullptr;
	node* right=nullptr;
};
void first(node* root, string* ret)
{
	*ret += to_string(root->value);
	if (root->left)
		first(root->left, ret);
	if (root->right)
		first(root->right, ret);
}
void middle(node* root, string* ret)
{
	if (root->left)
		middle(root->left, ret);
	*ret += to_string(root->value);
	if (root->right)
		middle(root->right, ret);
}
void last(node* root, string* ret)
{
	if (root->left)
		last(root->left, ret);
	if (root->right)
		last(root->right, ret);
	*ret += to_string(root->value);
}

vector<string> solution(vector<int>nodes)
{
	vector<string>answer;
	node* root = new node;
	root->value = nodes[0];

	node* standardNode = root;
	for (int i = 1; i < nodes.size(); ++i)
	{
		node* n = new node;
		n->value = nodes[i];
		while (1)//트리 생성
		{
			if (standardNode==NULL)
			{
				standardNode = n;
				break;
			}
			else if (!standardNode->left)
			{
				standardNode->left = new node;
				standardNode->left = n;
				break;
			}
			else if (!standardNode->right)
			{
				standardNode->right = new node;
				standardNode->right = n;
				standardNode = root;
				break;
			}
			if (!standardNode->left->left)
				standardNode = standardNode->left;
			else if(!standardNode->right->left)
				standardNode = standardNode->right;

		}
	}
	string firstcicle;//전위순회
	string middlecicle;//중위순회
	string lastcicle;//후위순회
	
	first(root, &firstcicle);
	middle(root, &middlecicle);
	last(root, &lastcicle);
	answer.push_back(firstcicle);
	answer.push_back(middlecicle);
	answer.push_back(lastcicle);



	return answer;
}
int main()
{
	vector<string>answer = solution({ 1, 2, 3, 4, 5, 6, 7 });
	for (auto ca : answer)
		cout << ca << endl;
}
// 정답코드
//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//// 전위순회
//string preorder(const vector<int>& nodes, int idx) {
//	if (idx < nodes.size()) {
//		string ret = to_string(nodes[idx]) + " ";
//		ret += preorder(nodes, idx * 2 + 1);
//		ret += preorder(nodes, idx * 2 + 2);
//		return ret;
//	}
//
//	return "";
//}
//
//// 중위순회
//string inorder(const vector<int>& nodes, int idx) {
//	if (idx < nodes.size()) {
//		string ret = inorder(nodes, idx * 2 + 1);
//		ret += to_string(nodes[idx]) + " ";
//		ret += inorder(nodes, idx * 2 + 2);
//		return ret;
//	}
//
//	return "";
//}
//
//// 후위순회
//string postorder(const vector<int>& nodes, int idx) {
//	if (idx < nodes.size()) {
//		string ret = postorder(nodes, idx * 2 + 1);
//		ret += postorder(nodes, idx * 2 + 2);
//		ret += to_string(nodes[idx]) + " ";
//		return ret;
//	}
//
//	return "";
//}
//
//vector<string> solution(const vector<int>& nodes) {
//	vector<string> result;
//	string pre = preorder(nodes, 0);
//	string in = inorder(nodes, 0);
//	string post = postorder(nodes, 0);
//
//	// 마지막 공백을 제거한 결과를 result에 추가
//	pre.pop_back();
//	in.pop_back();
//	post.pop_back();
//
//	result.push_back(pre);
//	result.push_back(in);
//	result.push_back(post);
//
//	return result;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iterator>
//#include <iostream>
//void print(vector<string> vec)
//{
//	copy(vec.begin(), vec.end(), std::ostream_iterator<string>(cout, "\n"));
//	cout << endl;
//}
//
//int main()
//{
//	print(solution({ 1, 2, 3, 4, 5, 6, 7 }));
//	/**
//	 출력값
//	 1 2 4 5 3 6 7
//	 4 2 5 1 6 3 7
//	 4 5 2 6 7 3 1
//	**/
//
//	return 0;
//}
//내코드와 다른점:
// 나는 포인터로 트리를 구성하였고, 정답코드에서는 배열로 트리를 구성하였다.
// 정답코드에서는 배열로 하다보니, 순회함수에 인덱스를 포함해서, 인덱스가 벡터의 크기보다 작을때
// 노드에 방문하였다.
// 시간복잡도 : O(N)