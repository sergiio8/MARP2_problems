#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

void resolver(vector<int> v, int P, int S){
    vector<int> m(P + 1);
    m[0] = 0;
    for (int i = 1; i <= P; ++i) m[i] = 5000;

    for (int i = 0; i < S; ++i){
        for (int j = v[i]; j <= P; j++){
            m[j] = min(m[j], m[j - v[i]] + 1);
        }
    }


    if (m[P] == 5000) {
        cout << "Imposible\n";
    }
    else {
        vector<int> sol(m[P]);
        int j = P;
        int i = S - 1;
        int ind = 0;
        while (j > 0 && ind < m[P]){
            if (j - v[i] >= 0 && m[j] == m[j - v[i]] + 1) {
                sol[ind] = v[i];
                j = j - v[i];
                ind++;
            }
            else i--;
        }
        cout << m[P] << ": ";
        for (int p = 0; p < sol.size(); ++p) cout << sol[p] << ' ';
        cout << '\n';
    }
}







bool resuelveCaso() {
    int P, S;
    cin >> P >> S;
    if (!cin) return false;

    vector<int> v(S);
    for (int i = 0; i < S; ++i){
        int a; cin >> a;
        v[i] = a;
    }

    resolver(v, P, S);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}