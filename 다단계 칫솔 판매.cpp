#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;
//내코드
class node
{
private:
    string name;
    vector<node*>sons;
    node* parent;
    node* center;
    int amount;
public:
    node():name("0"),center(nullptr),amount(0),parent(nullptr){}
    node(string _name,node* root):name(_name),center(root), amount(0), parent(nullptr) {}
    node(string _name,node* root,int _amount):name(_name),center(root),amount(_amount), parent(nullptr){}
    node(string _name):name(_name),center(nullptr), amount(0), parent(nullptr) {}
    vector<node*>&GetSons() { return sons; }
    int GetAmount(){ return amount; }
	node* search_node(string searchName, node* currentNode)
	{
        if (!currentNode)return nullptr;
		if (currentNode->name == searchName)
			return currentNode;
		else
		{
			for (auto cs : currentNode->sons)
			{
                if (node* found = search_node(searchName, cs))
                    return found;
			}
		}
        return nullptr;
	}
    void PlusAmount(int amt) { amount += amt; }
    void SetParent(node* p) { parent = p; }
    void SendRest(int amt) 
    {
        node* currentNode = this;
        int rest = amt / 10;
        while(rest && currentNode&&currentNode!=center)
        {            
            currentNode ->amount -= rest;
           currentNode->parent->amount += rest;
           currentNode = currentNode->parent;
           rest /= 10;
        }
    }
};

vector<int> solution(vector<string>enroll, vector<string> referral, vector<string>seller, vector<int>amount)
{
    vector<int>answer;
    node* center=new node("-");
    for (int i = 0; i < enroll.size(); ++i)
    {
        int amt = 0;
        for (int j = 0; j < seller.size(); ++j)
        {
            if (seller[j] == enroll[i])
                amt = amount[j]*100;
        }                   
        node* n = new node(enroll[i],center,amt);                
		node* parent = n->search_node(referral[i], center);
		n->SetParent(parent);
		parent->GetSons().push_back(n);
		n->SendRest(amt);
	}
	for (int i = 0; i < enroll.size(); ++i)
	{
        answer.push_back(center->search_node(enroll[i], center)->GetAmount());
	}

    return answer;

    //출력값 : 360 958 108 0 450 18 180 1080

}
int main()
{
    vector<int> a=solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
        { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
        { "young", "john", "tod", "emily", "mary" },
        { 12, 4, 2, 5, 10 }
    ); //출력값 : 360 958 108 0 450 18 180 1080

    vector<int> b=solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
        { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
        { "sam", "emily", "jaimie", "edward" },
        { 2, 3, 5, 4 }
    ); //출력값 : 0 110 378 180 270 450 0 0 

    for (auto ca : a)
        cout << ca << " ";
    cout << endl;
    for (auto cb : b)
        cout << cb << " ";
}
//정답코드:
//#include <iostream>
//#include <vector>
//#include <unordered_map>
//#include <string>
//
//using namespace std;
//
//vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
//    unordered_map<string, string> parent;
//
//    //❶ parent는 판매원 - 판매원을 참여시킨 추천인으로 구성 
//    for (size_t i = 0; i < enroll.size(); ++i) {
//        parent[enroll[i]] = referral[i];
//    }
//
//    unordered_map<string, int> total;
//    //❷ total은 판매원 - 판매원의 수익으로 구성되고 수익을 0으로 초기화
//    for (const auto& name : enroll) {
//        total[name] = 0;
//    }
//
//    for (size_t i = 0; i < seller.size(); ++i) {
//        //❸ cur_name은 실제 물건을 판 사람이고, money 현재 판매원의 수익금
//        int money = amount[i] * 100;
//        string cur_name = seller[i];
//
//        while (money > 0 && cur_name != "-") {
//            //❹ 실제 물건을 판 사람을 기준으로  추천인을 계속 추적하며 남은 수익의 10%를 분배
//            int to_distribute = money / 10;
//            total[cur_name] += money - to_distribute;
//            //❺ 현재 이름의 추천인이있으면, 현재이름은 추천인으로 변경, 그렇지 않으면 종료 
//            if (parent.find(cur_name) != parent.end()) {
//                cur_name = parent[cur_name];
//            }
//            else {
//                break;
//            }
//            //❻  현재 판매원이 추천인으로 변경되었으므로, 수익금도 이에 맞춰서 업데이트
//            money = to_distribute;
//        }
//    }
//
//    //❼ 수익금을 answer에 업데이트 해서 반환
//    vector<int> result;
//    result.reserve(enroll.size());
//    for (const auto& name : enroll) {
//        result.push_back(total[name]);
//    }
//
//    return result;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iterator>
//#include <iostream>
//void print(vector<int> vec)
//{
//    copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
//    cout << endl;
//}
//
//int main()
//{
//    print(solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
//        { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
//        { "young", "john", "tod", "emily", "mary" },
//        { 12, 4, 2, 5, 10 }
//    )); //출력값 : 360 958 108 0 450 18 180 1080
//
//    print(solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
//        { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
//        { "sam", "emily", "jaimie", "edward" },
//        { 2, 3, 5, 4 }
//    )); //출력값 : 0 110 378 180 270 450 0 0 
//    return 0;
//}
// 내 코드와 다른점:
//      나는 트리를 직접 구현했지만 정답코드에서는 unordered_map<string,string>을 이용해서 자식-부모 맵을 만들었다.
//      나는 트리를 생성하는 과정에서 각 노드가 번 수익을 즉시 부모노드에게 배분했다. 트리를 완성 한 후 
//      enroll의 이름들로 트리의 노드를 탐색해 amount를 반환하였다.
//      정답코드를 보니 트리를 생성할 필요가 없었다는게 느껴졌다. 트리를 생성하지 않고도 간결하게 코드를 짤 수 있었다.
//      중요한건 자식 - 부모 관계를 표현한 자료구조였다. 생각해보니 졸작에서 애니메이션 할때도 뼈 계층구조를 담는
//      unorder_map<string,string>을 사용했었는데 이걸 생각하지 못하다니..아쉬웠다.
// 시간복잡도: 
// 정답코드 : O(N*M)
// 내코드: O(N^2)
// 
//