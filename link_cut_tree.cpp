// Path sum version
struct Node{
    array<Node*, 2> child{};
    Node* parent{};
    Node* path_parent{};
    ll sub_sum, vl;
    bool rev = false;
    
    static ll get_sub(Node *nd) {
        if (nd) return nd->sub_sum;
        return 0;
    }
    
    void update() {
        sub_sum = vl+get_sub(child[0])+get_sub(child[1]);
    }
    
    Node(): sub_sum(0), vl(0){}
    Node(ll val): sub_sum(val), vl(val){}
    
    bool side() const {
        return parent->child[1] == this;
    }
    void push() {
        if (rev) {
            swap(child[0], child[1]);
            if (child[0]) child[0]->rev ^= 1;
            if (child[1]) child[1]->rev ^= 1;
            rev = false;
        }
    }
    void push_all() {
        if (parent) parent->push_all();
        push();
    }
    
    void attach(bool side, Node* const new_) {
        if (new_) new_->parent = this;
        child[side] = new_;
    }
    void rotate() {
        const auto p = parent;
        const auto i = side();
        
        if (!p->parent) {
            this->path_parent = p->path_parent;
            p->path_parent = nullptr;
        }
        
        if (p->parent) p->parent->attach(p->side(), this);
        else parent = nullptr;
        p->attach(i, child[!i]);
        attach(!i, p);
        
        p->update();
        this->update();
    }
    void splay() {
        push_all();
        for (; parent; rotate()) {
            if (parent->parent) (side() == parent->side() ? parent : this)->rotate();
        }
        update();
    }
};
Node *make_tree(ll vl) {
    return new Node(vl);
}
void detach_child(Node *node) {
    if (node->child[1]) {
        node->child[1]->path_parent = node;
        node->child[1]->parent = nullptr;
        node->child[1] = nullptr;
        node->update();
    }
}
Node *access(Node *node) {
    node->splay();
    detach_child(node);
    
    Node *par = node;
    while (node->path_parent) {
        par = node->path_parent;
        par->splay();
        detach_child(par);
        par->attach(1, node);
        node->path_parent = nullptr;
        par->update();
        node->splay();
    }
    return par;
}
void evert(Node *node) {
    access(node);
    node->rev ^= 1;
    node->push();
}
void link(Node *u, Node *v) {
    evert(u);
    access(v);
    u->path_parent = v;
}
void cut(Node *u, Node *v) {
    evert(u);
    access(v);
    if (v->child[0] == u && !u->child[1]) {
        v->child[0]->parent = nullptr;
        v->child[0] = nullptr;
        v->update();
    }
}
ll path_sum(Node *u, Node *v) {
    evert(u);
    access(v);
    return v->sub_sum;
}
void change_val(Node *u, ll vl) {
    access(u);
    u->vl = vl;
    u->update();
}

// Subtree sum version
struct Node{
    array<Node*, 2> child{};
    Node* parent{};
    Node* path_parent{};
    ll sub_sum, vl, vir_sum;
    bool rev = false;
    
    static ll get_sub(Node *nd) {
        if (nd) return nd->sub_sum;
        return 0;
    }
    
    void update() {
        sub_sum = get_sub(child[0])+get_sub(child[1])+vir_sum+vl;
    }
    
    Node(): sub_sum(0), vl(0), vir_sum(0){}
    Node(ll val): sub_sum(val), vl(val), vir_sum(0){}
    
    bool side() const {
        return parent->child[1] == this;
    }
    void push() {
        if (rev) {
            swap(child[0], child[1]);
            if (child[0]) child[0]->rev ^= 1;
            if (child[1]) child[1]->rev ^= 1;
            rev = false;
        }
    }
    void push_all() {
        if (parent) parent->push_all();
        push();
    }
    
    void attach(bool side, Node* const new_) {
        if (new_) new_->parent = this;
        child[side] = new_;
    }
    void rotate() {
        const auto p = parent;
        const auto i = side();
        
        if (!p->parent) {
            this->path_parent = p->path_parent;
            p->path_parent = nullptr;
        }
        
        if (p->parent) p->parent->attach(p->side(), this);
        else parent = nullptr;
        p->attach(i, child[!i]);
        attach(!i, p);
        
        p->update();
        this->update();
    }
    void splay() {
        push_all();
        for (; parent; rotate()) {
            if (parent->parent) (side() == parent->side() ? parent : this)->rotate();
        }
        update();
    }
};
Node *make_tree(ll vl) {
    return new Node(vl);
}
void detach_child(Node *node) {
    if (node->child[1]) {
        node->vir_sum += node->child[1]->sub_sum;
        node->child[1]->path_parent = node;
        node->child[1]->parent = nullptr;
        node->child[1] = nullptr;
        node->update();
    }
}
Node *access(Node *node) {
    node->splay();
    detach_child(node);
    
    Node *par = node;
    while (node->path_parent) {
        par = node->path_parent;
        par->splay();
        detach_child(par);
        par->attach(1, node);
        par->vir_sum -= node->sub_sum;
        node->path_parent = nullptr;
        par->update();
        node->splay();
    }
    return par;
}
void evert(Node *node) {
    access(node);
    node->rev ^= 1;
    node->push();
}
void link(Node *u, Node *v) {
    evert(u);
    access(v);
    u->path_parent = v;
    v->vir_sum += u->sub_sum;
    v->update();
}
void cut(Node *u, Node *v) {
    evert(u);
    access(v);
    if (v->child[0] == u && !u->child[1]) {
        v->child[0]->parent = nullptr;
        v->child[0] = nullptr;
        v->update();
    }
}
ll query_subtree(Node *root, Node *u) {
    evert(root);
    access(u);
    return u->vir_sum+u->vl;
}
void change_val(Node *u, ll vl) {
    access(u);
    u->vl = vl;
    u->update();
}