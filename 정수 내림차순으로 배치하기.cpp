#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

long long solution(long long n)
{
	string answer = to_string(n);
	long long ret(0);
	sort(answer.rbegin(), answer.rend());
	int mul(1);
	for (int i = answer.size() - 1; i >= 0; --i)
	{
		ret += (answer[i]-'0') * mul;
		mul *= 10;
	}

	return ret;
}
int main()
{
	cout << solution(118372) << endl; // 출력값 : 873211
}
//정답코드
#include <string>
#include <algorithm>

using namespace std;

long long solution(long long n) {
	//❶ 숫자를 문자열로 변환
	string str = to_string(n);

	//❷ 역순으로 정렬
	sort(str.rbegin(), str.rend());
	return stoll(str);
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution(118372) << endl; // 출력값 : 873211

	return 0;
}
// 내 코드와 다른 점:
// 이번에도 정답코드는 간결하게 끝내버렸다. to_string까진 같은데
// stoll라는 함수가 있었구나.. 나는 자릿수마다 10을 곱해주면서 return 값에 더해서 구했다.
// 
// 시간복잡도 :O(logNlog(logN))
//