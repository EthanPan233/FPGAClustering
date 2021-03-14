# include "Circuit.h"
# include <fstream>
# include <sstream>
# include <iostream>
# include <limits>
# include <cassert>
# include <stdexcept>
# include "math.h"
# include <numeric>
# include "draw.h"
using namespace std;

void Circuit::loadCircuit(const string& filename) {
    cout << "Start reading file " << endl;
    ifstream infile(filename);
    string line;
    getline(infile, line);
    // cout << "line: " << line << endl;
    istringstream issFirstLine(line);
    int numCells, numNets;
    issFirstLine >> numCells >> numNets;
    // cout <<"numCells, numWires, xSize, ySize: " << numCells << " " << numNets << endl;
    *this = Circuit(numNets);
    // cout << "Finish reading the first line" << endl;

    for (int i = 0; i < numCells; i++) {
        addCell(i);
    }

    for (int i = 0; i < numNets; i++) {
        // cout << "Start reading a new line!" << endl;
        getline(infile, line);
        istringstream issCellAndNets(line);
        int numCellsOnNet;
        issCellAndNets >> numCellsOnNet;
        vector<int> cellIds(numCellsOnNet, -1);
        for (int j = 0; j < numCellsOnNet; j++) {
            int cellId;
            issCellAndNets >> cellId;
            cells[cellId].assignToNet(i);
            nets[i].push_back(cellId);
        }
    }
    cout << "Finish reading file: " << filename << endl;
}

vector<vector<Cell>> Circuit::branchClustering() {
    // Has two elements, left branch and right branch
    drawInitCircuit();
    vector<vector<Cell>> assignment(2);
    int initCellId = 0;
    branchClusteringRecurse(assignment, initCellId);
    cout << "Best solution: " << bestSolution << endl;
    cout << "Size of assignment: " << assignment[0].size() << ", " << assignment[1].size() << endl;
    return assignment;
}

void Circuit::branchClusteringRecurse(vector<vector<Cell>>& currentAssignment, const int& cellId) {
    // If the tree is not balanced, return
    if ((currentAssignment[0].size() - cells.size()/2.0) > 0.5) return;
    if ((currentAssignment[1].size() - cells.size()/2.0) > 0.5) return;

    if (cellId >= cells.size()) { // If all cells are assigned
        int currentSolution = calLabel(currentAssignment);
        if (currentSolution < bestSolution) {
            // if a better solution is found
            cout << "Left branch: ";
            for (auto& cell : currentAssignment[0]) cout << cell.cellId << " ";
            cout << endl << "Right branch: ";
            for (auto& cell : currentAssignment[1]) cout << cell.cellId << " ";
            cout << endl;
            bestSolution = currentSolution;
            cout << "Updated solution = " << bestSolution << endl;
            drawAssignment(currentAssignment);
        }
    } else {
        int currentLabel = calLabel(currentAssignment);
        if (currentLabel < bestSolution) {
            // First assign the cell to left
            currentAssignment[0].push_back(cells[cellId]);
            branchClusteringRecurse(currentAssignment, cellId+1);
            // Then assign the cell to right
            currentAssignment[0].pop_back();
            currentAssignment[1].push_back(cells[cellId]);
            branchClusteringRecurse(currentAssignment, cellId+1);
            currentAssignment[1].pop_back();
        }
    }
}

int Circuit::calLabel(vector<vector<Cell>>& currentAssignment) {
    int label = 0;
    for (auto& net : nets) {
        bool isOnLeft = false;
        bool isOnRight = false;
        for (auto& cell : net) {
           // if cell is on the left
            for (auto& cell1 : currentAssignment[0]) {
                if (cell == cell1.cellId) isOnLeft = true;
            }
            for (auto& cell2 : currentAssignment[1]) {
                if (cell == cell2.cellId) isOnRight= true;
            }
        }
        if (isOnLeft && isOnRight) label++;
    }
    return label;
}