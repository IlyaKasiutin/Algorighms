#include <iostream>
#include <string>
#include <vector>

size_t str_hash(const std::string& data) 
{
    size_t hash = 0;
    for (char i : data)
        hash = hash * 13 + i ;
    return hash;
}


static constexpr size_t BUCKETS_SIZES_LIST[] = {
    7, 17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 
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
    HashSet() : buckets(nullptr), buckets_count(0), buckets_sizes_list_idx(0), items_count(0) {
    }
    ~HashSet() {
        delete[] buckets;
    }

    HashSet(const HashSet&)=delete;
    HashSet(HashSet&&)=delete;

    HashSet& operator=(const HashSet&)=delete;
    HashSet& operator=(HashSet&&)=delete;


    Key* find(const Key& key) 
    {
        if (empty())
        {
            return nullptr;
        }

        size_t cur_pos = hash(key) % buckets_count;
        size_t step = 1;
        int m = 16;
        size_t steps_limit = buckets_count;

        while (step <= steps_limit)
        {
            if (buckets[cur_pos] != key)
            {
                cur_pos = (cur_pos + step % m) % buckets_count;
                step++;
            }
            else
            {
                return (&buckets[cur_pos]);
            }
        }
        return nullptr;
    }

    bool insert(const Key& key) 
    {

    }

    bool erase(const Key& key) 
    {

    }

    size_t empty() const
    {
        return items_count == 0;
    }


private:
    void grow()
    {

    }

    std::vector<Key>* buckets;
    size_t buckets_count;

    size_t buckets_sizes_list_idx;
    size_t items_count;

    Hash hasher;
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
    }
}