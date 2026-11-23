#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits.h>
#include <tuple>


using namespace std;

// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T> >
class PriorityQueue {
   
   // vector que contiene los datos
   std::vector<T> array;     // primer elemento en la posición 1
   
   /* Objeto función que sabe comparar elementos.
    antes(a,b) es cierto si a es más prioritario que b (a debe salir antes que b) */
   Comparator antes;
   
public:
   
   PriorityQueue(Comparator c = Comparator()) : array(1), antes(c) {}
   
   /* Constructor a partir de un vector de elementos */
   PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
   array(v_ini.size() + 1), antes(c) {
      for (auto i = 0; i < v_ini.size(); ++i)
         array[i + 1] = v_ini[i];
      monticulizar();
   }

   
   /* Insertar el elemento x (que incluye su prioridad).
    Si no hay espacio, el array se agranda. */
   void push(T const& x) {
      array.push_back(x);
      flotar(array.size() - 1);
   }
   
   /* Devuelve el número de elementos en la cola. */
   int size() const { return int(array.size()) - 1; }
   
   /* Averigua si la cola con prioridad está vacía. */
   bool empty() const { return size() == 0; }
   
   /* Si la cola no es vacía, devuelve el elemento más prioritario. */
   T const& top()  const {
      if (empty()) throw std::domain_error("La cola vacia no tiene top");
      else return array[1];
   }
   
   /* Si la cola no es vacía, elimina el elemento más prioritario. */
   void pop() {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
   /* Si la cola no es vacía, elimina y devuelve el elemento más prioritario. */
   void pop(T & prim) {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         prim = std::move(array[1]);
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
private:
   
   /* Flota el elemento situado en la posición i del montículo. */
   void flotar(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && antes(elem, array[hueco / 2])) {
         array[hueco] = std::move(array[hueco / 2]);
         hueco /= 2;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Hunde el elemento situado en la posición n del montículo. */
   void hundir(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      int hijo = 2 * hueco; // hijo izquierdo, si existe
      while (hijo <= size())  {
         // cambiar al hijo derecho si existe y va antes que el izquierdo
         if (hijo < size() && antes(array[hijo + 1], array[hijo]))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiéndose
         if (antes(array[hijo], elem)) {
            array[hueco] = std::move(array[hijo]);
            hueco = hijo; hijo = 2 * hueco;
         }
         else break;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Convierte un vector en un montículo. */
   void monticulizar() {
      for (auto i = size() / 2; i > 0; --i)
         hundir(i);
   }
};

struct nodo{
    vector<int> sol;
    int k;
    int calidad;
    int calidad_opt;
    vector<bool> asignado;
};

bool operator<(const nodo& n1, const nodo& n2){
    return n1.calidad_opt >= n2.calidad_opt;
}

vector<int> cotas(vector<vector<int> > calidad, vector<int> anchura_carros, vector<int> anchura_caminos, int n, int m){
    vector<int> mejor(n);


    for (int i = 0; i < n; ++i){
        mejor[i] = 0;
        for (int j = 0; j < m; ++j){
            if (anchura_carros[i] <= anchura_caminos[j]) mejor[i] = max(mejor[i], calidad[i][j]);
        }
    }

    vector<int> opt(n + 1);

    opt[n] = 0;
    for (int i = n - 1; i >= 0; +--i){
        opt[i] = opt[i + 1] + mejor[i];
    }

    return opt;
}


pair<int, vector<int> > resolver(vector<vector<int> > calidad, vector<int> anchura_carros, vector<int> anchura_caminos, int n, int m){
    nodo X, Y;
    PriorityQueue<nodo> C = PriorityQueue<nodo>();
    vector<int> opt = cotas(calidad,anchura_carros, anchura_caminos, n, m);
    //vector<int> pes = cotas(calidad, n, m).second;
    int calidad_mejor = 0;
    vector<int> sol_mejor(n);

    Y.k = -1;
    Y.sol = vector<int>(n);
    Y.asignado = vector<bool>(m, false);
    Y.calidad = 0;
    Y.calidad_opt = opt[0];
    C.push(Y);

    while (!C.empty() && C.top().calidad_opt >= calidad_mejor){
        Y = C.top(); C.pop();
        X.k = Y.k + 1; X.sol = Y.sol; X.asignado = Y.asignado;
        for (int i = -1; i < m; ++i){
            if (i == -1){
                X.sol[X.k] = i;
                X.calidad = Y.calidad;
                X.calidad_opt = X.calidad + opt[X.k + 1];
                if (X.calidad_opt > calidad_mejor){
                    if (X.k == n - 1){
                        sol_mejor = X.sol;
                        calidad_mejor = X.calidad;
                    }
                    else{
                        C.push(X);
                        calidad_mejor = max(calidad_mejor, X.calidad);
                    }
                }
            }
            else{
                if (!X.asignado[i] && anchura_carros[X.k] <= anchura_caminos[i]){
                X.sol[X.k] = i; X.asignado[i] = true;
                X.calidad = Y.calidad + calidad[X.k][i];
                X.calidad_opt = X.calidad + opt[X.k + 1];
                if (X.calidad_opt > calidad_mejor){
                    if (X.k == n - 1){
                        sol_mejor = X.sol;
                        calidad_mejor = X.calidad;
                    }
                    else{
                        C.push(X);
                        calidad_mejor = max(calidad_mejor, X.calidad);
                    }
                }
                X.asignado[i] = false;            
            }

            }
        }
    }

    pair<int, vector<int> > sol;
    sol.first = calidad_mejor;
    sol.second = sol_mejor;

    return sol;


}

void resuelveCaso() {
    int n, m;
    cin >> n >> m;
    vector<int> anchura_carros(n);
    vector<int> anchura_caminos(m);
    for (int i = 0; i < n; ++i){
        cin >> anchura_carros[i];
    }
    for (int i = 0; i < m; ++i){
        cin >> anchura_caminos[i];
    }
    vector<vector<int> > calidad(n, vector<int>(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> calidad[i][j];
        }
    }

    if (n == 0) cout << "0\n";
    else cout << resolver(calidad, anchura_carros, anchura_caminos, n, m).first << '\n';


}

int main() {
    int num_casos;
    cin >> num_casos;
    for (int i = 0; i < num_casos; ++i) resuelveCaso();
    return 0;
}