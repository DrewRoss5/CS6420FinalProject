#ifndef INTERFERENCE_H
#define INTERFERENCE_H

#include <string>
#include <vector>
#include <set>

struct GraphNode {
    int reg = -1;
    std::set<int> neighbors;
};

// each live range is represented as a number. 
// In a compiler, this could be changed to strings for names, however this is simply an implementation detail 
class InterferenceGraph {
    public:
        InterferenceGraph(const std::string& file_path);
        // setters
        void set_color(int a, int reg_no);
        // getters
        bool is_colored(int a);
        bool is_connected(int a, int b);

    private:
        // members
        int _num_regs;
        int _num_vars;
        std::vector<GraphNode> _nodes;
        // private methods
        void _connect(int a, int b);
        inline void _import_node(const std::string& node);

};

#endif