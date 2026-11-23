#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

struct tCofre{
    int prof;
    int oro;
};

void resolver(vector<tCofre> v, int N, int T){
    vector<vector<int> > sol(N + 1, vector<int>(T + 1));

    for (int j = 0; j <= T; ++j) {
        sol[0][j] = 0;
    }
    for (int i = 0; i <= N; ++i){
        sol[i][0] = 0;
    }

    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= T; ++j){
            if (v[i - 1].prof*3 > j) sol[i][j] = sol[i - 1][j];
            else sol[i][j] = max(sol[i - 1][j], sol[i - 1][j - v[i - 1].prof*3] + v[i - 1].oro);
        }
    }

    cout << sol[N][T] << '\n';

    int resto = T;
    int cont = 0;
    vector<bool> cuales(N, false);
    for (int i = N; i >= 1; --i){
        if (sol[i][resto] == sol[i - 1][resto]) cuales[i - 1] = false;
        else {
            cuales[i - 1] = true;
            cont++;
            resto = resto - 3*v[i - 1].prof;
        }
    }
    cout << cont << '\n';

    for (int i = 0; i < cuales.size(); ++i){
        if (cuales[i]) cout << v[i].prof << ' ' << v[i].oro << '\n';
    }
    cout << "---\n";



}

bool resuelveCaso() {
    int T, N;
    cin >> T >> N;

    if (!cin) return false;

    vector<tCofre> v(N);

    for (int i = 0; i < N; ++i){
        cin >> v[i].prof >> v[i].oro;
    }
    

    resolver(v, N, T);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}