#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;


void resolver(vector<int> valor, vector<int> num, int N, int precio){
    vector<vector<int> > monedas(N + 1, vector<int>(precio + 1));

    for (int j = 1; j <= precio; ++j) monedas[0][j] = 1000000;
    for (int i = 0; i <= N; ++i) monedas[i][0] = 0;

    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= precio; ++j){
            monedas[i][j] = monedas[i - 1][j];
            for (int k = 1; k <= min(num[i - 1], j/valor[i - 1]); ++k){
                monedas[i][j] = min(monedas[i][j],monedas[i - 1][j - k*valor[i - 1]] + k);
            }
        }
    }

    /*for (int i = 0; i <= N; ++i){
        for (int j = 0; j <= precio; ++j){
            cout << monedas[i][j] << ' ';
        }
        cout << endl;
    }*/

    if (monedas[N][precio] == 1000000) cout << "NO\n";
    else cout << "SI " << monedas[N][precio] << '\n';


}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (!cin) return false;

    vector<int> valor(N);
    vector<int> num(N);

    for (int i = 0; i < N; ++i){
        cin >> valor[i];
    }

    for (int i = 0; i < N; ++i){
        cin >> num[i];
    }

    int precio;
    cin >> precio;
    

    resolver(valor, num, N, precio);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}