#include <iostream>
using namespace std;

template <class T>
struct BinaryTreeNode {
    T data;
    int repeat = 1;
    
    BinaryTreeNode<T> *parents = nullptr;
    BinaryTreeNode<T> *lchild = nullptr;
    BinaryTreeNode<T> *rchild = nullptr;
    
    BinaryTreeNode(T data) {
        this->data = data;
    }
    
    BinaryTreeNode() {
        
    }
    
    ~BinaryTreeNode() {
        if (this->lchild != nullptr) {
            delete this->lchild;
        }
        if (this->rchild != nullptr) {
            delete this->rchild;
        }
    }
    void enumDLRUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func) {
        this->_enumDLRUsingBlock(func, this);
    }
    
    void enumDLRUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func) {
        this->_enumDLRUsingBlock(func, this);
    }
    
    void enumLDRUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func) {
        this->_enumLDRUsingBlock(func, this);
    }
    
    void enumLDRUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func) {
        this->_enumLDRUsingBlock(func, this);
    }
    
    void enumLRDUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func) {
        this->_enumLRDUsingBlock(func, this);
    }
    
    void enumLRDUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func) {
        this->_enumLRDUsingBlock(func, this);
    }
    
private:
    //先序
    void _enumDLRUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func,
                            BinaryTreeNode<T> *node = nullptr,
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
    void _enumLDRUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func,
                            BinaryTreeNode<T> *node = nullptr,
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
    void _enumLRDUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func,
                            BinaryTreeNode<T> *node = nullptr,
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
    
    //带前驱元素先序遍历
    void _enumDLRUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func,
                            BinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr,
                            BinaryTreeNode<T> **beforeTree = nullptr) {
        BinaryTreeNode<T> *before;
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
    void _enumLDRUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func,
                            BinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr,
                            BinaryTreeNode<T> **beforeTree = nullptr) {
        BinaryTreeNode<T> *before;
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
    void _enumLRDUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func,
                            BinaryTreeNode<T> *node = nullptr,
                            bool *stop = nullptr,
                            BinaryTreeNode<T> **beforeTree = nullptr) {
        BinaryTreeNode<T> *before;
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
};

template <class T>
struct BinaryTree {
    BinaryTreeNode<T> *root = nullptr;
    
    BinaryTree() {
        
    }
    
    BinaryTree(T data) {
        auto rootNode = new BinaryTreeNode<T>(data);
        this->root = rootNode;
    }
    
    ~BinaryTree() {
        if (this->root != nullptr) {
            delete root;
            this->root = nullptr;
        }
    }
    
    void insertData(T data) {
        this->_insertData(data, this->root);
    }
    
    void removeData(T data) {
        if (data == this->root->data) {
            //删除根节点, 移动根
            this->enumLDRUsingBlock([&](BinaryTreeNode<T> *before, BinaryTreeNode<T> *now, bool &stop) {
                if (now == this->root) {
                    //中序直接前驱节点替换根节点
                    before->rchild = this->root->rchild;
                    this->root->rchild->parents = before;
                    this->root->lchild = nullptr;
                    this->root->rchild = nullptr;
                    
                    delete this->root;
                    this->root = before;
                    this->root->parents = nullptr;
                    
                    stop = true;
                }
            });
        } else {
            this->enumLDRUsingBlock([&](BinaryTreeNode<T> *beforeNode, BinaryTreeNode<T> *nowNode, bool &stop){
                if (nowNode->data == data) {
                    if (nowNode->lchild == nullptr && nowNode->rchild == nullptr) {
                        //删除节点为叶子
                        if (nowNode->parents->lchild == nowNode) {
                            nowNode->parents->lchild = nullptr;
                        } else {
                            nowNode->parents->rchild = nullptr;
                        }
                        delete nowNode;
                    } else if (nowNode->lchild != nullptr && nowNode->rchild != nullptr) {
                        //删除节点有两个孩子
                        
                        ////中序直接前驱节点替换当前节点
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
                    } else {
                        //删除节点只有一个孩子
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
                            //删除节点有孩子非空
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
                    }
                    stop = true;
                }
            });
        }
    }
    
    void enumDLRUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func) {
        this->root->enumDLRUsingBlock(func);
    }
    
    void enumDLRUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func) {
        this->root->enumDLRUsingBlock(func);
    }
    
    void enumLDRUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func) {
        this->root->enumLDRUsingBlock(func);
    }
    
    void enumLDRUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func) {
        this->root->enumLDRUsingBlock(func);
    }
    
    void enumLRDUsingBlock(function<void(BinaryTreeNode<T> *t, bool &stop)> func) {
        this->root->enumLRDUsingBlock(func);
    }
    
    void enumLRDUsingBlock(function<void(BinaryTreeNode<T> *b, BinaryTreeNode<T>* t, bool &stop)> func) {
        this->root->enumLRDUsingBlock(func);
    }
    
    BinaryTree& operator<<(T data) {
        this->_insertData(data, this->root);
        return *this;
    }
    
    
private:
    void _insertData(T data, BinaryTreeNode<T> *node = nullptr) {
        if (this->root == nullptr) {
            auto newNode = new BinaryTreeNode<T>(data);
            this->root = newNode;
        } else {
            if (node->data > data) {
                if (node->lchild == nullptr) {
                    auto newNode = new BinaryTreeNode<T>;
                    newNode->data = data;
                    newNode->parents = node;
                    node->lchild = newNode;
                } else {
                    _insertData(data, node->lchild);
                }
            } else if (node->data < data) {
                if (node->rchild == nullptr) {
                    auto newNode = new BinaryTreeNode<T>;
                    newNode->data = data;
                    newNode->parents = node;
                    node->rchild = newNode;
                } else {
                    _insertData(data, node->rchild);
                }
            } else {
                node->repeat++;
            }
        }
    }
};
