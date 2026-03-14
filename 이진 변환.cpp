#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;
string makeBinary(int n)
{
	stack<int> s;
	string newBinary;
	while (n / 2 != 0)
	{
		s.push(n % 2);
		n /= 2;
	}
	s.push(n);
	while (!s.empty())
	{
		if (s.top() == 1)
			newBinary += "1";
		else
			newBinary += "0";
		s.pop();
	}
	return newBinary;
}
vector<int> solution(string s)
{
	vector<int>answer;
	int tryCnt(0);
	int ZeroCnt(0);
	while (s!="1")
	{
		int cntOne(0);
		for (auto cs : s)
		{
			if (cs == '1')
				cntOne++;
			else
				ZeroCnt++;
		}
		s=makeBinary(cntOne);
		tryCnt++;
	}
	answer.push_back(tryCnt);
	answer.push_back(ZeroCnt);
	return answer;
}
int main()
{
	vector<int> a=solution("110010101001"); //출력값 : 3 8
	vector<int> b=solution("01110"); //출력값 : 3 3
	vector<int> c=solution("1111111"); //출력값 : 4 1
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
//정답코드 :
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

vector<int> solution(string s) {
	int transforms = 0;
	int removedZeros = 0;
	//❶  s가 “1”이 될때까지 계속 반복
	while (s != "1") {
		transforms++;

		//❷ '0' 개수를 세어 removedZeros에 누적
		removedZeros += count(s.begin(), s.end(), '0');

		//❸ '1' 개수를 세고, 이를 이진수로 변환
		int onesCount = count(s.begin(), s.end(), '1');
		s = bitset<32>(onesCount).to_string();
		s = s.substr(s.find('1'));
	}

	return { transforms, removedZeros };
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
	print(solution("110010101001")); //출력값 : 3 8
	print(solution("01110")); //출력값 : 3 3
	print(solution("1111111")); //출력값 : 4 1

	return 0;
}
// 내 코드와 다른점 :
// 이 책에서 10진수를 2진수로 변환하는 문제가 스택 챕터에서 나왔었다. 그 기억으로 나는
// 스택을 이용해서 2진수 변환 문자열을 반환하는 함수를 정의했는데, 정답코드에서는
// s = bitset<32>(onesCount).to_string(); 한줄로 끝내버렸다. 아주 섹시한 코드인것 같다.
// 위 코드는 10진수 int 형 변수 onesCount를 32자리로 표현한다.
// 그리고 s = s.substr(s.find('1'));를 통해 처음 1이 나올때까지 앞에 있는 0000...을 모두 자른다.
// 그 외에 로직은 나와 같다. 정답코드에서는 섹시하게 stl의 count를 사용했다.
// 
// 시간복잡도 :O(NlogN)
//