#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>


using namespace std;

int resolver(vector<int> areas , vector<int> beneficios, int N, int K){
    vector<int> m(N);
    m[0] = beneficios[0];
    int ult = -1;
    if (areas[1] - areas[0] >= K) ult = 0;
    for (int i = 1; i < N; ++i){
        if (i != 1){
            while (areas[i] - areas[ult + 1] >= K) ult++;
        }
        
        if (ult == -1){
            m[i] = max(beneficios[i], m[i - 1]);
        }
        else {
            m[i] = max(beneficios[i] + m[ult], m[i - 1]);
        }
    }

    return m[N - 1];
}



bool resuelveCaso() {
    int N, K;
    cin >> N >> K;
    if (!cin) return false;

    vector<int> areas(N);
    vector<int> beneficios(N);

    for (int i = 0; i < N; ++i) cin >> areas[i];
    for (int i = 0; i < N; ++i) cin >> beneficios[i];

    
    if (N == 1) cout << beneficios[0] << '\n';
    else cout << resolver(areas, beneficios, N, K) << '\n';

    return true;
}

int main() {
    while (resuelveCaso()); 
    return 0;
}