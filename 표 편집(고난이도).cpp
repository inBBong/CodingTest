#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;
int IDXDown(vector<int>& v, int cmd, int idx)
{
	//cmd -= 48;
	for (int j = 0; j < cmd; ++j)//v가 벡터이므로 값이 -1이면 한번더 Down.
	{
		idx++;
		while (v[idx] == -1)
			idx++;
	}
	return idx;
}
int IDXUp(vector<int>& v, int cmd, int idx)
{
	for (int j = 0; j < cmd; ++j)//v가 벡터이므로 값이 -1이면 한번더 Down.
	{
		idx--;
		while (v[idx] == -1)
			idx--;
	}
	return idx;
}
string solution(int n, int k, vector<string>cmd)
{
	vector<int> v;
	stack<int> deleted;
	stack<int> chart;
	int selectedIndx = k;
	string answer;
	for (int i = 0; i < n; ++i)
	{
		v.push_back(i);
	}
	for (int i = 0; i < cmd.size(); ++i)
	{
		switch (cmd[i][0])
		{
		case'D':
			//selectedIndx += cmd[i][2];			
			selectedIndx = IDXDown(v, stoi(cmd[i].substr(2)), selectedIndx);//cmd[i][2]는 char 형이므로 -48을 해줘야함
			break;
		case'U':
			selectedIndx = IDXUp(v, stoi(cmd[i].substr(2)), selectedIndx);
			break;
		case'C':
			deleted.push(v[selectedIndx]);
			v[selectedIndx] = -1;
			if (selectedIndx == n - 1)//마지막인덱스면
				selectedIndx=IDXUp(v,1,selectedIndx);
			else
				selectedIndx = IDXDown(v,1,selectedIndx);
			break;
		case'Z':
			v[deleted.top()] = deleted.top();
			deleted.pop();
			break;
		}
	}
	for (auto cv : v)
	{
		if (cv == -1)
			answer += "X";
		else
			answer += "O";
	}
	return answer;
}
int main()
{
	vector<string>cmd = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z" };
	vector<string>cmd2 = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z", "U 1", "C"};
	cout << solution(8, 2, cmd)<<endl;
	cout << solution(8, 2, cmd2)<<endl;
}
//정답코드
//#include <string>
//#include <vector>
//#include <stack>
//
//using namespace std;
//
//string solution(int n, int k, vector<string> cmd) {
//
//	//❶삭제 된 행의 인덱스를 저장 
//	stack<int> deleted;
//	//❷ 각 행의 위아래에 있는 행의 인덱스를 저장 
//	vector<int> up;
//	vector<int> down;
//
//	for (int i = 0; i < n + 2; i++) {
//		up.push_back(i - 1);
//		down.push_back(i + 1);
//	}
//	//❸ 임시공간을 고려한 현재위치 
//	k++;
//
//	//❹ 주어진 명령어를 순회  
//	for (int i = 0; i < cmd.size(); i++) {
//		//❺ 현재 위치를 삭제하고 그 다음 위치로 이동
//		if (cmd[i][0] == 'C') {
//			deleted.push(k);
//			down[up[k]] = down[k];
//			up[down[k]] = up[k];
//
//			if (down[k] == n + 1) k = up[k];
//			else k = down[k];
//		}
//
//		//❻ 가장 최근에 삭제한 행을 복원
//		else if (cmd[i][0] == 'Z') {
//			int r = deleted.top();
//			down[up[r]] = r;
//			up[down[r]] = r;
//			deleted.pop();
//		}
//
//		//❼  현재 행을 주어진 값 만큼 위혹은 아래로 이동
//		else {
//			int sz = stoi(cmd[i].substr(2));
//
//			if (cmd[i][0] == 'U') {
//				for (int j = 0; j < sz; j++) {
//					k = up[k];
//				}
//			}
//
//			else if (cmd[i][0] == 'D') {
//				for (int j = 0; j < sz; j++) {
//					k = down[k];
//				}
//			}
//		}
//
//	}
//
//	string answer;
//
//	//❽ 삭제된 행의 위치에 “X”, 그렇지 않은 행의 위치에 “X” 로 표시한 문자열 반환
//	answer.append(n, 'O');
//	while (!deleted.empty()) {
//		answer[deleted.top() - 1] = 'X';
//		deleted.pop();
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
//	cout << solution(8, 2, { "D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z" }) << endl;              //OOOOXOOO
//	cout << solution(8, 2, { "D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z", "U 1", "C" }) << endl;  //OOXOXOOO
//	return 0;
//}
//내 코드와 다른 점: 나는 인덱스 = 값인 벡터 v와 스택 deleted를 사용해서, 행 삭제시 벡터 v 의 값에 -1을 넣어 구분하였다.
// 복구할때는 -1 이저장되어있는 v[deleted.top()]에 deleted.top을 넣어 복구했다.
// up/down시 v가 -1을 만나면 한번더 up/down 해주는 식으로 하였음.
// 정답코드는 인덱스만으로 구현하였는데 각 행 기준 up 행, down 행을 저장한 up, down 벡터를 사용하였다. k행이 삭제되면
// down[up[k]]=down[k], up[down[k]]=up[k] 이런식으로 각 행의 상하 관계를 적절히 조치하였다. (마치 연결리스트 같이)
// 복구 코드는 나처럼 stack을 사용 함.
// 의문점 : 책에서는 배열을 사용하면 배열의 삭제, 삽입이 일어나므로 연산비용이 늘어난다고 했는데, 난 행 삭제시 배열의 해당메모리를 삭제하고 
//뒤 인덱스를 당기는 식으로 한게 아닌, 그냥 값에 -1을 넣어줬음. 복구때도 스택의 탑을 이용해서 그자리에 값을 다시 넣어주기만 함.
// 그럼 연산비용이 안늘어나는거 아닌가?

//피드백 : 내 코드는 데이터의 양이 많아지고 삭제가 많이 일어나면, 행 이동 시 -1이 아닌 데이터가 나올때까지
// 벡터를 탐색해야하므로 탐색 비용이 많아질 수 있음
//시간복잡도 : O(N)
