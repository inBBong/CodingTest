#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool isValid(int x,int y, int n,int m)
{
	if (x >= -m / 2 && x <= m / 2 && y >= -n / 2 && y <= n / 2)
		return true;
	else
		return false;
}
vector<int>solution(vector<string> keyinput, vector<int> board)
{
	int x = 0, y = 0;
	int n = board[1];
	int m = board[0];
	for (auto key : keyinput)
	{
		int newx=0, newy=0;
		switch (key[0])
		{
		case 'l':
			 newx = x - 1;
			 newy = y;
			
			break;
		case 'r':
			newx = x + 1;
			newy = y;			
			break;
		case 'u':
			newx = x;
			newy = y+1;
			break;
		case 'd':
			newx = x;
			newy = y - 1;
			break;
		}
		if (isValid(newx, newy, n, m))
		{
			x = newx;
			y = newy;
		}
	}
	return { x,y };
}
int main()
{
	vector<int>a=solution({ "left", "right", "up", "right", "right" }, { 11, 11 }); //출력값 : 2 1 
	vector<int>b = solution({ "down", "down", "down", "down", "down" }, { 7, 9 }); //출력값 : 0 -4  
	cout << a[0] << " " << a[1] << " " << b[0] << " " << b[1] << " ";
}
//정답코드:
#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<string> keyinput, vector<int> board)
{
	//❶ 현재 위치를 나타 내는 크기가 2이고 값이 모두 0인 벡터 선언
	vector<int> v(2, 0);

	//❷ 키 입력순으로 캐릭터 이동
	for (string s : keyinput)
	{
		if (s == "up" && v[1] < +board[1] / 2) v[1]++;
		else if (s == "down" && v[1] > -board[1] / 2) v[1]--;
		else if (s == "left" && v[0] > -board[0] / 2) v[0]--;
		else if (s == "right" && v[0] < +board[0] / 2) v[0]++;
	}

	return v;
}


//아래 코드는 테스트 코드 입니다.
#include <iterator>
#include <iostream>

using namespace std;

void print(vector<int> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{
	print(solution({ "left", "right", "up", "right", "right" }, { 11, 11 })); //출력값 : 2 1 
	print(solution({ "down", "down", "down", "down", "down" }, { 7, 9 })); //출력값 : 0 -4  

	return 0;
}
//내 코드와 다른점:
// 나는 isValid 함수를 만들어서 새로운 좌표가 유효한 좌표인지를 검사했다.
// 반면 정답코드에서는 key가 right일때는 사실 x가 오른쪽 끝보다 작은지만을 검사하면 된다는 점을 이용해서
// 조금더 효율적으로 코드를 구현했다.
// 
// 시간복잡도 : O(N)
//