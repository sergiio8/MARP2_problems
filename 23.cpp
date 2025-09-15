#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>



using namespace std;


bool resolver(vector<vector<int> > v, vector<int> cadena){
    vector<vector<vector<bool> > > m(cadena.size(), vector<vector<bool> >(cadena.size(), vector<bool>(3, false)));
    int n = cadena.size();

    for (int i = 0; i < n; ++i) m[i][i][cadena[i]] = true;

    int i = 0;
    int j = 1;
    while (i < n && j < n){
        m[i][j][v[cadena[i]][cadena[j]]] = true;
        i++;
        j++;
    }
    i = 0;
    j = 2;
    while (j < n){
        int aux = j + 1;
        while (j < n){
            int l = i;
            while (l < j){
                vector<bool> p1(3, false);
                for (int k = 0; k < 3; ++k){
                    if (m[i][l][k]) p1[k] = true;
                }

                vector<bool> p2(3, false);

                for (int k = 0; k < 3; ++k){
                    if (m[l + 1][j][k]) p2[k] = true;
                }

                for (int k = 0; k < 3; ++k){
                    if (p1[k]){
                        for (int n = 0; n < 3; ++n){
                            if (p2[n]) m[i][j][v[k][n]] = true;
                        }
                    }
                }
                l++;
            }
            i++;
            j++;  
        }
        j = aux;
        i = 0;
    }

    if (m[0][n - 1][0]) return true;
    else return false;
    
}

bool resuelveCaso() {
    string s;
    cin >> s;

    vector<int> cadena(s.size());

    if (!cin) return false;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'a') cadena[i] = 0;
        else if (s[i] == 'b') cadena[i] = 1;
        else if (s[i] == 'c') cadena[i] = 2;
    }
        
    vector<vector<int> > v(3, vector<int>(3));
    v[0][0] = 1; v[0][1] = 1; v[0][2] = 0;
    v[1][0] = 2; v[1][1] = 1; v[1][2] = 0;
    v[2][0] = 0; v[2][1] = 2; v[2][2] = 2;

    if (resolver(v, cadena)) cout << "SI\n";
    else cout << "NO\n";

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}