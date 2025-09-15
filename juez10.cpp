
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;


vector<string> separar_string(string s) {
	vector<string> l;
	l.push_back("");
	int i = 0;
	string aux = "";
	for (char c : s) {
		if (c != ' ') aux += c;
		else {
			l.push_back(aux);
			aux = "";
		}
	}

	l.push_back(aux);
	return l;
}

stack<string> calc_lista(const vector<string>& l1, const vector<string>& l2, vector<vector<int> >& M, int N1, int N2) {
	stack<string> sol;

	for (int i = 1; i <= N1; i++) {
		for (int j = 1; j <= N2; j++) {
			if (l1[i] == l2[j]) M[i][j] = M[i - 1][j - 1] + 1;
			else M[i][j] = max(M[i - 1][j], M[i][j - 1]);
			
		}
	}

	int i = N1, j = N2;
	while (i > 0 && j > 0) {
		if (M[i][j] == M[i - 1][j]) i--;
		else if (M[i][j] == M[i][j - 1])j--;
		else {
			sol.push(l1[i]);
			i--; j--;
		}
	}

	return sol;
}

bool resCaso() {
	string s1, s2; getline(cin, s1);
	if (!cin) return false;
	//char aux; cin >> aux;
	getline(cin, s2);

	vector<string> l1 = separar_string(s1);
	vector<string> l2 = separar_string(s2);
	
	int N1 = l1.size() - 1, N2 = l2.size() - 1;

	vector<vector<int> > M(N1 + 1, vector<int>(N2 +1, 0));

	stack<string> sol = calc_lista(l1, l2, M, N1, N2);
	
	while (!sol.empty()) {
		string x = sol.top(); sol.pop();
		cout << x << " ";
	}
	cout << "\n";
	
	return true;
}

int main() {
	while (resCaso()) {}
	return 0;
}