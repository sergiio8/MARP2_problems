#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct tSol {
    int num;
    string palabra;
};

int aibofobia(const string& palabra, vector<vector<int>>& matriz, int i, int j) {
    int& res = matriz[i][j];

    if (res == -1) {
        if (i == j || i > j)
            res = 0;
        else if (palabra[i] == palabra[j])
            res = aibofobia(palabra, matriz, i + 1, j - 1);
        else
            res = min(aibofobia(palabra, matriz, i + 1, j), aibofobia(palabra, matriz, i, j - 1)) + 1;
    }
    return res;
}

void palabra_final(string const& palabra, vector<vector<int>> const& matriz, string& sol, int i, int j) {
    if (i <= j) {
        if (i == j) {
            sol.push_back(palabra[i]);
        }
        else if (palabra[i] == palabra[j]) {
            sol.push_back(palabra[i]);
            palabra_final(palabra, matriz, sol, i + 1, j - 1);
            sol.push_back(palabra[i]);
        }
        else if (matriz[i][j] == matriz[i + 1][j] + 1) {
            sol.push_back(palabra[i]);
            palabra_final(palabra, matriz, sol, i + 1, j);
            sol.push_back(palabra[i]);
        }
        else {
            sol.push_back(palabra[j]);
            palabra_final(palabra, matriz, sol, i, j - 1);
            sol.push_back(palabra[j]);
        }
    }
}

void resolver(const string& palabra) {
    tSol sol; sol.num = 0; sol.palabra = "";
    int tam = palabra.size();
    vector<vector<int>> matriz(tam, vector<int>(tam, -1));

    sol.num = aibofobia(palabra, matriz, 0, tam - 1);

    palabra_final(palabra, matriz, sol.palabra, 0, tam - 1);

    cout << sol.num << ' ' << sol.palabra << '\n';
}

bool resuelveCaso() {
    string palabra; cin >> palabra;

    if (!std::cin)
        return false;

    resolver(palabra);

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}