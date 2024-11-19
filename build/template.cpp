#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef pair<i32, i32> pi32;
typedef pair<u32, u32> pu32;
typedef pair<i64, i64> pi64;
typedef pair<u64, u64> pu64;
typedef vector<i32> vi32;
typedef vector<u32> vu32;
typedef vector<i64> vi64;
typedef vector<u64> vu64;


/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)

/* UTILS */
const i32 MOD = 1000000007;
const i32 INF = 1000000050;
const i64 BIG = (i64)2e18 + 50;
const i32 MX = 200010;
const double EPS = 1e-9;
#define PI 3.1415926535897932384626433832795
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(i64 a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }


#ifdef LOCAL
		#define dbg(x) cout << #x << " : " << x << endl;
#else
		#define dbg(x)
#endif
#define pb push_back
#define eb emplace_back
#define ppb pop_back()
#define mp make_pair
#define siz(x) (int)x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(a) (int)a.size()
#define fi first
#define se second
#define cinv(v) for (auto& x: v) cin >> x
template<typename T1, typename T2>inline void mine(T1 &x, T2 y) { if (y < x) x = y; }
template<typename T1, typename T2>inline void maxe(T1 &x, T2 y) { if (x < y) x = y; }
template <typename T1, typename T2> inline bool chkmin(T1 &x, const T2 &y) {if (x > y) {x = y; return 1;} return 0;}
template <typename T1, typename T2> inline bool chkmax(T1 &x, const T2 &y) {if (x < y) {x = y; return 1;} return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef string str;
typedef pair<i32, i32> pii;
typedef vector<i32> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<char> vch;
typedef vector<str> vs;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
ostream& operator<< (ostream& out, const pair<T, T>& b) {
		out << "{" << b.first << ", " << b.second << "}";
		return out;
}
template <typename T>
ostream& operator<< (ostream &out, const vector<T> &b) {
		for (auto k : b) out << k << " ";
		return out;
}
template <typename T>
istream& operator>> (istream& in, pair<T, T>& b) {
		in >> b.first >> b.second;
		return in;
}

i32 main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	i32 n;
	vector<pair<i64, i64>> pairs;
	cin >> n;
	while(n--){
		i64 a,b;
		cin >> a >> b;
		pairs.push_back(pair(a,b));
	}
	cout << pairs << endl;
	return 0;
}
