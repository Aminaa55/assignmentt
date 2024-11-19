#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Visitor {
public:
    string id;
    char sex;
    string arrival;
    string category;

    Visitor(string id, char gender, string arrival, string category)
        : id(id), sex(gender), arrival(arrival), category(category) {}

    void showDetails() const {
        cout << "ID: " << id
             << ", Gender: " << sex
             << ", Arrival: " << arrival
             << ", Category: " << category << endl;
    }
};

class QueueSystem {
private:
    queue<Visitor> criticalQueue;
    queue<Visitor> routineQueue;

public:
    vector<Visitor> completedVisitors;

    void enqueue(const Visitor& visitor) {
        if (visitor.category == "Critical")
            criticalQueue.push(visitor);
        else
            routineQueue.push(visitor);
    }

    vector<Visitor> process(int maxServe) {
        vector<Visitor> processed;
        while (maxServe > 0) {
            if (!criticalQueue.empty()) {
                processed.push_back(criticalQueue.front());
                criticalQueue.pop();
            } else if (!routineQueue.empty()) {
                processed.push_back(routineQueue.front());
                routineQueue.pop();
            } else {
                break;
            }
            maxServe--;
        }
        completedVisitors.insert(completedVisitors.end(), processed.begin(), processed.end());
        return processed;
    }

    size_t criticalQueueSize() const { return criticalQueue.size(); }
    size_t routineQueueSize() const { return routineQueue.size(); }
};

string generateID() {
    string id = "";
    for (int i = 0; i < 14; ++i)
        id += to_string(rand() % 10);
    return id;
}

string generateTime() {
    int hour = rand() % 24;
    int minute = rand() % 60;
    return (hour < 10 ? "0" : "") + to_string(hour) + ":" +
           (minute < 10 ? "0" : "") + to_string(minute);
}

char randomGender() {
    return (rand() % 2 == 0) ? 'M' : 'F';
}

string randomCategory() {
    return (rand() % 2 == 0) ? "Critical" : "Routine";
}

vector<Visitor> createVisitors(int count) {
    vector<Visitor> visitors;
    for (int i = 0; i < count; ++i) {
        visitors.emplace_back(generateID(), randomGender(), generateTime(), randomCategory());
    }
    return visitors;
}

void simulateQueueSystem(int totalVisitors, int rounds) {
    vector<Visitor> visitors = createVisitors(totalVisitors);
    QueueSystem queueSystem;

    for (int round = 1; round <= rounds; ++round) {
        cout << "\n--- Round " << round << " ---\n";

        int visitorsThisRound = rand() % 3 + 1; // Enqueue 1-3 visitors per round
        for (int i = 0; i < visitorsThisRound && !visitors.empty(); ++i) {
            Visitor current = visitors.front();
            visitors.erase(visitors.begin());
            queueSystem.enqueue(current);
            cout << "Queued Visitor: ";
            current.showDetails();
        }

        int serveCount = rand() % 6 + 5; // Serve 5-10 visitors
        vector<Visitor> served = queueSystem.process(serveCount);
        cout << "Served in this round (" << served.size() << "):\n";
        for (const auto& visitor : served)
            visitor.showDetails();

        cout << "Press Enter to continue...";
        cin.ignore();
    }

    cout << "\n--- Simulation Summary ---\n";
    cout << "Total Visitors Processed: " << queueSystem.completedVisitors.size() << "\n";
    cout << "Critical Queue Remaining: " << queueSystem.criticalQueueSize() << "\n";
    cout << "Routine Queue Remaining: " << queueSystem.routineQueueSize() << "\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int visitorCount, rounds;
    cout << "Enter the number of visitors to simulate: ";
    cin >> visitorCount;
    cout << "Enter the number of simulation rounds: ";
    cin >> rounds;

    simulateQueueSystem(visitorCount, rounds);
    return 0;
}
