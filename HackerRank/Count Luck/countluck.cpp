#include <iostream>

int main() {
	// Input
	int t;
	cin >> t;
	if(t<1 or t>10){
		break;
	}
	for(int i=0; i<t; i++){
		int n, m;
		cint >> n >> m;
		if(1<=n and n<=100 and 1<=m and m<=100){
			test(n, m);
		}
	}    



    return 0;
}

void test(int n, int m){
	// Read matrix
	vector<vector<int>> mat(n, vector<int>(m));	
	char line[m];
	for(int i=0; i<n; i++){
		cin >> line;
		for(int j=0; j<m; j++){
			mat[i][j] = line[m];
		}
	}
	int k;
	cin >> k;
	print_mat(mat)
}

void print_mat(vector<vector<int>> mat, n, m){
	for(int i=0; i<n, i++){
		for(int j=0; j<m; j++){
			cout << mat[i][j];
		}
		cout << endl;
	}
}