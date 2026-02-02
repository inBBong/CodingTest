#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;
// 단 한명의 선수만 완주실패. 참가자 배열 participant와 완주자 배열 complettion 배열이 주어졌을때 완주하지 못한
// 선수의 이름을 반환하는 solution 함수를 만드세요.
long long Uhash(string s)
{
	int m = 100000007;
	long long hash_value(0);
	int p = 31;
	for (char c:s)
	{		
		hash_value = (hash_value*p + c) % m;
	}
	return hash_value;
}
string solution(vector<string> participant, vector<string>completion)
{
	unordered_set<long long>hashvalue;
	for (auto cc : completion)
		hashvalue.insert(Uhash(cc));
	for (auto cp : participant)
	{
		if (hashvalue.find(Uhash(cp)) != hashvalue.end())
			continue;
		else
			return cp;
	}
	return "0";
}
int main()
{
	vector<string> p = { "leo", "kiki", "eden" };
	vector<string> c = { "eden","kiki" };
	vector<string> p2 = { "mislav", "stanko", "mislav","ana"};
	vector<string> c2 = { "stanko", "ana","mislav" };
	cout << solution(p2, c2);
}
//정답코드
//#include <string>
//#include <vector>
//#include <unordered_map>
//
//using namespace std;
//
//string solution(vector<string> participant, vector<string> completion) {
//	//❶ participant를 나타낼 해시테이블 
//	unordered_map<string, int> ph;
//
//	//❷ 각 참가자들을 해시 테이블에 추가( 키 : 이름, 값 : 해당 이름의 명 수)
//	for (int i = 0; i < participant.size(); i++)
//		ph[participant[i]]++;
//
//
//	//❸ 참가자 정보가 저장된 해시 테이블에서, 완주한 선수들을 제외
//	for (int i = 0; i < completion.size(); i++)
//	{
//		ph[completion[i]]--;
//		//❹ 해시테이블에서 특정 이름의 인원이 0명이면, 해시 테이블에서 삭제
//		if (ph[completion[i]] == 0)
//			ph.erase(ph.find(completion[i]));
//	}
//	//❺ 마지막 남은 한 선수의 이름을 반환 
//	return ph.begin()->first;
//}
//
//
//
////아래 코드는 테스트 코드 입니다.
//
//#include <iostream>
//
//int main()
//{
//	cout << solution({ "leo", "kiki", "eden" }, { "eden", "kiki" }) << endl; // "leo"
//	cout << solution({ "marina", "josipa", "nikola", "vinko", "filipa" }, { "josipa", "filipa", "marina", "nikola" }) << endl; // "vinko"
//	cout << solution({ "mislav", "stanko", "mislav", "ana" }, { "stanko", "ana", "mislav" }) << endl; // "mislav"
//	return 0;
//
//}
// 내 코드와 다른점:
// 내 코드에서는 문자열 해싱을 사용해서 참가자 해쉬로 완주자 배열을 순회하면서
// 이름을 못찾으면 해당 이름을 반환하는 식으로 구현하였지만 이 코드의 한계는 중복되는 사람의
// 이름은 찾아내지 못한다는 것이었다.
// 정답코드에서는 이미 해시의 기능을 하는 unordered_map을 사용하고 있다.
// unordered_map<string, int> ph; 형식을 사용하여, 참가자 이름과, 그 이름의 사람 수를
// 저장한다.
// 완주자 배열을 순회하면서 탐색한 이름을 키값으로 하는 ph의 int 값을 -1 한다.
// int 값이 0이되면 맵에서 erase 한다.
// 순회를 마치면 ph에서 값이 1인 string 하나만 남을 것이다.
// string 을 반환하면 끝!
// 확실히 정답코드가 간결하군.. 아직 낯선 자료구조들도 많이 써봐야할것같다.
// 시간복잡도 :O(N)
// 또다른 정답코드:
//#include <string>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//string solution(vector<string> participant, vector<string> completion) {
//
//	sort(participant.begin(), participant.end());
//	sort(completion.begin(), completion.end());
//
//	for (int i = 0; i < completion.size(); i++)
//	{
//		if (participant[i] != completion[i])
//			return participant[i];
//	}
//
//	return participant[participant.size() - 1];
//}
//
//
//
////아래 코드는 테스트 코드 입니다.
//
//#include <iostream>
//
//int main()
//{
//	cout << solution({ "leo", "kiki", "eden" }, { "eden", "kiki" }) << endl; // "leo"
//	cout << solution({ "marina", "josipa", "nikola", "vinko", "filipa" }, { "josipa", "filipa", "marina", "nikola" }) << endl; // "vinko"
//	cout << solution({ "mislav", "stanko", "mislav", "ana" }, { "stanko", "ana", "mislav" }) << endl; // "mislav"
//	return 0;
//
//}
//시간복잡도 :O(NlogN)