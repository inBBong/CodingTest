#include<iostream>
#include<vector>
using namespace std;
void fillDP(vector<vector<int>> arr, vector<int>&dp, int num,int idx)
{
	if (idx == arr[0].size()-1)
		return;
	int sum(dp[idx]);

	switch (num)
	{
	case 1:
		if (arr[1][idx + 1] > arr[2][idx + 1])
		{
			dp[idx + 1] = sum + arr[1][idx + 1];
			num = 2;
		}
		else
		{
			dp[idx + 1] = sum + arr[2][idx + 1];
			num = 3;
		}
		
		break;
	case 2:
		dp[idx + 1] = sum + arr[2][idx + 1]+ arr[0][idx + 1];
		num = 4;
		break;
	case 3:
		if (arr[0][idx + 1] > arr[1][idx + 1])
		{
			dp[idx + 1] = sum + arr[0][idx + 1];
			num = 1;
		}
		else
		{
			dp[idx + 1] = sum + arr[1][idx + 1];
			num = 2;
		}
		break;
	case 4:
		dp[idx + 1] = sum + arr[1][idx + 1];
		num = 2;
		break;
	}
	idx++;
	fillDP(arr, dp, num, idx);
}
int solution(vector<vector<int>> arr)
{
	int N = arr[0].size();
	int answer(0);
	vector<int>dp1(N);
	vector<int>dp2(N);
	vector<int>dp3(N);
	vector<int>dp4(N);
	dp1[0] = arr[0][0];
	dp2[0] = arr[1][0];
	dp3[0] = arr[2][0];
	dp4[0] = arr[0][0]+ arr[2][0];
	fillDP(arr, dp1, 1,0);
	fillDP(arr, dp2, 2,0);
	fillDP(arr, dp3, 3,0);
	fillDP(arr, dp4, 4,0);
	if (dp1[N - 1] > answer)
		answer = dp1[N - 1];
	if (dp2[N - 1] > answer)
		answer = dp2[N - 1];
	if (dp3[N - 1] > answer)
		answer = dp3[N - 1];
	if (dp4[N - 1] > answer)
		answer = dp4[N - 1];
	return answer;
}
int main()
{
	cout << solution({ {1, 3, 3, 2}, {2, 1, 4, 1}, {1, 5, 2, 3} }) << endl; //출력값 : 19
	cout << solution({ {1, 7, 13, 2, 6}, {2, -4, 2, 5, 4}, {5, 3, 5, -3, 1} }) << endl; //출력값 : 32

}
//정답코드:
#include <vector>
#include <algorithm>

using namespace std;

// 조약돌 배치 패턴에 대해 최대 가중치를 계산하는 함수
int solution(vector<vector<int>> arr) {
	// ❶ 입력 벡터의 열의 개수
	int n = arr[0].size();
	// ❷ dp 벡터 초기화
	vector<vector<int>> dp(4, vector<int>(n, 0));

	// ❸ 첫 번째 열의 가중치 초기화 (0: 상단, 1: 중앙, 2: 하단, 3: 상단과 하단)
	dp[0][0] = arr[0][0];
	dp[1][0] = arr[1][0];
	dp[2][0] = arr[2][0];
	dp[3][0] = arr[0][0] + arr[2][0];

	// ❹ 두 번째 열부터 마지막 열까지 가중치를 구함
	for (int i = 1; i < n; ++i) {
		// 패턴 0이 선택된 경우, 이전은 패턴 {1, 2} 가능
		dp[0][i] = arr[0][i] + max(dp[1][i - 1], dp[2][i - 1]);
		// 패턴 1이 선택된 경우, 이전은 패턴 {0, 2, 3} 가능
		dp[1][i] = arr[1][i] + max({ dp[0][i - 1], dp[2][i - 1], dp[3][i - 1] });
		// 패턴 2가 선택된 경우, 이전은 패턴 {0, 1}이 가능
		dp[2][i] = arr[2][i] + max(dp[0][i - 1], dp[1][i - 1]);
		// 패턴 3이 선택된 경우, 이전은 패턴 {1}이 가능
		dp[3][i] = arr[0][i] + arr[2][i] + dp[1][i - 1];
	}

	// ❺ 마지막 열의 가중치 중, 최대 가중치를 반환합니다.
	return max({ dp[0][n - 1], dp[1][n - 1], dp[2][n - 1], dp[3][n - 1] });
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution({ {1, 3, 3, 2}, {2, 1, 4, 1}, {1, 5, 2, 3} }) << endl; //출력값 : 19
	cout << solution({ {1, 7, 13, 2, 6}, {2, -4, 2, 5, 4}, {5, 3, 5, -3, 1} }) << endl; //출력값 : 32

	return 0;
}
// 내 코드와 다른 점:
//  내 코드와 정답코드는 비슷해보이지만, 핵심적인 부분이 다르다. 물론 정답코드가 더 좋은 코드다.
// 내 코드는 dp1~dp4까지 선언하고, 처음에 1번행에 놓은경우, 2번행, 3번행, {1,3}번행에 놓은 경우로
// 4가지를 선언한다. 그리고 방금 놓은 조약돌의 경우를 이용해서 다음 놓을 곳을 정한다.
// 
// 반면 정답코드에서는 다음 놓을 조약돌을 기준으로 이전에 놓은 조약돌을 결정한다.
// 이것에 동적계획법에도 더 잘 맞고 더 효율적이다.
// 
// 시간복잡도 : O(N)
//