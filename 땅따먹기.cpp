#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int solution(vector<vector<int>>land)
{
	vector<bool>canStep(4, true);
	int N = land.size();
	vector<int>dp=land[0];

	for (int i = 1; i < N; ++i)
	{
		dp[0] += *max_element(land[i].begin() + 1, land[i].end());
		dp[1] += max(land[i][0], *max_element(land[i].begin() + 2, land[i].end()));
		dp[2] += max(land[i][3], *max_element(land[i].begin(), land[i].begin() + 2));
		dp[3] += *max_element(land[i].begin(), land[i].end()-1);
	}

	int answer(0);
	for (int i = 0; i < 4; ++i)
	{
		if (dp[i] > answer)
			answer = dp[i];
	}
	return answer;
}
int main()
{
	cout << solution({ {1, 2, 3, 5}, {5, 6, 7, 8}, {4, 3, 2, 1} }) << endl; //출력값 : 16
}
//정답코드 :
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> land) {
	// ➊ 각 행마다 이전 행에서의 최대 점수를 더해가며 최대 점수 누적
	for (int i = 1; i < land.size(); ++i) {
		for (int j = 0; j < 4; ++j) {
			// ➋ 이전 행에서 현재 열의 값을 제외한 나머지 열들 중에서 가장 큰 값을 더함
			int maxVal = 0;
			for (int k = 0; k < 4; ++k) {
				if (k != j) {
					maxVal = max(maxVal, land[i - 1][k]);
				}
			}
			land[i][j] += maxVal;
		}
	}
	// ➌ 마지막 행에서 얻을 수 있는 최대 점수를 반환
	return *max_element(land.back().begin(), land.back().end());
}



//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution({ {1, 2, 3, 5}, {5, 6, 7, 8}, {4, 3, 2, 1} }) << endl; //출력값 : 16

	return 0;
}
//내 코드와 다른 점:
// dp의 행을 늘려가면서 이전 행의 최댓값을 갱신해주는 로직은 정답코드와 같다.
// 그러나 정답코드에서는 4*4의 반복문을 사용해서 j!=k 일때의 max값을 더해줬고, dp를 새로 사용하지 않고
// 입력 벡터 land를 직접 갱신해줬다..
// 나는 dp 벡터를 선언하고 max_element함수를 사용해서 land[i]의 최댓값을 갱신했다.
// 
// 시간복잡도 :O(N)
//