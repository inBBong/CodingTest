#include<iostream>
#include<vector>

using namespace std;

int solution(int n)
{
	vector<int>fibo;
	fibo.push_back(1);
	fibo.push_back(1);
	for (int i = 2; i < n; ++i)
	{
		fibo.push_back(fibo[i - 2] + fibo[i - 1]);
	}
	return fibo[n - 1];
}
int main()
{
	cout << solution(3) << endl;
	cout << solution(5) << endl;
}
//정답코드
#include <vector>
using namespace std; // using 지시문 추가

int solution(int n) {
	vector<int> fib = { 0, 1 }; // F(0) = 0, F(1) = 1
	for (int i = 2; i <= n; i++) {
		fib.push_back(fib[i - 1] + fib[i - 2]);
	}
	return fib[n] % 1234567;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution(3) << endl; //출력값 : 2
	cout << solution(5) << endl; //출력값 : 5

	return 0;
}
//내 코드와 다른 점:
// 내 코드와 똑같지만, 정답코드는 Fib(0)을 포함시켜서, 인덱스를 보다 깔끔하게 맞췄다.
// 
// 시간복잡도 :O(N)
// 