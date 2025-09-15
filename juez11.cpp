#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;



void resolver(const vector<int>& v, const int& L, const int& N){
    vector<vector<long long int> > m(N + 2, vector<long long int>(N + 2));
    for (int i = 0; i < N + 2; ++i) m[i][i] = 0;
    
    int a = 0;
    int b = 1;
    while (a < N + 2 && b < N + 2){
        m[a][b] = 0;
        ++a;
        ++b;
    }

    a = 0;
    b = 2;

    while (a < N + 2 && b < N + 2){
        m[a][b] = 2*(v[b] - v[a]);
        ++a;
        ++b;
    }

    
    
    for (int i = N + 1; i >= 0; i--){
        for (int j = i + 2; j < N + 2; j++){
            int k = i + 1;
            m[i][j] = m[i][k] + m[k][j] + 2*(v[j] - v[i]);
            k++;
            while (k < j){
                m[i][j] = min(m[i][j], m[i][k] + m[k][j] + 2*(v[j] - v[i]));
                k++;
            }
        }
    }

    cout << m[0][N + 1] << '\n';
}







bool resuelveCaso() {
    int L, N;
    cin >> L >> N;
    if (L == 0 && N == 0) return false;

    vector<int> v;
    v.push_back(0);
    for (int i = 0; i < N; ++i){
        int a; cin >> a;
        v.push_back(a);
    }
    v.push_back(L);
    
    resolver(v, L, N);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}