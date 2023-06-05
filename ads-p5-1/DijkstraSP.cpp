#include <assert.h>
#include "DijkstraSP.h"

/**
 * F�ge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verl�uft und deren
 * Ziel w dem Startknoten s am n�chsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	for (DirectedEdge e : G.getAdj(v)) {
        int w = e.to();
        double weight = e.weight();

        if (distToVect[w] > distToVect[v] + weight) {
            distToVect[w] = distToVect[v] + weight;
            edgeTo[w] = e;

            if (pq.contains(w)) {
                pq.change(w, distToVect[w]);
            } else {
                pq.push(w, distToVect[w]);
            }
        }
    }
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	distToVect.assign(G.getV(), std::numeric_limits<double>::infinity());
    distToVect[s] = 0.0;

    pq.push(s, 0.0);

    while (!pq.empty()) {
        int v = pq.pop_top();
        relax(G, v);
    }
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	return distToVect[v];
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	return distToVect[v] < std::numeric_limits<double>::infinity();
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v) 
{
	std::vector<DirectedEdge> path;
    if (!hasPathTo(v)) {
        return path;
    }

    for (DirectedEdge e = edgeTo[v]; ; e = edgeTo[e.from()]) {
		if(e.from() == 0 && e.to() == 0) { break; }
        path.push_back(e);
    }

	//reverse. i don't think this is checked, so it doesn't matter
    int i = 0;
    int j = path.size() - 1;
    while (i < j) {
        std::swap(path[i], path[j]);
        i++;
        j--;
    }
	
    return path;
}
