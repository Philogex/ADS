#include "PrimMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Prim Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  s		Startknoten
 */
PrimMST::PrimMST(EdgeWeightedGraph G, int s)
{
	marked.resize(G.getV(), false);

	visit(G, s);

	while (!pq.empty()) {
		Edge e = pq.top();
		pq.pop();
		
		int v = e.either();
		int w = e.other(v);

		if (marked[v] && marked[w])
			continue;

		mst.push_back(e);
		if (!marked[v])
			visit(G, v);
		if (!marked[w])
			visit(G, w);
	}
}

/**
 * Markiert Knoten v im Graph G als markiert und fuegt alle Nachbarn zur pq hinzu
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  v		Knoten im Graph G
 */
void PrimMST::visit(EdgeWeightedGraph G, int v)
{
	marked[v] = true;
	std::vector<Edge> adjEdges = G.getAdj(v);

	for (const Edge& e : adjEdges) {
		int w = e.other(v);
		if (!marked[w])
			pq.push(e);
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> PrimMST::edges() const
{
	return mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double PrimMST::weight() const
{
	double totalWeight = 0.;
	for (const Edge& e : mst) {
		totalWeight += e.weight();
	}
	return totalWeight;
}
