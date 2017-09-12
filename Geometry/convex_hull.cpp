#include <bits/stdc++.h>

#define ll long long

using namespace std;

struct pt {
    int x, y;
    pt(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const pt& p) const {
        if (x == p.x)
            return y < p.y;
        return x < p.x;
    }
    double len() {
        return sqrt(x * x + y * y);
    }
};

ll area(pt a, pt b, pt c) {
    return (b.x - a.x) * 1ll * (c.y - a.y) - (b.y - a.y) * 1ll * (c.x - a.x);
}


int main() {
#ifdef __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    scanf("%d", &n);
    vector<pt> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i].x, &a[i].y);
    }
    sort(a.begin(), a.end());
    if (n < 3) {
        printf("0");
        return 0;
    }
    pt f = a[0], s = a.back();
    vector<pt> top, bottom;
    top.push_back(f);
    bottom.push_back(f);
    for (int i = 1; i < a.size(); ++i) {
        if (i + 1 == a.size() || area(f, a[i], s) > 0) {
            while (top.size() >= 2 && area(top[top.size() - 2], top[top.size() - 1], a[i]) <= 0)
                top.pop_back();
            top.push_back(a[i]);
        }
        if (i + 1 == a.size() || area(f, a[i], s) < 0) {
            while (bottom.size() >= 2 &&
                   area(bottom[bottom.size() - 2], bottom[bottom.size() - 1], a[i]) >= 0)
                bottom.pop_back();
            bottom.push_back(a[i]);
        }
    }
    a.clear();
    for (int i = 0; i < top.size(); ++i)
        a.push_back(top[i]);
    for (int i = static_cast<int>(bottom.size()) - 2; i > 0; --i)
        a.push_back(bottom[i]);


    double ans = 1000;
    for (int i = 0; i < a.size(); ++i) {
        int nxt = (i + 1) % a.size();
        int prev = (i - 1 + a.size()) % a.size();
        pt u(a[prev].x - a[i].x, a[prev].y - a[i].y);
        pt v(a[nxt].x - a[i].x, a[nxt].y - a[i].y);
        ll p = u.x * 1ll * v.y - u.y * 1ll * v.x;
        ll q = u.x * 1ll * v.x + u.y * 1ll * v.y;
        double ang = atan2(p, q);
        ans = min(ans, fabs(ang));
    }
    ans *= 180.0 / acos(-1);
    printf("%.7lf", ans);
    return 0;
}

