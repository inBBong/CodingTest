#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays)
{
	unordered_map<string,int> PlayforGenres;
	unordered_map<int,int> indexforPlay; //재생횟수 , 인덱스
	vector<pair<string, int>> forSort;

	vector<int> answer;
	for (int i = 0; i < genres.size(); ++i)
	{
		PlayforGenres[genres[i]] += plays[i];
		indexforPlay[plays[i]] = i;
	}
	for (auto cp : PlayforGenres)
	{
		forSort.push_back({ cp.first,cp.second });
	}
	sort(forSort.begin(), forSort.end(), [](const auto&a,const auto&b){return a.second>b.second});
	
	for (auto cf : forSort)// 장르, play 수 ->> play 수가 많은 순으로 정렬
	{
		
	}
}
int main()
{
	vector<int> v=solution({ "classic", "pop", "classic", "classic", "pop" }, { 500, 600, 150, 800, 2500 });
	for (auto cv : v)
		cout << cv<<" ";
}
//정답코드
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <unordered_map>
//
//using namespace std;
//
//bool compareGenre(const pair<string, int>& a, const pair<string, int>& b) {
//	return a.second > b.second;
//}
//
//bool compareSong(const pair<int, int>& a, const pair<int, int>& b) {
//	if (a.second == b.second) return a.first < b.first;
//	return a.second > b.second;
//}
//
//vector<int> solution(vector<string> genres, vector<int> plays) {
//	vector<int> answer;
//	unordered_map<string, vector<pair<int, int>>> genres_dict;
//	unordered_map<string, int> play_dict;
//
//	//❶ 장르별 총 재생 횟수와 각 곡의 재생 횟수 저장
//	for (int i = 0; i < genres.size(); ++i) {
//		genres_dict[genres[i]].push_back({ i, plays[i] });
//		play_dict[genres[i]] += plays[i];
//	}
//
//	//❷ 총 재생 횟수가 많은 장르순으로 정렬
//	vector<pair<string, int>> sorted_genres(play_dict.begin(), play_dict.end());
//	sort(sorted_genres.begin(), sorted_genres.end(), compareGenre);
//
//	//❸ 각 장르 내에서 노래를 재생 횟수 순으로 정렬해 최대 2곡 까지 선택
//	for (auto& genre : sorted_genres) {
//		auto& songs = genres_dict[genre.first];
//		sort(songs.begin(), songs.end(), compareSong);
//
//		for (int i = 0; i < min(2, (int)songs.size()); ++i) {
//			answer.push_back(songs[i].first);
//		}
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
//	print(solution({ "classic", "pop", "classic", "classic", "pop" }, { 500, 600, 150, 800, 2500 })); //출력값 :  1 0 0 1
//	return 0;
//
//}
//내 코드와 다른점:
// 이번 문제는 끝내 구현하지 못하고 정답코드를 봐버렸다. 이번 문제는 내가 구현하기에는 꽤나 복잡하고 어려운 문제였던것 같다.
// 다음에 한번 더 풀어보는것이 좋을 것 같다.
// 우선 내 코드의 문제점은 첫번째로, unordered_map의 키와 값에 pair가 올 수 있다는 것을 생각하지 못했다.
// unordered_map의 value를 벡터로 설정해서 push_back()으로 키에 대한 value를 여러개 추가할 수 있다는 아이디어가
// 중요했다고 생각한다. 그리고 
// unordered_map의 value를 기준으로 정렬하는법을 알지 못했다. 정답코드에서는 sorted_genres라는 새로운 벡터를 선언해서 정렬하였다.
// 또한 sort() 함수를 아직 많이 써보지 않아서 아직 compare 함수를 만드는 법을 잘 모르는것 같다.
// 마지막으로 auto 자료형을 많이 써본 경험이 부족한것같다. 정답코드에서는
// auto& songs = genres_dict[genre.first]; 이런식으로 자유자재로 auto 자료형을 사용하는데 이부분은 연습이 더 필요한 것 같다.
//시간복잡도 :O(NlogN) 
//