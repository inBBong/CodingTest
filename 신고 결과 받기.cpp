#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<sstream>
using namespace std;
vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
	vector<int> answer(id_list.size(), 0);
	unordered_map<string, unordered_set<string>> reportWhom;
	unordered_map<string, int>reported;
	unordered_map<string, bool>isBanned;
	unordered_map<string, int> isWho;
	for (int i=0;i<id_list.size();++i)
	{
		isBanned[id_list[i]] = false;
		isWho[id_list[i]] = i;
	}
	for (auto cr : report)
	{
		stringstream ss(cr);
		string who,whom;
		ss >> who >> whom;
		if (reportWhom[who].insert(whom).second)
		reported[whom]++;
	}
	for (auto cr : reported)
	{
		if (cr.second >= k)
			isBanned[cr.first] = true;
	}
	for (auto cr : reportWhom)
	{
		for (auto cw : cr.second)
		{
			if (isBanned[cw])
				answer[isWho[cr.first]]++;
		}
	}
	return answer;
}
int main()
{
	vector<int>v= solution({ "muzi", "frodo","apeach", "neo" }, { "muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi" }, 2); //출력값 : 2 1 1 0
	vector<int>v2 = solution({ "con", "ryan" }, { "ryan con", "ryan con", "ryan con", "ryan con" }, 3);
	for (auto cv1 : v)
		cout << cv1<<" ";

	cout << endl;
	for (auto cv2 : v2)
		cout << cv2<<" ";

}

//정답코드
//#include <vector>
//#include <string>
//#include <unordered_map>
//#include <unordered_set>
//#include <sstream>
//
//using namespace std;
//
//vector<int> solution(vector<string> id_list, vector<string> report, int k) {
//	unordered_map<string, unordered_set<string>> reported_user; // 신고당한 유저 - 신고 유저 집합
//	unordered_map<string, int> count; // 처리 결과 메일을 받은 유저 - 받은 횟수
//
//	// 신고 기록 순회
//	for (string& r : report) {
//		// ❶ 각 report에서 user_id와 report_id를 분리하고 reported_user에 추가 
//		stringstream ss(r);
//		string user_id, reported_id;
//		ss >> user_id >> reported_id;
//		reported_user[reported_id].insert(user_id);
//	}
//
//	for (auto& [reported_id, user_id_lst] : reported_user) {
//		//❷ k명 이상에게 신고당했는지 확인
//		if (user_id_lst.size() >= k) {
//			//❸ 각 uid가 신고 결과를 받은 횟수를 기록
//			for (const string& uid : user_id_lst) {
//				count[uid]++;
//			}
//		}
//	}
//
//	vector<int> answer;
//	//❹ 각 아이디별 메일을 받은 횟수를 id_list 순서대로 answer에 추가
//	for (string& id : id_list) {
//		answer.push_back(count[id]);
//	}
//
//	return answer;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iterator>
//#include <iostream>
//void print(vector<int> vec)
//{
//	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
//	cout << endl;
//}
//
//int main()
//{
//	print(solution({ "muzi", "frodo","apeach", "neo" }, { "muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi" }, 2)); //출력값 : 2 1 1 0
//	print(solution({ "con", "ryan" }, { "ryan con", "ryan con", "ryan con", "ryan con" }, 3)); //출력값 : 0 0 
//
//	return 0;
//}
// 내 코드와 차이점:
// 나는 신고한 유저 - 신고당한 유저의 집합을 저장하는 unordered_map을, 정답코드는
// 신고당한 유저 - 신고한 유저 집합을 저장하는 unorder_map을 사용했다.
// 정답코드처럼 구현하면, 내 코드와 달리 각 유저가 신고를 당했는지 체크하는 isBanned,
// 유저의 이름을 키로 하고 인덱스를 값으로 갖는 iswho, 각 유저가 몇번 신고 당했는지 체크하는 reported도 필요가 없어진다.
// 특히 입력 요소를 정렬하거나 할 필요가 없으므로 인덱스를 값으로 갖는 iswho는 만들 필요가 없었던것같다.
// 시간복잡도: O(N+M*K)
// 