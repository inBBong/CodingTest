#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;
//내 코드
vector<int> solution(int n, vector<string> words)
{	
	vector<string> comparevec;
	unordered_set<string> compareset;
	vector<int>answer;
	for (int i = 0; i < words.size(); ++i)
	{
		comparevec.push_back(words[i]);
		compareset.insert(words[i]);
		if (compareset.size() != comparevec.size())
		{
			answer.push_back((i % n) + 1);
			answer.push_back((i / n) + 1);
		}
	}
	for (int i = 0; i < words.size()-1; ++i)
	{
		if(words[i][words[i].size()-1]!=words[i+1][0])
		{
			answer.push_back(((i + 1) % n) + 1);
			answer.push_back(((i + 1) / n) + 1);
		}
	}
	if (answer.empty())
		return { 0,0 };
	return answer;
}

int main()
{
	//{"hello", "observe", "effect", "take", "either", "recognize", "encourage", "ensure", "establish", "hang", "gather", "refer", "reference", "estimate", "executive"})); // 결과값 : 0 0
	//print(solution(2, { "hello", "one", "even", "never", "now", "world", "draw" })); // 결과값 : 1 3
	vector<int> answer = solution(3, { "tank", "kick", "know", "wheel", "land", "dream", "mother", "robot", "tank" });
	for (auto ca : answer)
		cout << ca << " ";
	vector<int> answer2 = solution(5, { "hello", "observe", "effect", "take", "either", "recognize", "encourage", "ensure", "establish", "hang", "gather", "refer", "reference", "estimate", "executive" });
	for (auto ca : answer2)
		cout << ca << " ";
	vector<int> answer3 = solution(2, { "hello", "one", "even", "never", "now", "world", "draw" });
	for (auto ca : answer3)
		cout << ca << " ";
}
//정답코드
//#include <string>
//#include <vector>
//#include <unordered_set>
//
//using namespace std;
//
//vector<int> solution(int n, vector<string> words) {
//
//	vector<int> answer(2, 0);
//	unordered_set<string> usedWords;
//
//	usedWords.insert(words[0]);
//
//	//❶ 두 번째 단어부터 끝까지 반복
//	for (int i = 1; i < words.size(); ++i) {
//		//❷ 단어가 이미 사용되었거나, 끝말잇기 규칙에 맞지 않는 경우
//		if (!usedWords.insert(words[i]).second || words[i].front() != words[i - 1].back()) {
//			//❸ 플레이어 번호와 턴 번호 저장 후 바로 반환
//			answer[0] = i % n + 1;
//			answer[1] = i / n + 1;
//			return answer;
//		}
//	}
//
//	//❹ 중간에 탈락하는 플레이어가 없으면 [0, 0] 반환
//	return answer;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//#include <iterator>
//
//using namespace std;
//
//void print(vector<int> vec)
//{
//	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
//	cout << endl;
//}
//
//int main()
//{
//	print(solution(3, { "tank", "kick", "know", "wheel", "land", "dream", "mother", "robot", "tank" })); // 결과값 : 3 3
//	print(solution(5, { "hello", "observe", "effect", "take", "either", "recognize", "encourage", "ensure", "establish", "hang", "gather", "refer", "reference", "estimate", "executive" })); // 결과값 : 0 0
//	print(solution(2, { "hello", "one", "even", "never", "now", "world", "draw" })); // 결과값 : 1 3
//
//	return 0;
//}
//내 코드와 다른점:
// 로직은 같은것같은데, 정답코드에서 좀더 컨테이너의 함수를 유연하게 사용하였다.
// 나는 비교 벡터와 비교 셋을 선언해서, 주어진 단어들을 추가할때 셋은 중복을 허용하지 않는것을 이용해서 
// 벡터와 셋의 크기가 달라지면 중복된 단어를 추가했다는 의미이므로 answer에 해당 인덱스를 이용해 답을 리턴했다.
// 반면 정답코드에서는 
// !usedWords.insert(words[i]).second 라는 것을 사용했다. 셋의 insert 함수는 pair를 리턴한다. first는 iterator, second는 bool(중복인지아닌지)
// 를 이용해서 중복 검사를 하였다.
// 또한 나는 끝말잇기가 잘 되는지 여부를 확인하기위해
// words[i][words[i].size()-1] != words[i+1][0] 이런식으로 비교하였고 정답코드에서는
// string의 함수 front()와 back()을 사용하였다.
//시간복잡도 : O(N)