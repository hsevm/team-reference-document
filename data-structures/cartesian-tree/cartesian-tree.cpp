struct Node {
  int x, y, sz = 1;
  Node *l = nullptr;
  Node *r = nullptr;
  Node(int x) : x(x), y(rand()) {}
};

int get_sz(Node *root) { 
  return (root == nullptr ? 0 : root->sz);
}

void update(Node *root) {
  root->sz = 1 + get_sz(root->l) + get_sz(root->r);
}

pair<Node *, Node *> split(Node *&root, int x) {
  if (!root) {
    return {nullptr, nullptr};
  }
  if (root->x < x) {
    auto t = split(root->r, x);
    root->r = t.first;
    update(root);
    return {root, t.second};
  }
  auto t = split(root->l, x);
  root->l = t.second;
  update(root);
  return {t.first, root};
}

Node *mergeTree(Node *a, Node *b) {
  if (!a || !b)
    return a ? a : b;
  if (a->y < b->y) {
    a->r = mergeTree(a->r, b);
    update(a);
    return a;
  }
  b->l = mergeTree(a, b->l);
  update(b);
  return b;
}

void ins(Node *&root, int x) {
  Node *nn = new Node(x);
  auto a = split(root, x);
  root = mergeTree(mergeTree(a.first, nn), a.second);
}

void del(Node *&root, int x) {
  auto a = split(root, x + 1);
  auto b = split(a.first, x);
  root = mergeTree(b.first, a.second);
}