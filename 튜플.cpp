#include<iostream>
#include<vector>
#include<string>
using namespace std;
vector<int> counts(100001, 0);
vector<int> solution(string s)
{
	vector<int> numbers;
	string num;
	vector<int>answer;
	for (auto c : s)
	{
		if (isdigit(c))
		{
			num += c;
		}
		else
		{
			if (num.size())
			{
				numbers.push_back(stoi(num));
				num.clear();
			}
		}
	}
	for (auto n : numbers)
	{
		counts[n]++;
	}
	auto iter =max_element(counts.begin(),counts.end());
	int max = *iter;
	for (int i = 0; i < counts.size(); ++i)
	{
		if (counts[i] == max)
		{
			answer.push_back(i);
			max--;
			i = 0;
			if (!max)break;
		}
	}
	return answer;
}
void init()
{
	for (int i = 0; i < counts.size(); ++i)
		counts[i] = 0;
}
int main()
{
	vector<int>a=solution("{{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}"); // 출력값 : 2 1 3 4
	init();
	vector<int>b = solution("{{1, 2, 3}, {2, 1}, {1, 2, 4, 3}, {2}}"); // 출력값 : 2 1 3 4
	init();
	vector<int>c = solution("{{20, 111}, {111}}"); // 출력값 : 111 20
	init();
	vector<int>d = solution("{{123}}"); // 출력값 : 123
	init();
	vector<int>e = solution("{{4, 2, 3}, {3}, {2, 3, 4, 1}, {2, 3}}"); // 출력값 : 3 2 4 1 

	for (auto ca : a)
		cout << ca << " ";
	cout << endl;
	for (auto cb : b)
		cout << cb << " ";
	cout << endl;
	for (auto cc : c)
		cout << cc << " ";
	cout << endl;
	for (auto cd : d)
		cout << cd << " ";
	cout << endl;
	for (auto ce : e)
		cout << ce << " ";
	cout << endl;
}
//정답 코드 :
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int counts[100001] = {};

void updateCounts(const string& s) {
	string numStr;
	//❶ 인자로 받은 문자열을 순회
	for (char ch : s) {
		//❷ 현재 문자가 숫자인 경우
		if (isdigit(ch)) {
			numStr += ch;
			//❸ 현재 문자가 숫자가 아닌 경우
		}
		else {
			if (!numStr.empty()) {
				//❹ 계수정렬을 하기 위해 각 숫자의 개수를 저장 
				counts[stoi(numStr)]++;
				numStr.clear();
			}
		}
	}
}

vector<int> solution(string s) {
	vector<int> answer;
	//❺ 집합이 담긴 문자열의 각 원소를 계수정렬
	updateCounts(s);

	vector<pair<int, int>> freqPairs;
	for (int i = 1; i <= 100000; i++) {
		//❻ 집합에 있는 원소인 경우 (개수, 값) 형식으로 푸시
		if (counts[i] > 0) {
			freqPairs.push_back({ counts[i], i });
		}
	}

	//❼ 각 원소의 개수를 기준으로 내림차순 정렬
	sort(freqPairs.rbegin(), freqPairs.rend());

	//➑ 원소의 개수로 내림차순 정렬된 벡터를 순회하며 원소를 푸시
	for (const auto& p : freqPairs) {
		answer.push_back(p.second);
	}

	return answer;
}


//아래 코드는 테스트 코드 입니다.
#include <iterator>
#include <iostream>

using namespace std;

void init()
{
	for (int i = 0; i <= 100000; i++)
		counts[i] = 0;
}

void print(vector<int> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}


int main()
{
	print(solution("{{2}, {2, 1}, {2, 1, 3}, {2, 1, 3, 4}}")); // 출력값 : 2 1 3 4
	init();
	print(solution("{{1, 2, 3}, {2, 1}, {1, 2, 4, 3}, {2}}")); // 출력값 : 2 1 3 4
	init();
	print(solution("{{20, 111}, {111}}")); // 출력값 : 111 20
	init();
	print(solution("{{123}}")); // 출력값 : 123
	init();
	print(solution("{{4, 2, 3}, {3}, {2, 3, 4, 1}, {2, 3}}")); // 출력값 : 3 2 4 1 

	return 0;
}
// 내 코드와 다른 점:
// 계수정렬을 사용해서 인덱스의 숫자의 개수를 값으로 갖는 counts를 쓰는 로직은 같다.
// 하지만 정답코드에서는 (개수, 값) 형식의 vector<pair<int, int>> freqPairs;을 만들어서,
// sort를 한 후에 freqpairs.second를 answer에 push_back 했다. 반면에 나는 counts를 순회하면서, counts의 max 값을 이용해서
// 가장 많이 나온 원소를 먼저 추가함으로써 정렬했다.
// 그리고 나는 numbers라는 벡터를 만들어서 문자열에 등장하는 모든 숫자를 담았다. 하지만 정답코드에서 처럼
// 문자열 순회를 하면서 숫자를 발견했을때 counts를 늘려주면 해결할 수 있었다.
// 
// 시간복잡도 : O(N+ MlogM)
//