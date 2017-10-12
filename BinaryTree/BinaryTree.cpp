#include <iostream>
using namespace std;

template <class T>
struct BinaryTree {
    T data;
    int repeat = 1;
    
    BinaryTree *parents = nullptr;
    BinaryTree *lchild = nullptr;
    BinaryTree *rchild = nullptr;
    
    int leftDepth = 0;
    int rightDepth = 0;
    
    BinaryTree(T rootData) {
        this->data = rootData;
    }
    
    BinaryTree() {
        
    }
    //先序
    void enumDLRUsingBlock(function<void(BinaryTree *t, bool &stop)> func, BinaryTree *treeNode = nullptr, bool *stop = nullptr) {
        BinaryTree *tree;
        bool s;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        if (stop == nullptr) stop = &s; else s = *stop;
        
        for (int i = 0; i < tree->repeat; ++i) {
            func(tree, *stop);
            if (*stop) return;
        }
        
        if (tree->lchild != nullptr) enumDLRUsingBlock(func, tree->lchild, stop);
        if (tree->rchild != nullptr) enumDLRUsingBlock(func, tree->rchild, stop);
    }
    
    //中序
    void enumLDRUsingBlock(function<void(BinaryTree *t, bool &stop)> func, BinaryTree *treeNode = nullptr, bool *stop = nullptr) {
        BinaryTree *tree;
        bool s;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        if (stop == nullptr) stop = &s; else s = *stop;
        
        if (tree->lchild != nullptr) enumLDRUsingBlock(func, tree->lchild, stop);
        for (int i = 0; i < tree->repeat; ++i) {
            func(tree, *stop);
            if (*stop) return;
        }
        if (tree->rchild != nullptr) enumLDRUsingBlock(func, tree->rchild, stop);
    }
    
    //后序
    void enumLRDUsingBlock(function<void(BinaryTree *t, bool &stop)> func, BinaryTree *treeNode = nullptr, bool *stop = nullptr) {
        BinaryTree *tree;
        bool s;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        if (stop == nullptr) stop = &s; else s = *stop;
        
        if (tree->lchild != nullptr) enumLRDUsingBlock(func, tree->lchild, stop);
        if (tree->rchild != nullptr) enumLRDUsingBlock(func, tree->rchild, stop);
        for (int i = 0; i < tree->repeat; ++i) {
            func(tree, *stop);
            if (*stop) return;
        }
    }
    
    //先序
    void enumDLRUsingBlock(function<void(BinaryTree *b, BinaryTree* t, bool &stop)> func, BinaryTree *treeNode = nullptr, bool *stop = nullptr, BinaryTree **beforeTree = nullptr) {
        BinaryTree *tree;
        BinaryTree *before;
        bool s;
        
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        for (int i = 0; i < tree->repeat; ++i) {
            func(*beforeTree, tree, *stop);
            *beforeTree = tree;
            if (*stop) return;
        }
        if (tree->lchild != nullptr) enumDLRUsingBlock(func, tree->lchild, stop, beforeTree);
        if (tree->rchild != nullptr) enumDLRUsingBlock(func, tree->rchild, stop, beforeTree);
    }
    
    //中序
    void enumLDRUsingBlock(function<void(BinaryTree *b, BinaryTree* t, bool &stop)> func, BinaryTree *treeNode = nullptr, bool *stop = nullptr, BinaryTree **beforeTree = nullptr) {
        BinaryTree *tree;
        BinaryTree *before;
        bool s;
        
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        if (tree->lchild != nullptr) enumLDRUsingBlock(func, tree->lchild, stop, beforeTree);
        
        for (int i = 0; i < tree->repeat; ++i) {
            func(*beforeTree, tree, *stop);
            *beforeTree = tree;
            if (*stop) return;
        }
        
        if (tree->rchild != nullptr) enumLDRUsingBlock(func, tree->rchild, stop, beforeTree);
    }
    
    //后序
    void enumLRDUsingBlock(function<void(BinaryTree *b, BinaryTree* t, bool &stop)> func, BinaryTree *treeNode = nullptr, bool *stop = nullptr, BinaryTree **beforeTree = nullptr) {
        BinaryTree *tree;
        BinaryTree *before;
        bool s;
        
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        if (stop == nullptr) stop = &s; else s = *stop;
        if (beforeTree == nullptr) beforeTree = &before;
        
        if (tree->lchild != nullptr) enumLRDUsingBlock(func, tree->lchild, stop, beforeTree);
        if (tree->rchild != nullptr) enumLRDUsingBlock(func, tree->rchild, stop, beforeTree);
        for (int i = 0; i < tree->repeat; ++i) {
            func(*beforeTree, tree, *stop);
            *beforeTree = tree;
            if (*stop) return;
        }
    }
    
    void insertData(T d, BinaryTree *treeNode = nullptr) {
        BinaryTree *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        if (tree->data > d) {
            if (tree->lchild == nullptr) {
                auto node = new BinaryTree;
                node->data = d;
                node->parents = tree;
                node->leftDepth++;
                tree->lchild = node;
            } else {
                insertData(d, tree->lchild);
            }
        } else if (tree->data < d) {
            if (tree->rchild == nullptr) {
                auto node = new BinaryTree;
                node->data = d;
                node->parents = tree;
                node->rightDepth++;
                tree->rchild = node;
            } else {
                insertData(d, tree->rchild);
            }
        } else {
            tree->repeat++;
        }
    }
    
    void removeData(T d, BinaryTree *treeNode = nullptr) {
        BinaryTree *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        this->enumLDRUsingBlock([&](BinaryTree<T> *t, bool &stop){
            if (t->data == d) {
                stop = true;
                
                if (t->lchild == nullptr && t->rchild == nullptr) {
                    //删除节点为叶子
                    if (t->parents == nullptr) {
                        return ;
                    }
                    if (t->parents->lchild == t) {
                        t->parents->lchild = nullptr;
                    } else {
                        t->parents->rchild = nullptr;
                    }
                    delete t;
                    
                } else if (t->lchild != nullptr && t->rchild != nullptr) {
                    //删除节点有两个孩子
                    t->enumLDRUsingBlock([&](BinaryTree *before, BinaryTree *now, bool &stop){
                        if (t == now) {
                            //前驱右孩子为要删除节点的右孩子
                            before->rchild = t->rchild;
                            if (t->parents != nullptr) {
                                //删除非根节点
                                if (t->parents->lchild == t) {
                                    t->parents->lchild = before;
                                } else {
                                    t->parents->rchild = before;
                                }
                                t->lchild = nullptr;
                                t->rchild = nullptr;
                                delete t;
                            } else {
                                //删除根节点
                                t->data = before->data;
                                t->lchild = before->lchild;
                                t->rchild = before->rchild;
                                before->lchild = nullptr;
                                before->rchild = nullptr;
                                delete before;
                            }
                            stop = true;
                        }
                    });
                } else {
                    //删除节点只有一个孩子
                    if (t->lchild != nullptr) {
                        t->parents->lchild = t->lchild;
                        t->lchild = nullptr;
                        t->rchild = nullptr;
                        delete t;
                    }
                    
                    if (t->rchild != nullptr) {
                        t->parents->rchild = t->rchild;
                        t->lchild = nullptr;
                        t->rchild = nullptr;
                        delete t;
                    }
                    
                }
            }
        });
    }
    
    BinaryTree& operator<<(T d) {
        insertData(d, this);
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

template <class T>
struct AVLBinaryTree: BinaryTree<T> {
    void makeBalance(BinaryTree<T> *treeNode) {
        
    }
    
    void insertData(T d, BinaryTree<T> *treeNode = nullptr) {
        AVLBinaryTree<T> *tree;
        if (treeNode == nullptr) tree = this; else tree = (AVLBinaryTree *)treeNode;
        
        if (tree->data > d) {
            if (tree->lchild == nullptr) {
                auto node = new AVLBinaryTree<T>;
                node->data = d;
                node->parents = tree;
                node->leftDepth++;
                tree->lchild = node;
                
            } else {
                insertData(d, tree->lchild);
            }
            //平衡二叉树
            (tree->balanceFactor)--;
            makeBalance(tree);
            
        } else if (tree->data < d) {
            if (tree->rchild == nullptr) {
                auto node = new AVLBinaryTree<T>;
                node->data = d;
                node->parents = tree;
                node->rightDepth++;
                tree->rchild = node;
                
            } else {
                insertData(d, tree->rchild);
            }
            //平衡二叉树
            (tree->balanceFactor)++;
            makeBalance(tree);
        } else {
            tree->repeat++;
        }
    }
    
    void removeData(T d, BinaryTree<T> *treeNode = nullptr) {
        BinaryTree<T> *tree;
        if (treeNode == nullptr) tree = this; else tree = treeNode;
        
        this->enumLDRUsingBlock([&](BinaryTree<T> *t, bool &stop){
            if (t->data == d) {
                stop = true;
                
                if (t->lchild == nullptr && t->rchild == nullptr) {
                    //删除节点为叶子
                    if (t->parents == nullptr) {
                        return ;
                    }
                    if (t->parents->lchild == t) {
                        t->parents->lchild = nullptr;
                    } else {
                        t->parents->rchild = nullptr;
                    }
                    delete t;
                    
                } else if (t->lchild != nullptr && t->rchild != nullptr) {
                    //删除节点有两个孩子
                    t->enumLDRUsingBlock([&](BinaryTree<T> *before, BinaryTree<T> *now, bool &stop){
                        if (t == now) {
                            //前驱右孩子为要删除节点的右孩子
                            before->rchild = t->rchild;
                            if (t->parents != nullptr) {
                                //删除非根节点
                                if (t->parents->lchild == t) {
                                    t->parents->lchild = before;
                                } else {
                                    t->parents->rchild = before;
                                }
                                t->lchild = nullptr;
                                t->rchild = nullptr;
                                delete t;
                            } else {
                                //删除根节点
                                t->data = before->data;
                                t->lchild = before->lchild;
                                t->rchild = before->rchild;
                                before->lchild = nullptr;
                                before->rchild = nullptr;
                                delete before;
                            }
                            stop = true;
                        }
                    });
                } else {
                    //删除节点只有一个孩子
                    if (t->lchild != nullptr) {
                        t->parents->lchild = t->lchild;
                        t->lchild = nullptr;
                        t->rchild = nullptr;
                        delete t;
                    }
                    
                    if (t->rchild != nullptr) {
                        t->parents->rchild = t->rchild;
                        t->lchild = nullptr;
                        t->rchild = nullptr;
                        delete t;
                    }
                    
                }
            }
        });
    }
    
    AVLBinaryTree& operator<<(T d) {
        insertData(d, this);
        return *this;
    }
};
int main(int argc, char *argv[]) {
    AVLBinaryTree<int> tree;
    tree.data = 5;
    tree<<12<<3<<34<<2<<34<<7<<45<<34<<77<<89;
    
    cout<<"先序";
    tree.enumDLRUsingBlock([&](BinaryTree<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;

    cout<<"中序:";
    tree.enumLDRUsingBlock([](BinaryTree<int> *t, bool &stop){
        auto p = (AVLBinaryTree<int> *)t;
        cout<<p->data<<":"<<p->leftDepth - p->rightDepth<<", ";
    });
    cout<<endl;
    
    return 0;
    tree.removeData(3);
    cout<<"中序:";
    tree.enumLDRUsingBlock([](BinaryTree<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    cout<<"后序:";
    tree.enumLRDUsingBlock([](BinaryTree<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    
    return 0;
}
