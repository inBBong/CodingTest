#include<iostream>
#include<vector>
using namespace std;
int solution(int N, vector<int> stations, int W)
{
	vector<int>NoWifi;
	int nowifi(0);
	int answer(0);
	int yeswifi(0);
	for(auto station:stations)
	{
		NoWifi.push_back(station - W-1-yeswifi);
		yeswifi = station + W;
	}
	if (yeswifi < N)
		NoWifi.push_back(N - yeswifi);
	int range = 2 * W + 1;
	for (auto nw : NoWifi)
	{
		answer += ((nw - 1) / range) + 1;
	}
	return answer;
}
int main()
{
	cout << solution(11, { 4, 11 }, 1) << endl; // 3
	cout << solution(16, { 9 }, 2) << endl;   // 5
}
//정답코드 :
//#include <vector>
//
//using namespace std;
//
//int solution(int N, vector<int> stations, int W) {
//	int answer = 0;
//	int location = 1; // ❶ 현재 탐색하는 아파트의 위치
//	int idx = 0; // ❷ 설치된 기지국의 인덱스
//
//	while (location <= N) {
//		// ❸ 기지국이 설치된 위치에 도달한 경우
//		if (idx < stations.size() && location >= stations[idx] - W) {
//			location = stations[idx] + W + 1;
//			idx++;
//		}
//		// ❹ 기지국이 설치되지 않은 위치인 경우
//		else {
//			// ➎ 기지국을 설치하고 해당 범위를 넘어감
//			location += 2 * W + 1;
//			answer++;
//		}
//	}
//
//	return answer;
//}
//
////아래 코드는 테스트 코드 입니다.
//#include <iostream>
//
//int main()
//{
//	cout << solution(11, { 4, 11 }, 1) << endl; // 3
//	cout << solution(16, { 9 }, 1) << endl;   // 5
//	return 0;
//}
// 
// 내 코드와 다른 점:
// 나는 우선 기지국 범위안에 없는 아파트의 붙어있는 아파트의 수를 NoWifi 벡터에 저장하고,
// 해당 범위들에 기지국을 증설하는 기준 answer += (nw / range) + 1;으로 증설 기지국 수를 구했다.
// 
// 반면 정답코드에서는, 1번아파트부터 N번아파트까지 순회하면서, 현재 location이 기지국 범위 안에 있는지를
// 체크하고, 기지국 범위 밖이면 기지국을 설치한 뒤 location+=2*W +1만큼 이동한다. 기지국 범위 안이면,
// stations의 idx을 하나 증가시키고 기지국 밖으로 이동한다.
// 이번 문제는 내 코드와 정답코드의 로직은 조금 다르지만, 뭐가 더 좋은 코드인지는 잘 모르겠다.
// 그래서 클로드에게 물어봤는데, 내가 놓친부분을 알려줬다. 나는 기지국의 위치를 기준으로 범위 안에 없는
// 아파트의 붙어있는 아파트 수를 저장했는데, 마지막 기지국 이후에도 범위 밖의 아파트들이 있을 수 있다는 것을
// 놓쳤다.
// 시간복잡도 : O(N/W)
//