#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<int> solution(vector<string>enroll, vector<string> referral, vector<string>seller, vector<int>amount)
{

}
int main()
{
    vector<int> a=solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
        { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
        { "young", "john", "tod", "emily", "mary" },
        { 12, 4, 2, 5, 10 }
    ); //출력값 : 360 958 108 0 450 18 180 1080

    vector<int> b=solution({ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
        { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
        { "sam", "emily", "jaimie", "edward" },
        { 2, 3, 5, 4 }
    ); //출력값 : 0 110 378 180 270 450 0 0 

    for (auto ca : a)
        cout << ca << " ";
    for (auto cb : b)
        cout << cb << " ";
}