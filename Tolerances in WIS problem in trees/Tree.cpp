#include "Tree.h"

#include <vector>
#include <exception>
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <queue>

/* Build a tree from a file containing Prufer sequence and weight of each node */
Tree::Tree(const std::string& filename) {
    std::fstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Can't open file");

    std::string code_string;
    std::vector<std::size_t> code;
    std::getline(file, code_string);
    for (char c : code_string)
        code.push_back(c - '0');
    std::reverse(code.begin(), code.end());
    _size = code.size() + 2;

    _nodes.resize(_size);
    _adjacency_list.resize(_size);

    std::size_t key;
    double weight;
    std::vector<int> is_used(_size, 0);
    while (!file.eof()) {
        file >> key;
        file >> weight;
        if (key > _nodes.size() - 1)
            throw std::runtime_error("Some key value exceeds the tree size");
        if (is_used[key] == 1)
            throw std::runtime_error("Some weight values were specified several times");

        _nodes[key] = { key, weight };
        is_used[key] = 1;
    }
    for (int flag : is_used)
        if (flag == 0)
            throw std::runtime_error("Some weight values were not specified");

    //Prufer sequence decoding begins here
    std::vector<int> in_code(_size, 0);
    is_used = std::vector<int>(_size, 0);

    for (std::size_t code_key : code)
        if (code_key > _size)
            throw std::runtime_error("Bad code");
        else
            ++in_code[code_key];

    while (!code.empty()) {
        for (std::size_t i = 0; i < _size; ++i)
            if (in_code[i] == 0 && !is_used[i]) {
                std::size_t code_key = code.back();

                _adjacency_list[i].push_back(code_key);
                _adjacency_list[code_key].push_back(i);

                is_used[i] = 1;
                --in_code[code_key];
                code.pop_back();
                break;
            }
    }
    for (std::size_t i = 0; i < _size; ++i)
        if (!is_used[i]) {
            _adjacency_list[i].push_back(_size - 1);
            _adjacency_list[_size - 1].push_back(i);

            break;
        }
}

/* Random tree of a given size; based on the MST problem */
Tree::Tree(std::size_t size_): _size(size_) {
    if (_size == 0)
        throw std::runtime_error("Size must be a positive value");
    _nodes.resize(_size);
    _adjacency_list.resize(_size);

    std::random_device seed;
    std::default_random_engine r(seed());
    std::uniform_int_distribution<int> discrete(1, 50);
    std::uniform_real_distribution<double> uniform(1, 100);

    //MST algorithm begins here
    std::vector<int> is_used(_size, 0);
    std::vector<int> C(_size, 100);
    std::vector<std::size_t> E(_size);

    using edge = std::pair<std::size_t, double>;
    auto cmp = [](edge left,
                  edge right)
    { return left.second < right.second; };
    std::priority_queue<edge, std::vector<edge>, decltype(cmp)> priority(cmp);

    //start with an arbitrary edge
    priority.emplace(0, 0);

    while (!priority.empty()) {
        std::size_t current_key = priority.top().first; priority.pop();
        if (is_used[current_key])
            continue;

        for (std::size_t next_key = 0; next_key < _size; ++next_key) { //adjacent vertices emulation
            if (next_key == current_key)
                continue;

            int connection_cost = discrete(r); //random adjacency matrix emulation
            if (!is_used[next_key] && C[next_key] > connection_cost) {
                priority.emplace(next_key, connection_cost);
                C[next_key] = connection_cost;
                E[next_key] = current_key;
            }
        }

        if (current_key != E[current_key]) { //0 skipped
            _adjacency_list[current_key].push_back(E[current_key]);
            _adjacency_list[E[current_key]].push_back(current_key);
            _nodes[current_key] = { current_key, uniform(r) }; //random weight for a node
        }

        is_used[current_key] = 1;
    }
    _nodes[0] = { 0, uniform(r) }; //random weight for 0
}

std::size_t Tree::getSize() const {
    return _size;
}

Node Tree::getNode(std::size_t key) const {
    return _nodes[key];
}

const std::vector<std::size_t>& Tree::getAdjacent(std::size_t key) const {
    return _adjacency_list[key];
}

void Tree::print() const {
    std::cout << "Tree:" << std::endl;
    for (std::size_t i = 0; i < _adjacency_list.size(); ++i) {
        std::cout << i << ": ";
        for (std::size_t j = 0; j < _adjacency_list[i].size(); ++j) 
            if (j != _adjacency_list[i].size() - 1)
                std::cout << _adjacency_list[i][j] << ", ";
        std::cout << std::endl;
    }
}
