#include "Algorithm.h"

#include "Tree.h"
#include <queue>
#include <fstream>


namespace {

    /* traverse the tree in the BFS order, extracting required data about each node */
	std::vector<InfoNode> makeOrdered(const Tree& t) 
    {
		std::vector<InfoNode> BFS_order;

		std::queue<std::size_t> parents;
		std::vector<int> is_used(t.getSize(), 0);
			
		Node root = t.getNode(0);
		InfoNode info_root = { root.key, root.weight, root.key, {} };
		BFS_order.push_back(info_root);
		parents.push(root.key);
		is_used[root.key] = 1;

		std::size_t count = 0;
		while (!parents.empty()) {
			std::size_t parent_key = parents.front();

			for (std::size_t key : t.getAdjacent(parent_key)) {
				if (!is_used[key]) {
					parents.push(key);
					BFS_order[count].children_keys.push_back(key);

					Node node = t.getNode(key);
					InfoNode info_node = { node.key, node.weight, parent_key, {} };
					BFS_order.push_back(info_node);
					is_used[key] = 1;
				}
			}

			parents.pop();
			++count;
		}

		return BFS_order;
	}

	void printResult(
        const std::string& filename,
		const std::vector<double>& l,
		const std::vector<double>& u) 
	{
		std::ofstream file(filename);

		for (std::size_t i = 0; i < l.size(); ++i)
			if (l[i] != -1)
				file << "lower tolerance of vertice " << i << " is " << l[i] << std::endl;
			else
				file << "upper tolerance of vertice " << i << " is " << u[i] << std::endl;
	}

}   //anonymous namespace end




void computeTolerances(const Tree& t) {
	std::vector<InfoNode> BFS_order = makeOrdered(t);
	std::size_t size = t.getSize();

    /* w[x] == maximum weight of the independent set 
    for the subtree t(x) */
	std::vector<double> w(size); 
    /* win[x] == maximum weight of the independent set 
    among those containing x for the subtree t(x) */
	std::vector<double> win(size);
    /* wout[x] == maximum weight of the independent set
    among those without x for the subtree t(x) */
	std::vector<double> wout(size);

    /* Win[x] == maximum weight of the independent set among those containing x */
    std::vector<double> Win(size); 
    /* Wout[x] == maximum weight of the independent set among those without x */
	std::vector<double> Wout(size);

	std::vector<std::size_t> s; //maximum independent set

	std::vector<double> l(size); //lower tolerances
	std::vector<double> u(size); //upper tolerances

	for (std::size_t i = 0; i < size; ++i) {
		InfoNode x = BFS_order[size - i - 1]; //reverse BSF order
		if (x.isLeaf()) {
			win[x.key] = x.weight;
			wout[x.key] = 0;

			w[x.key] = win[x.key];
		}
		else {
			win[x.key] = x.weight;
			wout[x.key] = 0;

			for (std::size_t y_key : x.children_keys) {
				win[x.key] += wout[y_key];
				wout[x.key] += w[y_key];
			}

			w[x.key] = std::max(win[x.key], wout[x.key]);
		}
	}

	std::vector<int> is_used(size, 0);
	for (InfoNode x : BFS_order) { //in BFS order
		if (x.isRoot()) {
			Win[x.key] = win[x.key];
			Wout[x.key] = wout[x.key];
		}
		else {
			Win[x.key] = Wout[x.parent_key] - w[x.key] + win[x.key];
			Wout[x.key] = wout[x.key] + std::max(
                Win[x.parent_key] - wout[x.key],
				Wout[x.parent_key] - w[x.key]);
		}

		if (!is_used[x.parent_key] && win[x.key] >= wout[x.key]) {
			s.push_back(x.key);
			is_used[x.key] = 1;
		}
	}

	std::size_t root_key = BFS_order[0].key;
	for (InfoNode x : BFS_order) { //any order is ok here
		if (is_used[x.key]) {
			l[x.key] = w[root_key] - Wout[x.key];
			u[x.key] = -1;
		}
		else {
			u[x.key] = w[root_key] - Win[x.key];
			l[x.key] = -1;
		}
	}

	printResult("results.txt", l, u);
}

