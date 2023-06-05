#include "KruskalMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
	for(const Edge& e : G.edges()) {
		pq.push(e);
	}

	treeID.assign(G.getE(), 0);

	for(int i = 0; i < G.getV(); i++) {
		treeID[i] = i;
	}

	while(!pq.empty()) {
		Edge e = pq.top();
		pq.pop();

		int u = e.either();
		int v = e.other(u);

		if(treeID[u] != treeID[v]) {
			mst.push_back(e);

			//union
			int oldID = treeID[v];

			for (int i = 0; i < G.getV(); i++) {
				if (treeID[i] == oldID) {
					treeID[i] = treeID[u];
				}
			}
		}
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
	return mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
	double totalWeight = 0.;
    for (const Edge& e : mst) {
        totalWeight += e.weight();
    }
    return totalWeight;
}