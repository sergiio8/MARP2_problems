#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;



void resolver(int P, int N){
    vector<long long int> formas(N);
    
    formas[0] = 1;
    formas[1] = 1;
    formas[2] = 2;

    for (int i = 3; i < N; ++i){
        int k = max(0, i - P - 1);
        while (k < i){
            formas[i] = (formas[i] + formas[k])  % 1000000007;
            k++;
        }
    }

    cout << formas[N - 1] % 1000000007 << '\n';
}




bool resuelveCaso() {
    int N, P;
    cin >> N >> P;
    if (N == 0 && P == 0) return false;

    if (P == 0) cout << "1\n";
    else resolver(P, N);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}