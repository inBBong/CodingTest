#include<iostream>
#include<vector>
using namespace std;
vector<int>lionInfo(11,0);
vector<int>MaxlionInfo(1,-1);
vector<int>appeachInfo(11,0);
vector<int>answers;

int ScoreGap(vector<int>appeach, vector<int>lion)
{
	int lionScore(0);
	int appeachScore(0);

	for (int i = 0; i < 11; ++i)
	{
		if (appeach[i] < lion[i])
		{
			lionScore += 10 - i;
		}
		else if(appeach[i]!=0)
			appeachScore += 10 - i;
	}
	if (appeachScore < lionScore)
		return lionScore - appeachScore;
	else
		return -1;
}
void backTrack(int arrows,int index)
{
	if (index == 10|| arrows==0)
	{
		lionInfo[index]+=arrows;
		return;
	}
	int undo = lionInfo[index];
	lionInfo[index] = arrows;
	int SG = ScoreGap(appeachInfo, lionInfo);
	if (SG!= -1)// 이기면
	{
		int max(0);
		answers.push_back(SG);
		for (auto ca : answers)
		{
			if (ca > max)
				max = ca;
		}
		if (max == SG)
			MaxlionInfo = lionInfo;
	}
	for (int i = 1; i < arrows+1; ++i)
	{
		lionInfo[index] -= i;
		backTrack(i, index + 1);
		lionInfo[index] += i;		
		lionInfo[index + 1] -= i;		
	}
}
vector<int> solution(int n, vector<int> info)
{	
	appeachInfo = info;	
	
	backTrack(n,0);
	return MaxlionInfo;
}

void init()
{
	for (int i = 0; i < 11; ++i)
	{
		lionInfo[i] = 0;		
	}
	MaxlionInfo.clear();
	MaxlionInfo.push_back(-1);
	answers.clear();
	
}
int main()
{
	vector<int>a, b, c;
	a=solution(5, { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }); //출력값 : 0 2 2 0 1 0 0 0 0 0 0 
	init();
	for (auto ca : a)
		cout << ca << " ";
	cout << endl;

	b=solution(1, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }); //출력값 : -1
	init();
	for (auto cb : b)
		cout << cb << " ";
	cout << endl;

	c=solution(9, { 0, 0, 1, 2, 0, 1, 1, 1, 1, 1, 1 }); //출력값 : 1 1 2 0 1 2 2 0 0 0 0 
	for (auto cc : c)
		cout << cc << " ";
}
//정답코드
#include <vector>

using namespace std;

vector<int> answer;
vector<int> ryan(11, 0);
int maxScore = -1;

//❶ 어피치와 라이언의 점수차이를 계산
int calcScoreDiff(const vector<int>& apeach) {
	int scoreApeach = 0;
	int scoreLion = 0;

	for (int i = 0; i < 11; ++i) {
		if (apeach[i] == 0 && ryan[i] == 0) continue;
		if (apeach[i] >= ryan[i]) scoreApeach += 10 - i;
		else scoreLion += 10 - i;
	}

	return scoreLion - scoreApeach;
}

void dfs(const vector<int>& apeach, int score, int arrow) {
	if (score == -1 || arrow == 0) {
		ryan[10] = arrow;
		int scoreDiff = calcScoreDiff(apeach);
		//❷ 현재 구한 점수차가 기존 최대 점수차보다 더 크고, 라이언의 점수가 더 높은 경우 갱신
		if (scoreDiff > 0 && maxScore < scoreDiff) {
			maxScore = scoreDiff;
			answer = ryan;
		}
		ryan[10] = 0;
		return;
	}

	//❸ 아직 어피치가 쏠 화살이 남은 경우
	if (arrow > apeach[score]) {
		ryan[score] = apeach[score] + 1;
		dfs(apeach, score - 1, arrow - apeach[score] - 1);
		ryan[score] = 0;
	}

	//❹ 어피치가 화살을 사용하지 않는 경우
	dfs(apeach, score - 1, arrow);
}

vector<int> solution(int n, vector<int> info) {
	//❺ 10점 과녁부터 모든 조합을 확인
	dfs(info, 10, n);

	//❻ 라이언이 이길 수 있는 경우가 없는 경우
	if (maxScore == -1) answer.push_back(-1);

	return answer;
}





//아래 코드는 테스트 코드 입니다.
#include <iostream>
#include <iterator>
using namespace std;

void init() {
	answer.clear();
	maxScore = -1;

	for (int i = 0; i < ryan.size(); i++)
		ryan[i] = 0;
}

void print(vector<int> vec)
{
	copy(vec.begin(), vec.end(), std::ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{
	print(solution(5, { 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 })); //출력값 : 0 2 2 0 1 0 0 0 0 0 0 
	init();
	print(solution(1, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 })); //출력값 : -1
	init();
	print(solution(9, { 0, 0, 1, 2, 0, 1, 1, 1, 1, 1, 1 })); //출력값 : 1 1 2 0 1 2 2 0 0 0 0 
	return 0;
}
// 내 코드와 다른점 :
// 정답코드를 보고 놀라지 않을 수 없었다. 내 코드보다 훨씬 효율적인 코드였기 때문이다.
// 이번 문제도 아이디어를 떠올리는데만 시간을 엄청 많이 쓰고 결국 지피티에게 물어보면서
// 아이디어를 얻고 코드를 구현하였다. 나는 처음에는 화살 하나당 어떤 점수칸을 맞출지로
// 생각을 했었는데 그럼 경우의 수는 11^N으로 너무 비효율적인 시간복잡도가 나온다.
// 그래서 지피티한테 물어본게, 점수판에 몇발을 맞출지를 생각하면 중복인 경우를 제거할 수
// 있기 때문에 보다 효율적으로 할 수 있음을 알게 되었다. 내 코드는, 라이언의 화살이
// 점수판에 어떤 조합으로 맞출지 모든 경우의수를 판단하고, 유망함수 조건은
// 점수차가 어피치보다 클때로 정하였다. 반면 정답코드에서는, 점수판에 화살을 몇개 맞출지
// 조합으로 푼 것은 동일하지만, 좀 더 세심한 아이디어가 들어가 있었다. 
// 
// 라이언이 특정 점수칸을 맞춘다면, 어피치가 맞춘 화살보다 반드시 1개 더 맞추는것이 의미가
// 있다. 어피치보다 덜 맞추거나, 똑같이 맞추면 해당 점수는 어피치가 가져가고, 화살만 
// 낭비하는 꼴이다. 또한 어피치가 맞춘 화살보다 2발 이상 더 맞추면, 1발 더 맞추는 것과
// 가져가는 점수는 동일한데 화살을 1발 더 낭비하는 꼴이다. 때문에 정답코드에서는
// 해당 점수칸에 화살을 소비할거라면 무조건 어피치의 화살+1 만큼 화살을 소비하도록 구현하였다.
// 
// 이는 내가 고려하지 못한 부분이라 훨씬 효율적이라고 할 수 있다.
// 
// 시간복잡도 : O(2^11) 
//