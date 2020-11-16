#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class NQueensProblem {
    private:
        int size;
        vector<int> rows;
        vector<int> candidates;
    
    public:
        NQueensProblem();
        NQueensProblem(int);
        int calculateConflicts(int,int);
        void initialize();
        void moveQueen(int);
        int getMaxConflictsCol();
        int solve();
        void visualizeSolution();
};


// Function to initialize the board with N queens in an ideal layout
NQueensProblem::NQueensProblem(int size) {
    this->size = size;
    
    // this->initialize();
}

void NQueensProblem::initialize() {
    this->rows.clear();
    // Iterate every column to place the queen
    for(int col = 0; col < this->size; col++) {
        // Used to determine the best placement
        int bestConflicts = this->size;
        this->candidates.clear();
        // Find the rows with minimum number of conflicts and add them to candidates 
        this->rows.push_back(0);
        for(int row = 0; row < this->rows.size(); row++){
            int numOfConflicts = this->calculateConflicts(this->rows[row], col);
            if (numOfConflicts == bestConflicts) {
                this->candidates.push_back(row);
            }
            else if (numOfConflicts < bestConflicts) {
                this->candidates.clear();
                this->candidates.push_back(row);
                bestConflicts = numOfConflicts;
            }
        }
        int candidateIndex = rand() % this->candidates.size();
        this->rows[col] = candidates[candidateIndex];
    }
}

int NQueensProblem:: calculateConflicts(int row, int col) {
    int conflicts = 0;
    for (int val = 0; val < this->rows.size(); val++) {
        if(val != col) {
            int nextQueenRow = this->rows[val];
            if ((nextQueenRow == row) || (abs(nextQueenRow - row) == abs(val - col))) {
                conflicts++;
            }
        }
    }
    return conflicts;
}

int NQueensProblem::solve() {
    // MinConflicts
    int moves = 0;
    int maxIterations = 2 * this->size;
    int k = 0;
    initialize();

    while(true) {
        int numOfConflicts = 0;
        this->candidates.clear();

        // Get total conflicts
        for (int val = 0; val < this->rows.size(); val++) {
            numOfConflicts += this->calculateConflicts(this->rows[val], val);
        }

        // If the problem is solved return the moves
        if(!numOfConflicts) {
            return moves;
        }

        // Choose a random queen to move and increase the move counter
        int queenCol = rand() % (this->rows.size() - 1);
        this->moveQueen(queenCol);
        moves++;
    }

}

void NQueensProblem::moveQueen(int col) {
    this->candidates.clear();
    int bestConflicts = this->rows.size();
    for (int val = 0; val < this->rows.size(); val++) {
        int numOfConflicts = this->calculateConflicts(val, col);
        if (numOfConflicts == bestConflicts) {
            this->candidates.push_back(val);
        } else if (numOfConflicts < bestConflicts) {
            this->candidates.clear();
            bestConflicts = numOfConflicts;
            this->candidates.push_back(val);
        }   
    }
    if(this->candidates.size() > 0) {
        int candidateIndex = rand() % this->candidates.size();
        this->rows[col] = candidates[candidateIndex];
    }
}

void NQueensProblem::visualizeSolution() {
    for(int row = 0; row < this->size; row++) {
        for(int col = 0; col < this->size; col++) {
            if(this->rows[col] == row) {
                cout << "* ";
            } else {
                cout << "_ ";
            }
        }
        cout << "\n";
    }
}

int main(){
    auto start = high_resolution_clock::now();
    int N;
    cout << "N:\t"; cin >> N;
    if (N < 4) {
        cout << " Solution for N < 4 doesn't exist! Please try with higher number. " << endl;
    }
    NQueensProblem problem(N);
    
    int moves = problem.solve();
    if (N < 80) {
        problem.visualizeSolution();
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "NQueens Problem for N: " << N << " was solved with " << moves << " moves.\n"; 
    cout << "Time taken: " << duration.count()/1000 << " miliseconds" << endl; 
}