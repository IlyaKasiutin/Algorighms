#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <queue>

static const size_t LINE_SIZE = 3;
static const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using FieldArray = std::array<uint8_t, FIELD_SIZE>;

const FieldArray EMPTY_STATE = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};

const FieldArray GOAL_STATE = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
}; 

class FieldState
{
public:
    FieldState(const FieldState& st) :state(st.state), zero_pos(st.zero_pos) {}
    FieldState(const FieldArray& arr)
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
        std::vector<FieldState> result;

        if (zero_pos >= LINE_SIZE)
        {
            FieldState st(*this);
            st.move_up();
            result.push_back(st);
        }

        if (zero_pos < FIELD_SIZE - LINE_SIZE)
        {
            FieldState st(*this);
            st.move_down();
            result.push_back(st);
        }

        if (zero_pos % LINE_SIZE)
        {
            FieldState st(*this);
            st.move_left();
            result.push_back(st);
        }

        if ((zero_pos + 1) % LINE_SIZE)
        {
            FieldState st(*this);
            st.move_right();
            result.push_back(st);
        }
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

    FieldArray state;
    int zero_pos;
};

void bfs(FieldState start)
{
    FieldState empty(EMPTY_STATE);
    FieldState goal(GOAL_STATE);

    std::map<FieldState, FieldState> visited;
    visited.insert({start, empty});

    std::queue<FieldState> q;
    q.push(start);

    FieldState current(EMPTY_STATE);
    while (!q.empty())
    {
        current = q.front();
        q.pop();

        if (current == goal)
        {
            break;
        }

        std::vector<FieldState> children = current.GetNextVertices();
        for (auto it: children)
        {
            if (visited.find(it) == visited.end())
            {
                visited.insert({it, current});
                q.push(it);
            }
        }
    }

    if (q.empty())
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        int steps_count = 0;
        while (current != empty)
        {
            current.print();
            current = visited.find(current)->second;
            steps_count++;
        }
        std::cout << steps_count << std::endl;
    }
}

int main()
{
    FieldState ex(
        {
            1, 2, 3,
            4, 5, 0,
            7, 8, 6
        }
    );
    bfs(ex);
    return 0;
}