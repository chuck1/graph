#include <sstream>
#include <gr/graph/Graph.hpp>
#include <gr/plot/vert.hpp>

#include <gr/construct.hpp> // gr/construct.hpp_in

gr::graph::S_Graph	gr::complete(int n)
{
	auto g = std::make_shared<gr::graph::Graph>();
	// construct a complete graph with n vertices
	
	std::vector<gr::S_Vert> verts;
	
	for(int i = 0; i < n; ++i)
	{
		std::stringstream ss; ss << i;
		verts.push_back(std::make_shared<gr::plot::vert>(g, ss.str()));
	}

	for(int i = 0; i < n; ++i)
	{
		for(int j = i+1; j < n; ++j)
		{
			g->add_edge(std::make_shared<gr::edge>(verts[i], verts[j]));
		}
	}

	return g;
}
gr::graph::S_Graph	gr::flower(int n)
{
	auto g = std::make_shared<gr::graph::Graph>();
	
	std::vector<VERT_S> verts;

	int c = 0;
	
	auto root = std::make_shared<gr::plot::vert>(g, std::to_string(c++));
	
	for(int i = 0; i < n; ++i)
	{
		verts.push_back(std::make_shared<gr::plot::vert>(g, std::to_string(c++)));
		verts.push_back(std::make_shared<gr::plot::vert>(g, std::to_string(c++)));
		
		g->add_edge(root, verts[2*i]);
		g->add_edge(root, verts[2*i+1]);
		g->add_edge(verts[2*i], verts[2*i+1]);
	}

	return g;
}
std::vector<std::pair<int, int>>	possible_edges(int n)
{
	std::vector<std::pair<int, int>> ret;

	for(int i = 0; i < n; ++i)
	{
		for(int j = (i+1); j < n; ++j)
		{
			ret.emplace_back(i, j);
		}
	}

	return ret;
}
gr::graph::S_Graph		gr::random(int nverts, int n)
{
	auto g = std::make_shared<gr::graph::Graph>();
	
	auto possible = possible_edges(nverts);

	std::vector<VERT_S> verts;

	int c = 0;

	for(int i = 0; i < nverts; ++i)
		verts.push_back(std::make_shared<gr::plot::vert>(g, std::to_string(c++)));

	for(int i = 0; i < n; ++i)
	{
		int j = rand() % possible.size();
		
		auto p = possible[j];
		
		possible.erase(possible.begin() + j);
		
		g->add_edge(verts[p.first], verts[p.second]);
	}

	return g;
}



