#include<iostream>
#include<vector>

using namespace std;
vector<vector<int>>board;
pair<int, int>findEmpthy()
{
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[0].size(); ++j)
        {
            if (board[i][j] == 0)
                return { i,j };
        }
    }
    return { -1,-1 };
}
bool isValid(int row, int col,int num)
{
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }
    int StartRow = row - row % 3, StartCol = col-col%3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[StartRow + i][StartCol + j] == num)
            {
                return false;
            }
        }
    }
    return true;
}
void backtrack()
{
    pair<int, int> node = findEmpthy();
    if (node.first == -1)
        return;

	for (int num = 1; num <= board.size(); ++num)
	{
		if (isValid(node.first, node.second, num))
		{
			board[node.first][node.second] = num;
			backtrack();
			if (findEmpthy().first == -1)
			{
				return;
			}
			board[node.first][node.second] = 0;
		}

	}
}
vector<vector<int>> solution(vector<vector<int>> input_board)
{
    board = input_board;
    backtrack();
    return board;
}
int main()
{
    vector<vector<int>> a=solution({
                    {5, 3, 0, 0, 7, 0, 0, 0, 0},
                    {6, 0, 0, 1, 9, 5, 0, 0, 0},
                    {0, 9, 8, 0, 0, 0, 0, 6, 0},
                    {8, 0, 0, 0, 6, 0, 0, 0, 3},
                    {4, 0, 0, 8, 0, 3, 0, 0, 1},
                    {7, 0, 0, 0, 2, 0, 0, 0, 6},
                    {0, 6, 0, 0, 0, 0, 2, 8, 0},
                    {0, 0, 0, 4, 1, 9, 0, 0, 5},
                    {0, 0, 0, 0, 8, 0, 0, 7, 9}
        });

    /*
      출력값
      5 3 4 6 7 8 9 1 2
      6 7 2 1 9 5 3 4 8
      1 9 8 3 4 2 5 6 7
      8 5 9 7 6 1 4 2 3
      4 2 6 8 5 3 7 9 1
      7 1 3 9 2 4 8 5 6
      9 6 1 5 3 7 2 8 4
      2 8 7 4 1 9 6 3 5
      3 4 5 2 8 6 1 7 9
    */
    vector<vector<int>> b = solution({
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}
        });
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
    cout << endl;
    /*
      출력값
          1 2 3 4 5 6 7 8 9
          4 5 6 7 8 9 1 2 3
          7 8 9 1 2 3 4 5 6
          2 1 4 3 6 5 8 9 7
          3 6 5 8 9 7 2 1 4
          8 9 7 2 1 4 3 6 5
          5 3 1 6 4 2 9 7 8
          6 4 2 9 7 8 5 3 1
          9 7 8 5 3 1 6 4 2
    */
}
// 역시 백트래킹은 어렵구나.. 이번 문제도 계속 고민을 해봤지만 어떻게 구현해야할 지 감이
// 오지 않아 정답코드를 보고 구현하였다. 재귀함수 호출 타이밍을 어떻게 해야 할 지 생각 하는 것이
// 항상 가장 어려운 것 같다.
// 시간 복잡도 : O(9^N) 하지만 유망 함수에 의해 훨씬 적음.
//