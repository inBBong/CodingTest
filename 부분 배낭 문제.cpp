#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool compare(vector<double> a, vector<double> b)
{
	return a[2] > b[2];
}
double solution(vector<vector<double>> items, double weight_limit)
{
	vector<double> valuePerWeight(items.size());
	double value(0);
	for (auto& item : items)
	{
		item.push_back(item[1] / item[0]);
	}
	sort(items.begin(), items.end(), compare);
	
	int idx(0);
	while (weight_limit)
	{
		if (items[idx][0] > 0)
		{
			weight_limit--;
			items[idx][0]--;
			value += items[idx][2];
		}
		else
			idx++;
	}
	return value;
}
int main()
{
	cout << solution({ {10, 19}, {7, 10}, {6, 10} }, 15) << endl; //출력값 : 27.3333
	cout << solution({ {10, 60}, {20, 100}, {30, 120} }, 50) << endl; //출력값 : 240

}
// 정답코드 :
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//❶ 각 물건의 단위 무게당 가치를 계산하여 items 벡터에 추가
void calculate_unit_value(vector<vector<double>>& items) {
	for (auto& item : items) {
		item.push_back(item[1] / item[0]);
	}
}

//❷ 단위 무게당 가치가 높은 순으로 물건을 정렬
void sort_by_unit_value(vector<vector<double>>& items) {
	sort(items.begin(), items.end(), [](const vector<double>& a, const vector<double>& b) {
		return a[2] > b[2];
		});
}

double knapsack(vector<vector<double>>& items, double weight_limit) {
	double total_value = 0; //❸ 선택한 물건들의 총 가치를 저장
	double remaining_weight = weight_limit; //❹남은 무게 한도를 저장

	//❺ items을 순회하며 물건을 선택
	for (const auto& item : items) {
		if (item[0] <= remaining_weight) {
			//❻ 남은 무게 한도 내에서 물건을 통째로 선택
			total_value += item[1];
			remaining_weight -= item[0];
		}
		else {
			//❼ 남은 무게 한도가 물건의 무게보다 작으면 쪼개서 일부분만 선택
			double fraction = remaining_weight / item[0];
			total_value += item[1] * fraction;
			break; //❽ 이미 배낭의 무게 한도를 모두 사용한 경우
		}
	}
	return total_value;
}

double solution(vector<vector<double>> items, double weight_limit) {
	calculate_unit_value(items);
	sort_by_unit_value(items);
	//➒ 배낭의 무게 한도 내에서 담을 수 있는 물건들의 최대 가치를 반환(소수점 둘째자리 까지만 나타냄)
	return round(knapsack(items, weight_limit) * 100) / 100;
}

//아래 코드는 테스트 코드 입니다.
#include <iostream>

int main()
{
	cout << solution({ {10, 19}, {7, 10}, {6, 10} }, 15) << endl; //출력값 : 27.3333
	cout << solution({ {10, 60}, {20, 100}, {30, 120} }, 50) << endl; //출력값 : 240

	return 0;
}

//내 코드와 다른 점:
// 우선 items 입력에 1키로당 가치를 push_back 하고, items를 1키로당 가치를 기준으로 내림차순
// 정렬하는 것 까지는 같다.
// 한가지 다른 점은, 나는 남은 가방 용량이 0이 될때까지 1키로씩 남아있는 물건을 
// 가장 가치가 큰 물건부터 넣었고, 정답코드에서는 items 를 순회하면서, 가방의 용량보다
// item의 용량이 더 작으면 한번에 해당 용량만큼 넣었다. 그리고 가방의 용량이 item의 용량보다 
// 작으면 쪼개서 넣었다.
// 
// 시간복잡도 : O(NlogN)
//