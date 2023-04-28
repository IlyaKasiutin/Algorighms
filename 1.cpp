#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

size_t str_hash(const std::string& data) 
{
    size_t hash = 0;
    for (char i : data)
        hash = hash * 13 + i ;
    return hash;
}


static constexpr size_t BUCKETS_SIZES_LIST[] = {
    17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 
    10949, 21911, 43853, 87719, 175447, 350899, 701819, 1403641
};

template< class Key > struct hash {
    size_t operator()(const Key& value) {
        return value;
    }
};

template<> struct hash<std::string> {
    size_t operator()(const std::string& value) {
        return str_hash(value);
    }
};


template<typename Key, typename Hash=hash<Key>>
class HashSet {
    static constexpr double LOAD_FACTOR = 0.75;
public:
    HashSet() : buckets(INITIAL_SIZE), buckets_count(INITIAL_SIZE), buckets_sizes_list_idx(0), items_count(0),
    hasher(Hash()) {}
    ~HashSet() 
    {
        //delete[] buckets;
    }

    HashSet(const HashSet&)=delete;
    HashSet(HashSet&&)=delete;

    HashSet& operator=(const HashSet&)=delete;
    HashSet& operator=(HashSet&&)=delete;


    Key* find(const Key& k) 
    {
        if (empty())
        {
            return nullptr;
        }

        size_t cur_pos = hasher(k) % buckets_count;
       // std::cout << "cur_pos: " << cur_pos << std::endl;
        size_t step = 1;
        size_t steps_limit = buckets_count;

        while (step <= steps_limit)
        {
            if (buckets[cur_pos].key != k || buckets[cur_pos].deleted)
            {
                cur_pos = (cur_pos + step % m) % buckets_count;
                step++;
            }
            else
            {
                return &buckets[cur_pos].key;
            }
        }
        return nullptr;
    }

    bool insert(const Key& k) 
    {
        if (find(k))
        {
            return false;
        }

        if (double(items_count) / buckets_count >= LOAD_FACTOR)
        {
            grow();
        }

        size_t idx = hasher(k) % buckets_count;
        int step = 1;
        while(!(buckets[idx].empty || buckets[idx].deleted))
        {
            idx = (idx + step % m) % buckets_count;
            step++;
        }
        buckets[idx].key = k;
        buckets[idx].empty = false;
        items_count++;
        return true;
    }

    bool erase(const Key& k) 
    {
        size_t idx = hasher(k) % buckets_count;
        int step = 1;
        while(!(buckets[idx].key == k && !buckets[idx].deleted) && !buckets[idx].empty)
        {
            idx = (idx + step % m) % buckets_count;
            step++;
        }

        if (buckets[idx].key == k && !buckets[idx].deleted)
        {
            buckets[idx].deleted = true;
            items_count--;
            return true;
        }
        else if (buckets[idx].empty)
        {
            return false;
        }
        return false;
    }


    size_t empty() const
    {
        return items_count == 0;
    }

    void print()
    {
        for (auto node: buckets)
        {
            if (node.key == "" || node.deleted)
                std::cout << "0" << " ";
            
            else
                std::cout << node.key << " ";
        }
        std::cout << std::endl;
    }

private:

    struct Node
    {
        Node(): deleted(false), empty(true) {}
        Node(const Key& k): key(k), deleted(false), empty(true) {}

        Key key;
        bool deleted;
        bool empty;
    };

    void grow()
    {
        size_t new_buckets_count = BUCKETS_SIZES_LIST[buckets_sizes_list_idx++];
        //size_t new_buckets_count = 2 * buckets_count;
        std::vector<Node> new_buckets(new_buckets_count);

        for (auto node: buckets)
        {
            if (node.empty || node.deleted) continue;

            size_t idx = hasher(node.key) % new_buckets_count;
            int step = 1;
            while(!new_buckets[idx].empty)
            {
                idx = (idx + step % 1024) % new_buckets_count;
                step++;
            }
            new_buckets[idx].key = node.key;
            new_buckets[idx].empty = false;
        }

        buckets = new_buckets;
        buckets_count = new_buckets_count;
    }

    static constexpr int INITIAL_SIZE = 8;
    std::vector<Node> buckets;
    size_t buckets_count;

    size_t buckets_sizes_list_idx;
    size_t items_count;

    Hash hasher;

    int m = 8192;
};


int main() {
    HashSet<std::string> set;
    std::string key;
    char operation;
    while(std::cin >> operation >> key) {
        bool result = false;
        switch (operation) {
            case '+':
                result = set.insert(key);
                break;
            case '-':
                result = set.erase(key);
                break;
            case '?':
                result = (set.find(key) != nullptr);
                break;
            default:
                break;
        }
        if (result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        //set.print();
    }
}