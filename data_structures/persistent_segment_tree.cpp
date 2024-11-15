/*
 *
 * Persistent segment tree.
 *
 * Complexity: O(logN).
 *
 * Usage:
 *   - Init: Create array of roots and place empty Node()
 *   - Update: roots.push_back(update(roots.back(), ...))
 *   - Get: get(roots[r], ...) - get(roots[l - 1], ...)
 *
 */


struct Node {
    int val, sum;
    Node *left, *right;
    Node(int val = 0) : val(val), sum(0), left(nullptr), right(nullptr) {}
    Node(const Node& v) : val(v.val), sum(v.sum), left(v.left), right(v.right) {}
};

int get_sum(Node *node) {
    return node? node->sum : 0;
}

Node* update(Node *v, int tl, int tr, int pos, int val) {
    Node *u = v? new Node(*v) : new Node();
    if (tl == tr) {
        u->sum = val;
        u->val = val;
        return u;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        u->left = update(u->left, tl, tm, pos, val);
    else
        u->right = update(u->right, tm + 1, tr, pos, val);
    u->sum = get_sum(u->left) + get_sum(u->right);
    return u;
}


int get(Node *v, int tl, int tr, int l, int r) {
    if (v == nullptr)
        return 0;
    if (l > r)
        return 0;
    if (tl == l && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get(v->left, tl, tm, l, min(r, tm)) +
           get(v->right, tm + 1, tr, max(l, tm + 1), r);
}

