#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;
//내코드
string solution(vector<string> cards1, vector<string> cards2, vector<string> goal)
{
	queue<string> q1;
	queue<string> q2;
	for (auto cs : cards1)
		q1.push(cs);
	for (auto cs : cards2)
		q2.push(cs);

	for (auto cs : goal)
	{
		if (!q1.empty()&& cs == q1.front())
		{
			q1.pop();
		}
		else if (!q2.empty() && cs == q2.front())
		{
			q2.pop();
		}
		else
		{
			return "No";
		}
	}
	return "Yes";
}
int main()
{
	cout << solution({ "i","drink", "water" }, { "want","to" }, { "i", "want", "to", "drink", "water" });// yes
	cout << solution({ "i","water", "drink" }, { "want","to" }, { "i", "want", "to", "drink", "water" });// no

}
//정답코드
//#include <iostream>
//#include <queue>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
//    queue<string> c1, c2, g;
//
//    // ❶cards와 goal을 queue로 나타냄 
//    for (const string& s : cards1) c1.push(s);
//    for (const string& s : cards2) c2.push(s);
//    for (const string& s : goal) g.push(s);
//
//    //❷ 단어 배열을 앞에서 부터 순회 
//    while (!g.empty()) {
//        //❸ c1의 현재 문자열과 g의 현재 문자열이 일치하는 경우
//        if (!c1.empty() && c1.front() == g.front()) {
//            c1.pop();
//            g.pop();
//        }
//        //❹ c2의 현재문자열과  g의 현재 문자열이 일치하는 경우 
//        else if (!c2.empty() && c2.front() == g.front()) {
//            c2.pop();
//            g.pop();
//        }
//        //❺ 일치하는 카드뭉치가 없는 경우 반복문을 빠져나감 
//        else {
//            break;
//        }
//    }
//    //❻ 원하는 문자열을 카드뭉치에서 만들었으면 Yes 아니면 No 반환
//    return g.empty() ? "Yes" : "No";
//}
//
//
//
//
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//
//int main()
//{
//    cout << solution({ "i", "drink", "water" }, { "want", "to" }, { "i", "want", "to", "drink", "water" }) << endl; // "Yes"
//    cout << solution({ "i", "water", "drink" }, { "want", "to" }, { "i", "want", "to", "drink", "water" }) << endl; // "No"
//    return 0;
//
//}
// 내코드와 다른점 : 정답코드에서는 goal에 대한 queue도 만들어서 같이 pop하면서 진행함. 난 goal은 배열 그대로 사용함.
// 정답코드 방식이 좀더 간결한듯? 로직은 똑같음
// 시간복잡도 : O(N+M)
//