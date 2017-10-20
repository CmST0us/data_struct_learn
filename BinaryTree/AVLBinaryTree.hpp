#include <iostream>
#include <stdlib.h>
#include <deque>
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
    
    void enumDLRUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func) {
        this->_enumDLRUsingBlock(func, this);
    }
    
    void enumDLRUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func) {
        this->_enumDLRUsingBlock(func, this);
    }
    
    void enumLDRUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func) {
        this->_enumLDRUsingBlock(func, this);
    }
    
    void enumLDRUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func) {
        this->_enumLDRUsingBlock(func, this);
    }
    
    void enumLRDUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func) {
        this->_enumLRDUsingBlock(func, this);
    }
    
    void enumLRDUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func) {
        this->_enumLRDUsingBlock(func, this);
    }
    
    void enumLayerUsingBlock(function<void(AVLBinaryTreeNode<T> *, int, bool &)> func) {
        this->_enumLayerUsingBlock(func, this);
    }
    
    void enumLayerUsingBlock(function<void (AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T> *, int, bool&)> func) {
        this->_enumLayerUsingBlock(func, this);
    }
    
private:
    int _getHeight(AVLBinaryTreeNode<T> *node) {
        int lresult = 0, rresult = 0;
        if (node == nullptr) {
            return 0;
        }
        lresult = node->lchild->getHeight();
        rresult = node->rchild->getHeight();
        return (lresult >= rresult ? lresult : rresult) + 1;
    }
    
    int _getBalanceFactor (AVLBinaryTreeNode<T> *node) {
        int left = 0;
        int right = 0;
        
        node->lchild == nullptr ? left = 0 : left = node->lchild->getHeight();
        node->rchild == nullptr ? right = 0 : right = node->rchild->getHeight();
        
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
    //先序
    void _enumDLRUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func,
                            AVLBinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr) {
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        
        for (int i = 0; i < node->repeat; ++i) {
            func(node, *stop);
            if (*stop) return;
        }
        
        if (node->lchild != nullptr) _enumDLRUsingBlock(func, node->lchild, stop);
        if (node->rchild != nullptr) _enumDLRUsingBlock(func, node->rchild, stop);
    }
    
    //中序
    void _enumLDRUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func,
                            AVLBinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr) {
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        
        if (node->lchild != nullptr) _enumLDRUsingBlock(func, node->lchild, stop);
        for (int i = 0; i < node->repeat; ++i) {
            func(node, *stop);
            if (*stop) return;
        }
        if (node->rchild != nullptr) _enumLDRUsingBlock(func, node->rchild, stop);
    }
    
    //后序
    void _enumLRDUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func,
                            AVLBinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr) {
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        
        if (node->lchild != nullptr) _enumLRDUsingBlock(func, node->lchild, stop);
        if (node->rchild != nullptr) _enumLRDUsingBlock(func, node->rchild, stop);
        for (int i = 0; i < node->repeat; ++i) {
            func(node, *stop);
            if (*stop) return;
        }
    }
    
    //层序
    void _enumLayerUsingBlock(function<void(AVLBinaryTreeNode<T> *, int, bool &)> func,
                              AVLBinaryTreeNode<T> *node = nullptr,
                              bool *stop = nullptr) {
        bool s;
        if (stop == nullptr) stop = &s; else s = *stop;

        deque<AVLBinaryTreeNode<T>*> nodeQueue;
        nodeQueue.push_back(node);
        int i = 0;
        while(nodeQueue.size()) {
            auto pNode = nodeQueue.front();
            nodeQueue.pop_front();
            
            func(pNode, i++, *stop);
            if (!stop) {
                return;
            }
            
            if (pNode->lchild != nullptr) nodeQueue.push_back(pNode->lchild);
            if (pNode->rchild != nullptr) nodeQueue.push_back(pNode->rchild);
        }
    }
    //带前驱元素先序遍历
    void _enumDLRUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func,
                            AVLBinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr,
                            AVLBinaryTreeNode<T> **beforeTree = nullptr) {
        AVLBinaryTreeNode<T> *before;
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        for (int i = 0; i < node->repeat; ++i) {
            func(*beforeTree, node, *stop);
            *beforeTree = node;
            if (*stop) return;
        }
        if (node->lchild != nullptr) _enumDLRUsingBlock(func, node->lchild, stop, beforeTree);
        if (node->rchild != nullptr) _enumDLRUsingBlock(func, node->rchild, stop, beforeTree);
    }
    
    //带前驱元素的中序遍历
    void _enumLDRUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func,
                            AVLBinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr,
                            AVLBinaryTreeNode<T> **beforeTree = nullptr) {
        AVLBinaryTreeNode<T> *before;
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        if (node->lchild != nullptr) _enumLDRUsingBlock(func, node->lchild, stop, beforeTree);
        
        for (int i = 0; i < node->repeat; ++i) {
            func(*beforeTree, node, *stop);
            *beforeTree = node;
            if (*stop) return;
        }
        
        if (node->rchild != nullptr) _enumLDRUsingBlock(func, node->rchild, stop, beforeTree);
    }
    
    //带前驱元素的后序遍历
    void _enumLRDUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func,
                            AVLBinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr,
                            AVLBinaryTreeNode<T> **beforeTree = nullptr) {
        AVLBinaryTreeNode<T> *before;
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        if (node->lchild != nullptr) _enumLRDUsingBlock(func, node->lchild, stop, beforeTree);
        if (node->rchild != nullptr) _enumLRDUsingBlock(func, node->rchild, stop, beforeTree);
        for (int i = 0; i < node->repeat; ++i) {
            func(*beforeTree, node, *stop);
            *beforeTree = node;
            if (*stop) return;
        }
    }
    //带前驱元素的层序遍历
    void _enumLayerUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T> *, int, bool &)> func,
                              AVLBinaryTreeNode<T> *node = nullptr,
                              bool *stop = nullptr,
                              AVLBinaryTreeNode<T> **beforeTree = nullptr) {
        AVLBinaryTreeNode<T> *before;
        bool s;
        
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        deque<AVLBinaryTreeNode<T>*> nodeQueue;
        nodeQueue.push_back(node);
        int i = 0;
        while(nodeQueue.size()) {
            auto pNode = nodeQueue.front();
            nodeQueue.pop_front();
            
            func(*beforeTree, pNode, i++, *stop);
            *beforeTree = pNode;
            if (!stop) {
                return;
            }
            
            if (pNode->lchild != nullptr) nodeQueue.push_back(pNode->lchild);
            if (pNode->rchild != nullptr) nodeQueue.push_back(pNode->rchild);
        }
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
        //注意当子节点nodeBf等于0的情况
        int nodeBf = node->getBalanceFactor();
        if (nodeBf > 0) {
            //L-
            int lchildNodeBf = node->lchild->getBalanceFactor();
            if (lchildNodeBf >= 0) {
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
            if (rchildNodeBf <= 0) {
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
            this->root->parents = nullptr;
            auto rootRightChild = this->root->rchild;
            this->root->rchild = node;
            node->lchild = rootRightChild;
            if (rootRightChild != nullptr) rootRightChild->parents = node;
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
            this->root->parents = nullptr;
            auto rootLeftChild = this->root->lchild;
            this->root->lchild = node;
            node->rchild = rootLeftChild;
            if (rootLeftChild != nullptr) rootLeftChild->parents = node;
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
    
    void enumDLRUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func) {
        this->root->enumDLRUsingBlock(func);
    }
    
    void enumDLRUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func) {
        this->root->enumDLRUsingBlock(func);
    }
    
    void enumLDRUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func) {
        this->root->enumLDRUsingBlock(func);
    }
    
    void enumLDRUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func) {
        this->root->enumLDRUsingBlock(func);
    }
    
    void enumLRDUsingBlock(function<void(AVLBinaryTreeNode<T> *, bool &)> func) {
        this->root->enumLRDUsingBlock(func);
    }
    
    void enumLRDUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T>* , bool &)> func) {
        this->root->enumLRDUsingBlock(func);
    }
    
    void enumLayerUsingBlock(function<void(AVLBinaryTreeNode<T> *, int, bool &)> func) {
        this->root->enumLayerUsingBlock(func);
    }
    
    void enumLayerUsingBlock(function<void(AVLBinaryTreeNode<T> *, AVLBinaryTreeNode<T> *, int, bool &)> func) {
        this->root->enumLayerUsingBlock(func);
    }
    
    void insertData(T data) {
        this->_insertData(data, this->root);
    }
    
    void removeData(T data) {
        if (data == this->root->data) {
            //删除根节点, 移动根
            this->enumLDRUsingBlock([&](AVLBinaryTreeNode<T> *before, AVLBinaryTreeNode<T> *now, bool &stop) {
                if (now == this->root) {
                    //将root的右子树下接到root中序遍历直接前驱节点的右子树上
                    auto searchUnbalanceNodePtr = before->parents;
                    
                    before->rchild = this->root->rchild;
                    this->root->rchild->parents = before;
                    this->root->lchild = nullptr;
                    this->root->rchild = nullptr;
                    
                    delete this->root;
                    
                    this->root = before;
                    this->root->parents = nullptr;
                    stop = true;
                    
                    //start balance
                    auto unbalanceNode = searchUnbalanceNodePtr->getUnbalanceNode();
                    if (unbalanceNode != nullptr) this->makeBalance(unbalanceNode);
                }
            });
        } else {
            this->enumLDRUsingBlock([&](AVLBinaryTreeNode<T> *beforeNode, AVLBinaryTreeNode<T> *nowNode, bool &stop){
                if (nowNode->data == data) {
                    if (nowNode->lchild == nullptr && nowNode->rchild == nullptr) {
                        //删除节点为叶子
                        auto searchUnbalanceNodePtr = nowNode->parents;
                        
                        if (nowNode->parents->lchild == nowNode) {
                            nowNode->parents->lchild = nullptr;
                        } else {
                            nowNode->parents->rchild = nullptr;
                        }
                        
                        delete nowNode;
                        
                        auto unbalanceNode = searchUnbalanceNodePtr->getUnbalanceNode();
                        if (unbalanceNode != nullptr) this->makeBalance(unbalanceNode);
                        
                    } else if (nowNode->lchild != nullptr && nowNode->rchild != nullptr) {
                        //删除节点有两个孩子
                        
                        ////中序直接前驱节点替换当前节点
                        auto searchUnbalanceNodePtr = beforeNode->parents;
                        
                        if (nowNode->parents->lchild == nowNode) {
                            nowNode->parents->lchild = beforeNode;
                        } else {
                            nowNode->parents->rchild = beforeNode;
                        }
                        
                        if (beforeNode->parents->lchild == beforeNode) {
                            beforeNode->parents->lchild = nullptr;
                        } else {
                            beforeNode->parents->rchild = nullptr;
                        }
                        beforeNode->parents = nowNode->parents;
                        beforeNode->lchild = nowNode->lchild;
                        beforeNode->rchild = nowNode->rchild;
                        
                        nowNode->lchild = nullptr;
                        nowNode->rchild = nullptr;
                        nowNode->parents = nullptr;
                        
                        delete nowNode;
                        stop = true;
                        
                        auto unbalanceNode = searchUnbalanceNodePtr->getUnbalanceNode();
                        if (unbalanceNode != nullptr) this->makeBalance(unbalanceNode);
                    } else {
                        //删除节点只有一个孩子
                        auto searchUnbalanceNodePtr = nowNode->parents;
                        
                        if (nowNode->lchild != nullptr) {
                            //删除节点左孩子非空
                            if (nowNode->parents->rchild == nowNode) {
                                //删除节点为双亲节点的右孩子
                                nowNode->parents->rchild = nowNode->lchild;
                                nowNode->lchild->parents = nowNode->parents;
                            } else {
                                //删除节点为双亲节点的左孩子
                                nowNode->parents->lchild = nowNode->lchild;
                                nowNode->lchild->parents = nowNode->parents;
                            }
                        } else {
                            //删除节点右孩子非空
                            if (nowNode->parents->rchild == nowNode) {
                                //删除节点为双亲节点的右孩子
                                nowNode->parents->rchild = nowNode->rchild;
                                nowNode->rchild->parents = nowNode->parents;
                            } else {
                                //删除节点为双亲节点的左孩子
                                nowNode->parents->lchild = nowNode->rchild;
                                nowNode->rchild->parents = nowNode->parents;
                            }
                        }
                        nowNode->lchild = nullptr;
                        nowNode->rchild = nullptr;
                        delete nowNode;
                        
                        auto unbalanceNode = searchUnbalanceNodePtr->getUnbalanceNode();
                        if (unbalanceNode != nullptr) this->makeBalance(unbalanceNode);
                    }
                    stop = true;
                }
            });
        }
    }
    
    AVLBinaryTree& operator<<(T d) {
        this->_insertData(d, this->root);
        return *this;
    }
    
private:
    void _insertData(T data, AVLBinaryTreeNode<T> *node) {
        if (this->root == nullptr) {
            auto newNode = new AVLBinaryTreeNode<T>(data);
            this->root = newNode;
        } else {
            if (node->data > data) {
                if (node->lchild == nullptr) {
                    auto newNode = new AVLBinaryTreeNode<T>;
                    newNode->data = data;
                    newNode->parents = node;
                    node->lchild = newNode;
                    
                    auto unbalanceNode = newNode->getUnbalanceNode();
                    if (unbalanceNode != nullptr) {
                        this->makeBalance(unbalanceNode);
                    }
                } else {
                    _insertData(data, node->lchild);
                }
            } else if (node->data < data) {
                if (node->rchild == nullptr) {
                    auto newNode = new AVLBinaryTreeNode<T>;
                    newNode->data = data;
                    newNode->parents = node;
                    node->rchild = newNode;
                    
                    auto unbalanceNode = newNode->getUnbalanceNode();
                    if (unbalanceNode != nullptr) {
                        this->makeBalance(unbalanceNode);
                    }
                } else {
                    _insertData(data, node->rchild);
                }
            } else {
                node->repeat++;
            }
        }
    }
    
};

