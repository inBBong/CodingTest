#include<iostream>
#include<vector>
using namespace std;
int checkSquare(vector<vector<int>> board, int i, int j, int N)
{
	if (N == 1)
		return 1;
	int ret(1);
	for (int l = 2; l <= N;++l)
	{
		bool can(true);
		for (int n = i; n < i+l; ++n)
		{
			for (int m = j; m < j + l; ++m)
			{
				if (board[n][m] == 0)
				{
					can = false;
				}
			}
			if (!can)
				break;
		}
		if(can)
		ret = l*l;
	}
	return ret;
}
int solution(vector<vector<int>> board)
{
	int N = min(board.size(), board[0].size());
	int answer(0);
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[0].size(); ++j)
		{
			if (board[i][j] == 1)
			{
				answer = max(answer, checkSquare(board, i, j, min(board.size()-i,board[0].size()-j)));
			}
		}
	}
	return answer;
}
int main()
{
	cout << solution({ {0, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {0, 0, 1, 0} }) << endl; //출력값 : 9
	cout << solution({ {0, 0, 1, 1}, {1, 1, 1, 1} }) << endl; //출력값 : 4  

}
//정답코드
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> board) {
	//❶ 주어진 2차원 보드의 행과 열의 개수를 변수에 저장합니다.
	int ROW = board.size(), COL = board[0].size();

	//❷ 각 행과 열을 순회하며 가장 큰 정사각형의 길이 확인
	for (int i = 1; i < ROW; ++i) {
		for (int j = 1; j < COL; ++j) {
			//❸ 현재 위치의 값이 1인 경우
			if (board[i][j] == 1) {
				//❹ 현재 위치에서 위, 왼쪽, 대각선 왼쪽 위의 값을 구함
				int up = board[i - 1][j];
				int left = board[i][j - 1];
				int up_left = board[i - 1][j - 1];

				//❺ 현재 위치의 값을 이전 위치들의 값들 중 가장 작은 값에 1을 더한 값으로 업데이트
				board[i][j] = min(min(up, left), up_left) + 1;
			}
		}
	}

	//❻ 보드에서 가장 큰 값(최대 정사각형의 한 변의 길이) 확인
	int max_val = 0;
	for (const auto& row : board) {
		max_val = max(max_val, *max_element(row.begin(), row.end()));
	}
	//❼ 최대 정사각형 넓이 반환
	return max_val * max_val;
}




//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution({ {0, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {0, 0, 1, 0} }) << endl; //출력값 : 9
	cout << solution({ {0, 0, 1, 1}, {1, 1, 1, 1} }) << endl; //출력값 : 4  
	return 0;
}
// 내 코드와 다른 점:
// 나도 어떻게든 구현을 해내긴 했지만, 동적계획법을 사용한 풀이는 아니었던것 같다.
// 나는 보드를 순회하면서, 1을 만나면 해당 위치부터 보드에서 정사각형 모양으로 순회하면서,
// 0을 만나지 않으면 해당 정사각형의 넓이를 반환하는 함수를 만들었다.
//  반면, 정답코드는 보드의 1행1열부터 n-1행n-1열까지 순회하면서, 진행방향에 맞게
// 왼쪽,위쪽,왼쪽의위쪽 값의 가장작은값 +1을 저장했다. 그럼 자연스럽게 정사각형의 길이가
// 보드의 값으로 저장된다. 그리고 다시 보드를 순회하면서 가장 큰 값의 제곱값을 반환한다.
// 
// 시간복잡도 : O(N*M)
//