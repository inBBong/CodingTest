#include<iostream>
#include<vector>
#include<limits>
#include<string>
#include<unordered_set>

using namespace std;

int solution(vector<string> strs, string t)
{
	int n = t.length();
	int INF = numeric_limits<int>::max();
	vector<long long>dp(n + 1, INF);
	dp[0] = 0;
	unordered_set<int>sizes;
	unordered_set<string>strsSet(strs.begin(), strs.end());
	for (auto str : strs)
		sizes.insert(str.size());

	for (int i = 1; i < dp.size(); ++i)
	{
		for (auto size : sizes)
		{
			if (i >= size && strsSet.count(t.substr(i - size, size)))
				dp[i] = min(dp[i], dp[i - size] + 1);
		}
	}
	return dp[n]==INF ? -1 : dp[n];
}
int main()
{
	cout << solution({ "ba", "na", "n", "a" }, "banana") << endl; //출력값 : 3
	cout << solution({ "app", "ap", "p", "l", "e", "ple", "pp" }, "apple") << endl; //출력값 : 2  
	cout << solution({ "ba", "an", "nan", "ban", "n" }, "banana") << endl; //출력값 : -1 
}
//정답코드 :
//#include <vector>
//#include <string>
//#include <unordered_set>
//#include <algorithm>
//#include <limits>
//
//using namespace std;
//
//int solution(vector<string> strs, string t) {
//    int INF = numeric_limits<int>::max();
//    int n = t.length();  //❶ 타겟 문자열 t의 길이
//    vector<long long> dp(n + 1, INF);  //❷ 각 위치에서 필요한 최소 조각수를 저장할 벡터(초깃값은 INF)
//    dp[0] = 0;  //❸ 빈 문자열을 얻기 위한 최소 조각수는 0
//
//    unordered_set<int> sizes;  //❹ strs 조각들의 길이를 저장한 집합
//    for (const auto& s : strs) {
//        sizes.insert(s.length());
//    }
//
//    unordered_set<string> strsSet(strs.begin(), strs.end());  //❺ strs의 원소를 저장한 집합
//
//
//
//    for (int i = 1; i <= n; ++i) {
//        for (int size : sizes) {  //❻ 각 str 조각의 문자열 길이에 대하여
//            //❼ 이미 구한 해와 str 조각을 추가해서 문자열을 만들 수 있다면
//            if (i >= size && strsSet.count(t.substr(i - size, size))) {
//                dp[i] = min(dp[i], dp[i - size] + 1);  //❽ 해당 위치의 최소 조각수를 갱신
//            }
//        }
//    }
//    return dp[n] != INF ? dp[n] : -1;  //➒ 최소 조각수를 반환(만들 수 없으면 -1)
//}
//
//
//
//
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//    cout << solution({ "ba", "na", "n", "a" }, "banana") << endl; //출력값 : 3
//    cout << solution({ "app", "ap", "p", "l", "e", "ple", "pp" }, "apple") << endl; //출력값 : 2  
//    cout << solution({ "ba", "an", "nan", "ban", "n" }, "banana") << endl; //출력값 : -1 
//
//    return 0;
//}

//내 코드와 다른 점:
// 이번 문제도 난이도가 엄청 높은 문제였던 것 같다. 그래서 정답코드를 먼저 본 후에 이해를 하고 구현하였다.
// 처음에는 dp의 자료형을 int로 했더니 결과 값이 -275273238232 같은 값이 나왔다. 클로드한테 물어보니
// INF에서 1을 더하면 int 에서 표현할 수 있는 양수값의 최대를 초과해서 오버플로우가 났다고 했다.
// 그래서 dp의 자료형을 long long으로 바꾸니까 결과가 잘 나왔다.
// 
// 시간복잡도 : O(N)