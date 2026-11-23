#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

int duracion;
vii canciones;


void vuelta_atras(int cancionAct, int puntuacionAct, int ocupadoCara1,
	int ocupadoCara2, int acumulado, int& mejorRes) {
	if (cancionAct == canciones.size()) {
		mejorRes = max(puntuacionAct, mejorRes);
	}else {
			 if (puntuacionAct + acumulado <= mejorRes)
			 return;
			 if (ocupadoCara1 + canciones[cancionAct].first <= duracion) {
			 vuelta_atras(cancionAct + 1, puntuacionAct +
				canciones[cancionAct].second, ocupadoCara1 +
				 canciones[cancionAct].first, ocupadoCara2,
				 acumulado - canciones[cancionAct].second, mejorRes);
			
		}
			  if (ocupadoCara2 != ocupadoCara1 &&
				  ocupadoCara2 + canciones[cancionAct].first <= duracion) {
				  vuelta_atras(cancionAct + 1, puntuacionAct +
					 canciones[cancionAct].second, ocupadoCara1,
					 ocupadoCara2 + canciones[cancionAct].first,
					 acumulado - canciones[cancionAct].second, mejorRes);
			 }
				  vuelta_atras(cancionAct + 1, puntuacionAct, ocupadoCara1, ocupadoCara2,
					 acumulado - canciones[cancionAct].second, mejorRes);
			 
	}
	
}
 int main() {
	 int n;
	 cin >> n;
	 while (n != 0) {
		cin >> duracion;
		 canciones.resize(n);
		 int acum = 0;
		
			for (ii& cancion : canciones) {
			cin >> cancion.first >> cancion.second;
			acum += cancion.second;
		}
			int sol = 0;
		 vuelta_atras(0, 0, 0, 0, acum, sol);
		
			 cout << sol << '\n';
		      cin >> n;
		
	}
		 return 0;
	
}