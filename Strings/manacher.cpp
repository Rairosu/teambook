#include <bits/stdc++.h>

using namespace std;

int main() {

    string s;
    cin >> s;
    int n = s.size();
    
    vector<int> d1(n), d2(n);
    int l = -1, r = -1;
    for(int i = 0; i < n; i++){
        int k = i > r? 1 : min(d1[l + r - i], r - i); 
        
        while(0 <= i - k && i + k < n && s[i - k] == s[i + k])
            k++;
        d1[i] = k;
        if(i + k - 1 > r) {
            r = i + k - 1;
            l = i - k + 1;
        }
    }
    for(int i = 0; i < n; i++){
        int k = i > r? 0 : min(d2[l + r - i + 1], r - i + 1);

        while(0 <= i - k - 1 && i + k < n && s[i + k] == s[i - k - 1])
            k++;
        d2[i] = k;
        if(i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }

    return 0;
}
