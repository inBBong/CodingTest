#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;
//내코드
int solution(vector<string> want, vector<int> number, vector<string> discount)
{
    unordered_map<string, int> list;
    int answer = 0;
    for (int i = 0; i < want.size(); ++i)
        list[want[i]] = number[i];

	for (int k = 0; k < discount.size() - 9; ++k)
	{
		bool compareSucceed = true;
		unordered_map<string, int>compareList(0);
		for (int i = k; i < k + 10; ++i)
		{
			compareList[discount[i]]++;
		}
        for (auto cl :list)
        {
            if (cl.second != compareList[cl.first])                            
            {
                compareSucceed = false; break;
            }
        }
        if (compareSucceed)
            answer++;
    }
    return answer;
}
int main()
{
    cout << solution({ "banana", "apple", "rice", "pork", "pot" },
        { 3, 2, 2, 2, 1 },
        { "chicken", "apple", "apple", "banana", "rice","apple", "pork", "banana", "pork", "rice", "pot","banana", "apple", "banana" }) << endl; // 3

    cout << solution({ "apple" },
        { 10 },
        { "banana", "banana", "banana", "banana","banana", "banana", "banana", "banana", "banana","banana" }) << endl; // 0
}
//정답코드
//#include <string>
//#include <vector>
//#include <unordered_map>
//
//using namespace std;
//
//int solution(vector<string> want, vector<int> number, vector<string> discount) {
//    int answer = 0;
//
//    unordered_map<string, int> wantMap;
//    //❶ want를 키로  number를 값으로 해서 wantMap을 선언
//    for (int i = 0; i < want.size(); i++)
//        wantMap[want[i]] = number[i];
//
//
//    for (int i = 0; i < discount.size() - 9; i++) {
//        // ❷ i일 회원가입 시, 할인받을 수 있는 품목을 키로, 개수를 값으로 해서  discount_10d 선언
//        unordered_map<string, int> discount_10d;
//
//        // ❸  각 할인하는 품목을 키로  개수를 저장
//        for (int j = i; j < 10 + i; j++)
//            discount_10d[discount[j]]++;
//
//        // ❹ 할인하는 상품의 품목및 개수가 원하는 상품의 품목 및 개수와 일치하면 카운트 증가
//        if (wantMap == discount_10d) answer++;
//    }
//
//    return answer;
//}
//
////여기부터는 테스트 코드 입니다.
//#include <iostream>
//
//int main()
//{
//    cout << solution({ "banana", "apple", "rice", "pork", "pot" },
//        { 3, 2, 2, 2, 1 },
//        { "chicken", "apple", "apple", "banana", "rice","apple", "pork", "banana", "pork", "rice", "pot","banana", "apple", "banana" }) << endl; // 3
//
//    cout << solution({ "apple" },
//        { 10 },
//        { "banana", "banana", "banana", "banana","banana", "banana", "banana", "banana", "banana","banana" }) << endl; // 0
//    return 0;
//}
// 내코드와 다른점:
// 내 코드와 정답코드의 로직은 같다.
// 다만 나는 list와 compareList의 비교를 할때 for 문을 이용해 list 를 순회하면서 각 키별 값을 모두 비교했다.
// 하지만 unordered_map에는 == 연산자 오버로딩이 되어있었다!!
// 정답코드에서는 그저 list == compareList 로 판단한 것이다.
// 이거 때문에, 정답코드와 내 코드는 , list를 한번 순회하느냐 마느냐가 결정되었다.
// 따라서 내 코드의 시간복잡도는 O(N^2)이지만 정답코드의 시간복잡도는 O(N)이 된다는 큰 차이가 생겨버렸다..
//