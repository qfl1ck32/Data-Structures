#include <iostream>
#include <fstream>
#include <vector>

std :: ifstream in("abce.in");
std :: ofstream out("abce.out");

class node {
public:
    int key;
    node *left, *right;
};

node *new_node(int key) {
    node *temp = new node;
    temp -> key = key;
    temp -> left = temp -> right = nullptr;
    return temp;
}

node *right_rotate(node *x) {
    node *y = x -> left;
    x -> left = y -> right;
    y -> right = x;
    return y;
}

node *left_rotate(node *x) {
    node *y = x -> right;
    x -> right = y -> left;
    y -> left = x;
    return y;
}

node *splay(node *tree, int key) {

    if (tree == nullptr || tree -> key == key)
        return tree;

    if (tree -> key > key) {

        if (tree -> left == nullptr)
            return tree;

        if (tree -> left -> key > key) {
            tree -> left -> left = splay(tree -> left -> left, key);
            tree = right_rotate(tree);
        }

        else if (tree -> left -> key < key) {
            tree -> left -> right = splay(tree -> left -> right, key);
            if (tree -> left -> right != nullptr)
                tree -> left = left_rotate(tree -> left);
        }

        return (tree -> left == nullptr) ? tree : right_rotate(tree);
    }

    else {

        if (tree -> right == nullptr)
            return tree;

        if (tree -> right -> key > key) {
            tree -> right -> left = splay(tree -> right -> left, key);
            if (tree -> right -> left != nullptr)
                tree -> right = right_rotate(tree -> right);
        }

        else if (tree -> right -> key < key) {
            tree -> right -> right = splay(tree -> right -> right, key);
            tree = left_rotate(tree);
        }

        return (tree -> right == nullptr) ? tree : left_rotate(tree);
    }
}

node *search_key(node *tree, int key) {
    return splay(tree, key);
}

node *insert_key(node *tree, int key) {

    if (tree == nullptr)
        return new_node(key);

    tree = splay(tree, key);

    if (tree -> key == key)
        return tree;

    node *New = new_node(key);

    if (tree -> key > key) {
        New -> right = tree;
        New -> left = tree -> left;
        tree -> left = nullptr;
    }

    else {
        New -> left = tree;
        New -> right = tree -> right;
        tree -> right = nullptr;
    }

    return New;
}

node *delete_key(node *tree, int key) {

    if (tree == nullptr)
        return tree;

    tree = splay(tree, key);

    if (tree -> key != key)
        return tree;

    if (tree -> left == nullptr)
        tree = tree -> right;

    else {
        node *New = tree;
        tree = splay(tree -> left, key);
        tree -> right = New -> right;
        delete New;
    }

    return tree;
}

node *predecessor(node *tree, int key) {

    tree = splay(tree, key);
    node *aux = tree;

    if (aux -> key <= key) {
        return tree;
    }

    if (aux -> left != nullptr)
        aux = aux -> left;

    while (aux -> right != nullptr)
        aux = aux -> right;

    tree = splay(tree, aux -> key);

    return tree;
}

node *successor(node *tree, int key) {

    tree = splay(tree, key);
    node *aux = tree;

    if (aux -> key >= key) {
        return tree;
    }

    if (aux -> right != nullptr)
        aux = aux -> right;

    while (aux -> left != nullptr)
        aux = aux -> left;

    tree = splay(tree, aux -> key);

    return tree;
}

node *range(node *tree, int l, int r, std :: vector <int> *ans) {

    int last, aux;

    tree = splay(tree, l);
    last = tree -> key;
    aux = last + 1;

    while (last <= r && aux != last) {
        aux = last;
        if (last >= l)
            ans -> push_back(last);
        tree = splay(tree, last + 1);
        last = tree -> key;
    }

    return tree;
}

int main() {

    int N, op, a, b;

    node *tree = new node;
    tree = nullptr;

    in >> N;

    while(N--) {

        in >> op;

        switch(op) {

        case 1:
            in >> a;
            tree = insert_key(tree, a);
            break;

        case 2:
            in >> a;
            tree = delete_key(tree, a);
            break;

        case 3:
            in >> a;

            if (tree == nullptr)
                out << 0;

            else {
                tree = search_key(tree, a);
                if (tree -> key == a)
                    out << 1;
                else
                    out << 0;
            }

            if (N)
                out << "\n";

            break;

        case 4:
            in >> a;
            tree = predecessor(tree, a);
            out << tree -> key;
            if (N)
                out <<"\n";
            break;

        case 5:
            in >> a;
            tree = successor(tree, a);
            out << tree -> key;
            if (N)
                out << "\n";
            break;

        case 6:
            in >> a >> b;
            std :: vector <int> *ans = new std :: vector <int>;
            tree = range(tree, a, b, ans);
            for (size_t i = 0; i < ans -> size(); ++i) {
                out << ans -> at(i);
                if (i != ans -> size()- 1)
                    out << " ";
            }
            delete ans;
            if (N)
                out << "\n";
        }
    }

    in.close();
    out.close();

    return 0;
}
