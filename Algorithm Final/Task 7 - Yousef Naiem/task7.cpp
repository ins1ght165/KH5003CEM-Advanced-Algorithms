#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

class Graph {
    int vertNum;   

    // We are going to create a pointer to an array containing the adjacency list
    list<int>* adj;    

public:

    // In our constructer we are declaring our functions
    Graph(int numberOfVertices);
    void createEdge(int v, int w);
    void orderVertices(int v, bool visited[], stack<int>& Stack);
    void findGroups(int v, bool visited[], int& size);
    void largestGroup();
    Graph transpose();
};

Graph::Graph(int numberOfVertices) {
    this->vertNum = numberOfVertices;
    adj = new list<int>[numberOfVertices];
}

// This function utulizes depth first search recursively from vertex v. Any adjacent vertex is explored and marked as visited once done. And as we are navigating the adjacent edges we are keeping a count to determine at the end the largest group
void Graph::findGroups(int v, bool visited[], int& size) {
    // Marking the current edge as visited
    visited[v] = true;  
    // Keeping a count of the size
    size++;  

    // Recursive call for all adjacent vertixes that have not been visited yet 
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            findGroups(*i, visited, size);
}

// This is our transpose funciton. This will reverse the order of every edge. 
Graph Graph::transpose() {
    Graph g(vertNum);
    for (int v = 0; v < vertNum; v++) {
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

// This function will allow us to manually add edges to our graph later in the main function 
void Graph::createEdge(int v, int w) {
    adj[v].push_back(w);
}

// Here we are ordering our vertices in order of their finishing time
void Graph::orderVertices(int v, bool visited[], stack<int>& Stack) {
    // marking our vertix we are currently on as visited
    visited[v] = true;

    // same recursive call to go through all adjacent vertices that have not been visited yet
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            orderVertices(*i, visited, Stack);

    // Pusing the vertices that we were able to reach into a stack 
    Stack.push(v);
}

// As the name implies this function is the find the largest aka the strongest connection groups. 
void Graph::largestGroup() {
    stack<int> Stack;

    // Mark all vertices as not visited for first depth first search. This will help us keep track of the visited verteces instead of having to go back later to check
    bool* visited = new bool[vertNum];
    for (int i = 0; i < vertNum; i++)
        visited[i] = false;

    // Based of their finishing times we will push them to a stack. So our last visited vertex will be at the top of the stack. 
    for (int i = 0; i < vertNum; i++)
        if (!visited[i])
            orderVertices(i, visited, Stack);

    // Now we will transpose the graph. In other words reverse the order
    Graph gr = transpose();

    // Same thing again here we will mark all the verteces as unvisited again. 
    for (int i = 0; i < vertNum; i++)
        visited[i] = false;

    // Now we will navigate the stack that we have previously created. And start to pop every vertex one by one. But everytime we will check if it has been visited or not.
    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        // If we find one vertex that has not been visited yet we will call the findGroups() function to perform the depth first search again but this time on the transpose graph and count the groups
        // And at the end we print out the sizes of the group
        if (!visited[v]) {
            int size = 0;
            gr.findGroups(v, visited, size);
            cout << "Size of group is " << size << endl;
        }
    }

    // Freeing up the memory after we are finished
    delete[] visited; 
}

// Main function 
int main() {
    cout << "Initializing Kosaraju's algorithm to find the largest groups based of the given graph: " << endl;
    // Calling the graph function
    Graph g(7); 

    g.createEdge(1, 0);
    g.createEdge(0, 2);
    g.createEdge(2, 1);
    g.createEdge(0, 3);
    g.createEdge(3, 0);
    g.createEdge(4, 3);
    g.createEdge(3, 4);


    // Calling our function to print all strongest connected groups
    g.largestGroup();  

}
