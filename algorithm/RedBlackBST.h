/*****************************************************
红黑树保证左右子树的长度小于两倍，查找的最坏时间复杂度为2lgn,
近似于AVL的性能。红黑树可以等价于一颗二三树，通过构造各种变换
保证黑色节点的数量平衡，插入方法具体实现参考《算法》第四版
*****************************************************/
#define RED     1
#define BLACK   0

template<typename k, typename v>
struct Node
{
    k key;
    v value;
    Node<k,v>* left;
    Node<k,v>* right;
    int color;
    Node(k _key ,v _value ,Node<k,v>* _left, Node<k,v>* _right, int _color):
    key(_key),value(_value),left(_left),right(_right),color(_color);
    Node<k,v> operator=(const Node<k,v>& node)
    {
        this->key = node.key;
        this->color = node.color;
        this->right = node.right;
        this->left = node.left;
        this->value = node.value;
    };
};

template<typename k, typename v>
class RedBlackBST
{
public:
    RedBlackBST();
    void Add(k key, v value);
    void Delete(k key);
    Node<k,v>* Find(k key);
    void Modify(k key, v value);
    void Show();
private:
    Node<k,v>* root;
    int sum;
    int height;
};
