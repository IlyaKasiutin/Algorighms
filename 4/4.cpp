/*
4_2. Порядковые статистики. Дано число N и N строк. 
Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. 
Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. 
Запрос на получение k-ой порядковой статистики задается числом k. */

#include <stddef.h>
#include <iostream>

template <class T>
struct DefaultComparator
{
    int operator () (const T& l, const T& r) const 
    {
        if (l < r) return -1;
        if (l > r) return 1;
        return 0;
    }
};

template <class Key, class Value, class Comparator = DefaultComparator<Key> >
class AVLTree 
{
    struct Node 
    {
        Key key;
        Value value;
        
        uint8_t height;
        int size;
        
        Node* left;
        Node* right;
        
        Node(const Key& key, const Value& value) :
            key(key),
            value(value),
            height(1),
            size(1),
            left(nullptr),
            right(nullptr)
        {
        }
    };
public:
    AVLTree(Comparator comp = Comparator()) : root(nullptr), tree_size(0), comp(comp)
    {
    }
    
    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator =(const AVLTree&) = delete;
    AVLTree& operator =(AVLTree&&) = delete;
    
    ~AVLTree()
    {
        destroy_tree(root);
        root = nullptr;
    }
    
    Node* find(const Key& key)
    {
        return _find(root, key);
    }
    const Node* find(const Key& key) const
    {
        return find(key);
    }
    
    void insert(const Key& key, const Value& value)
    {
        root = _insert(root, key, value);
    }
    
    void erase( const Key& key )
    {
        root = _erase(root, key);
    }

    Value kth_search(size_t pos)
    {
        return k_search(pos, root);
    }
    
private:

    void destroy_tree(Node* node)
    {
        if (node)
        {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }
    Node* _find( Node* node, const Key& key)
    {
        if (!node)
        {
            return nullptr;
        }
        int comp_res  = comp(key, node->key);
        if (comp_res == -1) 
        {
            return _find(node->left, key);
        } 
        else if (comp_res == 1) 
        {
            return _find(node->right, key);
        }
        return node;
    }
    
    Node* _insert( Node* node, const Key& key, const Value& value)
    {
        if (!node) 
        {
            tree_size++;
            return new Node(key, value);
        }
        
        int comp_res  = comp(key, node->key);
        if (comp_res == -1) 
        {
            node->left = _insert(node->left, key, value);
        }
        else 
        {
            node->right = _insert(node->right, key, value);
        }
        return balance(node);
    }
    
    Node* _erase(Node* node, const Key& key)
    {
        if (!node)
        {
            return nullptr;
        }
        
        int comp_res = comp(key, node->key);
        if (comp_res == -1)
        {
            node->left = _erase(node->left, key);
        }
        else if (comp_res == 1)
        {
            node->right = _erase(node->right, key);
        }
        else
        {
            Node* left = node->left;
            Node* right = node->right;
            
            delete node;
            
            if (!right)
            {
                return left;
            }
            
            Node* min_node = find_min(right);
            min_node->right = remove_min(right);
            min_node->left = left;
            
            return balance(min_node);
        }
        return balance(node);
    }
    
    Node* find_min(Node* node)
    {
        if (!node->left)
        {
            return node;
        }
        return find_min(node->left);
    }
    
    Node* remove_min(Node* node)
    {
        if (!node->left)
        {
            return node->right;
        }
        node->left = remove_min(node->left);
        return balance (node);
    }
    
    uint8_t height(Node* node) const
    {
        return node ? node->height : 0;
    }
    
    void fix_height(Node* node)
    {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    int size(Node* node) const
    {
        return node ? node->size : 0;
    }

    void fix_size(Node* node)
    {
        node->size = size(node->left) + size(node->right) + 1;
    }
    
    int bfactor(Node* node) const
    {
        return height(node->right) - height(node->left);
    }
    
    Node* rotate_left(Node* node)
    {
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fix_height(node);
        fix_height(tmp);
        fix_size(node);
        fix_size(tmp);
        return tmp;
    }

    Node* rotate_right(Node* node)
    {
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fix_height(node);
        fix_height(tmp);
        fix_size(node);
        fix_size(tmp);
        return tmp;
    }
    
    Node* balance(Node* node)
    {
        fix_height(node);
        fix_size(node);
        int bf = bfactor(node);
        
        if (bf == 2)
        {
            if (bfactor(node->right) < 0)
            {
                node->right  = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        else if (bf == -2)
        {
            if (bfactor(node->left) > 0)
            {
                node->left  = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }
    
    Node* root;
    size_t tree_size;
    Comparator comp;

    Value k_search(size_t pos, Node* node)
    {
        pos++;
        node = root;

        size_t l_size = size(root->left);
        size_t r_size = size(root->right);
        size_t elems_from_left = l_size;

        while (pos - elems_from_left != 1)
        {
            if (elems_from_left < pos - 1)
            {
                node = node->right;
                elems_from_left += size(node->left) + 1;
            }
            else
            {
                node = node->left;
                elems_from_left -= size(node->right) + 1;
            }
        }
        return node->value;
    }
};

int main()
{
    AVLTree<int, int> avlTree;
    int n = 0;
    std::cin >> n;
    int value = 0, k = 0;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> value >> k;
        if (value > 0)
            avlTree.insert(value, value);
        else
            avlTree.erase(-value);
        
        std::cout << avlTree.kth_search(k) << std::endl;
    }
    return 0;
}