#include <iostream>
#include<bits/stdc++.h>

using namespace std;


// Create and define status for the Farmer, wolf, goat and cabbage
struct status {
    // Inittially, all atom are in the same bank so define the status for all as 1 
    int farmer = 1;
    int wolf = 1; 
    int goat = 1;
    int cab = 1; 

    // Init the f, g, h for a* algorithm
    int g = 0;
    int h = 0;
    int f = 0;

    // Initialize the previous status 
    struct status* prev = NULL;
    bool operator<(const status& n) const {
        return f > n.f; // for the priority queue to order nodes by lowest f_cost
    }
};

// Define the unavailable status 
bool false_status (status current_status) {
    if (current_status.farmer != current_status.goat){
        if (current_status.goat == current_status.wolf) return false;
        if (current_status.goat == current_status.cab) return false;
    }
    return true;
}

// Define 4 action in the puzzle 
status move_wolf (status current_status) {
    current_status.farmer = 1 - current_status.farmer;
    current_status.wolf = 1 - current_status.wolf;

    return current_status;
}

status move_goat (status current_status) {
    current_status.farmer = 1 - current_status.farmer;
    current_status.goat = 1 - current_status.goat;

    return current_status;
}

status move_cab (status current_status) {
    current_status.farmer = 1 - current_status.farmer;
    current_status.cab = 1 - current_status.cab;

    return current_status;
}

status move_nothing (status current_status) {
    current_status.farmer = 1 - current_status.farmer;

    return current_status;
}

// Calculate the heuristic cost to move object 
int cal_h(status current_status) {
    return current_status.farmer + current_status.wolf + current_status.goat + current_status.cab;
}

// Calculate f cost of the current status 
status cal_f(status current_status, status prev_status) {
    current_status.prev = new status;
    *current_status.prev = prev_status;
    current_status.g = prev_status.g + 1;
    current_status.h = cal_h(current_status);
    current_status.f = current_status.g + current_status.h;

    return current_status;
}

// Check fiinshed status 
bool isGoal(status current_status){
    return current_status.farmer + current_status.wolf + current_status.goat + current_status.cab == 0;
}

bool checkIfExist (priority_queue<status>& pq, status& node) {
    priority_queue<status> temp_pq = pq;
    while (!temp_pq.empty()) {
        if (temp_pq.top().farmer == node.farmer &&
            temp_pq.top().wolf == node.wolf &&
            temp_pq.top().goat == node.goat &&
            temp_pq.top().cab == node.cab)
            return true;
        temp_pq.pop();
    }
    return false;
}

bool checkIfExist (vector<status> vt, status current_status) {
    for (int i = 0; i < vt.size(); i++) {
        if (vt[i].farmer == current_status.farmer &&
            vt[i].wolf == current_status.wolf &&
            vt[i].goat == current_status.goat &&
            vt[i].cab == current_status.cab)
            return true;
    }
    return false;
}

vector<status> getNeighbors(status current_status) {
    vector<status> vt_temp;

    if (current_status.farmer == current_status.wolf) {
        status temp = move_wolf(current_status);
        temp = cal_f(temp, current_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    if (current_status.farmer == current_status.goat) {
        status temp = move_goat(current_status);
        temp = cal_f(temp, current_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    if (current_status.farmer == current_status.cab) {
        status temp = move_cab(current_status);
        temp = cal_f(temp, current_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    if (1 == 1) {
        status temp = move_nothing(current_status);
        temp = cal_f(temp, current_status);
        if (false_status(temp)){
            vt_temp.push_back(temp);
        }
    }
    return vt_temp;

}

void print(status* goal){
    cout << goal->farmer << " " << goal->wolf << " " << goal->goat << goal->cab << endl;
    do {
        goal = goal->prev;
        cout << goal->farmer << " " << goal->wolf << " " << goal->goat << " " << goal->cab << endl;
    } while (goal->prev != NULL); 
}

template <typename T>
void astar(T curstatus, vector<T> (*getNeighbors)(T), bool (*isGoal)(T), void (*print)(T*)) {
    priority_queue <T> open;
    vector<T> close;
    open.push(curstatus);

    T* goal = new T;
    int isOut = false;

    while(open.size() > 0) {
        curstatus = open.top();

        open.pop();

        vector<T> vt_temp = getNeighbors(curstatus);

        for (T i: vt_temp) {
            if (isGoal(i)) {
                goal = &i;
                isOut = true;
                break;
            }
        }

        if (isOut)
            break;

        for (T i: vt_temp) {
            if (!checkIfExist(close, i) && !checkIfExist(open, i)) {
                open.push(i);
            }
        }
        close.push_back(curstatus);
    }

    print(goal);
}

int main() {
    status current_status;
    current_status.farmer = 1;
    current_status.wolf = 1; 
    current_status.goat = 1; 
    current_status.cab = 1; 

    astar(current_status, &getNeighbors, &isGoal, &print);

    return 0;
}