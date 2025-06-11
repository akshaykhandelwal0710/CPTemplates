struct Data {
    char val;
    int rev;
 
    Data() {
        val = 'a';
        rev = 0;
    }
};
 
struct treap{
    Data val;
    treap *left, *right;
    int weight, size;
 
    treap(Data &vl) {
        size = 1;
        weight = rand();
        left = right = nullptr;
        val = vl;
    }
 
    void push_down() {
        if (val.rev) {
            swap(left, right);
            val.rev = 0;
            if (left != nullptr) left->val.rev ^= 1;
            if (right != nullptr) right->val.rev ^= 1;
        }
    }
 
    void update() {
        size = get_size(left) + get_size(right) + 1;
    }
 
    static int get_size(treap *node) {
        return (node == nullptr ? 0 : node->size);
    }
 
    static void split(treap *node, treap *&left, treap *&right, int l_size) {
        if (node == nullptr) {
            left = right = nullptr;
            return;
        }
        node->push_down();
 
        if (get_size(node->left) < l_size) {
            split(node->right, node->right, right, l_size - 1 - get_size(node->left));
            left = node;
        }
        else {
            split(node->left, left, node->left, l_size);
            right = node;
        }
 
        node->update();
    }
 
    static void merge(treap *&node, treap *left, treap *right) {
        if (left == nullptr) {
            node = right;
            return;
        }
        if (right == nullptr) {
            node = left;
            return;
        }
        left->push_down();
        right->push_down();
 
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            node = left;
        }
        else {
            merge(right->left, left, right->left);
            node = right;
        }
        node->update();
    }
};
 
ostream &operator<<(ostream &os, treap *n) {
    if (n == nullptr) return os;
    n->push_down();
    os << n->left;
    os << n->val.val;
    os << n->right;
    return os;
}
