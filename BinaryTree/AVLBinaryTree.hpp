#include <iostream>
#include <stdlib.h>

using namespace std;
template <class T>
struct AVLBinaryTreeNode {
    T data;
    int repeat = 1;
    
    AVLBinaryTreeNode<T> *lchild = nullptr;
    AVLBinaryTreeNode<T> *rchild = nullptr;
    AVLBinaryTreeNode<T> *parents = nullptr;

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
    
    AVLBinaryTreeNode<T> *getUnbalanceNode() {
        return this->_getUnbalanceNode(this);
    }
    
private:
    int _getHeight(AVLBinaryTreeNode<T> *treeNode) {
        int lresult = 0, rresult = 0;
        if (treeNode == nullptr) {
            return 0;
        }
        lresult = treeNode->lchild->getHeight();
        rresult = treeNode->rchild->getHeight();
        return (lresult >= rresult ? lresult : rresult) + 1;
    }
    
    int _getBalanceFactor (AVLBinaryTreeNode<T> *treeNode) {
        int left = 0;
        int right = 0;
        
        treeNode->lchild == nullptr ? left = 0 : left = treeNode->lchild->getHeight();
        treeNode->rchild == nullptr ? right = 0 : right = treeNode->rchild->getHeight();
        
        return left - right;
    }
    
    AVLBinaryTreeNode<T> *_getUnbalanceNode(AVLBinaryTreeNode<T> *node) {
        if (node == nullptr) {
            return nullptr;
        }
        auto bf = node->getBalanceFactor();
        if (abs(bf) > 1) {
            return node;
        }
        return _getUnbalanceNode(node->parents);
    }
};

template <class T>
struct AVLBinaryTree {
    AVLBinaryTreeNode<T> *root = nullptr;
    
    int getHeight() {
        return this->root->getHeight();
    }
    
    int getBalanceFactor() {
        return this->root->getBalanceFactor();
    }
    
    void makeBalance(AVLBinaryTreeNode<T> *node) {
        //判断旋转类型
        int nodeBf = node->getBalanceFactor();
        if (nodeBf > 0) {
            //L-
            int lchildNodeBf = node->lchild->getBalanceFactor();
            if (lchildNodeBf > 0) {
                //L-L
                rotationL(node);
            } else {
                //L-R
                rotationR(node->lchild);
                rotationL(node);
            }
        } else {
            //R-
            int rchildNodeBf = node->rchild->getBalanceFactor();
            if (rchildNodeBf < 0) {
                //R-R
                rotationR(node);
            } else {
                //R-L
                rotationL(node->rchild);
                rotationR(node);
            }
        }
    }
    
    void rotationL(AVLBinaryTreeNode<T> *node) {
        if (node->parents == nullptr) {
            //node is root
            this->root = node->lchild;
            node->lchild = node->lchild->rchild;
            this->root->rchild = node;
            this->root->parents = nullptr;
            node->parents = this->root;
        } else {
            if (node->parents->lchild == node) {
                node->parents->lchild = node->lchild;
            } else {
                node->parents->rchild = node->lchild;
            }
            node->lchild->parents = node->parents;
            node->lchild->rchild = node;
            node->parents = node->lchild;
            node->lchild = nullptr;
        }
    }
    
    void rotationR(AVLBinaryTreeNode<T> *node) {
        if (node->parents == nullptr) {
            //node is root
            this->root = node->rchild;
            node->rchild = node->rchild->lchild;
            this->root->lchild = node;
            this->root->parents = nullptr;
            node->parents = this->root;
        } else {
            if (node->parents->lchild == node) {
                node->parents->lchild = node->rchild;
            } else {
                node->parents->rchild = node->rchild;
            }
            node->rchild->parents = node->parents;
            node->rchild->lchild = node;
            node->parents = node->rchild;
            node->rchild = nullptr;
        }
    }
    
    void insertData(T data) {
        this->_insertData(data, this->root);
    }
    
    AVLBinaryTree& operator<<(T d) {
        this->_insertData(d, this->root);
        return *this;
    }
    
private:
    void _insertData(T data, AVLBinaryTreeNode<T> *treeNode) {
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
                    
                    auto unbalanceNode = newNode->getUnbalanceNode();
                    if (unbalanceNode != nullptr) {
                        this->makeBalance(unbalanceNode);
                    }
                } else {
                    _insertData(data, treeNode->lchild);
                }
            } else if (treeNode->data < data) {
                if (treeNode->rchild == nullptr) {
                    auto newNode = new AVLBinaryTreeNode<T>;
                    newNode->data = data;
                    newNode->parents = treeNode;
                    treeNode->rchild = newNode;
                    
                    auto unbalanceNode = newNode->getUnbalanceNode();
                    if (unbalanceNode != nullptr) {
                        this->makeBalance(unbalanceNode);
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

