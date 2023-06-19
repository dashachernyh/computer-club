#include <iostream>
#include <fstream>
#include<string>

template<class T>
class Node
{
public:
    T value;
    int table;
    Node* left;
    Node* right;

    Node(T val, int t = -1) {
        left = nullptr;
        right = nullptr;
        value = val;
        table = t;
    }
};

template<class T>
std::ostream& operator << (std::ostream& out, Node<T>* n) {
    if (n != nullptr)
        out << n->value;
    return out;
}

template<class T>
class BinTree
{
private:
    Node<T>* root;
    int size;
    void print_tree(std::string& file_name, std::string& time, Node<T>*);
    void delete_tree(Node<T>*);

public:
    BinTree() {
        root = nullptr;
        size = 0;
    }
    BinTree(T value) {
        root = new Node<T>(value);
        size = 1;
    }
    ~BinTree();
    void print(std::string& file_name, std::string& time);
    Node<T>* find(T val);
    void insert(T val);
    void erase(T val);
    int getsize() {
        return size;
    }
};

template<class T>
BinTree<T>::~BinTree()
{
    delete_tree(root);
}

template<class T>
void BinTree<T>::delete_tree(Node<T>* curr)
{
    if (curr)
    {
        delete_tree(curr->left);
        delete_tree(curr->right);
        delete curr;
    }
}

template<class T>
void BinTree<T>::print(std::string& file_name, std::string& time)
{
    print_tree(file_name, time, root);
}

template<class T>
void BinTree<T>::print_tree(std::string& file_name, std::string& time, Node<T>* curr)
{
    if (curr)
    {
        print_tree(file_name, time, curr->left);
        std::ofstream out(file_name.c_str(), std::ios::app);
        std::cout <<time <<" 11 "<< curr->value << "\n";
        out << time << " 11 " << curr->value << "\n";
        out.close();
        print_tree(file_name, time, curr->right);
    }
}

template<class T>
Node<T>* BinTree<T>::find(T val)
{
    Node<T>* curr = root;
    while (curr && curr->value != val)
    {
        if (curr->value > val)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr;
}

template<class T>
void BinTree<T>::insert(T val)
{
    if (root == nullptr) {
        root = new Node<T>(val);
        root->right = nullptr;
        root->left = nullptr;
        ++size;
    }
    else {
        Node<T>* curr = root;
        while (curr && curr->value != val)
        {
            if (curr->value > val && curr->left == nullptr)
            {
                curr->left = new Node<T>(val);
                ++size;
                return;
            }
            if (curr->value < val && curr->right == nullptr)
            {
                curr->right = new Node<T>(val);
                ++size;
                return;
            }
            if (curr->value > val)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }
}

template<class T>
void BinTree<T>::erase(T val)
{
    Node<T>* curr = root;
    Node<T>* parent = nullptr;
    while (curr && curr->value != val)
    {
        parent = curr;
        if (curr->value > val)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (!curr)
        return;
    if (curr->left == nullptr)
    {
        if (parent && parent->left == curr)
            parent->left = curr->right;
        else if (parent && parent->right == curr)
            parent->right = curr->right;
        else if (curr == root && root->right != nullptr) {
            root = root->right;
        }
        --size;
        delete curr;
        return;
    }
    if (curr->right == nullptr)
    {
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        else if (curr == root && root->left != nullptr) {
            root = root->left;
        }
        --size;
        delete curr;
        return;
    }

    Node<T>* replace = curr->right;
    while (replace->left)
        replace = replace->left;
    T replace_value = replace->value;
    erase(replace_value);
    curr->value = replace_value;
}
