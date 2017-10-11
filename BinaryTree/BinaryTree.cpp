#include <iostream>
using namespace std;

template <class T>
struct BinaryTree {
    T data;
    int weight = 1;
    int repeat = 1;
    BinaryTree *lchild = nullptr;
    BinaryTree *rchild = nullptr;
    
    BinaryTree(T rootData) {
        this->data = rootData;
    }
    
    BinaryTree() {
        
    }
    //先序
    void enumDLRUsingBlock(function<void(T d)> func, BinaryTree *treeNode = nullptr) {
        BinaryTree *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        for (int i = 0; i < tree->repeat; ++i) func(tree->data);
        if (tree->lchild != nullptr) enumDLRUsingBlock(func, tree->lchild);
        if (tree->rchild != nullptr) enumDLRUsingBlock(func, tree->rchild);
    }
    
    //中序
    void enumLDRUsingBlock(function<void(T d)> func, BinaryTree *treeNode = nullptr) {
        BinaryTree *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        if (tree->lchild != nullptr) enumLDRUsingBlock(func, tree->lchild);
        for (int i = 0; i < tree->repeat; ++i) func(tree->data);
        if (tree->rchild != nullptr) enumLDRUsingBlock(func, tree->rchild);
    }
    
    //后序
    void enumLRDUsingBlock(function<void(T d)> func, BinaryTree *treeNode = nullptr) {
        BinaryTree *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        if (tree->lchild != nullptr) enumLRDUsingBlock(func, tree->lchild);
        if (tree->rchild != nullptr) enumLRDUsingBlock(func, tree->rchild);
        for (int i = 0; i < tree->repeat; ++i) func(tree->data);
    }
    
    void insertDataAsOrderBinaryTree(T d, BinaryTree *treeNode = nullptr) {
        BinaryTree *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        if (tree->data > d) {
            if (tree->lchild == nullptr) {
                auto node = new BinaryTree;
                node->data = d;
                tree->lchild = node;
            } else {
                insertDataAsOrderBinaryTree(d, tree->lchild);
            }
        } else if (tree->data < d) {
            if (tree->rchild == nullptr) {
                auto node = new BinaryTree;
                node->data = d;
                tree->rchild = node;
            } else {
                insertDataAsOrderBinaryTree(d, tree->rchild);
            }
        } else {
            tree->repeat++;
        }
    }
    
    BinaryTree& operator<<(T d) {
        insertDataAsOrderBinaryTree(d, this);
        return *this;
    }
    
    ~BinaryTree() {
        if (this->lchild != nullptr) {
            delete this->lchild;
        }
        if (this->rchild != nullptr) {
            delete this->rchild;
        }
    }
};


int main(int argc, char *argv[]) {
    BinaryTree<int> tree;
    tree.data = 5;
    tree<<12<<3<<34<<2<<34<<7<<45<<34<<77<<89;
    
    cout<<"先序:";
    tree.enumDLRUsingBlock([](int data){
        cout<<data<<", ";
    });
    cout<<endl;
    
    cout<<"中序:";
    tree.enumLDRUsingBlock([](int data){
        cout<<data<<", ";
    });
    cout<<endl;
    
    cout<<"后序:";
    tree.enumLRDUsingBlock([](int data){
        cout<<data<<", ";
    });
    cout<<endl;
    
    
    return 0;
}
