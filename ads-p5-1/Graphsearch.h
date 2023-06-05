#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>

namespace Graphsearch {

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked[v] = true;

		std::cout << v << " ";

		for (const Edge& edge : G.getAdj(v)) {
			int w = edge.other(v);
			if (!marked[w]) {
				edgeTo[w] = v;
				DFS_recursive(G, w, marked, edgeTo);
			}
		}

		
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked.assign(G.getV(), false);
		edgeTo.assign(G.getV(), -1);

		DFS_recursive(G, v, marked, edgeTo);

		for (bool isMarked : marked) {
			if (!isMarked) {
				return false; 
			}
		}
		return true;
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		std::queue<int> queue;
		marked[v] = true;
		queue.push(v);

		while (!queue.empty()) {
			int currentVertex = queue.front();
			queue.pop();

			std::cout << currentVertex << " ";

			for (const Edge& edge : G.getAdj(currentVertex)) {
				int w = edge.other(currentVertex);
				if (!marked[w]) {
					marked[w] = true;
					edgeTo[w] = currentVertex;
					queue.push(w);
				}
			}
		}

		for (bool isMarked : marked) {
			if (!isMarked) {
				return false;
			}
		}
		return true;
	}
}
