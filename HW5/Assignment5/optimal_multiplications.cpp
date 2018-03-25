// Hasan Abdullah: optimal_multiplications.cpp (12-10-2017)
// Main file for Homework 5. Reads in the sizes of a number of matrices from a
// text file and then calculates and prints the optimal ordering and the optimal
// number of multiplications in the matrix chain (using dynamic programming).

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

namespace {

// Recursively print the optimal parenthesization (ordering) of a matrix chain.
// @i and @j are the left and right indices (respectively) of the expression to
// be printed. @parens is a 2-D vector that stores optimal parentheses break
// points. @m_name is the name of the matrix (e.g. 'A', 'B', ...).
// For simplicity, no error checking is done.
void OptimalParenthesization(int i, int j, const vector<vector<int>> &parens,
                             char &m_name) {
  if (i == j) {   // Base case: only one matrix is left to be printed.
    cout << m_name; ++m_name; return;
  }
  cout << "(";
  // Recursively put parentheses around subexpression[i...parens[i][j]].
  OptimalParenthesization(i, parens[i][j], parens, m_name);
  // Recursively put parentheses around subexpression[parens[i][j]+1...j].
  OptimalParenthesization(parens[i][j]+1, j, parens, m_name);
  cout << ")";
}

// Given the @sizes of a matrix chain (e.g. {10,20,30}->[10x20]*[20x30]), print
// the optimal parenthesization and the optimal number of multiplications.
// Assumes that @sizes.size() >= 3 and that all elements of @sizes are >= 1.
void PrintOptimalOrderAndMultiplications(const vector<int> &sizes) {
  const int n = sizes.size();
  // For simplicity, indexes are 1...n (0th row and 0th column are unused).
  vector<vector<int>> m(n, vector<int>(n)), parens(n, vector<int>(n));
  // m[i][j] = min. # of multiplications to compute A[i]A[i+1]...A[j] = A[i...j]
  // the dimensions of A[i] are sizes[i-1] x sizes[i]
  for (int i = 1; i < n; ++i)
    m[i][i] = 0;   // The diagonal is all 0 b/c no cost to multiply one matrix.

  for (int len = 2; len < n; ++len) {   // len is the current chain length
    for (int i = 1; i < n-len+1; ++i) {
      int j = i+len-1;
      m[i][j] = INT_MAX; // Initialize each element of current diagonal to inf.
      for (int k = i; k < j; ++k) {
        int cost = m[i][k] + m[k+1][j] + sizes[i-1]*sizes[k]*sizes[j];
        if (cost < m[i][j]) {
          m[i][j] = cost;
          parens[i][j] = k; // optimal paren break point in subexpression[i...j]
        }
      }
    }
  }

  char m_name = 'A';   // The first matrix is 'A', the next matrix is 'B', etc.
  cout << "Optimal Parenthesization is: ";
  OptimalParenthesization(1, n-1, parens, m_name);
  cout << endl << "Optimal Cost is: " << m[1][n-1] << endl;
}

} // namespace

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <dimensions_file>" << endl;
    abort();
  }
  const string filename{argv[1]};
  ifstream my_file{filename};
  if (my_file.fail()) {
    cerr << "Unable to open '" << filename << "'!" << endl;
    abort();
  }
  int size; vector<int> sizes;
  while (my_file >> size) {
    if (size < 1) {
      cerr << "All matrix sizes in " << filename << " must be > 0!" << endl;
      abort();
    }
    sizes.push_back(size);
  }
  my_file.close();
  if (sizes.size() < 3) {
    cerr << filename << " must contain at least 3 matrix sizes!" << endl;
    abort();
  }
  PrintOptimalOrderAndMultiplications(sizes);
  return 0;
}
