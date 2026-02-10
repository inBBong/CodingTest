#include<iostream>

using namespace std;

int solution(int n, int a, int b)
{
	int cnt(1);
	while(1)
	{
		if (abs(a - b) == 1 && (a - 1) / 2 == (b - 1) / 2)
			return cnt;
		else
		{
			cnt++;
			a = (a - 1) / 2 + 1;
			b = (b - 1) / 2 + 1;
		}
	}

}
int main()
{
	cout << solution(8, 4, 7);
}

//정답코드
//int solution(int n, int a, int b)
//{
//	int answer = 0;
//
//	do {
//		a = (a + 1) / 2;
//		b = (b + 1) / 2;
//		++answer;
//	} while (a != b);
//
//	return answer;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//	cout << solution(8, 4, 7) << endl; //출력값 : 3
//	return 0;
//}
// 내 코드와 다른 점:
//		걍 똑같음. 라운드마다 인원수가 logN으로 줄어든다는 것만 알면 될듯.
// 시간복잡도: O(logN)
//