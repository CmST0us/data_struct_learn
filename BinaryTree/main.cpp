//
//  main.cpp
//  BinaryTree
//
//  Created by CmST0us on 2017/10/19.
//  Copyright © 2017年 eric3u. All rights reserved.
//
#include "AVLBinaryTree.hpp"
#include "BinaryTree.hpp"


void test_BinaryTree() {
    BinaryTree<int> tree;
    tree<<15<<6<<11<<7<<8<<9<<10<<17<<18;
    
    
    
    tree.removeData(15);
    cout<<"remove15中序:";
    tree.enumLDRUsingBlock([](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    tree.removeData(7);
    cout<<"remove:7中序:";
    tree.enumLDRUsingBlock([](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    tree.removeData(21);
    cout<<"remove:21中序:";
    tree.enumLDRUsingBlock([](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    tree.removeData(10);
    cout<<"remove:10中序:";
    tree.enumLDRUsingBlock([](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    cout<<"先序";
    tree.enumDLRUsingBlock([&](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    cout<<"中序:";
    tree.enumLDRUsingBlock([](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
    
    cout<<"后序:";
    tree.enumLRDUsingBlock([](BinaryTreeNode<int> *t, bool &stop){
        cout<<t->data<<", ";
    });
    cout<<endl;
}

void test_AVLBinaryTree() {
    AVLBinaryTree<int> tree;
    tree<<15<<6<<11<<7<<8<<9<<10<<17<<18;
    
    tree.removeData(8);
    
    tree.removeData(15);
    
    tree.removeData(17);
    
    cout<<"先序:";
    tree.enumDLRUsingBlock([](AVLBinaryTreeNode<int> *node, bool &stop){
        cout<<node->data<<",";
    });
    cout<<endl;
    
    cout<<"中序:";
    tree.enumLDRUsingBlock([](AVLBinaryTreeNode<int> *node, bool &stop){
        cout<<node->data<<",";
    });
    
    
    cout<<endl;
    
}
int main(int argc, char *argv[]) {
    test_BinaryTree();
    test_AVLBinaryTree();
    
    return 0;
}
