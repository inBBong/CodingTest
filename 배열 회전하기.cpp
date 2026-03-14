#include<iostream>
#include<vector>
using namespace std;
// 반시계방향 회전 : arr[i][j] -> arr[N-1-j][i]
// 시계방향 회전 : arr[i][j] -> arr[j][N-1-i]
//
void rotateVec(vector<vector<int>>& arr)
{
	int N = arr.size();
	vector < vector<int>>answer(N, vector<int>(N));
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr[0].size(); ++j)
		{
			answer[j][N - 1 - i] = arr[i][j];
		}
	}
	arr = answer;
}
vector<vector<int>>solution(vector<vector<int>> arr, int n)
{
	for (int i = 0; i < n; ++i)
	{
		rotateVec(arr);
	}
	return arr;
}

int main()
{
	vector<vector<int>>a=solution({
				   {1, 2, 3, 4},
				   {5, 6, 7, 8},
				   {9, 10, 11, 12},
				   {13, 14, 15, 16}
		}, 1);
	/*
	  출력값
	  13 9 5 1
	  14 10 6 2
	  15 11 7 3
	  16 12 8 4
	*/

	vector<vector<int>>b = solution({
					 {1, 2, 3, 4},
					 {5, 6, 7, 8},
					 {9, 10, 11, 12},
					 {13, 14, 15, 16}
		}, 2);

	for (auto ca : a)
	{
		for (auto cca : ca)
			cout << cca << " ";
		cout << endl;
	}
	for (auto cb : b)
	{
		for (auto ccb : cb)
			cout << ccb << " ";
		cout << endl;
	}

}
//정답코드 :
#include <vector>

using namespace std;

// ❶ 2차원 벡터를 인자로 받고 90도 회전
vector<vector<int>> rotate_90(const vector<vector<int>>& arr) {
	int n = arr.size();
	// ❷ 인자로 받은 벡터와 크기가 같은 2차원 백터 생성(초깃값은 0)
	vector<vector<int>> rotated_arr(n, vector<int>(n, 0));
	// ❸ 2차원 벡터를 90도로 회전
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			rotated_arr[j][n - i - 1] = arr[i][j];
		}
	}
	return rotated_arr;
}

vector<vector<int>> solution(vector<vector<int>> arr, int n) {
	vector<vector<int>> rotated_arr = arr;

	// ❹ 2차원 벡터를 90도로 n번 회전
	for (int i = 0; i < n; ++i) {
		rotated_arr = rotate_90(rotated_arr);
	}
	return rotated_arr;
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
	print(solution({
					 {1, 2, 3, 4},
					 {5, 6, 7, 8},
					 {9, 10, 11, 12},
					 {13, 14, 15, 16}
		}, 1));
	/*
	  출력값
	  13 9 5 1
	  14 10 6 2
	  15 11 7 3
	  16 12 8 4
	*/

	print(solution({
					 {1, 2, 3, 4},
					 {5, 6, 7, 8},
					 {9, 10, 11, 12},
					 {13, 14, 15, 16}
		}, 3));
	/*
	  출력값
	  4 8 12 16
	  3 7 11 15
	  2 6 10 14
	  1 5 9 13
	*/

	return 0;
}
//내 코드와 다른 점 :
// 배열을 돌리는 함수의 반환값이 다른 것 말고는 완전히 동일함.
// 시간복잡도 : O(N^2)
//