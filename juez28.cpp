#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

int resolver(int k, int s){
    vector<vector<int> > m(k + 1, vector<int>(s + 1));

    for (int i = 0; i <= k; ++i) m[i][0] = 1;
    for (int i = 1; i <= s; ++i) m[0][i] = 0;

    for (int i = 1; i <= s; ++i) m[1][i] = 1;

    for (int i = 2; i <= k; ++i){
        for (int j = 1; j <= s; ++j){
            if (i > j) m[i][j] = m[i - 1][j];
            else m[i][j] = m[i - 1][j] + m[i][j - i];
        }
    }

    return m[k][s];
}



void resuelveCaso() {
    int k, s;
    cin >> k >> s;

    cout << resolver(k, s) << '\n';


}

int main() {
    int n;
    cin >> n;
    while (n > 0){
        resuelveCaso();
        n--;
    }
    return 0;
}