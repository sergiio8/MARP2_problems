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
    int basura;
    int basura_opt;
    vector<int> playas;
};

bool operator<(const nodo& n1, const nodo& n2){
    return n1.basura_opt < n2.basura_opt;
}

vector<int> cota(vector<vector<int> > recoger, int n, int m){
    vector<int> max_basura(n);

    for (int i = 0; i < n; ++i){
       max_basura[i] = recoger[i][0];
       for (int j = 1; j < m; ++j){
          max_basura[i] = max(max_basura[i], recoger[i][j]);
       }
    }

    vector<int> opt(n + 1);
    opt[n] = 0;
    opt[n - 1] = max_basura[n - 1];

    for (int i = n - 2; i >= 0; --i){
       opt[i] = max_basura[i] + opt[i + 1];  
    }

    return opt;
}




pair<int, int> resolver(vector<vector<int> > recoger, vector<int> basuras, int n, int m, int l){
    nodo X, Y;
    PriorityQueue<nodo> C = PriorityQueue<nodo>();
    vector<int> opt = cota(recoger, n, m);
    int basura_mejor = 0;
    vector<int> playas_mejor(m, -1);
    vector<int> sol_mejor(n);

    Y.k = -1;
    Y.sol = vector<int>(n);
    Y.basura = 0;
    Y.basura_opt = opt[0];
    Y.playas = basuras;
    C.push(Y);


    while (!C.empty() && C.top().basura_opt >= basura_mejor){
        Y = C.top(); C.pop();
        X.k = Y.k + 1; X.sol = Y.sol; X.playas = Y.playas; 
        for (int i = 0; i < m; ++i){  
            if (X.playas[i] > 0){
                X.sol[X.k] = i; 
                X.basura = Y.basura + min(recoger[X.k][i], X.playas[i]);
                X.playas[i] = X.playas[i] - min(recoger[X.k][i], X.playas[i]);
                X.basura_opt = X.basura + opt[X.k + 1];
                if (X.basura_opt > basura_mejor){
                    if (X.k == n - 1){
                        int cont = 0;
                        for (int i = 0; i < m; ++i){
                           if (X.playas[i] == 0) cont++;
                        }
                        if (cont >= l){
                           sol_mejor = X.sol;
                           basura_mejor = X.basura;
                           playas_mejor = X.playas;
                        }
                    }
                    else{
                        C.push(X);
                        basura_mejor = max(basura_mejor, X.basura);
                    }
                }  
                X.playas[i] = Y.playas[i];   
            }     
        }
    }
     
    int cont = 0;

    for (int i = 0; i < m; ++i) if (playas_mejor[i] == 0) cont++;

    pair<int, int> sol;
    sol.first = basura_mejor;
    sol.second = cont;

    return sol;
}

void resuelveCaso() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> basura(m);
    for (int i = 0; i < m; ++i) cin >> basura[i];

    vector<vector<int> > recoger(n, vector<int>(m));

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
          cin >> recoger[i][j];
        }
    }

    pair<int,int> sol = resolver(recoger, basura, n, m, l);

    if (sol.second < l) cout << "IMPOSIBLE\n";
    else cout << sol.first << ' ' << sol.second << '\n';
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