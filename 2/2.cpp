#include <iostream>
#include <queue>
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

    ~BinaryTree() {}

    void insert(const T& val)
    {
        if (!root)
        {
            root = new Node(val);
        }
        else
        {
            Node* cur_node = root;
            while (cur_node)
            {
                if (comp(cur_node->value, val))
                {
                    cur_node = cur_node->right;
                }
                else
                {
                    cur_node = cur_node->left;
                }
            }
            cur_node = new Node(val);
        }
    }

    std::queue<T> bfs(void (*operation_function)(std::queue<T>&) = nullptr)
    {
        std::queue<T> list;
        std::vector<T> output;
        Node* cur_node = root;
        std::cout << root->value << std::endl;
        list.push(root->value);
        while (list.size() > 0)
        {
            auto elem = list.front();
            std::cout << elem << elem->right << std::endl;
            output.push_back(list.front());
            /*if (list.front()->left)
                list.push(list.front().left.value);
            if (list.front()->right)
                list.push(list.front().right.value);*/
            list.pop();
        }

        std::cout << "queue: ";
        for (auto &val: output)
            std::cout << val << " ";
        std::cout << std::endl;

        if (operation_function)
            operation_function(list);
        return list;
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
};

template <typename T>
void print(std::queue<T>& q)
{
    for (auto elem: q)
        std::cout << q << " ";
    std::cout << std::endl;
}

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
    
    tree.bfs();
    std::cout << "ok" << std::endl;
    return 0;
}