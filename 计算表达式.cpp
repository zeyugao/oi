#include<iostream> 
#include<cstring> 
#include<stack> 
#include<string> 
#include<cmath> 
using namespace std; 
char pred[8][8]= 
{ //比较i 与j的优先级，i>j返回>
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
            if(c=='<'){op.push(str[i]);i++;} 
            else if(c=='>') 
            { 
                int num2=num.top();num.pop(); 
                int num1=num.top();num.pop(); 
                char ch=op.top();op.pop(); 
                num.push(calculate(num1,num2,ch)); 
            } 
            else if(c=='='){op.pop();i++;}  
        } 
    } 
    cout<<num.top()<<endl; 
    return 0; 
}