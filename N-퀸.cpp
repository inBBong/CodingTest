#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
vector<int>queen;
int answer(0);
bool isValid(int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		if (queen[i] == col || abs(i - row)==abs(queen[i]-col))
			return false;
	}
	return true;
}
void SetQueen(int row,int n)
{
	if (row == n)
	{
		answer++; return;
	}
	for (int i = 0; i < n; ++i)
	{
		if (isValid(queen.size(), i))
		{
			queen.push_back(i);
			SetQueen(queen.size(), n);
			queen.pop_back();
		}
	}
}
long long solution(int n)
{
	//queen.resize(n,-1);
	SetQueen(0,n);
	return answer;
}
int main()
{
	cout << solution(4);
}

//정답코드
#include <vector>
#include <algorithm>

using namespace std;

//❶ 현재 행에 이미 다른 퀸이 있는지 확인하는 함수
bool isSameRow(int placedRow, int currentRow) {
	return placedRow == currentRow;
}

//❷ 대각선에 다른 퀸이 있는지 확인하는 함수
bool isDiagonalAttack(int placedCol, int placedRow, int currentCol, int currentRow) {
	return abs(placedCol - currentCol) == abs(placedRow - currentRow);
}

//❸ 퀸을 안전하게 배치할 수 있는지 확인하는 함수
bool isSafePosition(const vector<int>& queen, int col, int row) {
	for (int i = 0; i < col; ++i) {
		if (isSameRow(queen[i], row) || isDiagonalAttack(i, queen[i], col, row)) {
			return false;
		}
	}
	return true;
}

//❹ 퀸을 배치하는 함수
long long placeQueens(vector<int>& queen, int col) {
	int n = queen.size();
	if (col == n) {
		return 1;
	}

	long long count = 0;
	for (int row = 0; row < n; ++row) {
		//❺ 퀸을 놓을수 있는 위치인 경우 퀸을 놓음
		if (isSafePosition(queen, col, row)) {
			queen[col] = row;
			count += placeQueens(queen, col + 1);
			queen[col] = -1;
		}
	}
	return count;
}

long long solution(int n) {
	vector<int> queen(n, -1);

	//❻ 퀸을 놓을수 있는 경우의 수를 반환
	return placeQueens(queen, 0);
}
//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution(4) << endl; // 출력값 : 2
	return 0;
}
// 내 코드와 다른점:
// 유망함수, 즉 퀸을 놓을 수 있는지 여부에 대한 로직은 똑같다.
// 정답코드에서는 queen 벡터를 solution 함수의 지역변수로, 나는 전역변수로 선언하였다.
// 그래서 나는 queen을 push_back, pop_back을 하며 queen.size()를 기준으로
// 현재 행에 퀸을 놓았고, 정답코드에서는 직접 매개변수 col을 +1 해주면서 퀸을 놓았다.
// 원복은 그냥 queen[col]=-1을 하였다.
// 또한 지피티에게 내 코드 피드백을 부탁했는데, 이런... 내가 SetQueen 함수에
// return을 아예 넣어주지 않았다. 그래서 다시 추가했다. SetQueen 함수를 n번 돌면 더이상 퀸을
// 놓을 수 있는 열이 존재 하지 않기때문에 다행히 답은 나왔지만, 쓸데없는 연산을 더 하게 되었다.
// 백트래킹 문제중 처음으로 내 힘으로 문제를 풀어내서 뿌듯했다.
// 
// 시간복잡도: O(N!) 하지만 유망함수에 의해 훨씬 적음