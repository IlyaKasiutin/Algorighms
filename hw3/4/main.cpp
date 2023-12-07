/*
Написать алгоритм для решения игры в “пятнашки”. 
Решением задачи является приведение к виду: [ 1 2 3 4 ] [ 5 6 7 8 ] [ 9 10 11 12] [ 13 14 15 0 ], 
где 0 задает пустую ячейку. 
Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.
*/

#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

static const size_t LINE_SIZE = 4;
static const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using FieldArray = std::array<uint8_t, FIELD_SIZE>;

const FieldArray EMPTY_STATE = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

const FieldArray GOAL_STATE = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 0
};

class FieldState
{
public:
    FieldState(const FieldState& st): state(st.state), zero_pos(st.zero_pos), distance(st.GetDistance()) {}
    FieldState(const FieldArray& arr, long long distance = 0): distance(distance)
    {
        for (int i = 0; i < arr.size(); ++i)
        {
            if (arr[i] == 0)
                zero_pos = i;
            state[i] = arr[i];
        }
    }


    ~FieldState() {}

    std::vector<FieldState> GetNextVertices() const
    {
        FieldState empty(EMPTY_STATE);
        std::vector<FieldState> result;

        if (zero_pos >= LINE_SIZE)
        {
            FieldState st(*this);
            st.move_up();
            result.push_back(st);
        }    
        else
            result.push_back(empty);

        if (zero_pos < FIELD_SIZE - LINE_SIZE)
        {
            FieldState st(*this);
            st.move_down();
            result.push_back(st);
        }
        else
            result.push_back(empty);

        if (zero_pos % LINE_SIZE)
        {
            FieldState st(*this);
            st.move_left();
            result.push_back(st);
        }
        else
            result.push_back(empty);

        if ((zero_pos + 1) % LINE_SIZE)
        {
            FieldState st(*this);
            st.move_right();
            result.push_back(st);
        }
        else result.push_back(empty);
        return result;
    }

    bool operator==(const FieldState& r) const
    {
        return state == r.state;
    }

    bool operator!=(const FieldState& r) const
    {
        return !(state == r.state);
    }

    bool operator<(const FieldState& r) const
    {
        return state < r.state;
    }

     void print() const
     {
        for (int i = 0; i < state.size(); ++i)
        {
            std::cout << (int)state[i] << " ";
            if ((i + 1) % LINE_SIZE == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << "_______________" << std::endl;
     }

     bool HasSolution() const
    {
        int n = 0, k = 0;
        k = zero_pos / LINE_SIZE + 1;

        for (int i = 0; i < state.size(); ++i)
        {
            if (state[i] == 0)
                continue;

            for (int j = 0; j < i; ++j)
            {
                if (state[j] > state[i] && state[j] != 0)
                {
                    n++;
                }
            }
        }
        return (n + k) % 2 == 0;
    }

    void SetDistance(long long dist)
    {
        distance = dist;
    }

    long long GetDistance() const
    {
        return distance;
    }

    long long GetMetric() const
    {
        double coeff = 3.0;

        if (state == EMPTY_STATE)
            return LINE_SIZE * LINE_SIZE * FIELD_SIZE + distance;

        int metric = 0;

        for (int i = 0; i < FIELD_SIZE; ++i)
        {
            if (state[i] == 0)
                continue;
            metric += (int) (manhattan_distance(state[i], i % LINE_SIZE, i / LINE_SIZE));
        }
        return coeff * metric + distance;
    }



private:
    void move_up()
    {
        int new_zero_pos = zero_pos - LINE_SIZE;
        std::swap(state[new_zero_pos], state[zero_pos]);
        zero_pos = new_zero_pos;
    }
    void move_down()
    {
        int new_zero_pos = zero_pos + LINE_SIZE;
        std::swap(state[new_zero_pos], state[zero_pos]);
        zero_pos = new_zero_pos;
    }
    void move_left()
    {
        int new_zero_pos = zero_pos - 1;
        std::swap(state[new_zero_pos], state[zero_pos]);
        zero_pos = new_zero_pos;
    }
    void move_right()
    {
        int new_zero_pos = zero_pos + 1;
        std::swap(state[new_zero_pos], state[zero_pos]);
        zero_pos = new_zero_pos;
    }

    int get_x(uint8_t value) const
    {
        if (value == 0)
            return LINE_SIZE - 1;
        return ((int)value - 1) % LINE_SIZE;
    }

    int get_y(uint8_t value) const
    {
        if (value == 0)
            return LINE_SIZE - 1;
        return ((int)value - 1) / LINE_SIZE;
    }

    int manhattan_distance(uint8_t value, int cur_x, int cur_y) const
    {
        int right_x = get_x(value);
        int right_y = get_y(value);
        return std::abs(cur_x - right_x) + std::abs(cur_y - right_y);
    }


    FieldArray state;
    int zero_pos;
    long long distance;
};

void a_star(FieldState start)
{
    if (!start.HasSolution())
    {
        std::cout << -1 << std::endl;
        return;
    }

    FieldState empty(EMPTY_STATE);
    FieldState goal(GOAL_STATE);

    std::map<FieldState, FieldState> visited;
    visited.insert({start, empty});

    auto cmp = [](FieldState left, FieldState right)
    {
        if (left.GetMetric() < right.GetMetric())
        {
            return true;
        }
        return false;
    };
    std::multiset<FieldState, decltype(cmp) > q(cmp);
    q.insert(start);

    FieldState current(EMPTY_STATE);
    while (!q.empty())
    {
        current = *q.begin();
        q.erase(q.begin());

        if (current == goal)
        {
            break;
        }
        
        std::vector<FieldState> children = current.GetNextVertices();
        for (auto it: children)
        {
            it.SetDistance(current.GetDistance() + 1);

            if (visited.find(it) == visited.end())
            {
                visited.insert({it, current});
                q.insert(it);
            }            
        }
    }

    int steps_count = 0;
    std::string path;
    while (current != empty)
    {
        FieldState previous = visited.find(current)->second;
        if (previous == empty)
            break;
        std::vector<FieldState> children = previous.GetNextVertices();
        if (current == children[0])
        {
            path += "D";
        }
        else if (current == children[1])
        {
            path += "U";
        }
        else if (current == children[2])
        {
            path += "R";
        }
        else if (current == children[3])
        {
            path += "L";
        }

        current = visited.find(current)->second;
        steps_count++;
    }
    std::cout << steps_count << std::endl;
    std::reverse(path.begin(), path.end());
    std::cout << path << std::endl;
}

int main()
{
    FieldArray input;
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        int elem;
        std::cin >> elem;
        input[i] = elem;
    }
    FieldState ex(input);
    a_star(ex);
    return 0;
}