#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

void resolver(vector<int> v, int N){
    vector<vector<int> > sol(N, vector<int>(N));
    for (int i = 0; i < N; ++i){
        sol[i][i] = v[i];
    }
    int j = 1;
    int i = 0;
    while (j < N && i < N){
        sol[i][j] = max(v[i], v[j]);
        i++;
        j++;
    }
    
    j = 2;
    while (j < N){
        int k = j;
        int l = 0;
        while (l + 2 < N && k < N){
            if (v[k - 1] > v[l] && v[l + 1] > v[k]) sol[l][k] = max(v[k] + sol[l][k - 2], v[l] + sol[l + 2][k]);
            else if (v[k - 1] > v[l] && v[l + 1] <= v[k]) sol[l][k] = max(v[k] + sol[l][k - 2], v[l] + sol[l + 1][k - 1]);
            else if (v[k - 1] <= v[l] && v[l + 1] > v[k]) sol[l][k] = max(v[k] + sol[l + 1][k - 1], v[l] + sol[l + 2][k]);
            else sol[l][k] = max(v[k] + sol[l + 1][k - 1], v[l] + sol[l + 1][k - 1]);
            k++;
            l++;
        }
        j++;
    }
    
    cout << sol[0][N - 1] << '\n';
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) return false;

    vector<int> v(N);

    for (int i = 0; i < N; ++i){
        cin >> v[i];
    }
    
    resolver(v, N);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}