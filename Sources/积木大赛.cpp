#include <set>
#include <iostream>
using namespace std;

int main(){
	int i,t;
	cin>>i;
	set<int> aaa;
	while(i--){
		cin>>t;
		aaa.insert(t);
	}
	for(set<int>::iterator i =aaa.begin();i!=aaa.end();i++){
		cout<<*i<<endl;
	}
	return 0;
}
