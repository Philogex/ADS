#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"

//missing
#include <vector>
#include <map>
#include <set>

void print_adjacency_list(const EdgeWeightedGraph& graph) {
    int V = graph.getV();
    const std::vector<std::vector<Edge>>& adj = graph.getAdj();

    for (int v = 0; v < V; ++v) {
        std::cout << v << " -> ";

        const std::vector<Edge>& adjEdges = adj[v];
        for (int i = 0; i < adjEdges.size(); ++i) {
            const Edge& edge = adjEdges[i];
            int w = edge.other(v);
            int weight = edge.weight();

            std::cout << w << " [" << weight << "]";
            if (i != adjEdges.size() - 1) {
                std::cout << " -> ";
            }
        }

        std::cout << std::endl;
    }
}

void mainscreen_printMainscreen() {
    std::cout 
        << "Praktikum 5: Graphenalgorithem:" << std::endl
        << "1) Graph einlesen (Gerichtet/ Ungerichtet)" << std::endl
        << "2) Tiefensuche (Ungerichtet)" << std::endl
        << "3) Breitensuche (Ungerichtet)" << std::endl
        << "4) MST nach Prim (Eingabe: Startknoten) (Ungerichtet)" << std::endl
		<< "5) MST nach Kruskal (Ungerichtet)" << std::endl
        << "6) Kuerzeste Wege nach Dijkstra (Eingabe: Startknoten) (Gerichtet)" << std::endl
        << "7) Ausgabe der Adjazenzliste (Ungerichtet)" << std::endl
		<< "8) Kante loeschen (Gerichtet/ Ungerichtet)" << std::endl
        << "9) Kante hinzufuegen (Gerichtet/ Ungerichtet)" << std::endl
		<< "10)Programm beenden" << std::endl
		<< "Weiter mit beliebiger Eingabe ..." << std::endl
        << "?>";
}

void mainscreen_read_graph(EdgeWeightedGraph* &graph, EdgeWeightedDigraph* &digraph) {
	std::string input = "";
	while(true) {
		std::cout
			<< "1) Beispielgraph 1" << std::endl
			<< "2) Beispielgraph 2" << std::endl
			<< "3) Beispielgraph 3" << std::endl
			<< "4) Auswahl Beenden" << std::endl
			<< "?>";
		
		std::getline(std::cin, input);
		switch(std::stoi(input)) {
			case 1:
				graph = new EdgeWeightedGraph("graph1.txt");
				digraph = new EdgeWeightedDigraph("graph1.txt");
				return;
			case 2:
				graph = new EdgeWeightedGraph("graph2.txt");
				digraph = new EdgeWeightedDigraph("graph2.txt");
				return;
			case 3:
				graph = new EdgeWeightedGraph("graph3.txt");
				digraph = new EdgeWeightedDigraph("graph3.txt");
				return;
			case 4:
				return;
		}
	}
}

void mainscreen_dfs(EdgeWeightedGraph* &graph) {
	std::string input;
	std::cout
		<< "Startvertex fuer DFS eingeben: " << std::endl;
	
	std::getline(std::cin, input);

	std::vector<bool> marked;
	std::vector<int> edgeTo;
	marked.resize(graph->getV(), false);
	edgeTo.resize(graph->getV(), -1);
	Graphsearch::DFS(*graph, std::stoi(input), marked, edgeTo);
}

void mainscreen_bfs(EdgeWeightedGraph* &graph) {
	std::string input;
	std::cout
		<< "Startvertex fuer BFS eingeben: " << std::endl;
	
	std::getline(std::cin, input);
	
	std::vector<bool> marked;
	std::vector<int> edgeTo;
	marked.resize(graph->getV(), false);
	edgeTo.resize(graph->getV(), -1);
	Graphsearch::BFS(*graph, std::stoi(input), marked, edgeTo);
}

void mainscreen_prim(EdgeWeightedGraph* &graph) {
	std::string input;
	std::cout
		<< "Startvertex fuer MST-Suche nach Prim eingeben: " << std::endl;
	
	std::getline(std::cin, input);
	PrimMST prim(*graph, std::stoi(input));
	for(Edge e : prim.edges()) {
		std::cout << e.either() << ", " << e.other(e.either()) << ": [" << e.weight() << "]" << std::endl;
	}

	std::cout << "Gesamtgewicht: " << prim.weight() << std::endl;
}

void mainscreen_kruskal(EdgeWeightedGraph* &graph) {
	KruskalMST kruskal(*graph);
	for(Edge e : kruskal.edges()) {
		std::cout << e.either() << ", " << e.other(e.either()) << ": [" << e.weight() << "]" << std::endl;
	}

	std::cout << "Gesamtgewicht: " << kruskal.weight() << std::endl;
}

void mainscreen_dijkstra(EdgeWeightedDigraph* &digraph) {
	std::string input;
	std::cout
		<< "Startvertex fuer SPM-Suche nach Dijkstra eingeben: " << std::endl;
	
	std::getline(std::cin, input);

	DijkstraSP spm(*digraph, std::stoi(input));

	std::set<int> vertices;

	for(const DirectedEdge &e : digraph->edges()) {
		if(e.to() != std::stoi(input)) {
			vertices.insert(e.to());
		}
	}

	for(const int& vertex : vertices) {
		std::cout << "Path to: " << vertex << std::endl;
		for(DirectedEdge out : spm.pathTo(vertex)) {
			std::cout << out.from() << " -> " << out.to() << ": [" << out.weight() << "]" << std::endl;
		}
		std::cout << std::endl;
	}
}

void mainscreen_adj(EdgeWeightedGraph* &graph) {
	print_adjacency_list(*graph);
}

void mainscreen_del_edge(EdgeWeightedGraph* &graph, EdgeWeightedDigraph* &digraph) {
	std::string i_1;
	std::string i_2;
	std::cout
		<< "Vertex 1 (from) zur loeschenden Edge in Graph/Digraph eingeben: " << std::endl;
	std::getline(std::cin, i_1);

	std::cout
		<< "Vertex 2 (to) zur loeschenden Edge in Graph/Digraph eingeben: " << std::endl;
	std::getline(std::cin, i_2);

	//del from graph
	Edge del_e(0, 0, 0.);
	for(const Edge& e : (*graph)[std::stoi(i_1)]) {
		if((e.either() == std::stoi(i_1) || e.either() == std::stoi(i_2)) && (e.other(e.either()) == std::stoi(i_1) || e.other(e.either()) == std::stoi(i_2))) {
			del_e = e;
			break;
		}
	}
	
	//del from digraph
	DirectedEdge del_de(0, 0, 0.);
	for(const DirectedEdge& e : (*digraph)[std::stoi(i_1)]) {
		if(e.from() == std::stoi(i_1) && e.to() == std::stoi(i_2)) {
			del_de = e;
			break;
		}
	}

	if(
		(del_e.either() != 0 || del_e.other(del_e.either()) != 0) 
		&&
		(del_de.from() != 0 || del_de.to() != 0)
		) 
	{	
		if(digraph->del_Edge(del_de)) {
			graph->del_Edge(del_e);
			std::cout << "+ Vertex geloescht." << std::endl;
		}
		else {
			std::cout << "- From/To stimmen nicht mit dem direktionalen Graphen ueberein." << std::endl;
		}
	}
	else {
		std::cout << "- Vertex durch Fehler nicht geloescht." << std::endl;
	}
	
}

void mainscreen_add_edge(EdgeWeightedGraph* &graph, EdgeWeightedDigraph* &digraph) {
	std::string i_1;
	std::string i_2;
	std::string i_3;
	std::cout
		<< "Vertex 1 (from) zur hinzufuegenden Edge in Graph/Digraph eingeben: " << std::endl;
	std::getline(std::cin, i_1);

	std::cout
		<< "Vertex 2 (to) zur hinzufuegenden Edge in Graph/Digraph eingeben: " << std::endl;
	std::getline(std::cin, i_2);

	std::cout
		<< "Weight zur hinzufuegenden Edge in Graph/Digraph eingeben: " << std::endl;
	std::getline(std::cin, i_3);

	Edge del_e(std::stoi(i_1), std::stoi(i_2), std::stod(i_3));
	DirectedEdge del_de(std::stoi(i_1), std::stoi(i_2), std::stod(i_3));

	graph->add(del_e);
	digraph->add(del_de);

	std::cout << "+ Vertex hinzugefuegt." << std::endl;
}

int main() {
	// Starte Unit-Tests
	Catch::Session().run();

	EdgeWeightedGraph* graph;
	EdgeWeightedDigraph* digraph;
	std::string input;
	bool c = true;

	while(c) {
        mainscreen_printMainscreen();
        getline(std::cin, input);
        switch(std::stoi(input)) {
            case 1:
                mainscreen_read_graph(graph, digraph);
                break;
            case 2:
                mainscreen_dfs(graph);
                break;
            case 3:
                mainscreen_bfs(graph);
                break;
            case 4:
                mainscreen_prim(graph);
                break;
            case 5:
                mainscreen_kruskal(graph);
                break;
			case 6:
                mainscreen_dijkstra(digraph);
                break;
			case 7:
                mainscreen_adj(graph);
                break;
			case 8:
                mainscreen_del_edge(graph, digraph);
                break;
			case 9:
                mainscreen_add_edge(graph, digraph);
                break;
			case 10:
                exit(0);
            default:
                std::cout << "- Fehlerhafte Anweisung" << std::endl;
				c = false;
        }
        std::cout << std::endl;
    }

	return 0;
}