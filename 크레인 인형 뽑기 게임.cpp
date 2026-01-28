#include<iostream>
#include<stack>
#include<vector>
using namespace std;
int solution(vector<vector<int>> board, vector<int>moves)
{
	stack<int> basket;
	int answer(0);
	for (int i = 0; i < moves.size(); ++i)
	{
		for(int j=0;j<board.size();++j)
		{
			if (board[j][moves[i]-1] != 0)
			{
				if (!basket.empty()&&basket.top() == board[j][moves[i] - 1])
				{
					basket.pop();
					answer += 2;
				}
				else
				{
					basket.push(board[j][moves[i]-1]);
				}
				board[j][moves[i] - 1] = 0;
				break;
			}
		}
	}
	return answer;
}
int main()
{
	vector<vector<int>> board=
	{
		{0,0,0,0,0},
		{0,0,1,0,3},
		{0,2,5,0,1},
		{4,2,4,4,2},
		{3,5,1,3,1}
	};
	vector<int>moves = { 1,5,3,5,1,2,1,4 };
	cout << solution(board, moves);
}
//정답코드
//#include <stack>
//#include <vector>
//
//using namespace std;
//
//int solution(vector<vector<int>> board, vector<int> moves) {
//	//❶ 보드판의 열의 크기만큼 스택을 생성 
//	stack<int> lanes[board[0].size()];
//	//❷ 보드의 가장 밑의 행부터 위로 올라가먼서 순회 
//	for (int i = board.size() - 1; i >= 0; --i) {
//		for (int j = 0; j < board[0].size(); ++j) {
//			//❸ 블럭이 있는 경우 해당 열에 해당되는 스택에 푸시 
//			if (board[i][j]) {
//				lanes[j].push(board[i][j]);
//			}
//		}
//	}
//
//	// 보드판에서 꺼낸 인형을 담을 bucket과 사라진 인형의 개수를 저장할 answer 선언
//	stack<int> bucket;
//	int answer = 0;
//
//	for (int m : moves) {
//		//❹ 해당 lane에 블럭이 있으면
//		if (lanes[m - 1].size()) {
//			int doll = lanes[m - 1].top();
//			lanes[m - 1].pop();
//			//❺ 버킷에 블럭이 있고, 가장 최근에 들어간 블럭과 현재 블럭이 같은지 확인
//			if (bucket.size() && bucket.top() == doll) {
//				bucket.pop();
//				answer += 2;
//			}
//			else {
//				bucket.push(doll);
//			}
//		}
//	}
//
//	return answer;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//
//int main()
//{
//
//	cout << solution({ {0, 0, 0, 0, 0}, {0, 0, 1, 0, 3}, {0, 2, 5, 0, 1}, {4, 2, 4, 4, 2}, {3, 5, 1, 3, 1} }, { 1, 5, 3, 5, 1, 2, 1, 4 }) << endl; // 4
//	return 0;
//}
//내 코드와 다른점: 나는 인형을 담는 basket만 스택으로 처리하고, 인형을 뽑는 작업은 배열을 그대로 사용함
//정답코드는 배열에 담긴 모든 인형을 각 열에 대한 lane스택으로 만듦 : 만들땐 아래 행부터 push, lane에 인형이 없는 경우 예외처리
//시간 복잡도 : O(N^2+M) N:보드판 가로길이 M :moves 길이