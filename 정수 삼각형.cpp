#include<iostream>
#include<vector>
using namespace std;

int solution(vector<vector<int>> triangle)
{
	int N = triangle.size();
	vector<int>dp(N,0);
	for (int i = N - 2; i >= 0; --i)
	{
		for(int j = 0; j < triangle[i].size();++j)
		{
			triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
	return triangle[0][0];
}
int main()
{
	cout << solution({ {7}, {3, 8}, {8, 1, 0}, {2, 7, 4, 4}, {4, 5, 2, 6, 5} }) << endl; //출력값 : 30
}
// 정답코드 :
#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, 0)); // ➊ dp 테이블 초기화

    // ➋ dp 테이블의 맨 아래쪽 라인 초기화
    for (int i = 0; i < n; i++) {
        dp[n - 1][i] = triangle[n - 1][i];
    }

    // ➌ 아래쪽 라인부터 올라가면서 dp 테이블 채우기
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
        }
    }

    return dp[0][0]; // 꼭대기에서의 최댓값 반환
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
    cout << solution({ {7}, {3, 8}, {8, 1, 0}, {2, 7, 4, 4}, {4, 5, 2, 6, 5} }) << endl; //출력값 : 30

    return 0;
}
//내 코드와 다른 점:
// 똑같은데 나는 입력 배열 triangle을 그대로 사용하였고 정답코드에서는 dp를 사용하였다.
// 
// 시간복잡도 : O(N^2)
//