#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<int> solution(vector<int>array, vector<vector<int>> commands)
{
	vector<int>answer;
	for (auto cc : commands)
	{
		vector<int>newvec;
		for (int i = cc[0] - 1; i < cc[1]; ++i)
			newvec.push_back(array[i]);

		sort(newvec.begin(), newvec.end());
		answer.push_back(newvec[cc[2] - 1]);
	}
	return answer;
}
int main()
{
	vector<int>a=solution({ 1, 5, 2, 6, 3, 7, 4 }, { {2, 5, 3}, {4, 4, 1}, {1, 7, 3} }); // 출력값 : 5 6 3
	for (auto ca : a)
		cout << ca << " ";
}
//정답코드 :
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer;
	vector<int> subArray;

	for (const auto& cmd : commands) {
		//❶ array에서 각 cmd에 해당되는 영역만 subArray로 복사후 정렬
		subArray.assign(array.begin() + (cmd[0] - 1), array.begin() + cmd[1]);
		sort(subArray.begin(), subArray.end());

		//❷ subArray에서 k번 째 answer에 추가
		answer.push_back(subArray[cmd[2] - 1]);
	}

	return answer;
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
	print(solution({ 1, 5, 2, 6, 3, 7, 4 }, { {2, 5, 3}, {4, 4, 1}, {1, 7, 3} })); // 출력값 : 5 6 3

	return 0;
}
// 내 코드와 다른 점:
// 이번에도 역시 로직은 같다. 하지만 subArray를 생성하는 부분이 나는
// vector<int>newvec;
// for (int i = cc[0] - 1; i < cc[1]; ++i)
//	 newvec.push_back(array[i]);
// 이렇게 반복문을 써서 한 반면 정답코드에서는 
// subArray.assign(array.begin() + (cmd[0] - 1), array.begin() + cmd[1]); 
// 로 한번에 끝냈다.
// 
// 시간복잡도 : O(M*NlogN)
//