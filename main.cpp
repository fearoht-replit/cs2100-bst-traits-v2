#include <iostream>

class SimpleNode {
public:
    SimpleNode() : left(nullptr), right(nullptr), value(0) {}
    SimpleNode *left;
    SimpleNode *right;
    int value;
};

class NodeWithDepth {
public:
    NodeWithDepth() : left(nullptr), right(nullptr), value(0), depth(1) {}
    NodeWithDepth *left;
    NodeWithDepth *right;
    int value;
    size_t depth;
};


class NodeWithString {
public:
    NodeWithString() : left(nullptr), right(nullptr), value(0), depth("Hola") {}
    NodeWithString *left;
    NodeWithString *right;
    int value;
    std::string depth;

};


template<typename T>
struct NodeTraits {
    static const int isStoringDepth = 0;
};
template<>
struct NodeTraits<NodeWithDepth> {
    static const int isStoringDepth = 1;
};

template<>
struct NodeTraits<NodeWithString> {
    static const int isStoringDepth = 2;
};

template<typename Node>
class BST {
public:
    BST() : head(nullptr) {}
    void Add(const int _value) {
        Add<NodeTraits<Node>::isStoringDepth>(&head, _value);
    }

    void print(){
      print_node(head);
    }
private:
    Node *head;
    template<int isStoringDepth>
    void Add(Node **, const int); 

    void print_node(Node* root){
      if (root->left)
        print_node(root->left);
      std::cout << root->depth;
      if (root->right)
        print_node(root->right);
    }
};

template<typename Node, int isStoringDepth>
struct BSTHelper {
    static void Add(Node **_head, int _value) {
        if (*_head == nullptr) {
            auto *node = new Node();
             node->value = _value;
            *_head = node;
        }
        else {
            if ((*_head)->value < _value) {
                BSTHelper<Node, isStoringDepth>::Add(&((*_head)->right), _value);
            }
            else {
                BSTHelper<Node, isStoringDepth>::Add(&((*_head)->left), _value);
            }
        }
    }
};

template<typename Node>
struct BSTHelper<Node, 1> {
    static void Add(Node **_head, int _value) {
        if (*_head == nullptr) {
            auto *node = new Node();
            node->value = _value;
            *_head = node;
        }
        else {
           if ((*_head)->value < _value) {
               BSTHelper<Node, 1>::Add(&((*_head)->right), _value);
               (*_head)->depth = (*_head)->right->depth + 1;
           }
           else {
               BSTHelper<Node, 1>::Add(&((*_head)->left), _value);
               (*_head)->depth = (*_head)->left->depth + 1;
           }
        }
    }
};

template<typename Node>
struct BSTHelper<Node, 2> {
    static void Add(Node **_head, int _value) {
        if (*_head == nullptr) {
            auto *node = new Node();
            node->value = _value;
            *_head = node;
        }
        else {
           if ((*_head)->value < _value) {
               BSTHelper<Node, 2>::Add(&((*_head)->right), _value);
               (*_head)->depth = "Root";
           }
           else {
               BSTHelper<Node, 2>::Add(&((*_head)->left), _value);
               (*_head)->depth = "Left";
           }
        }
    }
};

template<typename Node> template<int isStoringDepth>
void BST<Node>::Add(Node **_head, int _value)
{
    BSTHelper<Node, isStoringDepth>::Add(_head, _value);
}

int main() {
  BST<NodeWithString> bst1;
  bst1.Add(42);
  bst1.print();
  BST<NodeWithString> bst2;
  bst2.Add(42);
}