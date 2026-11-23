#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>
#include <unordered_map>


using namespace std;

void resolver(vector<vector<bool> > relaciones, int P, int N, unordered_map<int, string> personas,unordered_map<string, int> numeros){
    vector<vector<int> > m(P, vector<int>(P, 0));

    for (int i = 0; i < P; ++i){
        for (int j = 0; j < P; ++j){
            if (i != j){
                if (relaciones[i][j]) m[i][j] = 1;
                else m[i][j] = 500;
            }
        }
    }

    for (int k = 0; k < P; ++k){
        for (int i = 0; i < P; ++i){
            for (int j = 0; j < P; ++j){
                int temp = m[i][k] + m[k][j];
                if (temp < m[i][j]){
                    m[i][j] = temp;
                }
            }
        }
    }
    
    int res = 0;
    bool stop = false;

    for (int i = 0; i < P && !stop; ++i){
        for (int j = 0; j < P && !stop; ++j){
            if (m[i][j] > res) res = m[i][j];
            else if (m[i][j] == 500){
                cout << "DESCONECTADA\n";
                stop = true;
            } 
        }
    }

    if (!stop) cout << res << '\n';

}







bool resuelveCaso() {
    int P, N;
    cin >> P >> N;
    if (!cin) return false;

    vector<vector<bool> > relaciones(P, vector<bool>(P, false));
    unordered_map<int, string> personas;
    unordered_map<string, int> numeros;
    int cont = 0;
    for (int i = 0; i < N; ++i){
        string a, b;
        cin >> a >> b;
        if (!numeros.count(a)){
            personas[cont] = a;
            numeros[a] = cont;
            cont++;
        }
        if (!numeros.count(b)){
            personas[cont] = b;
            numeros[b] = cont;
            cont++;
        }
        relaciones[numeros[a]][numeros[b]] = true;
        relaciones[numeros[b]][numeros[a]] = true;
    }

    

    resolver(relaciones, P, N, personas, numeros);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}