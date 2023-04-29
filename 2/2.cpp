
/*Дано число N < 10^6 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, 
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).*/

#include <iostream>
#include <deque>
#include <vector>

template <typename T>
struct DefaultComparator
{
    bool operator () (const T& l, const T& r) const
    {
        if (l < r) return true;
        return false;
    }
};

template <typename T,  typename Comparator = DefaultComparator<T> >
class BinaryTree
{
public:
    BinaryTree(Comparator comp = Comparator()): root(nullptr), comp(comp) {}
    BinaryTree(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

    ~BinaryTree()
    {
        std::deque<Node*> q = bfs();
        Node* cur_node;
        while (!q.empty())
        {
            cur_node = q.back();
            q.pop_back();
            delete cur_node;
        }
    }

    void insert(const T& val)
    {
        if (!root)
        {
            root = new Node(val);
        }
        else
        {
            Node* cur_node = root;
            while (true)
            {
                if (comp(cur_node->value, val))
                {
                    if (!cur_node->right)
                    {
                        cur_node->right = new Node(val);
                        break;
                    }
                    else
                        cur_node = cur_node->right;
                }
                else
                {
                    if (!cur_node->left)
                    {
                        cur_node->left = new Node(val);
                        break;
                    }
                    else
                        cur_node = cur_node->left;
                }
            }
        }
    }

    void print()
    {
        std::deque<Node*> q = bfs();
        while (!q.empty())
        {
            std::cout << q.front()->value << " ";
            q.pop_front();
        }
        std::cout << std::endl;
    }
    
private:
    struct Node
    {
        Node(const T& val): value(val), left(nullptr), right(nullptr) {}
        T value;
        Node* left;
        Node* right;
    };
    Node* root;
    Comparator comp;

    std::deque<Node*> bfs()
    {
        std::deque<Node*> list;
        std::deque<Node*> buf;
        buf.push_back(root);
        while (buf.size() > 0)
        {
            list.push_back(buf.front());
            if (buf.front()->left)
                buf.push_back(buf.front()->left);

            if (buf.front()->right)
                buf.push_back(buf.front()->right);

            buf.pop_front();
        }
        return list;
    }
};

int main()
{
    BinaryTree<int> tree;

    int n = 0, val = 0;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> val;
        tree.insert(val);
    }
    
    tree.print();
    return 0;
}