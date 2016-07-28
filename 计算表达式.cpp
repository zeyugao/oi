#include<iostream> 
#include<cstring> 
#include<stack> 
#include<string> 
#include<cmath> 
using namespace std; 
char pred[8][8]= 
{	//比较i与j的优先级，i>j返回>
	//优先级相同时，使前面的优先级大于后面的，使其进行计算
	//+/-,*//,^的优先级根据其定义来
	//')'在前面时，不存在这种情况
	//')'在后面时，使其小于所有运算符，直到'('是前面的运算符，保证'('到')'之间的部分全部运算完成
	//'('在前面时，使其小于所有运算符，保证它不参加运算
	//'('在后面时，使其大于所有运算符，使前面的运算符不运算，保持运算准确
	//'#'在后时，说明已到最后一个字符（哨兵），这时，让运算符队列中所有运算符参与运算即可
	//'#'在前时，说明运算符队列已空，压入字符，i++，如果下一个字符不是#，则继续运算，否则，在while那即可终止循环
    {'>','>','<','<','<','<','>','>'}, 
    {'>','>','<','<','<','<','>','>'}, 
    {'>','>','>','>','<','<','>','>'}, 
    {'>','>','>','>','<','<','>','>'}, 
    {'>','>','>','>','>','<','>','>'}, 
    {'<','<','<','<','<','<','=','>'}, 
    {' ',' ',' ',' ',' ',' ',' ',' '}, 
    {'<','<','<','<','<','<','<','='}
}; 
int convert(char ch) 
{ 
    if(ch=='+')return 0; 
    if(ch=='-')return 1; 
    if(ch=='*')return 2; 
    if(ch=='/')return 3; 
    if(ch=='^')return 4; 
    if(ch=='(')return 5; 
    if(ch==')')return 6; 
    if(ch=='#')return 7; 
} 
int calculate(int num1,int num2,char ch) 
{ 
    if(ch=='+')return num1+num2; 
    if(ch=='-')return num1-num2; 
    if(ch=='*')return num1*num2; 
    if(ch=='/')return num1/num2; 
    if(ch=='^')return (int)pow((double)num1,(double)num2); 
} 
string str; 
stack<int> num; 
stack<char> op; 
int l,sum=0,i=0,kh=0; 
int main() 
{ 
    cin>>str; 
    l=str.length(); 
    for(int aa=0;aa<=l-1;aa++)
        if(str[aa]=='(')kh++;
        else if(str[aa]==')')kh--;
    while(kh>0)
    {
        str+=")";
        kh--;
    }
    while(kh<0)
    {
        str="("+str;
        kh++;
    }
	//结束标准符
    str=str+"#";op.push('#');
    num.push(0); 
    while ((str[i]!='#')||(op.top()!='#')) 
    { 
        if(str[i]>='0'&&str[i]<='9') 
        { 
            int j=0; 
            do
            { 
                j*=10;j+=int(str[i]-'0'); 
                i++; 
            } 
            while(str[i]>='0'&&str[i]<='9'); 
            num.push(j); 
        } 
        else
        {
            char c=pred[convert(op.top())][convert(str[i])]; 
			//如果当前运算符的优先级比前一个高，则前一个运算符不能进行计算，如1+3*4
            if(c=='<'){op.push(str[i]);i++;} 
			//如果当前运算符的优先级比前一个低，则前一个运算符能进行计算，如1*3+1
            else if(c=='>') 
            {
                int num2=num.top();num.pop(); 
                int num1=num.top();num.pop(); 
                char ch=op.top();op.pop(); 
                num.push(calculate(num1,num2,ch));
				//这里不进行i++，是为了在进行计算后，查看再前面的有没有符合这种情况的，有的话，继续进行计算，知道前一个运算符的优先级不比其大
            }
			//取'='只有在pred['('][')']或pred['#']['#']时取到
			//第一种情况，即把'()'去掉，让里面的结果出来
			//第二种情况，不可能存在，while的判断语句使其不可能
            else if(c=='='){op.pop();i++;}  
        } 
    } 
    cout<<num.top()<<endl; 
    return 0; 
}