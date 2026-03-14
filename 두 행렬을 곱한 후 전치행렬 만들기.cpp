#include<iostream>
#include<vector>
using namespace std;
int mulMatElement(vector<vector<int>> matrix1, vector<vector<int>> matrix2,int n,int m)
{
	int result(0);
	int N = matrix2.size();
	for (int i = 0; i < N; ++i)
	{
		result += matrix1[n][i] * matrix2[i][m];
	}
	return result;
}
void transposeMat(vector<vector<int>>& mat)
{
	int n = mat.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			if (i == j)continue;
			int temp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = temp;
		}
	}
}
vector<vector<int>> solution(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
	vector<vector<int>> answer(matrix1[0].size(), vector<int>(matrix2.size()));
	int n = matrix1[0].size();
	int result(0);	

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			answer[i][j] = mulMatElement(matrix1, matrix2, i, j);
		}
	}
	transposeMat(answer);
	return answer;
}
int main()
{
	vector<vector<int>> a=solution({
					 {1, 2, 3},
					 {4, 5, 6},
					 {7, 8, 9},
		},
					{
					 {9, 8, 7},
					 {6, 5, 4},
					 {3, 2, 1},
					}
					);
	/*
	출력값 :
	30 84 138
	24 69 114
	18 54 90
	*/

	vector<vector<int>> b = solution({
					 {2, 4 ,6},
					 {1, 3, 5},
					 {7, 8, 9},
		},
					{
					 {9, 1, 2},
					 {4, 5, 6},
					 {7, 3, 8},
					}
					);
	/*
	출력값:
	76 56 158
	40 31 74
	76 60 134
	*/

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

vector<vector<int>> multiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
	//❶ 결과값을 저장할 벡터를  0으로 초기화
	vector<vector<int>> result(3, vector<int>(3, 0));

	//❷ 행렬 곱셈을 수행합니다.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	return result;
}

vector<vector<int>> transpose(vector<vector<int>> matrix) {
	//❸ 결과 행렬을 0으로 초기화합니다.
	vector<vector<int>> result(3, vector<int>(3, 0));

	//❹ 전치 행렬을 계산합니다.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[j][i] = matrix[i][j];
		}
	}

	return result;
}

vector<vector<int>> solution(vector<vector<int>> matrix1, vector<vector<int>>matrix2) {
	//❺ 주어진 두 행렬을 곱합니다.
	vector<vector<int>> multiplied = multiply(matrix1, matrix2);

	//❻ 곱셈 결과의 전치 행렬을 계산합니다.
	vector<vector<int>> transposed = transpose(multiplied);
	return transposed;
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
					 {1, 2, 3},
					 {4, 5, 6},
					 {7, 8, 9},
		},
					{
					 {9, 8, 7},
					 {6, 5, 4},
					 {3, 2, 1},
					}
					));
	/*
	출력값 :
	30 84 138
	24 69 114
	18 54 90
	*/

	print(solution({
					 {2, 4 ,6},
					 {1, 3, 5},
					 {7, 8, 9},
		},
					{
					 {9, 1, 2},
					 {4, 5, 6},
					 {7, 3, 8},
					}
					));
	/*
	출력값:
	76 56 158
	40 31 74
	76 60 134
	*/
	return 0;
}
// 내 코드와 다른 점:
// 우선 두 행렬을 곱한 뒤 전치 해주는 로직은 같다. 세부적으로는 조금 다르게 구현했는데,
// 나는 행렬곱 함수에 매개변수로 m과 n을 전달해서 결과 행렬의 각 값을 반환받았고,
// 정답코드에서는 3중 for문을 사용해서 결과 행렬의 값을 계산했다.
// 그리고 전치를 할때 나는 int형 변수 temp를 선언해서 행과 열을 바꿔주었고, 정답코드에서는
// 그냥 이차원배열을 순회하면서 행과 열을 바꾼 값을 새로운 배열에 할당해주고 그 배열을 반환해주었다.
// 
// 시간복잡도 :O(1) (배열의 크기가 3*3으로 고정되어 있기 때문)
//