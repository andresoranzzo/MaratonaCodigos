#include <bits/stdc++.h>
using namespace std;

/*
Example:
1
4 5
1 4 5 7 5 2 -2 4
-4 -2 3 9 1 2 -1 3 8 -3
*/

struct point2d
{
    int x, y;
};
struct dataset
{
    int n, m;
    vector<point2d> bobRoute;
    vector<point2d> ralphRoute;
};

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// O(V + E)
bool bfs(vector<vector<int>> graph, int n, int m, int source, int target, map<int, int> &parent)
{
    parent.clear();
    queue<int> q;
    q.push(source);
    int u, v, f;
    map<int, int> visited;

    while (!q.empty())
    {
        u = q.front();
        q.pop();
        if (visited[u] == 1)
        {
            continue;
        }
        visited[u] = 1;
        if (u == target)
        {
            return true;
        }
        // for all edges in G.adjacentEdges()
        for(int p=0; p<graph[u].size(); p++){
            v = graph[u][p];
            //cout << "v: " << v << " | v+n+1: " << v+n+1 << endl;
            if(v+n+1 <= n+m+1){
                parent[v + n + 1] = u;
                // Adjust vertex to correct graph format
                q.push(v + n + 1);
            }
            
        }
    }
    return false;
}

// O(max_flor * E)
int fk(vector<vector<int>> graph, int n, int m)
{
    int source = 0;
    int target = n + m + 1;
    long maxFlow = 0;
    map<int, int> parent;
    while (bfs(graph, n, m, source, target, parent) == true)
    {

        int v = target;
        int min_flow = INT_MAX;
        int u;
        while (v != source)
        {

            u = parent[v];
            min_flow = min(graph[u][v], min_flow);
            v = u;
        }
        v = target;
        while (v != source)
        {
            u = parent[v];
            graph[u][v] -= min_flow; // sentido usual.
            graph[v][u] += min_flow; // sentido contrario, pra podermos ver quais escolhas foram feitas.
            v = u;
        }
        maxFlow += min_flow;
    }
    return maxFlow;
}

int main()
{
    //variable declaration
    int l, i, j, z;
    dataset datasetAux;
    point2d pointAux;
    vector<dataset> dataset;
    cin >> l;
    // O(l)
    for (z = 0; z < l; z++)
    {
        cout << endl; //blank line between datasets
        cin >> datasetAux.n >> datasetAux.m;
        //Create graph
        //vector<int> graph[datasetAux.n + datasetAux.m + 2];
        vector<vector<int>> graph(datasetAux.n+datasetAux.m+2, vector<int>(datasetAux.n+datasetAux.m+2, 0));  
        //read bob's route
        datasetAux.bobRoute.clear();
        for (j = 1; j <= datasetAux.n; j++)
        {
            cin >> pointAux.x >> pointAux.y;
            datasetAux.bobRoute.push_back(pointAux);
            // Link Source to all Bob`s vertex.
            graph[0][j] = 1;
        }

        datasetAux.ralphRoute.clear();
        for (j = datasetAux.n+1; j <=  datasetAux.n+datasetAux.m; j++)
        {
            cin >> pointAux.x >> pointAux.y;
            datasetAux.ralphRoute.push_back(pointAux);
            // Link Ralph`s vertices to Target.
            graph[j][datasetAux.n+datasetAux.m] = 1;
        }

        // Link Bob`s vertices to Ralph`s vertices.
        for (int i = 0; i < datasetAux.n-1; i++)
        {
            // check if we can go to jth-interest place and go back to i+1-th place
            //double distance(int x1, int y1, int x2, int y2)
            double distance_i_nextI = distance(datasetAux.bobRoute[i].x, datasetAux.bobRoute[i].y,
                                               datasetAux.bobRoute[i + 1].x, datasetAux.bobRoute[i + 1].y);

            for (int j = 0; j < datasetAux.ralphRoute.size(); j++)
            {
                double distance_i_j = distance(datasetAux.bobRoute[i].x, datasetAux.bobRoute[i].y,
                                               datasetAux.ralphRoute[j].x, datasetAux.ralphRoute[j].y);

                double distance_j_nextI = distance(datasetAux.ralphRoute[j].x, datasetAux.ralphRoute[j].y,
                                                   datasetAux.bobRoute[i + 1].x, datasetAux.bobRoute[i + 1].y);
                if (distance_i_j + distance_j_nextI <= distance_i_nextI * 2)
                {
                    graph[i + 1].push_back(datasetAux.n + 1 + j);
                }
            }
        }

        fk(graph, datasetAux.n, datasetAux.m);
        
        // Choose path
        vector<point2d> output;
        vector<int> visitedPoints(datasetAux.m, 0);
        for(int y=0; y<datasetAux.n; y++)
        {
            // Add Bob vertex i
            output.push_back(datasetAux.bobRoute[y]);
            // Try to find interesting point in the middle
            for (int u = 0; u<graph[y+1].size(); u++)
            {
                int pointRalph = graph[y+1][u]-datasetAux.n;
                if(visitedPoints[pointRalph] == 0){
                    output.push_back(datasetAux.ralphRoute[graph[y+1][u]-datasetAux.n]);
                    visitedPoints[pointRalph] = 1;
                    break;
                }
                
            }
        }

        // Output
        cout << output.size() << endl;
        for(int y=0; y<output.size(); y++){
            cout << output[y].x << " " << output[y].y << " ";
        }
        cout << endl;
    }
    return 0;
}