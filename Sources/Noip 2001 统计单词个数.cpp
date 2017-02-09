#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

int lines,part_k,dict_cnt;
string str;
int len;
vector<string> dict[26];
int word_cnt[201][201] ={0};

bool Check(string str_check){
	if(dict[str_check[0]-'a'].empty()){ //
		return false;
	}
	for(vector<string>::iterator i = dict[str_check[0]-'a'].begin();i!=dict[str_check[0]-'a'].end();i++){
		
		if(str_check.length()>=(*i).length()&&str_check.substr(0,(*i).length()) == (*i)){
			return true;
		}
	}
	return false;
}

int PreCalcWordCnt(){
	for(int j = len-1;j>=0;j--){ //倒着递推
		for(int i = j;i>=0;i--){
			word_cnt[i][j] = word_cnt[i+1][j] +(int)Check(str.substr(i,j-i+1));
		}
	}
}


//Summary:
//	dp[i][j] = max{dp[t][j-1]+word_cnt[t+1][i]} j<=t<i
//	其中，word_cnt可以预处理出来，
//	用倒着推（为什么？）
//	保证每次推的时候当前区间的第一个字符是没有用到的，不会因为后面的单词导致无法使用这个单词
//	如果不用倒着推，还得要再次判断这个前面的字符有没有与它冲突的
//	并且，直接通过往前开辟一个字符进行判断的好处还有
//	要用到这个字符，那么就只有以这个字符打头的单词才可以了，减少了判断的复杂度 
int main(){
	cin>>lines>>part_k;
	for(int i =1 ;i<=lines;i++){
		
		string temp_read;
		
		cin>>temp_read;
		str+=temp_read;  
	}
	len =  str.length();
	cin>>dict_cnt;
	for(int i = 1;i<=dict_cnt;i++){
		string temp_read;
		cin>>temp_read;
		dict[temp_read[0]-'a'].push_back(temp_read);
	}
	PreCalcWordCnt();
	
	int dp[201][201] = {0};
	
	dp[0][0]  = word_cnt[0][0];
	
	for(int i = 0;i<len;i++){
		dp[i][0] = word_cnt[0][i]; //分成1份预处理 
	}
	for(int i = 1;i<part_k;i++){ // 最少分成2份 
		dp[i][i] = dp[i-1][i-1] + word_cnt[i][i]; // 将前i个字符分成i份 
	}
	
	for(int i = 0;i<len;i++){
		for(int j = 1;j<part_k && j<i;j++){
			for(int t = j ;t < i;t++){
				dp[i][j] =max(dp[i][j],dp[t][j-1]+word_cnt[t+1][i]);
			}
		}
	}
	cout<<dp[len-1][part_k-1];
	return 0;
}
