#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int inf = 1e9;


struct Node {
    ll val, sum, f;
    Node *left, *right;
    Node(ll val = 0) : val(val), sum(0), f(val), left(nullptr), right(nullptr) {}
    Node(const Node& v) : val(v.val), sum(v.sum), f(v.f), left(v.left), right(v.right) {}
};

ll get_sum(Node *node) {
    return node? node->sum : 0;
}

ll get_f(Node *node) {
    return node? node->f : 0;
}

Node* update(Node *v, ll tl, ll tr, ll pos, ll val) {
    Node *u = v? new Node(*v) : new Node();
    if (tl == tr) {
        u->sum = 1;
        u->val = val;
        u->f = val;
        return u;
    }
    ll tm = (tl + tr) / 2;
    if (pos <= tm)
        u->left = update(u->left, tl, tm, pos, val);
    else
        u->right = update(u->right, tm + 1, tr, pos, val);
    u->sum = get_sum(u->left) + get_sum(u->right);
    u->f = get_f(u->left) + get_f(u->right);
    return u;
}

ll query1(Node *a, Node *b, ll tl, ll tr, ll k, ll left = 0) {
    if (tl == tr)
        return b->val;
    ll tm = (tl + tr) / 2;
    ll addl = get_sum(b? b->left : nullptr) - get_sum(a? a->left : nullptr);
    if (left + addl >= k)
        return query1(a? a->left : nullptr, b? b->left : nullptr, tl, tm, k, left);
    else
        return query1(a? a->right : nullptr, b? b->right : nullptr, tm + 1, tr, k, left + addl);
}


ll query2(Node *v, ll tl, ll tr, ll l, ll r) {
    if (v == nullptr)
        return 0;
    if (l > r)
        return 0;
    if (tl == l && tr == r)
        return v->f;
    ll tm = (tl + tr) / 2;
    return query2(v->left, tl, tm, l, min(r, tm)) +
           query2(v->right, tm + 1, tr, max(l, tm + 1), r);
}


void solve() {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    vector<Node*> roots;
    roots.push_back(new Node());
    vector<ll> a(n);
    ll maxx = 0;
    for (ll i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
        maxx = max(maxx, a[i]);
    }
    for (ll i = 0; i < n; ++i)
        roots.push_back(update(roots.back(), 0, maxx, a[i], a[i]));
    for (ll i = 0; i < m; ++i) {
        ll l, r;
        scanf("%lld %lld", &l, &r);
        ll sz = r - l + 1;
        ll tp = floor(1.0 * sz / 10.0);
        --l;
        ll md = query1(roots[l], roots[r], 0, maxx, sz / 2 + 1);
        ll left = tp? query1(roots[l], roots[r], 0, maxx, tp + 1) : 0;
        ll right = tp? query1(roots[l], roots[r], 0, maxx, sz - tp) : maxx;
        ll sum = query2(roots[r], 0, maxx, left, right) -
                  query2(roots[l], 0, maxx, left, right);
        ll md2 = floor(1.0 * sum / (1.0 * sz - 2 * tp));
        printf("%lld\n", abs(md - md2));
    }
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    clock_t start = clock();
#else
    // freopen(TASKNAME".in", "r", stdin);
    // freopen(TASKNAME".out", "w", stdout);
#endif
    srand(time(NULL));

    solve();

    return 0;
}

