#include<iostream>
#include<vector>
using namespace std;

int solution(vector<int>money)
{
	int N = money.size();
	vector<int>stealFirstHome(N,0);
	vector<int>NotstealFirstHome(N,0);
	stealFirstHome[0] = money[0];
	stealFirstHome[1] = stealFirstHome[0];	
	NotstealFirstHome[1] = money[1];

	for (int i=2;i<N-1;++i)
	{
		stealFirstHome[i] = max(stealFirstHome[i - 2] + money[i], stealFirstHome[i - 1]);
	}
	for(int i=2;i<N;++i)
	{
		NotstealFirstHome[i] = max(NotstealFirstHome[i - 2] + money[i], NotstealFirstHome[i - 1]);
	}
	return max(stealFirstHome[N - 2],NotstealFirstHome[N-1]);
}
int main()
{
	cout << solution({ 1, 2, 3, 1 }) << endl; //출력값 : 4
}
//정답코드:
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> money) {
	//❶ 점화식에 필요한 변수를 초기화
	int n = money.size();
	vector<int> dp1(n, 0);
	vector<int> dp2(n, 0);

	//❷ 첫 번째 집을 터는 경우
	dp1[0] = money[0];
	dp1[1] = money[0];
	for (int i = 2; i < n - 1; ++i) {
		dp1[i] = max(dp1[i - 1], dp1[i - 2] + money[i]);
	}

	//❸ 첫 번째 집을 털지 않는 경우
	dp2[1] = money[1];
	for (int i = 2; i < n; ++i) {
		dp2[i] = max(dp2[i - 1], dp2[i - 2] + money[i]);
	}

	//❹ 두 경우 중, 최대값 찾기
	int answer = max(dp1[n - 2], dp2[n - 1]);
	return answer;
}



//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution({ 1, 2, 3, 1 }) << endl; //출력값 : 4

	return 0;
}
//내 코드와 다른 점:
// 완전히 같은 코드이다. 문제를 보고 책에 나온 문제 분석을 본 후 구현했더니 완전히 같은 로직으로 구현하게 되었다.
// 다만, 테스트케이스가 부족해서 맞게 구현했는지 긴가민가 해서 프로그래머스에 제출을 해봤는데, 자꾸 틀리게 나왔다.
// 정답코드와 비교해보니, 정답코드에서는 첫번째 집을 방문한 벡터의 값을 채울때, 마지막집은 방문할 수 없다는 것을 고려해주었다.
// 집은 원형으로 놓여있기 때문에 첫번째 집을 털면 마지막 집은 털 수 없다. 이부분을 놓쳐서 계속 틀린 것이었다.
// 
// 시간복잡도 :O(N)
//
