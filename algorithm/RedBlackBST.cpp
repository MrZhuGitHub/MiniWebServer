#include "RedBlackBST.h"
#include <stack>
#include <vector>

using namespace std;

template<typename k, typename v>
RedBlackBST<k,v>::RedBlackBST()
{
    int sum = 0;
    int height = 0;
}

template<typename k, typename v>
bool isred(Node<k,v>* node)
{
    if(node == nullptr)
    {
        return false;
    }
    if(node->color == RED)
    {
        return true;
    }
    else
    {
        return false;
    }   
}

template<typename k, typename v>
Node<k,v>* InsertNode(Node<k,v>* root, k& key, v& value)
{
    //插入叶子节点
    if(root == nullptr)
    {
        sum++;
        Node<k,v>* node = new Node(RED, key, value, nullptr, nullptr);
        return node;
    }

    if(root->key == key)
    {
        root->value = value;
        return root;
    }
    else if(root->key > key)
    {
        root->left = InsertNode(root->left, key, value);
    }
    else
    {
        root->right = InsertNode(root->right, key, value);
    }

    //右子节点的颜色为红色，则左旋调整
    if(isred(root->right))
    {
        Node<k,v>* node = new Node(root->color, root->key, root->value, root->left, root->right->left);
        *root = *(root->right);
        root->left = node;
        delete root->right;
    }
    //左子节点和左孙子节点都为红色，则右旋调整
    if(isred(root->left) && isred(root->left->left))
    {
        Node<k,v>* node = new Node(root->color, root->key, root->value, root->right, root->left->right);
        *root = *(root->left);
        root->right->node;
        delete root->left;
    }
    //root节点的颜色转换为红色，等价于向父节点添加一个节点
    if(isred(root->left) && isred(root->right))
    {
        root->left->color = BLACK;
        root->right->color = BLACK;
        root->color = RED;
    }
    return root;
}

template<typename k, typename v>
void RedBlackBST<k,v>::Add(k key, v value)
{
    root = InsertNode(key, value);
    if(root->color != BLACK)
    {
        height++;
        root->color == BLACK;
    }
}

template<typename k, typename v>
void RedBlackBST<k,v>::Delete(k key)
{

}

template<typename k, typename v>
Node<k,v>* RedBlackBST<k,v>::Find(k key)
{
    stack<Node<k,v>*> AllNode;
    AllNode.push(root);
    while(AllNode.top() != nullptr)
    {
        if(AllNode.top()->key == key)
        {
            return AllNode.top();
        }
        else if(AllNode.top()->key < key)
        {
            AllNode.push(AllNode.top()->right);
        }
        else
        {
            AllNode.push(AllNode.top()->left);
        }       
    }
    return nullptr;
}

template<typename k, typename v>
void RedBlackBST<k,v>::Modify(k key, v value)
{
    Node<k,v>* node = Find(key);
    if(node != nullptr)
    {
        node->value = value;
    }
    else
    {
        printf("The key=%d is not exist in this RedBlackBST!\n",key);
    }   
}

template<typename k, typename v>
void RedBlackBST<k,v>::Show()
{
    printf("RedBlackBST: sum = %d , height = %d !\n", this->sum, this->height);
}