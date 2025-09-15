#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

int resolver(string s, int n){
    vector<vector<int> > m(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) m[i][i] = 1;
    int i = 0;
    int j = 1;
    while (i < n && j < n){
        if (s[i] == s[j]) m[i][j] = 1;
        else m[i][j] = 2;
        ++i;
        ++j;
    }

    i = 0;
    j = 2;
    while (i < n && j < n){
        int aux = j + 1;
        while (i < n && j < n){
            int aux_1 = i;
            int aux_2 = j;
            while (aux_1 <= aux_2 && (s[aux_1] == s[i] || s[aux_2] == s[i])){
                if (s[aux_1] == s[i]){
                    aux_1++;
                }
                if (s[aux_2] == s[i]){
                    aux_2--;
                }
            }

            int aux_3 = i;
            int aux_4 = j;
            while (aux_3 <= aux_4 && (s[aux_3] == s[j] || s[aux_4] == s[j])){
                if (s[aux_3] == s[j]){
                    aux_3++;
                }
                if (s[aux_4] == s[j]){
                    aux_4--;
                }
            }

            m[i][j] = 1 + min(m[aux_1][aux_2], m[aux_3][aux_4]);
            i++;
            j++;
        }
        j = aux;
        i = 0;
    }

    return m[0][n - 1];

}



bool resuelveCaso() {
    string s;
    cin >> s;

    if (!cin) return false;

    int n = s.size();

    cout << resolver(s, n) << '\n';
    


    return true;


}

int main() {
    while (resuelveCaso());
    return 0;
}