#include<iostream>
#include<stack>
#include<string>
#include<unordered_map>
using namespace std;
//대괄호, 중괄호, 그리고 소괄호로 이루어진 문자열 s가 매개변수로 주어집니다. 이 s를 왼쪽으로 x(0<=x<(s의길이)) 칸 만큼 회전시켰을 때 s가 올바른 
//괄호 문자열이 되게 하는 x의 개수를 반환하는 solution() 함수를 완성하세요.
//내 코드 (작성 후 정답코드 보고 수정)
unordered_map<char, char> bracketPair
{
	{']','['},
	{')','('},
	{'}','{'}
};
bool isvalid(string s,int start)
{
	stack<char> st;

	for (int i = 0; i < s.size(); ++i)
	{
		//if (s[i] == '(' || s[i] == '[' || s[i] == '{')
		//{
		//	st.push(s[i]);
		//}
		char ch = s[(start + i) % s.size()];
		if (bracketPair.count(ch))//닫힌 괄호면
		{
			if (st.empty() || st.top() != bracketPair[ch])
				return false;
			else
				st.pop();
		}
		else//열린 괄호면
		{
			st.push(ch);
			/*if (st.empty())return false;

			if ((st.top() == '('&&s[i]==')') || (st.top() == '{' && s[i] == '}') || (st.top() == '[' && s[i] == ']') )
				st.pop();
			else
				return false;*/
		}
	}
	return st.empty();
}
int solution(string s)
{
	int cnt(0);
	for(int j=0;j<s.size();++j)
	{
		if (isvalid(s,j))
			cnt++;
		/*char temp = s[0];
		for (int i = 0; i < s.size() - 1; ++i)
		{
			s[i] = s[i + 1];
		}
		s[s.size() - 1] = temp;*/ //내코드인데 배열을 직접 바꾸는건 비용이 큼.
	}
	return cnt;
}
int main()
{
	cout << solution("[](){}");
	cout << solution("}]()[{");
	cout << solution("[)(]");
}
//정답코드
//#include <string>
//#include <vector>
//#include <stack>
//#include <unordered_map>
//using namespace std;
//
//// ❶ 닫힌 괄호의 짝을 바로 확인할 수 있도록 맵 선언 
//unordered_map<char, char> bracketPair = {
//		{')', '('},
//		{']', '['},
//		{'}', '{'}
//};
//
////❷현자 인자로 받은 문자열 기준 괄호짝이 맞는지 확인
//bool isValid(string& s, int start) {
//	stack<char> stk;
//	unsigned int  sz = s.size();
//
//	//❸ 문자열을 순회하면서
//	for (int i = 0; i < sz; i++) {
//		char ch = s[(start + i) % sz];
//		//❹ ch가 닫힌 괄호 인경우
//		if (bracketPair.count(ch)) {
//			// ❺ 스택이 비었거나 top 원소가 ch와 짝이 맞는 열린괄호가 아닌 경우 false 반환
//			if (stk.empty() || stk.top() != bracketPair[ch]) return false;
//			//❻ ch와 짝이 맞는 열린괄호일경우 해당 열린괄호를 제거
//			stk.pop();
//		}
//		else {
//			//❼ 열린 괄호일경우 스택이 푸시
//			stk.push(ch);
//		}
//	}
//	//❽스택이 비었으면 true를 반환(비었다는것은 괄호 짝이 맞다는 것을 의미)
//	return stk.empty();
//}
//
//int solution(string s) {
//	int answer = 0;
//	int n = s.size();
//
//	//❾ 문자열을 rotation하면서 괄호짝이 맞으면 answer를 1증가 시킴
//	for (int i = 0; i < n; i++) {
//		answer += isValid(s, i);
//	}
//	return answer;
//}
//
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//int main()
//{
//	cout << solution("[](){}") << endl; // 3
//	cout << solution("}]()[{") << endl; // 2 
//	cout << solution("[)(]") << endl;   // 0 
//	cout << solution("}}}") << endl;    // 0   
//	return 0;
//} 
//시간복잡도 : O(N^2)