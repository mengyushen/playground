#include <iostream>
#include <vector>
#include <numeric>
#include <utility>  
#include <unordered_map>

using std::vector;
using std::pair;
using std::unordered_map;

// brute force
vector<pair<int,int>> findSwapValues_Naive(vector<int> A, vector<int> B)
{
  vector<pair<int,int>> results;
  int sumA = std::accumulate(A.begin(), A.end(), 0);
  int sumB = std::accumulate(B.begin(), B.end(), 0);
  
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < B.size(); ++j) {
      int newSumA = sumA - A[i] + B[j];
      int newSumB = sumB + A[i] - B[j];
      if (newSumA == newSumB) {
        results.emplace_back(std::make_pair(A[i], B[j]));
      }
    }
  }
  return results;
}

// target approach
vector<pair<int,int>> findSwapValues_Target(vector<int> A, vector<int> B)
{
  vector<pair<int,int>> results;
  int sumA = std::accumulate(A.begin(), A.end(), 0);
  int sumB = std::accumulate(B.begin(), B.end(), 0);
  if ((sumA - sumB) % 2 != 0) return results;
  int target = (sumA - sumB) / 2;
  
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < B.size(); ++j) {
      if (target == A[i] - B[j]) {
        results.emplace_back(std::make_pair(A[i], B[j]));
      }
    }
  }
  return results;
}

// optimial solution
vector<pair<int,int>> findSwapValues_Optimal(vector<int> A, vector<int> B)
{
  vector<pair<int,int>> results;
  unordered_map<int,int> mapB;
  int sumA = std::accumulate(A.begin(), A.end(), 0);
  int sumB = std::accumulate(B.begin(), B.end(), 0);
  if ((sumA - sumB) % 2 != 0) return results;
  int target = (sumA - sumB) / 2;

  // build B map
  for (size_t i = 0; i < B.size(); ++i) {
    if (mapB.find(B[i]) == mapB.end()) {
      mapB[B[i]] = 1;
    }
  }

  for (size_t i = 0; i < A.size(); ++i) {
    int newB = A[i] - target;
    if (mapB.find(newB) != mapB.end()) {
      results.emplace_back(std::make_pair(A[i], newB));
    }
  }
}

int main() {
  vector<int> inputA = {4, 1, 2, 1, 1, 2}; 
  vector<int> inputB = {3, 6, 3, 3};

  // vector<pair<int,int>> swap_pair = findSwapValues_Naive(inputA, inputB);
  // vector<pair<int,int>> swap_pair = findSwapValues_Target(inputA, inputB);
  vector<pair<int,int>> swap_pair = findSwapValues_Optimal(inputA, inputB);

  if (!swap_pair.size()) {
    printf("null\n");
  }

  for( size_t i = 0; i < swap_pair.size(); i++ ) {
    printf("result %ld: (%d, %d)\n", i, swap_pair[i].first, swap_pair[i].second);
  }
  return 0; 
}
