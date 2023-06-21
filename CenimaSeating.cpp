#include<bits/stdc++.h>
using namespace std;
#define int long long
#define el '\n'
map<int, int> mp;

void Solve(){
    int n, k, l, r; cin >> n >> k;
    mp[n] = 1;
    while(k > 0){
        auto it = prev(mp.end());
        int sz = it -> first, cnt = it -> second;
        mp.erase(it);

        l = sz / 2, r = (sz - 1) / 2;
        mp[l] += cnt;
        mp[r] += cnt;
        k -= cnt;
    }
    cout << l << ' ' << r << el;
    mp.clear();
}
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("inp.txt", "r", stdin);freopen("out.txt", "w", stdout);
    #endif
    int t = 1; cin >> t;
    while(t--) Solve();
}