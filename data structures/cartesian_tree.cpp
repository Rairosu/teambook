/*
 * Cartesian tree with implicit keys.
 * Operation: min_element on segment.
 *
 * Build complexity: O(NlogN)
 * split/merge complexity: O(logN)
 *
 * Usage:
 *   - initialize root with nullptr
 *   - split(root, x) returns tree with keys <= x
 *
 */


struct Node {
    int val;
    int size, y;
    int min_e, min_i;
    Node *left, *right;
    Node(int val = 0)
            : val(val), size(1), y(rand()),
              min_e(val), min_i(0),
              left(nullptr), right(nullptr) { }
};

int get_size(Node *node) {
    return node != nullptr? node->size : 0;
}

void recalc(Node *node) {
    node->size = get_size(node->left) + get_size(node->right) + 1;
    int mv = node->val;
    int pos = get_size(node->left);
    if (node->left != nullptr) {
        if (mv >= node->left->min_e) {
            mv = node->left->min_e;
            pos = node->left->min_i;
        }
    }
    if (node->right != nullptr) {
        if (mv > node->right->min_e) {
            mv = node->right->min_e;
            pos = get_size(node->left) + 1 + node->right->min_i;
        }
    }
    node->min_e = mv;
    node->min_i = pos;
}

pair<Node*, Node*> split(Node *root, int val) {
    if (root == nullptr)
        return mp(nullptr, nullptr);
    int x = get_size(root->left);
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

