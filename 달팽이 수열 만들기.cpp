#include<iostream>
#include<vector>
using namespace std;
enum direction
{
	RIGHT=0,
	DOWN,
	LEFT,
	UP
};
bool isValid(vector<vector<int>> mat,int n, int m,int N)
{
	if (n >= 0 && n < N && m >= 0 && m < N&&mat[n][m]==0)
		return true;
	else
		return false;
}
void SnailMat(vector<vector<int>>&mat,int num,int direction,int n,int m)
{	
	if (num > mat.size() * mat.size())
		return;
	mat[n][m] = num;
	int N = mat.size();
	int dm, dn;
	switch (direction)
	{
	case direction::RIGHT:
		dm = 1;
		dn = 0;
		break;
	case direction::DOWN:
		dm = 0;
		dn = 1;
		break;
	case direction::LEFT:
		dm = -1;
		dn = 0;
		break;
	case direction::UP:
		dm = 0;
		dn = -1;
		break;
	}
	m += dm;
	n += dn;
	if (isValid(mat,n, m,N))
	{
		SnailMat(mat, ++num, direction, n, m);
	}
	else
	{
		direction = (direction + 1) % 4;
		m -= dm;
		n -= dn;
		switch (direction)
		{
		case direction::RIGHT:
			dm = 1;
			dn = 0;
			break;
		case direction::DOWN:
			dm = 0;
			dn = 1;
			break;
		case direction::LEFT:
			dm = -1;
			dn = 0;
			break;
		case direction::UP:
			dm = 0;
			dn = -1;
			break;
		}
		m += dm;
		n += dn;
		SnailMat(mat, ++num, direction, n, m);
	}
}
vector<vector<int>> solution(int n)
{
	vector<vector<int>>answer(n, vector<int>(n));
	SnailMat(answer, 1, direction::RIGHT,0,0);
	return answer;
}
int main()
{
	vector<vector<int>> a = solution(3);
	vector<vector<int>> b = solution(4);

	for (auto ca : a)
	{
		for (auto cca : ca)
			cout << cca << " ";
		cout << endl;
	}
	cout << endl;
	for (auto cb : b)
	{
		for (auto ccb : cb)
			cout << ccb << " ";
		cout << endl;
	}
}

//정답코드:
#include <vector>

using namespace std;

vector<vector<int>> solution(int n) {

	//❶ N*N 2차원 벡터를 선언하고 초깃값을 0으로 함
	vector<vector<int>> snail_array(n, vector<int>(n, 0));
	int num = 1;
	// 행과 열의 시작과 끝 인덱스를 설정
	int start_row = 0, end_row = n - 1;
	int start_col = 0, end_col = n - 1;

	//❷ 제일 외각부터 달팽이 수열 규칙대로 채움
	while (start_row <= end_row && start_col <= end_col) {
		// 가장 왼쪽 윗부분 에서 가장 아래 바로 직전 까지  채우기
		for (int i = start_col; i <= end_col; ++i) {
			snail_array[start_row][i] = num++;
		}
		++start_row;

		// 가장 왼쪽  아래부분 에서 가장 오른쪽 바로 직전 까지 채우기
		for (int i = start_row; i <= end_row; ++i) {
			snail_array[i][end_col] = num++;
		}
		--end_col;

		// 가장 오른쪽 아래부분 에서 가장 위 바로 직전 까지 채우기
		if (start_row <= end_row) {
			for (int i = end_col; i >= start_col; --i) {
				snail_array[end_row][i] = num++;
			}
			--end_row;
		}

		// 가장 윗부분 에서 가장 왼쪽 바로 직전 까지 채우기
		if (start_col <= end_col) {
			for (int i = end_row; i >= start_row; --i) {
				snail_array[i][start_col] = num++;
			}
			++start_col;
		}
	}

	return snail_array;
}



//아래 코드는 테스트 코드 입니다.
#include <iterator>
#include <iostream>

using namespace std;

void print(vector<vector<int>> vec)
{
	for (int i = 0; i < vec.size(); i++) {
		copy(vec[i].begin(), vec[i].end(), std::ostream_iterator<int>(cout, " "));
		cout << endl;
	}

}

int main()
{
	print(solution(3));
	/*
	출력값 :
	1 2 3
	8 9 4
	7 6 5
	*/

	print(solution(4));
	/*
	출력값:
	1 2 3 4
	12 13 14 5
	11 16 15 6
	10 9 8 7
	*/
	return 0;
}
// 내 코드와 다른 점:
// 나는 SnailMat함수의 매개변수로 행렬, num, 방향, 인덱스를 받아서 조건에 맞게
// 해당 인덱스에 num을 채워나가는 재귀함수를 구현하였다. 행렬의 끝에 다다르면 방향을 바꾸면서 다음 채울 인덱스를 조절해주었다.
// 반면 정답코드는 따로 함수를 만들지 않고 solution 함수에서 모든걸 해결하였다.
// 채워야할 행시작과 행끝, 열시작과 열끝을 선언하고 한줄 채우면 이 변수들을 조절하면서 행렬의 값을 채웠다.
// 
// 시간복잡도 :O(N^2)
// 