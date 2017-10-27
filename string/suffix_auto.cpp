/*
 *  This file contains Suffix automation.
 *
 *  Requirements: "string", "map"
 */

struct State{
    int len;
    int link;
    int endpos;
    int cnt = 0;
    map<char, int> next;
};

State st[2 * N - 1];

string s;

bool cmp(int a, int b)  {
    return st[a].len > st[b].len;
}

void build(){
    int n = s.size();
    st[0].link = -1;
    st[0].endpos = -1;
    int last = 0;
    int size = 1;
    for(int i = 0; i < n; i++){
        char c = s[i];
        int cur = size++;
        st[cur].cnt = 1;
        st[cur].len = st[last].len + 1;
        int p;
        for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = (st[p].next.count(c) > 0 ? st[p].next[c] : -1);
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = size++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for (; p!=-1 && (st[p].next.count(c) ? st[p].next[c] == q : false); p=st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    vector<int> ord(size);
    for (int i = 0; i < size; ++i) {
        ord[i] = i;
    }
    sort(ord.begin(), ord.end(), cmp);
    for (auto i : ord) {
        if (st[i].link > 0)
            st[st[i].link].cnt += st[i].cnt;
    }
}

