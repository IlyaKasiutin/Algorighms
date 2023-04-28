/*Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. 
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.*/

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
    17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 
    10949, 21911, 43853, 87719, 175447, 350899, 701819, 1403641
};

template<typename Key> struct hash {
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
    ~HashSet() {}

    HashSet(const HashSet&)=delete;
    HashSet(HashSet&&)=delete;

    HashSet& operator=(const HashSet&) = delete;
    HashSet& operator=(HashSet&&) = delete;


    int find(const Key& k) 
    {
        if (empty())
        {
            return -1;
        }

        size_t cur_pos = hasher(k) % buckets_count;
        size_t step = 1;

        while (step <= buckets_count && !buckets[cur_pos].empty)
        {
            if (!(buckets[cur_pos].key == k && !buckets[cur_pos].deleted))
            {
                cur_pos = (cur_pos + step % m) % buckets_count;
                step++;
            }
            else
            {
                return cur_pos;
            }
        }
        return -1;
    }

    bool insert(const Key& k) 
    {
        if (find(k) != -1)
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
        buckets[idx].deleted = false;
        items_count++;
        return true;
    }

    bool erase(const Key& k) 
    {
        int pos = find(k);
        if (pos == -1)
        {
            return false;
        }

        buckets[pos].deleted = true;
        items_count--;
        return true;
    }


    size_t empty() const
    {
        return items_count == 0;
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
        std::vector<Node> new_buckets(new_buckets_count);

        for (auto node: buckets)
        {
            if (node.empty || node.deleted) continue;

            size_t idx = hasher(node.key) % new_buckets_count;
            int step = 1;
            while(!new_buckets[idx].empty && step < buckets_count)
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
                result = (set.find(key) != -1);
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