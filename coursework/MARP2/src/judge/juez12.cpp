#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>
#include <string>


using namespace std;

struct tPeli{
    int inicio;
    int final;
    int d;
};


bool operator<(const tPeli& p1, const tPeli& p2){
    return p1.inicio < p2.inicio;
}


void resolver(vector<tPeli> v, int N){
    vector<int> t(N);
    t[N - 1] = v[N - 1].d;
    for (int i = N - 2; i >= 0; i--){
        int l = i + 1;
        while (l < N && v[i].final > v[l].inicio) l++;
        if (l == N) t[i] = max(v[i].d, t[i + 1]);
        else{
            t[i] = max(v[i].d + t[l], t[i + 1]);
        }
    }

    cout << t[0] << '\n';
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (N == 0) return false;

    vector<tPeli> v(N);

    for (int i = 0; i < N; ++i){
        string s;
        cin >> s;
        string hora;
        hora += s[0];
        hora += s[1];
        string min;
        min += s[3];
        min += s[4];
        int h = stoi(hora);
        int m = stoi(min);
        int elem = h*60 + m;
        int d;
        cin >> d;
        v[i].d = d;
        v[i].inicio = elem;
        v[i].final = elem + d + 10;
    }

    sort(v.begin(), v.end());
    

    resolver(v, N);

    return true;

}

int main() {
    while (resuelveCaso()); 
    return 0;
}