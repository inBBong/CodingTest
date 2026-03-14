#include<iostream>
#include<vector>
using namespace std;
int greenCnt(int whiteX, int whiteY)
{
	return 2 * (whiteX + whiteY) + 4;
}
vector<int> solution(int green, int white)
{
	for (int i = 1; i < white+1; ++i)
	{		
		int whiteX = white / i;
		int whiteY = i;
		if (whiteX * whiteY == white)
		{
			if (greenCnt(whiteX, whiteY) == green)
			{
				return{ whiteX + 2,whiteY + 2 };
			}
		}
	}
}
int main()
{
	vector<int> a=solution(10, 2); //출력값 : 4 3
	vector<int> b=solution(8, 1); //출력값 : 3 3
	vector<int> c=solution(24, 24); //출력값 : 8 6
	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
	cout << endl;
	for (auto cc : c)
		cout << cc << " ";
	cout << endl;
}
//정답코드:
#include <vector>
#include <cmath>

using namespace std;

vector<int> solution(int green, int white) {
	// ❶ 격자의 총 개수 (파란색 격자 + 흰색 격자)
	int total_size = green + white;
	// ❷ 세로 길이의 범위는 3부터 (파란색 격자 + 흰색 격자)의 제곱근
	for (int vertical = 3; vertical <= sqrt(total_size); ++vertical) {
		// ❸ 사각형 구성이 되는지 확인
		if (total_size % vertical == 0) {
			int horizontal = total_size / vertical; // ❹ 사각형의 가로 길이
			// ❺ 카펫 형태로 만들 수 있는지 확인
			if (green == (horizontal + vertical - 2) * 2) {
				return { horizontal, vertical }; // ❻ {가로 길이, 세로 길이}
			}
		}
	}
	return {}; // ❼ 만약 답을 찾지 못했다면 빈 벡터를 반환
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
	print(solution(10, 2)); //출력값 : 4 3
	print(solution(8, 1)); //출력값 : 3 3
	print(solution(24, 24)); //출력값 : 8 6

	return 0;
}
// 내 코드와 다른점:
// 이번 문제는 정답코드와 내 코드의 로직이 다르다.
// 나는 흰색 타일을 소인수분해 해서, 흰색의 가로와 세로 길이를 정하고, 흰색 타일과 초록색 타일의 관계를 이용해서
// ( 2*(흰색의 가로+ 흰색의 세로) + 4  =초록의 개수) 가 되는 흰색의 가로와 세로를 구해서 구현하였다.
// 반면 정답코드에서는 전체타일 수 (흰색+초록색)을 구하고 세로의 길이(최소 3)을 하나씩 늘리면서
// 전체 타일 수에서 세로로 나눠서 가로를 구하고, 전체 타일의 가로와 세로 길이를 이용해 초록타일의 수와 비교하여
// 구현하였다.
// 
// 시간복잡도: O(루트N)
//