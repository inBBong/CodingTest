#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;
//각 쿼리 배열에 있는 문자열이 string_list의 문자열 배열에 있는지 여부를 확인해야 합니다.문자열이 있으면 true, 없으면 false가 됩니다. 
//각 문자열에 대해서 문자열의 존재 여부를 배열 형태로 반환하는 solution() 함수를 작성해주세요.
//hash(s) =(s[0] + s[1]*p + s[2]*p^2 + ...s[n-1]*p^n-1)mod m
//내 코드
int Uhash(string s, int mod)
{
	int result(0);
	int p = 1;
	for (int i = 0; i < s.size(); ++i)
	{
		int val = s[i] - 'a' + 1;
		result += (val * p) % mod;
		p *= 31;
	}
	return result;
}
vector<bool>solution(vector<string> string_list, vector<string> query_list)
{
	vector<int> key;
	vector<bool>answer;
	for (auto cs : string_list)
		key.push_back(Uhash(cs, string_list.size()));
	
	for (auto cq : query_list)
	{
		if (key.end() != find(key.begin(), key.end(), Uhash(cq, string_list.size())))
			answer.push_back(true);
		else
			answer.push_back(false);
	}
	return answer;
}
int main()
{
	vector<string> v = { "apple","banana","cherry" };
	vector<string> v2 = { "banana","kiwi","melon","apple" };
	vector<bool>answer;
	answer = solution(v, v2);
	for (auto ca : answer)
		cout << ca<<" ";

}
////정답코드
//#include <vector>
//#include <string>
//#include <unordered_set>
//
//using namespace std;
//
//// ❶ 다항 해시 함수 구현
//long long polynomial_hash(const string& str) {
//    const int p = 31;  // 소수
//    const long long m = 1000000007;  // 버킷 크기
//    long long hash_value = 0;
//
//    for (char c : str) {
//        hash_value = (hash_value * p + c) % m;
//    }
//
//    return hash_value;
//}
//
//vector<bool> solution(vector<string> string_list, vector<string> query_list) {
//    unordered_set<long long> hash_set;
//
//    //❷ string_list의 각 문자열에 대해 다항 해시값을 계산하고 저장
//    for (const string& str : string_list) {
//        long long hash = polynomial_hash(str);
//        hash_set.insert(hash);
//    }
//
//    vector<bool> result;
//
//    //❸  query_list의 각 문자열이 string_list에 있는지 확인하고 result에 추가
//    for (const string& query : query_list) {
//        long long query_hash = polynomial_hash(query);
//        bool found = (hash_set.find(query_hash) != hash_set.end());
//        result.push_back(found);
//    }
//    // ❹ query_list의 문자열이 hash에 있는지 결과가 저장된 result를 반환
//    return result;
//}
//
//
////아래 코드는 테스트 코드 입니다.
//#include <iterator>
//#include <iostream>
//void print(vector<bool> vec)
//{
//    copy(vec.begin(), vec.end(), std::ostream_iterator<bool>(cout, " "));
//    cout << endl;
//}
//
//int main()
//{
//    //true를 출력하면 1이되고 false를 출력하면 0
//    print(solution({ "apple", "banana", "cherry" }, { "banana", "kiwi", "melon", "apple" })); // 1 0 0 1
//    return 0;
//
//}
// 내 코드와 다른 점:
// 나는 키 값을 담은 int 형vector를 사용했고, 정답코드에서는 long long 형unordered_set을 사용함.
// long long 자료형이 표현할 수 있는 정수의 범위가 훨씬 많음 900해임 ㅅㅂㅋㅋ int는 21억정도
// mod 값을 나는 string_list의 사이즈로 했는데 정답코드에서는 100000007을 사용함.
// 이건 내가 개념이 덜 잡혀서 그런듯.string_list의 사이즈로 하면 경우의 수가 string_list의 사이즈밖에 안나와서
// 해시 충돌이 많이 일어날 것 같음.
// 또 해시 함수를 나는 N-1번째 문자에 p^(N-1)로 계산했는데 정답코드는 0번째 문자에 p^(N-1)로 계산함.
// 가중치는 정방향, 역방향 어떻게 해도 상관이 없다고 함.
// 
// 시간복잡도 :O(N + K)
//