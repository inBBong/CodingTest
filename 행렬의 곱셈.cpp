#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//2차원 배열 arr1과 arr2를 입력받아 arr1에 arr2를 행렬 곱한 결과를 반환하는 solution 함수를 완성하세요.
//제약조건
//1. 배열 arr1, arr2의 행과 열의 길이는 2 이상 100 이하입니다.
//2. 배열 arr1, arr2의 데이터는 -10 이상 20 이하인 자연수입니다.
//3. 행렬 곱 할 수 있는 배열만 주어집니다.
//내코드 (정답코드 보고 함)
vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2)
{
	vector<vector<int>> answer;

	answer.assign(arr1.size(), vector<int>(arr2[0].size(), 0)); //answer 공간 할당. arr1의 행, arr2의 열.(axb 행렬 * bxc 행렬 = axc 행렬 이기때문)

	//행렬곱 연산 시행
	for (int i = 0; i < arr1.size(); i++)
	{
		for (int j = 0; j < arr2[0].size(); j++)
		{
			for (int k = 0; k < arr2.size(); k++)
				answer[i][j] += arr1[i][k] * arr2[k][j];
		}
	}
	return answer;
}
int main()
{
	vector<vector<int>> a1 = { {1,4},{3,2},{4,1} };
	vector<vector<int>> a2 = { {3,3},{3,3}};
	vector<vector<int>> r = solution(a1, a2);
	for (int i = 0; i < r.size(); ++i)
	{
		for (int j = 0; j < r[0].size(); ++j)
			cout << r[i][j] <<" ";
		cout<<endl;
	}
		
}
//시간복잡도 : O(V^3)