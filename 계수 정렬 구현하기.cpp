#include<iostream>
#include<vector>
#include<string>
using namespace std;

string solution(string s)
{
	vector<int> a(26, 0);
	string answer;
	for (auto c : s)
	{
		a[c - 'a']++;
	}
	for (int i=0;i<a.size();++i)
	{
		for(int j=0;j<a[i];++j)
			answer += i + 'a';
	}
	return answer;
}
int main()
{
	cout << solution("hello") << endl; // 출력값 : ehllo
	cout << solution("algorithm") << endl; // 출력값 : aghilmort

}
//정답코드
#include <string>
#include <vector>

using namespace std;

string solution(string s) {
	//❶ 알파벳 개수(26개)만큼 빈도수 배열 생성
	vector<int> counts(26, 0);

	//❷ 문자열의 각 문자에 대한 빈도수를 빈도수 배열에 저장
	for (char c : s) {
		counts[c - 'a']++;
	}

	//❸ 빈도수 배열을 순회하면서 정렬된 문자열을 생성
	string sorted_str = "";
	for (int i = 0; i < 26; i++) {
		sorted_str += string(counts[i], i + 'a');
	}

	return sorted_str;
}

//아래 코드는 테스트 코드 입니다.
#include <iostream>

using namespace std;

int main()
{
	cout << solution("hello") << endl; // 출력값 : ehllo
	cout << solution("algorithm") << endl; // 출력값 : aghilmort

	return 0;
}
//내 코드와 다른점:
// 이번 문제는 몸풀기라 어렵진 않았다. 정답코드와 로직도 똑같다.
// 하나 다른점은 answer에 알파벳을 추가할때 나는 문자단위로 a[i]번 추가했고
// 정답코드에서는 string을 하나 선언해서 추가해주었다.
// 시간복잡도:O(N)
//