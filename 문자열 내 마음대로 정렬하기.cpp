#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<string> solution(vector<string> strings, int n)
{
	sort(strings.begin(), strings.end());
	vector<string>answer;
	for (int i = 0; i < 26; ++i)
	{
		for (auto st : strings)
			if ('a' + i == st[n])
				answer.push_back(st);
	}
	return answer;
}
int main()
{
	vector<string>a = solution({ "sun", "bed", "car" }, 1); //출력값 : car bed sun
	vector<string>b = solution({ "abce", "abcd", "cdx" }, 2);  // 출력값 : abcd abce cdx
	
	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";


}
// 정답코드:
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int idx;

//❶ 비교 함수
bool compare(string a, string b) {
	return a[idx] == b[idx] ? a < b : a[idx] < b[idx];
}

vector<string> solution(vector<string> strings, int n) {
	idx = n;

	//❷ 각 문자열의 idx번째 문자를 기준으로 정렬 
	sort(strings.begin(), strings.end(), compare);
	return strings;
}


//아래 코드는 테스트 코드 입니다.
#include <iostream>
#include <iterator>

using namespace std;

void print(vector<string> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<string>(cout, " "));
	cout << endl;
}

int main()
{
	print(solution({ "sun", "bed", "car" }, 1)); //출력값 : car bed sun
	print(solution({ "abce", "abcd", "cdx" }, 2));  // 출력값 : abcd abce cdx

	return 0;
}
// 내 코드와 다른 점 :
// 정답코드를 보고 놀라지 않을 수 없었다. 이렇게 sexy한 코드일 수가.
// 나는 a부터 z까지 순회하면서 정렬된 strings의 n번째 인덱스가 같으면 answer에 추가했다.
// 하지만 정답코드에서는 compare함수 하나로 간결하게 끝내버렸다. compare조차 삼항연산자로 
// 한줄만에 끝내버렸다.
// 시간복잡도: O(NSlogN)
//