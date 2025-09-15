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
    int parejas;
    int parejas_opt;
    vector<bool> asignado;
    bool existe;
};

bool operator<(const nodo& n1, const nodo& n2){
    return n1.parejas_opt < n2.parejas_opt;
}

vector<int> cota(vector<vector<int> > allegados, int N, int M){
    vector<int> num_allegados(M);

    for (int i = 0; i < M; ++i){
       for (int j = 0; j < M; ++j){
          if (allegados[i][j]) num_allegados[i]++;
       }
    }

    vector<int> opt(M + 1);
    opt[M] = 0;
    opt[M - 1] = num_allegados[M - 1];

    for (int i = M - 2; i >= 0; --i){
       opt[i] = num_allegados[i] + opt[i + 1];  
    }

    return opt;
}

bool comprobar(vector<vector<float> > distancias, vector<vector<int> > allegados, int k, vector<int> sol, int pos){
   for (int i = 0; i < k; ++i){
      if (distancias[sol[i]][pos] < 2 && !allegados[i][k]) return false;
   }

   return true;
}

int contar_allegados(vector<vector<float> > distancias, vector<vector<int> > allegados, int k, vector<int> sol, int pos){
   int cont = 0;
   for (int i = 0; i < k; ++i){
      if (distancias[sol[i]][sol[k]] < 2 && allegados[i][k]) cont++;
   }

   return cont;
}


pair<int, bool > resolver(vector<vector<float> > distancias, vector<vector<int> > allegados, int N, int M){
    nodo X, Y;
    PriorityQueue<nodo> C = PriorityQueue<nodo>();
    vector<int> opt = cota(allegados, N, M);
    //vector<int> pes = cotas(tiempo, N).second;
    int parejas_max = -1;
    vector<int> sol_mejor(N);

    Y.k = -1;
    Y.sol = vector<int>(N, - 1);
    Y.asignado = vector<bool>(N, false);
    Y.parejas = 0;
    Y.parejas_opt = opt[0];
    Y.existe = true;
    C.push(Y);
    bool parar = false;

    while (!C.empty() && C.top().parejas_opt >= parejas_max && !parar){
        Y = C.top(); C.pop();
        X.k = Y.k + 1; X.sol = Y.sol; X.asignado = Y.asignado; X.existe = Y.existe;
        bool sentado = false;
        for (int i = 0; i < N; ++i){
            if (!X.asignado[i] && comprobar(distancias, allegados, X.k, X.sol, i)){
                sentado = true;
                X.sol[X.k] = i; X.asignado[i] = true;
                X.parejas = Y.parejas + contar_allegados(distancias, allegados, X.k, X.sol, i);
                X.parejas_opt = X.parejas + opt[X.k + 1];
                if (X.parejas_opt > parejas_max){
                    if (X.k == M - 1){
                        sol_mejor = X.sol;
                        parejas_max = X.parejas;
                    }
                    else{
                        C.push(X);
                        parejas_max = max(parejas_max, X.parejas);
                    }
                }
                X.asignado[i] = false;            
            }
        }
        if (!sentado) parar = true;
    }

    pair<int, bool > sol;
    sol.first = parejas_max;
    sol.second = !parar;

    return sol;
}

void resuelveCaso() {
    int N, M;
    cin >> N >> M;

    vector<vector<float> > distancias(N, vector<float>(N));

     for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cin >> distancias[i][j];
        }
    }
    vector<vector<int> > allegados(M, vector<int>(M));

     for (int i = 0; i < M; ++i){
        for (int j = 0; j < M; ++j){
            cin >> allegados[i][j];
        }
    }

    if (resolver(distancias, allegados, N, M).second) cout << "PAREJAS " << resolver(distancias, allegados, N, M).first << '\n';
    else cout << "CANCELA\n";


}

int main() {
   int n;
   cin >> n;
    while (n > 0) {
       resuelveCaso();
       n--;
    }
    return 0;
}