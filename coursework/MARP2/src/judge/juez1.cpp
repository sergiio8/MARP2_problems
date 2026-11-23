#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

struct tCordel{
    int longitud;
    int coste;
};

long long int matematico(int N, int l, vector<tCordel> v){
    vector< vector<long long int> > m(N + 1, vector<long long int> (l + 1));
    for (int j = 1; j <= l; ++j) m[0][j] = 0;
    for (int i = 0; i <= N; ++i) m[i][0] = 1;

    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= l; ++j){
            if (v[i - 1].longitud > j) m[i][j] = m[i - 1][j];
            else m[i][j] = m[i - 1][j] + m[i - 1][j - v[i - 1].longitud];
        }
    }

    return m[N][l];
}

long long int ingeniero(int N, int l, vector<tCordel> v){
    vector< vector<long long int> > m(N + 1, vector<long long int> (l + 1));
    for (int j = 1; j <= l; ++j) m[0][j] = INT_MAX - 2;
    for (int i = 0; i <= N; ++i) m[i][0] = 0;

    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= l; ++j){
            if (v[i - 1].longitud > j) m[i][j] = m[i - 1][j];
            else m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1].longitud] + 1);
        }
    }

    return m[N][l];
}

long long int economista(int N, int l, vector<tCordel> v){
    vector< vector<long long int> > m(N + 1, vector<long long int> (l + 1));
    for (int j = 1; j <= l; ++j) m[0][j] = INT_MAX - 1001;
    for (int i = 0; i <= N; ++i) m[i][0] = 0;

    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= l; ++j){
            if (v[i - 1].longitud > j) m[i][j] = m[i - 1][j];
            else m[i][j] = min(m[i - 1][j], m[i - 1][j - v[i - 1].longitud] + v[i - 1].coste);
        }
    }

    return m[N][l];

}

bool resuelveCaso() {
    int N, l;
    cin >> N >> l;
    if (!cin)  return false;

    vector<tCordel> v(N);
    for (int i = 0; i < N; ++i){
        int longitud, coste;
        cin >> longitud >> coste;
        tCordel c; c.longitud = longitud; c.coste = coste;
        v[i] = c;
    }

    if (matematico(N, l, v) != 0){
        cout << "SI " << matematico(N, l, v) << ' ' << ingeniero(N, l, v) << ' ' << economista(N, l, v) << '\n';
    }
    else cout << "NO\n";
    
    return true; 
}

int main() {
    while (resuelveCaso()); 
    return 0;
}