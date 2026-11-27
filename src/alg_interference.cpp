#include "alg_interference.h"

#include <stdexcept>
#include <sstream>
#include <fstream>

void InterferenceGraph::_import_node(const std::string& line) {
    // tracker for node numbers that we've seen
    static std::vector<bool> seen(_num_vars, false);
    // read node number
    std::string buf;
    std::stringstream stream(line);
    int var_no;
    std::getline(stream, buf, ':');
     try {
        var_no = std::stoi(buf);
        if (var_no >= _num_regs)
            var_no = -1;
    }
    catch (...) {
         var_no = -1;
    }    
    if (var_no < 0)
        throw std::runtime_error("invalid variable id");
    // check if we've already defined this variable
    if (seen[var_no])
        throw std::runtime_error("redefinition of variable");
    seen[var_no] = true;
    // read neighbors
    int neighbor;
    while (std::getline(stream, buf, ' ')) {
        std::getline(stream, buf, ':');
        try {
            neighbor = std::stoi(buf);
            if (neighbor >= _num_regs)
                neighbor = -1;
        }
        catch (...) {
            neighbor = -1;
        }    
        if (neighbor < 0)
            throw std::runtime_error("invalid neighbor id");
        _connect(neighbor, var_no);
    }
}

InterferenceGraph::InterferenceGraph(const std::string& file_path) {
    // validate file path 
    std::ifstream in_file(file_path);
    if (!in_file.is_open())
        throw std::runtime_error("Could not open the graph file. Does it exist?");
    // read size
    std::string size_str;
    std::getline(in_file, size_str);
    try {
        size_t ptr;
        _num_regs = std::stoi(size_str, &ptr);
        if (ptr != size_str.size())
            _num_regs = -1;
    }
    catch (...) {
        _num_regs = -1;
    }
    if (_num_regs <= 0)
        throw std::runtime_error("Register count must be a non-zero, positive integer");
    // read number of variables
     std::getline(in_file, size_str);
    try {
        size_t ptr;
        _num_vars = std::stoi(size_str, &ptr);
        if (ptr != size_str.size())
            _num_vars = -1;
    }
    catch (...) {
        _num_vars = -1;
    }
    if (_num_vars <= 0)
        throw std::runtime_error("Variable count must be a non-zero, positive integer");
    _nodes.resize(_num_vars);
    // read each vertex
    int read = 0;
    std::string buf;
    while (std::getline(in_file, buf)) {
        // check if we've gone out of bounds
        if (read == _num_regs)
            throw std::runtime_error("Too many vertices for given variable count");
        _import_node(buf);
        read++;
    }
    if (read != _num_regs)
        throw std::runtime_error("Not enough vertices defined");
}

// colors a with register reg_no
void InterferenceGraph::set_color(int a, int reg_no) {
    if (a < 0 || a >= _num_vars)
        throw std::runtime_error("variable id out of range.");
    else if (reg_no <= 0 || reg_no > _num_regs)
        throw std::runtime_error("register number out of range");
    _nodes[a].reg = reg_no;
}

// connects a to b. Because this is an undirected graph, this also connects b to a
void InterferenceGraph::_connect(int a, int b) {
    if (a < 0 || a >= _num_vars || b < 0 || b >= _num_vars)
        throw std::runtime_error("variable id out of range.");
    _nodes[a].neighbors.insert(b);
    _nodes[b].neighbors.insert(a);
}

// returns if the given node is colored
bool InterferenceGraph::is_colored(int a) {
    if (a < 0 || a >= _num_vars)
        return false;
    return _nodes[a].reg != -1;
}

// returns if nodes A and B are connected, returning false if either is out of range.
// this returns true if a == b
bool InterferenceGraph::is_connected(int a, int b) {
    if (a < 0 || a >= _num_vars || b < 0 || b >= _num_vars)
        return false;
    else if (a == b)
        return true;
    return _nodes[a].neighbors.find(b) != _nodes[a].neighbors.end();
}