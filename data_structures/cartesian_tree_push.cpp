/*
 * Cartesian tree with implicit keys and lazy propagation.
 * Operations: insert, add on segment, sum on segment, left-right traversal.
 *
 * Build complexity: O(NlogN)
 * queries complexity: O(logN)
 *
 */

#define ll long long

struct Node {
    ll push, sum;
    ll val;
    ll size, y;
    Node *left, *right;
    Node(ll val = 0)
            : val(val), size(1), y(rand()),
              push(-1), sum(val),
              left(nullptr), right(nullptr) { }
};


ll get_push(Node *node) {
    return node != nullptr? node->push : -1;
}

ll get_size(Node *node) {
    return node != nullptr? node->size : 0;
}

ll get_sum(Node *node) {
    return node != nullptr? node->sum : 0;
}

void push(Node *v) {
    if (v == nullptr || v->push == -1)
        return;
    if (v->left)
        v->left->push = v->push;
    if (v->right)
        v->right->push = v->push;
    v->val = v->push;
    v->sum = v->push * v->size;
    v->push = -1;
}

void recalc(Node *node) {
    node->size = get_size(node->left) + get_size(node->right) + 1;
    if (node->push != -1)
        node->sum = node->push * node->size;
    else {
        ll left_sum, right_sum;
        if (get_push(node->left) != -1)
            left_sum = get_push(node->left) * get_size(node->left);
        else left_sum = get_sum(node->left);
        if (get_push(node->right) != -1)
            right_sum = get_push(node->right) * get_size(node->right);
        else right_sum = get_sum(node->right);
        node->sum = left_sum + right_sum + node->val;
    }
}

pair<Node*, Node*> split(Node *root, ll val) {
    push(root);
    if (root == nullptr)
        return mp(nullptr, nullptr);
    ll x = get_size(root->left);
    if (x <= val) {
        pair<Node*, Node*> splitted = split(root->right, val - x - 1);
        root->right = splitted.first;
        recalc(root);
        return mp(root, splitted.second);
    } else {
        pair<Node*, Node*> splitted = split(root->left, val);
        root->left = splitted.second;
        recalc(root);
        return mp(splitted.first, root);
    }
}

Node* merge(Node *left, Node *right) {
    push(left);
    push(right);
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    if (left->y > right->y) {
        left->right = merge(left->right, right);
        recalc(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        recalc(right);
        return right;
    }
}

void insert(Node *&root, ll pos, ll val) {
    pair<Node*, Node*> splitted = split(root, pos - 1);
    root = merge(merge(splitted.first, new Node(val)), splitted.second);
}

void update(Node *&root, ll l, ll r, ll add) {
    pair<Node*, Node*> splitted = split(root, l - 1);
    pair<Node*, Node*> splitted2 = split(splitted.second, r - l);
    splitted2.first->push = add;
    root = merge(splitted.first, merge(splitted2.first, splitted2.second));
}

ll get(Node *&root, ll l, ll r) {
    pair<Node*, Node*> splitted = split(root, l - 1);
    pair<Node*, Node*> splitted2 = split(splitted.second, r - l);
    ll res = splitted2.first->sum;
    root = merge(splitted.first, merge(splitted2.first, splitted2.second));
    return res;
}

vector<ll> all;

void get_all(Node *root) {
    if (root == nullptr)
        return;
    get_all(root->left);
    all.push_back(root->val);
    get_all(root->right);
}

