//#include<iostream>
//#include<string>
//#include<vector>
//#include<unordered_map>
//#include<algorithm>
//using namespace std;
//
////내코드
//enum command
//{
//	Enter = 0, Leave, Change
//};
//vector<string> solution(vector<string> record)
//{
//	unordered_map<string,string> ids;
//	vector<string> answer;
//	for(auto cr:record)
//	{
//			bool idFin = false;
//			string id;
//		for (int i = 0; i < cr.size(); ++i)
//		{
//			if (cr[i] == ' '&&!idFin)
//			{
//				id = cr.substr(i + 1, 7);
//				ids[id];
//				idFin = true;
//			}
//			else if(cr[i]==' ')
//			{
//				ids[id]= cr.substr(i + 1, cr.size()-i);
//			}
//		}		
//	}
//	for (auto cr : record)
//	{		
//		int cmd;
//		string id;
//		for (int i = 0; i < cr.size(); ++i)
//		{
//			if (cr[i] == ' ')
//			{
//				if (cr.substr(0, i) == "Enter")
//					cmd = command::Enter;
//				else if (cr.substr(0, i) == "Leave")
//					cmd = command::Leave;
//				else
//					cmd = command::Change;
//
//				id = cr.substr(i + 1, 7);
//				break;
//			}			
//		}
//		string ans = ids[id];
//		switch (cmd)
//		{
//		case command::Enter:
//			ans += "님이 들어왔습니다.";
//			answer.push_back(ans);
//			break;
//		case command::Leave:
//			ans += "님이 나갔습니다.";
//			answer.push_back(ans);
//			break;
//		case command::Change:			
//			break;
//		}
//	}
//
//	return answer;
//}

//int main()
//{
//
//	vector<string> answer= solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234", "Enter uid1234 Prodo","Change uid4567 Ryan" });
//	for (auto ca : answer)
//		cout << ca;
//}
//정답코드
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

vector<string> solution(vector<string> record) {
	vector<string> answer;
	unordered_map<string, string> uid;

	for (const auto& line : record) {
		//❶ 각 record에 대해서,  cmd에는 명령어를 저장하고  id에는 유저id을 저장
		stringstream ss(line);
		string cmd, id, nickname;
		ss >> cmd >> id;
		//❷ 명령어가 Enter 혹은 Change일 경우 nickname에 닉네임을 저장
		if (cmd != "Leave") {
			ss >> nickname;
			uid[id] = nickname;
		}
	}

	for (const auto& line : record) {
		stringstream ss(line);
		string cmd, id;
		ss >> cmd >> id;
		//❸ Enter 및 Change 명령어의 경우 최종 닉네임과 정해진 문자열을 answer에 추가
		if (cmd == "Enter") {
			answer.push_back(uid[id] + "님이 들어왔습니다.");
		}
		else if (cmd == "Leave") {
			answer.push_back(uid[id] + "님이 나갔습니다.");
		}
		// "Change"는 메시지 생성에 영향을 주지 않으므로 무시
	}

	return answer;
}

//아래 코드는 테스트 코드 입니다.
#include <iostream>
#include <iterator>
void print(vector<string> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<string>(cout, " "));
	cout << endl;
}

int main()
{
	print(solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234", "Enter uid1234 Prodo","Change uid4567 Ryan" }));
	// Prodo님이 들어왔습니다. Ryan님이 들어왔습니다. Prodo님이 나갔습니다. Prodo님이 들어왔습니다.    

	return 0;
}
// 내 코드와 다른점:
// record를 한번 순회하고, unordered_map으로 id를 키, 닉네임을 값으로 저장하면 최종 수정된 id와 닉네임을
// 얻을 수 있다는 아이디어는 같다. 하지만 정답코드에서는 stringstream이라는 것을 사용해서
// id와 닉네임을 보다 간결하게 얻어냈다. 나는 stringstream을 몰랐기 때문에 복잡하게 id와 닉네임을 얻어냈다.
// -> 씹어먹는C++ : C++에서의 입출력 공부
//시간복잡도 : O(N)