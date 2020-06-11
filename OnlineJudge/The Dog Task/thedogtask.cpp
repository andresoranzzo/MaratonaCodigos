#include <bits/stdc++.h>
using namespace std;

/*
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

bool bfs(map<int, map<int, int>> &graph, int n, int m, int source, int target, map<int, int> &parent)
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
        //   printf("Visiting node %d\n", u);
        visited[u] = 1;
        if (u == target)
        {
            return true;
        }
        for (auto it = graph[u].begin(); it != graph[u].end(); it++)
        {
            v = it->first;
            f = it->second;
            if (f == 1)
            {
                //    printf(" Adicionando na fila a partir do %d -> %d\n", u, v);
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return false;
}

int fk(map<int, map<int, int>> &graph, int n, int m)
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
            printf("from v=%d to u=%d.  Graph[u][v] = %d,  graph[v][u] = %d\n", v, u, graph[u][v], graph[v][u]);
            min_flow = min(graph[u][v], min_flow);
            v = u;
        }
        printf("Minflow found was %d\n",min_flow);
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
    map<int, map<int, int>> graph;
    cin >> l;
    for (z = 0; z < l; z++)
    {
        cout << endl; //blank line between datasets
        graph.clear();
        //graph size =  START + TARGET + BOB + RALHP =  2 + n+ m
        // 0 -> START
        // [1,n] -> Bob`s vertices
        // [n+1, n+m] -> Ralph`s vertices
        // n+m+1 -> TARGET
        cin >> datasetAux.n >> datasetAux.m;
        //read bob's route
        datasetAux.bobRoute.clear();
        for (j = 0; j < datasetAux.n; j++)
        {
            cin >> pointAux.x >> pointAux.y;
            datasetAux.bobRoute.push_back(pointAux);
        }
        datasetAux.ralphRoute.clear();
        for (j = 0; j < datasetAux.m; j++)
        {
            cin >> pointAux.x >> pointAux.y;
            datasetAux.ralphRoute.push_back(pointAux);
        }

        // Link Source to all Bob`s vertex.
        for (int i = 1; i <= datasetAux.n; i++)
        {
            if (i == datasetAux.n)
            {
                graph[0][i] = 0;
                graph[i][0] = 0;
            }
            else
            {
                graph[0][i] = 1;
                graph[i][0] = 0;
            }
        }

        // Link Ralph`s vertices to Target.
        for (int i = datasetAux.n + 1; i <= datasetAux.n + datasetAux.m; i++)
        {
            graph[i][datasetAux.n + datasetAux.m + 1] = 1;
            graph[datasetAux.n + datasetAux.m + 1][i] = 0;
        }
        // Link Bob`s vertices to Ralph`s vertices.
        for (int i = 0; i < datasetAux.n - 1; i++)
        {
            // check if we can go to jth-interest place and go back to i+1-th place
            //double distance(int x1, int y1, int x2, int y2)

            //    distance_i_next_i* 2 >=   distance_pro_interessante  + distance_do_interessante_pro_proximo;

            double distance_i_nextI = distance(datasetAux.bobRoute[i].x, datasetAux.bobRoute[i].y,
                                               datasetAux.bobRoute[i + 1].x, datasetAux.bobRoute[i + 1].y);

            for (int j = 0; j < datasetAux.m; j++)
            {
                double distance_i_j = distance(datasetAux.bobRoute[i].x, datasetAux.bobRoute[i].y,
                                               datasetAux.ralphRoute[j].x, datasetAux.ralphRoute[j].y);

                double distance_j_nextI = distance(datasetAux.ralphRoute[j].x, datasetAux.ralphRoute[j].y,
                                                   datasetAux.bobRoute[i + 1].x, datasetAux.bobRoute[i + 1].y);
                if (distance_i_j + distance_j_nextI <= distance_i_nextI * 2)
                {
                    printf("i= %d(%d) to j=%d(%d)  is possible \n", i, i + 1, j, datasetAux.n + 1 + j);
                    graph[i + 1][datasetAux.n + 1 + j] = 1;
                    graph[datasetAux.n + 1 + j][i + 1] = 0;
                }
            }
        }

        printf("%d\n", fk(graph, datasetAux.n, datasetAux.m)); // Algoritmo ford fulkerson que ira alterar o grafo
                                                               //printPath(); //Printar o caminho enquanto olhamos o grafo residual.

        


        //for(int u = 0; u <= datasetAux.n+ datasetAux.m+1; u++){
            for(int u = 5; u <=9; u++){
            for (auto it = graph[u].begin(); it != graph[u].end(); it++){
                int v = it->first;
                int f = it->second;
                printf("graph[%d][%d] = %d\n", u, v, f);
            }
        }
        /*
        for (int i = 0; i < datasetAux.n - 1; i++)
        {
            for (int j = 0; j < datasetAux.m; j++)
            {
                if (graph[i + 1][datasetAux.n + j + 1] == 1)
                {
                    printf("We can go from BOB %d to Ralph %d\n", i, j);
                }
            }
        }/*

        dataset.push_back(datasetAux);
    }
    //print
    /*
    
    for(i=0; i<dataset.size(); i++){
        cout << dataset[i].n << " " << dataset[i].m << endl;
        for(j=0; j<dataset[i].bobRoute.size(); j++){
            cout << dataset[i].bobRoute[j].x << " " << dataset[i].bobRoute[j].y << " ";
        }
        cout << endl;
        for(j=0; j<dataset[i].ralphRoute.size(); j++){
            cout << dataset[i].ralphRoute[j].x << " " << dataset[i].ralphRoute[j].y << " ";
        }
        cout << endl;

    }*/
    }
    return 0;
}
