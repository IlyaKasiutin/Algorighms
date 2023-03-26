#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
    Process(int P, int T): P(P), T(T), t(0) {}
    
    void Update() { t += P; }
    int get_T() { return T; }
    int get_t() { return t; }

    bool operator<(Process other_process)
    {
        return P * (t + 1) < other_process.P * (other_process.t + 1);
    }

private:
    int P;
    int t;
    int T;

};

#endif