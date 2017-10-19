#include <iostream>
#include <stdlib.h>

using namespace std;
template <class T>
struct AVLBinaryTreeNode {
    T data;
    int repeat = 1;
    
    AVLBinaryTreeNode<T> *lchild;
    AVLBinaryTreeNode<T> *rchild;
    AVLBinaryTreeNode<T> *parents;

    AVLBinaryTreeNode(T data) {
        this->data = data;
    }
    
    AVLBinaryTreeNode() {
        
    }
    
    ~AVLBinaryTreeNode() {
        if (this->lchild != nullptr) {
            delete this->lchild;
            this->lchild = nullptr;
        }
        
        if (this->rchild != nullptr) {
            delete this->rchild;
            this->rchild = nullptr;
        }
    }
    int getHeight() {
        return this->_getHeight(this);
    }
    
    int getBalanceFactor() {
        return this->_getBalanceFactor(this);
    }
    
    void makeBalance() {
        this->_makeBalance(this);
    }
    
    void rotationL(AVLBinaryTreeNode<T> *treeNode) {
        //        auto newRootNode = treeNode->rchild;
        //        auto oldRootNode = treeNode;
        //
        //        newRootNode->lchild = oldRootNode;
        //        oldRootNode->rchild = oldRootNode->rchild->lchild;
        cout<<"L"<<endl;
    }

    void rotationR(AVLBinaryTreeNode<T> *treeNode) {
        //        auto oldRootNode = treeNode;
        //
        //        treeNode->data = treeNode->lchild->data;
        //        treeNode->lchild = treeNode->lchild->lchild;
        //        treeNode->rchild = treeNode->lchild->rchild;
        //        treeNode->parents = treeNode->lchild->parents;
        //        treeNode->repeat = treeNode->lchild->repeat;
        //
        //
        //
        //        newRootNode->rchild = oldRootNode;
        //        oldRootNode->lchild = oldRootNode->lchild->rchild;
        cout<<"R"<<endl;
    }

    
private:
    int _getHeight(AVLBinaryTreeNode<T> *treeNode = nullptr) {
        int lresult = 0, rresult = 0;
        if (treeNode == nullptr) {
            return 0;
        }
        lresult = treeNode->lchild->getHeight();
        rresult = treeNode->rchild->getHeight();
        return (lresult >= rresult ? lresult : rresult) + 1;
    }
    
    int _getBalanceFactor (AVLBinaryTreeNode<T> *treeNode = nullptr) {
        int left = 0;
        int right = 0;
        
        treeNode->lchild == nullptr ? left = 0 : left = treeNode->lchild->getHeight();
        treeNode->rchild == nullptr ? left = 0 : right = treeNode->rchild->getHeight();
        
        return left - right;
    }
    
    void _makeBalance(AVLBinaryTreeNode<T> *treeNode) {
        //判断旋转类型
        int treeNodeBf = treeNode->getBalanceFactor();
        if (treeNodeBf > 0) {
            //L-
            int lchildNodeBf = treeNode->lchild->getBalanceFactor();
            if (lchildNodeBf > 0) {
                //L-L
                rotationR(treeNode);
            } else {
                //L-R
                rotationL(treeNode->lchild);
                rotationR(treeNode);
            }
        } else {
            //R-
            int rchildNodeBf = treeNode->rchild->getBalanceFactor();
            if (rchildNodeBf < 0) {
                //R-R
                rotationL(treeNode);
            } else {
                //R-L
                rotationR(treeNode->rchild);
                rotationL(treeNode->lchild);
            }
        }
    }

};

template <class T>
struct AVLBinaryTree {
    AVLBinaryTreeNode<T> *root;
    
    int getHeight() {
        return this->root->getHeight();
    }
    
    int getBalanceFactor() {
        return this->root->getBalanceFactor();
    }
    
    void makeBalance() {
        return this->root->makeBalance();
    }
    void insertData(T data) {
        this->_insertData(data, this->root);
    }
    
    AVLBinaryTree& operator<<(T d) {
        this->_insertData(d, this->root);
        return *this;
    }
    
private:
    void _insertData(T data, AVLBinaryTreeNode<T> *treeNode = nullptr) {
        if (this->root == nullptr) {
            auto newNode = new AVLBinaryTreeNode<T>(data);
            this->root = newNode;
        } else {
            if (treeNode->data > data) {
                if (treeNode->lchild == nullptr) {
                    auto newNode = new AVLBinaryTreeNode<T>;
                    newNode->data = data;
                    newNode->parents = treeNode;
                    treeNode->lchild = newNode;
                    
                    auto bf = this->getBalanceFactor();
                    if (abs(bf) > 1) {
                        this->makeBalance();
                    }
                } else {
                    _insertData(data, treeNode->lchild);
                }
            } else if (treeNode->data < data) {
                if (treeNode->rchild == nullptr) {
                    auto node = new AVLBinaryTreeNode<T>;
                    node->data = data;
                    node->parents = treeNode;
                    treeNode->rchild = node;
                    
                    auto bf = this->getBalanceFactor();
                    if (abs(bf) > 1) {
                        this->makeBalance();
                    }
                } else {
                    _insertData(data, treeNode->rchild);
                }
            } else {
                treeNode->repeat++;
            }
        }
    }
};

