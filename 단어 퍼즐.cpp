#include<iostream>
#include<vector>
using namespace std;

int solution(vector<string> strs, string t)
{

}
int main()
{
	cout << solution({ "ba", "na", "n", "a" }, "banana") << endl; //출력값 : 3
	cout << solution({ "app", "ap", "p", "l", "e", "ple", "pp" }, "apple") << endl; //출력값 : 2  
	cout << solution({ "ba", "an", "nan", "ban", "n" }, "banana") << endl; //출력값 : -1 
}