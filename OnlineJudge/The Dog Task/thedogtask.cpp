#include <iostream>
#include <vector>
using namespace std;

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

int main(){
    //variable declaration
    int l, i, j;
    dataset datasetAux;
    point2d pointAux;
    vector<dataset> dataset;

    cin >> l;   
    for(i=0; i<l; i++){
        cout << endl; //blank line between datasets
        cin >> datasetAux.n >> datasetAux.m;
        //read bob's route
        for(j=0; j<datasetAux.n; j++){
            cin >> pointAux.x >> pointAux.y;
            datasetAux.bobRoute.push_back(pointAux);
        }
        for(j=0; j<datasetAux.m; j++){
            cin >> pointAux.x >> pointAux.y;
            datasetAux.ralphRoute.push_back(pointAux);
        }
        dataset.push_back(datasetAux);
    }
    //print
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

    }
    return 0;
}