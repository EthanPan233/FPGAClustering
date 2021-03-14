# pragma once
# include "Cell.h"
# include "geo.h"
# include <limits>
using namespace std;

class Circuit : public Cell {
public:
    Circuit() {}
    Circuit(const int& numNets) : nets(vector<vector<int>>(numNets)) { }

    void loadCircuit(const string& filename);
    void addCell(Cell& cell) { cells.push_back(cell); }
 
    void addCell(const int& cellId) { 
        cells.push_back(Cell(0,0,cellId));
    }

    // Partitioning
    vector<vector<Cell>> branchClustering();
    void branchClusteringRecurse(vector<vector<Cell>>& currentAssignment, const int& cellId);
    int calLabel(vector<vector<Cell>>& currentAssignment);
    int bestSolution = numeric_limits<int>::max();

private:
    vector<Cell> cells;
    vector<vector<int>> nets; //nets[netId][cellId]
};