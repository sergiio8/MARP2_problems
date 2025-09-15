#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <vector>
#include <ostream>

template <typename Object>
class Matriz {
public:
    // crea una matriz con fils filas y cols columnas,
    // con todas sus celdas inicializadas al valor e
    Matriz(int fils = 0, int cols = 0, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}
    
    // operadores para poder utilizar notación M[i][j]
    std::vector<Object> const& operator[](int f) const {
        return datos[f];
    }
    std::vector<Object> & operator[](int f) {
        return datos[f];
    }
    
    // métodos que lanzan una excepción si la posición no existe
    Object const& at(int f, int c) const {
        return datos.at(f).at(c);
    }
    Object & at(int f, int c) {
        return datos.at(f).at(c);
    }
    
    int numfils() const { return datos.size(); }
    int numcols() const { return numfils() > 0 ? datos[0].size() : 0; }
    
    bool posCorrecta(int f, int c) const {
        return 0 <= f && f < numfils() && 0 <= c && c < numcols();
    }
    
private:
    std::vector<std::vector<Object> > datos;
};

template <typename Object>
inline std::ostream & operator<<(std::ostream & out, Matriz<Object> const& m) {
   for (int i = 0; i < m.numfils(); ++i) {
      for (int j = 0; j < m.numcols(); ++j) {
         out << m[i][j] << ' ';
      }
      out << '\n';
   }
   return out;
}


using namespace std;

const double DIST_SEG = 2.0;

/* Representa los datos de una solución parcial para el problema. */
struct Nodo
{
    vector<bool> asientos_libres; // asientos_libres[i] = true si está libre, false si está ocupado
    vector<int> asiento_comensal; // asiento de cada comensal
    int ult_comensal;             // ultimo niño al que se le ha dado asiento
    int parejas_felices;          // parejas allegados a menor distancia de la de seguridad
    int parejas_estimadas;        // satisfaccion estimada
    bool operator<(Nodo const &otro) const { return parejas_estimadas < otro.parejas_estimadas; }
};

void vectorDeParejasMaximasAcumuladas(int comensales, const Matriz<bool> &allegados,
                                      vector<int> &allegados_max_acumulados)
{
    // allegados_max[i] = maximo teorico de parejas de allegados al haber sentado a los
    // comensales 0..i-1
    vector<int> allegados_max(comensales, 0);

    for (int com1 = 0; com1 < comensales; com1++)
        for (int com2 = 0; com2 < com1; com2++)
            if (allegados[com1][com2])
                allegados_max[com1]++;

    allegados_max_acumulados = vector<int>(comensales, 0);

    for (int com = comensales - 2; com >= 0; com--)
        allegados_max_acumulados[com] =
            allegados_max_acumulados[com + 1] + allegados_max[com + 1];
}

void addNode(priority_queue<Nodo> &queue, const Nodo &nuevo_nodo, int &max_parejas, int comensales, bool &hay_sol)
{
    if (nuevo_nodo.parejas_estimadas >= max_parejas)
    {
        if (nuevo_nodo.ult_comensal == comensales - 1)
        {
            max_parejas = nuevo_nodo.parejas_felices;
            hay_sol = true;
        }
        else
            queue.push(nuevo_nodo);
    }
}

int resolver(int plazas, int comensales, const Matriz<double> &distancias, const Matriz<bool> &allegados)
{
    int max_parejas = 0;
    bool hay_solucion = false;

    vector<int> allegados_max_acumulados;
    priority_queue<Nodo> queue;
    vectorDeParejasMaximasAcumuladas(comensales, allegados, allegados_max_acumulados);

    Nodo primer_nodo;
    primer_nodo.ult_comensal = -1;
    primer_nodo.parejas_felices = 0;
    primer_nodo.asientos_libres = vector<bool>(plazas, true);
    primer_nodo.asiento_comensal = vector<int>(comensales, -1);
    primer_nodo.parejas_estimadas = INT_MAX;

    queue.push(primer_nodo);
    while (!queue.empty() && queue.top().parejas_estimadas >= max_parejas)
    {
        const Nodo top = queue.top();
        queue.pop();

        Nodo nodo(top);
        nodo.ult_comensal++;

        // Probamos con todos los asientos disponibles
        for (int asiento = 0; asiento < plazas; asiento++)
            if (top.asientos_libres[asiento])
            {
                bool factible = true;
                int parejas_nuevas = 0;

                // Comprobamos que se cumpla la distancia de seguridad con los comensales ya sentados
                // el resto de comensales no nos preocupa.
                for (int com = 0; com < top.ult_comensal + 1 && factible; com++)
                {
                    if (!allegados[nodo.ult_comensal][com] &&
                        distancias[asiento][nodo.asiento_comensal[com]] < DIST_SEG)
                        factible = false;

                    else if (allegados[nodo.ult_comensal][com] &&
                             distancias[asiento][nodo.asiento_comensal[com]] < DIST_SEG)
                        parejas_nuevas++;
                }

                if (factible)
                {
                    nodo.asientos_libres[asiento] = false;
                    nodo.asiento_comensal[nodo.ult_comensal] = asiento;
                    nodo.parejas_felices = top.parejas_felices + parejas_nuevas;
                    nodo.parejas_estimadas =
                        nodo.parejas_felices + allegados_max_acumulados[nodo.ult_comensal];

                    addNode(queue, nodo, max_parejas, comensales, hay_solucion);

                    nodo.asientos_libres[asiento] = true;
                    nodo.asiento_comensal[nodo.ult_comensal] = -1;
                    //nodo.parejas_felices = top.parejas_felices;
                    //nodo.parejas_estimadas = top.parejas_estimadas;
                }
            }
    }

    if (!hay_solucion)
        return -1;
    else
        return max_parejas;
}

void resuelveCaso()
{
    int plazas;
    int comensales;
    Matriz<double> distancias;
    Matriz<bool> allegados;

    cin >> plazas >> comensales;
    for (int i = 0; i < plazas; ++i){
        for (int j = 0; j < plazas; ++j){
            cin >> distancias[i][j];
        }
    }

    allegados = Matriz<bool>(comensales, comensales);
    for (int i = 0; i < comensales; i++)
        for (int j = 0; j < comensales; j++)
        {
            int n;
            cin >> n;
            allegados[i][j] = (n == 1);
        }

    int sol = resolver(plazas, comensales, distancias, allegados);
    if (sol == -1)
        cout << "CANCELA" << endl;
    else
        cout << "PAREJAS " << sol << endl;
}

int main()
{

    int ncasos;
    cin >> ncasos;
    for (int i = 0; i < ncasos; i++)
        resuelveCaso();


    return 0;
}