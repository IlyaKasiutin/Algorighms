/*Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне [0..232-1]
Требования:
    B-дерево должно быть реализовано в виде шаблонного класса.
    Решение должно поддерживать передачу функции сравнения снаружи.*/

#include <iostream>
#include <assert.h>
#include <vector>
#include <sstream>
#include <deque>

template <class T>
struct DefaultComparator
{
    int operator () (const T& l, const T& r) const
    {
        if ( l < r ) return -1;
        if ( l > r ) return 1;
        return 0;
    }
};

template <typename Key, typename Comparator = DefaultComparator<Key>>
class BTree
{
public:
    struct Node
    {
        Node(bool leaf, int h)
                : leaf(leaf), height(h)
        {
        }

        ~Node()
        {
            for (Node* child: children)
            {
                delete child;
            }
        }

        bool leaf;
        int height;
        std::vector<Key> keys;
        std::vector<Node*> children;

        void print()
        {
            std::cout << "keys size: " << keys.size() << std::endl;
            std::cout << "keys: [";
            for (auto key: keys)
            {
                std::cout << key << " ";
            }
            std::cout << "]" << std::endl;
            std::cout << "children: " << children.size() << std::endl << std::endl;
        }
    };

    BTree(size_t min_degree, Comparator comp = Comparator())
            : root(nullptr), t(min_degree), comp(comp)
    {
        assert(min_degree >= 2);
    }

    ~BTree()
    {
        if (root)
            delete root;
    }

    void insert(const Key &key)
    {
        if (!root)
            root = new Node(true, 1);

        if (is_node_full(root))
        {
            Node *newRoot = new Node(false, 1);
            newRoot->children.push_back(root);
            root = newRoot;
            split(root, 0);
        }

        insert_non_full(root, key);
    }

    bool find(const Key &key)
    {
        return find_aux(root, key);
    }

    void print()
    {
        std::deque<Node*> d = bfs();
        int cur_height = 1;
        for (auto node: d)
        {
            if (node->height != cur_height)
            {
                std::cout << std::endl;
                cur_height = node->height;
            }
            for (int value: node->keys)
            {
                std::cout << value << " ";
            }
        }
        std::cout << std::endl;
    }

private:
    int height(Node* node) const
    {
        return node ? node->height : 0;
    }

    void fix_height(Node* node)
    {
        if (node->leaf)
            return;

        for (int i = 0; i < node->children.size(); i++)
        {
            node->children[i]->height = node->height + 1;
            fix_height(node->children[i]);
        }
    }

    bool is_node_full(Node *node)
    {
        return node->keys.size() == 2*t - 1;
    }

    bool find_aux(Node* node, const Key &key)
    {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
            i++;

        if (i < node->keys.size() && key == node->keys[i])
            return true;
        else if (node->leaf)
            return false;
        else
            return find_aux(node->children[i], key);
    }

    void split(Node *node, size_t index)
    {
        Node* new_node = new Node(false, node->height + 1);
        Node* split_node = node->children[index];

        new_node->leaf = split_node->leaf;
        for (int j = 0; j < t - 1; j++)
        {
            new_node->keys.push_back(split_node->keys[t + j]);
        }

        if (!split_node->leaf)
        {
            for (int j = 0; j < t; j++)
            {
                new_node->children.push_back(split_node->children[t + j]);
            }
        }
        split_node->keys.resize(t - 1);
        split_node->children.resize(t);

        node->children.push_back(nullptr);
        for (int j = node->children.size() - 1; j > index; --j)
        {
            node->children[j] = node->children[j - 1];
        }
        node->children[index + 1] = new_node;

        node->keys.push_back(0);
        for (int j = node->keys.size() - 1; j > index; --j)
        {
            node->keys[j] = node->keys[j - 1];
        }
        node->keys[index] = split_node->keys[t - 1];
    }

    void insert_non_full(Node *node, const Key &key)
    {
        int pos = node->keys.size() - 1;
        if (node->leaf)
        {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos])
            {
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            node->keys[pos + 1] = key;
        }
        else
        {
            while (pos >= 0 && key < node->keys[pos])
            {
                pos--;
            }

            if (is_node_full(node->children[pos + 1]))
            {
                split(node, pos + 1);
                if (key > node->keys[pos + 1])
                {
                    pos++;
                }
            }
            insert_non_full(node->children[pos + 1], key);
        }
    }

    std::deque<Node*> bfs()
    {
        fix_height(root);
        std::deque<Node*> list;
        std::deque<Node*> buf;
        buf.push_back(root);
        while (buf.size() > 0)
        {
            list.push_back(buf.front());
            if (!buf.front()->leaf)
            {
                for (int i = 0; i < buf.front()->children.size(); i++)
                {
                    buf.push_back(buf.front()->children[i]);
                }
            }
            buf.pop_front();
        }
        return list;
    }




    Node *root;
    Comparator comp;
    size_t t; // minimum degree

};

int main()
{
    unsigned int t = 0;
    std::cin >> t;
    BTree<int> b_tree(t);
    int value = 0;
    while (std::cin >> value)
        b_tree.insert(value);

    b_tree.print();
    return 0;
}