#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <string>

using namespace std;

class Graph {
public:
    unordered_map<string, unordered_map<string, int>> vertices;

    void addVertex(const string &vname) {
        vertices[vname];
    }

    void addEdge(const string &vname1, const string &vname2, int cost) {
        vertices[vname1][vname2] = cost;
        vertices[vname2][vname1] = cost;
    }

    bool containsVertex(const string &vname) {
        return vertices.find(vname) != vertices.end();
    }

    pair<int, vector<string>> dijkstra(const string &src, const string &dest) {
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;
        vector<string> path;

        for (const auto &vpair : vertices) {
            dist[vpair.first] = INT_MAX;
        }

        dist[src] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [currentDist, currentVertex] = pq.top();
            pq.pop();

            if (currentDist > dist[currentVertex]) continue;

            for (const auto &npair : vertices[currentVertex]) {
                const string &neighbor = npair.first;
                int edgeCost = npair.second;

                if (dist[currentVertex] + edgeCost < dist[neighbor]) {
                    dist[neighbor] = dist[currentVertex] + edgeCost;
                    prev[neighbor] = currentVertex;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }

        int cost = dist[dest];
        if (cost == INT_MAX) {
            return {cost, {}};
        }

        for (string at = dest; !at.empty(); at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        return {cost, path};
    }
};

void createVaranasiMap(Graph &g) {
    g.addVertex("Akhari Bypass");
    g.addVertex("Dafi");
    g.addVertex("BHU Gate");
    g.addVertex("BHU VT");
    g.addVertex("Samne Ghat");
    g.addVertex("DurgaKund");
    g.addVertex("SankatMochan");
    g.addVertex("Assi Ghat");
    g.addVertex("Old VT");
    g.addVertex("Sigra Chauraha");
    g.addVertex("ManiKanika Ghat");
    g.addVertex("Cant RailwayStation");
    g.addVertex("Sarnath");
    g.addVertex("Namoghat");
    g.addVertex("Babatpur Airport");
    g.addVertex("Hardev Mandir");
    g.addVertex("Ramnagar Kila");

    g.addEdge("Akhari Bypass", "BHU Gate", 40);
    g.addEdge("Akhari Bypass", "Dafi", 10);
    g.addEdge("Dafi", "BHU Gate", 10);
    g.addEdge("BHU Gate", "Samne Ghat", 10);
    g.addEdge("BHU Gate", "BHU VT", 20);
    g.addEdge("BHU Gate", "DurgaKund", 15);
    g.addEdge("BHU Gate", "SankatMochan", 10);
    g.addEdge("BHU Gate", "Ramnagar Kila", 15);
    g.addEdge("BHU Gate", "Assi Ghat", 20);
    g.addEdge("Samne Ghat", "Ramnagar Kila", 10);
    g.addEdge("DurgaKund", "Old VT", 40);
    g.addEdge("DurgaKund", "Assi Ghat", 10);
    g.addEdge("DurgaKund", "Sigra Chauraha", 20);
    g.addEdge("SankatMochan", "Assi Ghat", 15);
    g.addEdge("Assi Ghat", "Old VT", 25);
    g.addEdge("Assi Ghat", "ManiKanika Ghat", 30);
    g.addEdge("Sigra Chauraha", "Cant RailwayStation", 15);
    g.addEdge("Old VT", "ManiKanika Ghat", 5);
    g.addEdge("Cant RailwayStation", "ManiKanika Ghat", 30);
    g.addEdge("Cant RailwayStation", "Old VT", 30);
    g.addEdge("Cant RailwayStation", "Sarnath", 35);
    g.addEdge("Sarnath", "Namoghat", 40);
    g.addEdge("Sarnath", "Babatpur Airport", 50);
    g.addEdge("Sarnath", "Hardev Mandir", 60);
    g.addEdge("Babatpur Airport", "Hardev Mandir", 50);
    g.addEdge("Namoghat", "Ramnagar Kila", 30);
}

int main() {
    Graph g;
    createVaranasiMap(g);

    cout << "\n\t\t\t****WELCOME TO THE VARANASI TOURIST'S PLACES APP*****\n";

    while (true) {
        cout << "\n\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout << "1. LIST ALL THE VARANASI'S TOURIST PLACES IN THE MAP\n";
        cout << "2. SHOW THE TOURIST PLACES\n";
        cout << "3. GET SHORTEST PATH (COST WISE) FROM A 'SOURCE' LOCATION TO 'DESTINATION' LOCATION\n";
        cout << "4. SHOW DISTANCE FROM CURRENT LOCATION TO A TOURIST PLACE\n";
        cout << "5. EXIT THE MENU\n";
        cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 5) : ";
        int choice;
        cin >> choice;

        cout << "\n***********************************************************\n";

        if (choice == 5) {
            break;
        }

        switch (choice) {
            case 1:
                cout << "The Varanasi tourist places are:\n";
                for (const auto &vpair : g.vertices) {
                    cout << "- " << vpair.first << endl;
                }
                break;
            case 2:
                cout << "\t\t\tVaranasi Tourist Place Map\n";
                cout << "-------------------------------------\n";
                for (const auto &vpair : g.vertices) {
                    const string &vname = vpair.first;
                    const unordered_map<string, int> &neighbors = vpair.second;
                    cout << vname << " =>\n";
                    for (const auto &npair : neighbors) {
                        cout << "\t" << npair.first << "\t" << npair.second << endl;
                    }
                    cout << endl;
                }
                cout << "-------------------------------------\n";
                break;
            case 3:
                {
                    string src, dest;
                    cout << "Enter the source location: ";
                    cin.ignore();
                    getline(cin, src);
                    cout << "Enter the destination location: ";
                    getline(cin, dest);

                    if (!g.containsVertex(src) || !g.containsVertex(dest)) {
                        cout << "Invalid input! One or both locations are not in the map.\n";
                    } else {
                        auto [cost, path] = g.dijkstra(src, dest);
                        if (cost == INT_MAX) {
                            cout << "No path exists between " << src << " and " << dest << ".\n";
                        } else {
                            cout << "The shortest path from " << src << " to " << dest << " is:\n";
                            for (const auto &p : path) {
                                cout << p;
                                if (p != dest) cout << " -> ";
                            }
                            cout << "\nTotal cost: " << cost << endl;
                        }
                    }
                }
                break;
            case 4:
                {
                    string current, place;
                    cout << "Enter your current location: ";
                    cin.ignore();
                    getline(cin, current);
                    cout << "Enter the tourist place you want to visit: ";
                    getline(cin, place);

                    if (!g.containsVertex(current) || !g.containsVertex(place)) {
                        cout << "Invalid input! One or both locations are not in the map.\n";
                    } else {
                        auto [cost, path] = g.dijkstra(current, place);
                        if (cost == INT_MAX) {
                            cout << "No path exists between " << current << " and " << place << ".\n";
                        } else {
                            cout << "The distance from " << current << " to " << place << " is " << cost << ".\n";
                        }
                    }
                }
                break;
            default:
                cout << "Invalid choice! Please choose a valid option (1-5).\n";
                break;
        }

        cout << "\n***********************************************************\n";
    }

    cout << "\nThank you for using the Varanasi Tourist's Places App! Goodbye!\n";

    return 0;
}

