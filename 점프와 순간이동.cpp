#include<iostream>
#include<vector>
using namespace std;

int solution(int N)
{
	int jump = 1;
	while (N != 1)
	{
		if (N % 2 == 0)
			N /= 2;
		else
		{
			N--;
			jump++;
		}
	}
	return jump;
}
int main()
{
	cout << solution(5) << endl; //출력값 : 2
	cout << solution(6) << endl; //출력값 : 2 
	cout << solution(5000) << endl; //출력값 : 5
}
//정답코드:
#include <bitset>

using namespace std;

int solution(int N) {
	return bitset<32>(N).count(); // 2진수로 변환한 N의 1의 개수를 반환
}




//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution(5) << endl; //출력값 : 2
	cout << solution(6) << endl; //출력값 : 2 
	cout << solution(5000) << endl; //출력값 : 5

	return 0;
}
// 내 코드와 다른 점:
// 역시 이번에도 정답코드는 섹시하게 한줄로 마무리했다.
// 나는 종료지점에서부터 거꾸로 생각하면서, N이 짝수면 순간이동을 했을것이므로 2로 나누고, N이 홀수면 점프를 
// 했을것이므로 N에서 1을 빼고 jump 값을 1 더해주었다. 반면 정답코드에서는 이를
// 2진수변환에서 1의 개수로 생각해버렸다. 정말 야무진 아이디어인것 같다.
// 
// 시간복잡도 :O(logN)
// 
//