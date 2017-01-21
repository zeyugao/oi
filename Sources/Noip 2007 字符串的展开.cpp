#include <string>
#include <iostream>
using namespace std;
string s;
int p1,p2,p3;
void print(char c){
	for(int i =0;i<p2;i++){
		cout<<c;
	}
}
void print(char s,char e){
	if(p3==1)
		for(char i = s+1;i<e;i++)
			print(i);
		
	if(p3==2)
		for(char i =e-1;i>s;i--)
			print(i); 
}
//不理解“与要填充的字母个数相同的星号“*”来填充”就没有用这个函数，就WA了
void print(int x){
    for(int i =1;i<=x;i++) print('*');
}
void extend(int x){
  //开头的以及结尾的不需要转换
	if(x == 0||x >= s.length()-1){cout<<'-';return;}
	
  
	char c1 = s[x-1], c2 = s[x+1];
	bool isbothalpha = (isalpha(c1)&&isalpha(c2));
	bool isbothdigit = (isdigit(c1)&&isdigit(c2));
  //如果是数字-字母/字母-数字的形式也不用转换
	if(!isbothalpha&&!isbothdigit) {cout<<'-';return;} 
	
	if(c1>=c2)
	{cout<<'-';return;}
	if(isbothalpha){
		if(p1 == 1) 
		 	print(c1,c2);
		else if(p1 ==2)
			print(c1 + 'A'-'a',c2 + 'A'-'a');
		else if(p1==3)
			print(c2-c1-1);
	}
	else{
		if(p1==3)print(c2-c1-1);
		else if(p1==1||p1==2)print(c1,c2); 
	}
}
int main(){
	cin >> p1 >> p2 >> p3 >> s;
	
	for(int i =0;i<s.length();i++){
		if(s[i]=='-'){
			extend(i);
		}
		else{
			cout<<s[i];
		}
	} 
	return 0;
}
