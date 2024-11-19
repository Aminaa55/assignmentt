#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Patient {
public:
    string id;
    char gender;
    string arrival_time;
    string type;

    Patient(string id, char gender, string arrival_time, string type)
        : id(id), gender(gender), arrival_time(arrival_time), type(type) {}
};

void dispatchPatients(vector<Patient>& patients, queue<Patient>& urgentQueue, queue<Patient>& normalQueue, const string& currentTime) {
    for (auto it = patients.begin(); it != patients.end();) {
        if (it->arrival_time == currentTime) {
            if (it->type == "Urgent") {
                urgentQueue.push(*it);
            } else {
                normalQueue.push(*it);
            }
            it = patients.erase(it);
        } else {
            ++it;
        }
    }
}

void servePatients(queue<Patient>& urgentQueue, queue<Patient>& normalQueue, vector<Patient>& inService, int maxServe) {
    int served = 0;
    while (!urgentQueue.empty() && served < maxServe) {
        inService.push_back(urgentQueue.front());
        urgentQueue.pop();
        ++served;
    }
    while (!normalQueue.empty() && served < maxServe) {
        inService.push_back(normalQueue.front());
        normalQueue.pop();
        ++served;
    }
}

void displayStatus(const queue<Patient>& urgentQueue, const queue<Patient>& normalQueue, const vector<Patient>& inService, const vector<Patient>& completed) {
    cout << "Urgent Queue: ";
    for (auto q = urgentQueue; !q.empty(); q.pop()) {
        cout << q.front().id << " ";
    }
    cout << "\nNormal Queue: ";
    for (auto q = normalQueue; !q.empty(); q.pop()) {
        cout << q.front().id << " ";
    }
    cout << "\nIn Service: ";
    for (const auto& patient : inService) {
        cout << patient.id << " ";
    }
    cout << "\nCompleted Patients: ";
    for (const auto& patient : completed) {
        cout << patient.id << " ";
    }
    cout << endl;
}

int main() {
    vector<Patient> patients;
    queue<Patient> urgentQueue, normalQueue;
    vector<Patient> inService, completed;

    patients.push_back(Patient("28501012345678", 'M', "14:30", "Urgent"));
    patients.push_back(Patient("28501012345679", 'F', "14:35", "Normal"));

    string currentTime = "14:30";
    dispatchPatients(patients, urgentQueue, normalQueue, currentTime);
    servePatients(urgentQueue, normalQueue, inService, 5);
    displayStatus(urgentQueue, normalQueue, inService, completed);

    return 0;
}
