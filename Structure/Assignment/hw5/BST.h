//22412051 이승은
#ifndef BST_H
#define BST_H

#include "TreeNode.h" 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using std::cout;
using std::endl;
using std::ofstream;

inline void gets_s(char *buffer) 
{
    if (fgets(buffer, 50, stdin) != NULL) { 
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

template <typename KeyT, typename ValueT>
class BST
{
public:
    BST() : root(nullptr), count(0) {}
    ~BST() { destroyTree(root); }

    TreeNode<KeyT, ValueT> *searchNode(const KeyT& key);
    ValueT insertNode(const KeyT& key, const ValueT& value);
    void deleteNode(const KeyT& key);
    void printTree(ofstream &fp);
    void treeStatus();

private:
    TreeNode<KeyT, ValueT> *root;
    int count;
    void destroyTree(TreeNode<KeyT, ValueT>* node);
    void inorderTraversal(TreeNode<KeyT, ValueT>* node, ofstream& fp);
    TreeNode<KeyT, ValueT>* findMin(TreeNode<KeyT, ValueT>* node);
    int findMaxDepth(TreeNode<KeyT, ValueT>* node);
    long long findTotalSearch(TreeNode<KeyT, ValueT>* node, int level);
};

template <typename KeyT, typename ValueT>
TreeNode<KeyT, ValueT>* BST<KeyT, ValueT>::searchNode(const KeyT& key) 
{
    TreeNode<KeyT, ValueT>* current = root;
    while (current != nullptr) {
        if (key == current->key) return current;
        else if (key < current->key) current = current->lchild;
        else current = current->rchild;
    }
    return nullptr;
}

template <typename KeyT, typename ValueT>
ValueT BST<KeyT, ValueT>::insertNode(const KeyT& key, const ValueT& value)
{
    if (root == nullptr) {
        root = new TreeNode<KeyT, ValueT>(key, value);
        count++;
        return root->value;
    }

    TreeNode<KeyT, ValueT>* current = root;
    TreeNode<KeyT, ValueT>* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (key == current->key) {
            current->value += value;
            return current->value;
        } else if (key < current->key) {
            current = current->lchild;
        } else {
            current = current->rchild;
        }
    }

    TreeNode<KeyT, ValueT>* newNode = new TreeNode<KeyT, ValueT>(key, value);
    if (key < parent->key) {
        parent->lchild = newNode;
    } else {
        parent->rchild = newNode;
    }

    count++;
    return newNode->value;
}

template <typename KeyT, typename ValueT>
void BST<KeyT, ValueT>::deleteNode(const KeyT& key)
{
    TreeNode<KeyT, ValueT>* current = root;
    TreeNode<KeyT, ValueT>* parent = nullptr;

    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) current = current->lchild;
        else current = current->rchild;
    }
    if (current == nullptr) return; 

    TreeNode<KeyT, ValueT>* node_Del = current;
    if (current->lchild == nullptr || current->rchild == nullptr) {
        
        TreeNode<KeyT, ValueT>* child;
        if (current->lchild != nullptr) {
            child = current->lchild;
        } else {
            child = current->rchild;
        }
        
        if (parent == nullptr) root = child;
        else if (parent->lchild == current) parent->lchild = child;
        else parent->rchild = child;
        
        delete node_Del;
        count--;
        return;
    }

    TreeNode<KeyT, ValueT>* succ = current->rchild;
    TreeNode<KeyT, ValueT>* succParent = current;

    while (succ->lchild != nullptr) {
        succParent = succ;
        succ = succ->lchild;
    }
    current->key = succ->key;
    current->value = succ->value;
    if (succParent->lchild == succ) {
        succParent->lchild = succ->rchild;
    } else {
        succParent->rchild = succ->rchild;
    }
    delete succ;
    count--; 
}

template <typename KeyT, typename ValueT>
void BST<KeyT, ValueT>::printTree(ofstream &fp)
{
    inorderTraversal(root, fp);
}

template <typename KeyT, typename ValueT>
void BST<KeyT, ValueT>::treeStatus()
{
    long long   total = 0;
    double      avg = 0.0;
    int         depth = 0;
    
    if (count > 0) {
        depth = findMaxDepth(root);
        total = findTotalSearch(root, 1); 
        avg = (double)total / count;
    }

    printf("트리의 깊이 = %d, 전체 노드 수 = %d", depth, count);
    if (count > 0) {
        printf(", 평균 검색 수 = %.2f", avg);
    } 
}

template <typename KeyT, typename ValueT>
void BST<KeyT, ValueT>::destroyTree(TreeNode<KeyT, ValueT>* node)
{
    if (node) {
        destroyTree(node->lchild);
        destroyTree(node->rchild);
        delete node;
    }
}

template <typename KeyT, typename ValueT>
void BST<KeyT, ValueT>::inorderTraversal(TreeNode<KeyT, ValueT>* node, ofstream& fp)
{
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->lchild, fp);
    fp << node->key; 
    int key_len = node->key.length(); 
    int total = 20 - key_len; 
    if (total < 0) {
        total = 0;
    }
    for (int i = 0; i < total; ++i) {
        fp << ' ';
    }
    fp << '\t' << node->value << endl;
    inorderTraversal(node->rchild, fp);
}

template <typename KeyT, typename ValueT>
int BST<KeyT, ValueT>::findMaxDepth(TreeNode<KeyT, ValueT>* node)
{
    if (node == nullptr) return 0;
    
    int lDepth = findMaxDepth(node->lchild);
    int rDepth = findMaxDepth(node->rchild);

    if (lDepth > rDepth) {
        return 1 + lDepth;
    } else {
        return 1 + rDepth;
    }
}

template <typename KeyT, typename ValueT>
long long BST<KeyT, ValueT>::findTotalSearch(TreeNode<KeyT, ValueT>* node, int level)
{
    if (node == nullptr) return 0;
    long long count = (long long)level * node->value; 
    count += findTotalSearch(node->lchild, level + 1);
    count += findTotalSearch(node->rchild, level + 1);
    return count;
}

template <typename KeyT, typename ValueT>
TreeNode<KeyT, ValueT>* findMin(TreeNode<KeyT, ValueT>* node)
{
    while (node->lchild != nullptr) {
        node = node->lchild;
    }
    return node;
}

#endif