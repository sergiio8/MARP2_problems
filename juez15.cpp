//ALUMNO: Rodrigo Cuadro L�pez
//ASIGNATURA: MARP 2

#include <iostream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>

class EntInf {
   int num;
public:
   static const int _intInf = 1000000000;

   EntInf(int n = 0) : num(n) {}

   EntInf operator+(EntInf const& b) const {
      if (num == _intInf || b.num == _intInf || num >= (_intInf - b.num))
         return _intInf;
      else return num + b.num;
   }

   bool operator==(EntInf const& b) const {
      return num == b.num;
   }

   bool operator!=(EntInf const& b) const {
      return !(*this == b);
   }
   
   bool operator<(EntInf const& b) const {
      if (num == _intInf) return false;
      else if (b.num == _intInf) return true;
      else return num < b.num;
   }

   bool operator>(EntInf const& b) const {
      return b < *this;
   }

   void print(std::ostream & out = std::cout) const {
      if (num == _intInf) out << "+Inf";
      else out << num;
   }
};

const EntInf Infinito(EntInf::_intInf);

inline std::ostream & operator<<(std::ostream & out, EntInf const& e) {
   e.print(out);
   return out;
}



using namespace std;

struct info {
	int numM;
	int formas;
};

void formas_minimas(const vector<int>& monedas, vector<info>& V, int N, int C) {
	for (int i = 1; i <= N; i++) {
		for (int j = C; j > 0; j--) {
			info nuevo = { EntInf::_intInf , 0 };
			int pos = j, k = 0;
			while (pos >= 0) {
				if (V[pos].numM + k < nuevo.numM) {
					nuevo.numM = V[pos].numM + k;
					nuevo.formas = V[pos].formas;
				}
				else if (V[pos].numM + k == nuevo.numM) {
					nuevo.formas += V[pos].formas;
				}
				k++;
				pos -= monedas[i - 1];
			}
			V[j] = nuevo;
		}
	}
}

bool resCaso() {
	int C, N; cin >> C;
	if (!cin) return false;
	cin >> N;

	vector<int> monedas(N);

	for (int& x: monedas) 
		cin >> x;

	vector<info> V(C + 1);
	for (int i = 0; i < C + 1; ++i){
		V[i].numM = EntInf::_intInf;
		V[i].formas = 0;
	}
	V[0].numM = 0;
	V[0].formas = 1;

	formas_minimas(monedas, V, N, C);

	cout << V[C].formas << "\n";

	return true;
}


int main() {
	while (resCaso()) {}
	return 0;
}