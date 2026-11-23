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
    int coste;
    int coste_opt;
    vector<int> restantes;
};

bool operator<(const nodo& n1, const nodo& n2){
    return n1.coste_opt > n2.coste_opt;
}

int cota(vector<int> precios, vector<int> restantes,  int N, int M, int k){
   int precio_min = 0;
   if (k < M) precio_min = precios[k];

    for (int i = k + 1; i < M; ++i){
       if (precios[i] < precio_min) precio_min = precios[i];
    }

    int opt = 0;
    for (int i = 0; i < restantes.size(); ++i) opt += restantes[i]*precio_min;
    return opt;
}

int pes(vector<int> precios, vector<int> restante, vector<int> suministradores, int N, int M, int k){
    int i = 0;
    int j = k;
    int pes = 0;

    vector<int> restantes = restante;

    bool p = true;

    if (j >= M) {
       p = false;
       pes = - 1;
    }
    while (j < M && i < N && p){
       if (restantes[i] == 0){
          i++;
       }
       else{
          pes += min(restantes[i], suministradores[j])*precios[j];
          restantes[i] -= min(restantes[i], suministradores[j]);
          
            if (restantes[i] == 0) {
               i++;
            }
            j++;
       }
    }
    if (j == M && i < N) pes = -1;

    bool buena = true;
    int r = 0;
    while (r < N && buena){
       if (restantes[r] != 0) buena = false;
       r++;
    }
    if (!buena) pes = -1;
    return pes;
}






pair<int, bool> resolver(vector<int> facultades, vector<int> suministradores, vector<int> precios,int N, int M){
    nodo X, Y;
    PriorityQueue<nodo> C = PriorityQueue<nodo>();
    int opt = cota(precios, facultades, N, M, 0);
    int coste_mejor = INT_MAX;
    vector<int> sol_mejor(M, -1);
    bool solu = false;

    Y.k = -1;
    Y.sol = vector<int>(M, -1);
    Y.coste = 0;
    Y.coste_opt = -1;
    Y.restantes = facultades;
    C.push(Y);

    while (!C.empty() && C.top().coste_opt <= coste_mejor){
        Y = C.top(); C.pop();
        X.k = Y.k + 1; X.sol = Y.sol; X.restantes = Y.restantes;
        for (int i = -1; i < N; ++i){
            if (i == -1){
                X.sol[X.k] = i; 
                X.coste = Y.coste;
                cout << X.coste << '\n';
                X.coste_opt = X.coste + cota(precios, X.restantes, N, M, X.k + 1);
                  bool buena = true;
                  int suma1 = 0;
                  int j = 0;
                    while (j < N){
                        suma1 += X.restantes[j];
                        if (X.restantes[j] != 0) buena = false;
                        j++;
                     }

                     int suma2 = 0;
                     for (int p = X.k + 1; p < M; ++p) suma2 += suministradores[p];
                    if (buena && X.coste <= coste_mejor){
                        solu = true;
                        sol_mejor = X.sol;
                        coste_mejor = X.coste;  
                     }   
                  else if (suma2 >= suma1 && X.coste_opt <= coste_mejor){
                     C.push(X);
                     int s = pes(precios, X.restantes, suministradores, N, M, X.k + 1);
                     if (coste_mejor >= X.coste + s && s != -1){
                        coste_mejor = X.coste + s;
                        solu = true;
                     }
                  }
                  X.restantes = Y.restantes;    
            }
            else{
            if (X.restantes[i] > 0){
                X.sol[X.k] = i; 
                X.coste = Y.coste + min(suministradores[X.k], X.restantes[i])*precios[X.k];
                cout << X.coste << '\n';
                X.restantes[i] = X.restantes[i] - min(X.restantes[i], suministradores[X.k]);
                X.coste_opt = X.coste + cota(precios, X.restantes, N, M, X.k + 1);
                bool buena = true;
                int suma1 = 0;
                int j = 0;
                while (j < N){
                     suma1 += X.restantes[j];
                     if (X.restantes[j] != 0) buena = false;
                     j++;
                }

                int suma2 = 0;
                for (int p = X.k + 1; p < M; ++p) suma2 += suministradores[p];
                if (buena && X.coste <= coste_mejor){
                   solu = true;
                   sol_mejor = X.sol;
                   coste_mejor = X.coste;  
                }   
               else if (suma2 >= suma1 && X.coste_opt <= coste_mejor){
                  C.push(X);
                  int s = pes(precios, X.restantes, suministradores, N, M, X.k + 1);
                  if (coste_mejor > X.coste + s && s!= - 1){
                     coste_mejor = X.coste + s;
                     solu = true;
                  }
               }
               X.restantes = Y.restantes;    
            }
         }
      }

      for (int i = 0; i < N; ++i) cout << sol_mejor[i] << ' ';
    


    pair<int, bool > sol;
    sol.first = coste_mejor;
    sol.second = solu;

    return sol;
}
}
void resuelveCaso() {
    int N, M;
    cin >> N >> M;

    vector<int> facultades(N);
    vector<int> suministradores(M);
    vector<int> precios(M);
    for (int i = 0; i < N; ++i) cin >> facultades[i];
    for (int i = 0; i < M; ++i) cin >> suministradores[i];
    for (int i = 0; i < M; ++i) cin >> precios[i];

    pair<int, bool> sol = resolver(facultades, suministradores, precios, N, M);
    if (sol.second) cout << sol.first << '\n';
    else cout << "NO\n";
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