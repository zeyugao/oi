#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    int num[1001] = { 0 };
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    sort(num,num+n);
    int n_bak = n;
    int last = num[0];
    for (int i = 1; i < n_bak; i++) {
        if (num[i] == last)
            num[i] = -1,n--;
        else
            last = num[i];
    }
    cout << n<<endl;
    for (int i = 0; i < n_bak; i++) {
        if (num[i] != -1)
            cout << num[i] << " ";
    }

    return 0;
}