#include <assert.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include "EdgeWeightedDigraph.h"

/**
 * Gibt zurueck ob der Knoten v ein gueltiger Knoten im Graph ist
 *
 * \param[in]  v		Knoten
 * \return Gueltigkeit des Knoten
 */
bool EdgeWeightedDigraph::validateVertex(int v) const
{
	return v >= 0 && v < this->V;
}

/**
 * Gibt eine Fehlermeldung aus, wenn der Knoten v im Graph nicht gueltig ist
 *
 * \param[in]  v		Knoten
 */
void EdgeWeightedDigraph::validateVertexWithError(int v) const
{
	assert(("Vertex is out of bounds!", this->validateVertex(v)));
}

/**
 * Erstellt einen Kantengewichteten-Gaph mit V Knoten
 *
 * \param[in]  V		Anzahl der Knoten
 */
EdgeWeightedDigraph::EdgeWeightedDigraph(int V)
	: V{V}
	, E{0}
{
	adj.resize(V);
}

/**
* Erstellt einen Kantengewichteten-Gaph anhand der Kantenliste in fname
*
* \param[in]  fname		Dateiname der Kantenliste
*/
EdgeWeightedDigraph::EdgeWeightedDigraph(std::string filename)
{
	std::ifstream infile(filename);
	int tmp_e = 0;
	infile >> this->V >> tmp_e;

	this->E = 0;

	this->adj.resize(this->V, std::vector<DirectedEdge>());

	int v, w;
	double weight;
	while (infile >> v >> w >> weight)
	{
		this->add(DirectedEdge(v, w, weight));
	}

	assert(("Missing edges!", tmp_e == this->E));
}

/**
 * Fuegt die Kante e zum Graphen hinzu
 *
 * \param[in]  e		Kante
 */
void EdgeWeightedDigraph::add(DirectedEdge e)
{
	this->validateVertexWithError(e.from());
	this->validateVertexWithError(e.to());

	this->adj[e.from()].push_back(e);

	this->E++;
}

/**
 * Gibt die Anzahl der Knoten zurueck
 *
 * \return Anzahl der Knoten
 */
int EdgeWeightedDigraph::getV() const
{
	return this->V;
}

/**
 * Gibt die Anzahl der Kanten zurueck
 *
 * \return Anzahl der Kanten
 */
int EdgeWeightedDigraph::getE() const
{
	return this->E;
}

/**
 * Liefert alle benachbarten Kanten zu v
 *
 * \param[in] v Knoten von dem aus gesucht wird
 * \return Vektor mit allen benachbarten Kanten
 */
std::vector<std::vector<DirectedEdge>> EdgeWeightedDigraph::getAdj() const
{
	return this->adj;
}

/**
 * Liefert alle benachbarten Kanten zu v
 *
 * \param[in] v Knoten von dem aus gesucht wird
 * \return Vektor mit allen benachbarten Kanten
 */
std::vector<DirectedEdge> EdgeWeightedDigraph::getAdj(int v) const
{
	std::vector<DirectedEdge> neighbors;
	for (auto const& n : adj[v]) {
		neighbors.push_back(n);
	}
	return neighbors;
}

/**
 * Gibt alle Kanten im Graph zurueck
 *
 * \return Vektor mit allen Kanten im Graph
 */
std::vector<DirectedEdge> EdgeWeightedDigraph::edges() const
{
	std::vector<DirectedEdge> list;
	for (int v = 0; v < this->V; v++)
	{
		for (DirectedEdge e : this->adj[v])
		{
			list.push_back(e);
		}
	}
	return list;
}

bool EdgeWeightedDigraph::del_Edge(DirectedEdge e)
{
	int v = e.from();
    int w = e.to();

    std::vector<DirectedEdge> v_edges = adj[v];
    std::vector<DirectedEdge> w_edges = adj[w];

    // Check if the edge exists in the graph
    bool v_c = true, w_c = true;
    int v_i = 0, w_i = 0;
    for (int i = 0; i < v_edges.size(); ++i) {
        if (v_edges[i] == e) {
            v_c = false;
            v_i = i;
            break;
        }
    }
    for (int i = 0; i < w_edges.size(); ++i) {
        if (w_edges[i] == e) {
            w_c = false;
            w_i = i;
            break;
        }
    }
    if (v_c || w_c) {
        return false;
    }

    // Remove the edge from the adjacency lists of both vertices
    v_edges.erase(v_edges.begin() + v_i);
    w_edges.erase(w_edges.begin() + w_i);

    this->E--;

    return true;
}

/**
 * Gibt die Kantenliste eines Knoten v zurueck
 *
 * \param[in]  v		Knoten
 * \return Vektor mit den Kanten vom Knoten v
 */
const std::vector<DirectedEdge> EdgeWeightedDigraph::operator[](int from) const
{
	return this->adj[from];
}


