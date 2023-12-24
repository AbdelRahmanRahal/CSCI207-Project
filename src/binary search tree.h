//
// Created by 20127 on 12/23/2023.
//

#ifndef PROJECT_CSCI207_BINARY_SEARCH_TREE_H
#define PROJECT_CSCI207_BINARY_SEARCH_TREE_H

#endif //PROJECT_CSCI207_BINARY_SEARCH_TREE_H
#include <iostream>
using namespace std;
template <typename T>
class Node
{
public:
    T data;
    Node<T>*left;
    Node<T>*Right;


    Node():data(0),left(nullptr),Right(nullptr)
    {

    }
};
template <typename T>
class BST
{
public:

    Node<T>*Root;
    BST():Root(nullptr)
    {

    }
    Node<T>*insert(Node<T>* parent_node,int item)
    {

        if(parent_node==nullptr)
        {
            Node<T>*newnode = new Node<T>();

            newnode->data=item;
            parent_node=newnode;

        }
        else if(item<(parent_node->data))
        {
            parent_node->left=   insert(parent_node->left,item);

        }
        else{
            parent_node->Right=insert(parent_node->Right,item);
        }
        return parent_node;

    }
    // simple copy of insert method
    void insert(int item)
    {
        Root=insert(Root,item);
        // simple version of insert because user not hate himself
    }
    void pre_orderDisplay(Node <T>*parent_node)
    {
        // root->left->right
        if(parent_node==nullptr)
            return;
        cout<<parent_node->data<<" ";
        pre_orderDisplay(parent_node->left);
        pre_orderDisplay(parent_node->Right);
    }
    void in_order(Node<T>*parent_node)// left->root->right

    {

        if(parent_node==nullptr)
            return;
        in_order(parent_node->left);
        cout<<parent_node->data<<" ";

        in_order(parent_node->Right);
    }
    void post_orderDisplay(Node<T>*parent_node)//left->right->root
    {

        if(parent_node==nullptr)
            return;

        post_orderDisplay(parent_node->left);
        post_orderDisplay(parent_node->Right);
        cout<<parent_node->data<<" ";
    }
    Node<T>*search(Node<T>*parent_node,int key)
    {
        if(parent_node==nullptr)
            return nullptr;
        else if(key==parent_node->data)
            return parent_node;
        else if(key<parent_node->data)
            return search(parent_node->left,key);
        else
            return search(parent_node->Right,key);

    }
    bool search(int item)
    {
        Node<T>*result=search(Root,item);
        if(result==nullptr)
            return false;
        else
            return true;
    }
    Node <T>* find_min(Node<T>*parent_node)
    {
        if(parent_node==nullptr)
            return nullptr;
        else if((parent_node->left)== nullptr)
            return parent_node;
        else
            return find_min(parent_node->left);
    }
    Node <T>* find_max(Node<T>*parent_node)
    {
        if(parent_node==nullptr)
            return nullptr;
        else if((parent_node->Right)== nullptr)
            return parent_node;
        else
            return find_max(parent_node->Right);
    }
    Node<T> *delete_item(Node <T>*parent_node,T item)
    {
        if(parent_node==nullptr)
            return nullptr;
        if     (item<(parent_node->data))// item exists in the left sub
            parent_node->left= delete_item(parent_node->left,item);
        else if(item>(parent_node->data))// item exists in the right sub
            parent_node->Right=delete_item(parent_node->Right,item);
        else
        {
            if(parent_node->left==nullptr&&parent_node->Right==nullptr)// leaf node
                parent_node=nullptr;
            else if(parent_node->left!=nullptr&&parent_node->Right==nullptr)// one child in the left
            {
                parent_node->data = parent_node->left->data;
                delete parent_node->left;
                parent_node->left = nullptr;
            }
            else if(parent_node->Right!=nullptr&&parent_node->left==nullptr)// one child on the right
            {
                parent_node->data=parent_node->Right->data;
                delete parent_node->Right;
                parent_node->Right=nullptr;
            }
            else
            {
                Node<T>*predecessor= find_max(parent_node->left);
                parent_node->data= predecessor->data;
                parent_node->left=  delete_item(parent_node->left,predecessor->data);
            }
            return parent_node;
        }
    }


};

