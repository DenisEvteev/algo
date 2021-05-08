#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>

/*
 * template of a class to work with different algorithms of finding Longest Common Subsequence
 * */
template<class Object>
class Solution {
 public:
  Solution(const Solution &sl) = delete;
  Solution &operator=(const Solution &sl) = delete;

  Solution(const int sz1, const int sz2, const int type) : lines_(sz1 + 1), columns_(sz2 + 1), type_(type) {
	if (type_ == 1) {
	  return;
	}
	dp = new int *[lines_]{};
	for (int i = 0; i < lines_; ++i) {
	  dp[i] = new int[columns_]{};
	}
  }

  friend std::ostream &operator<<(std::ostream &out, const Solution &sl) {
	for (int i = 0; i < sl.lines_; ++i) {
	  for (int j = 0; j < sl.columns_; ++j) {
		out << sl.dp[i][j] << " ";
	  }
	  out << std::endl;
	}
	return out;
  }

  Object FindLCS(const Object &s1, const Object &s2) {
	assert(s1.size() + 1 == lines_ && s2.size() + 1 == columns_);
	int size = FindSizeOfLCS(s1, s2);
	Object res(size, '\0');
	int i = lines_ - 1, j = columns_ - 1, ip = size - 1;
	while (i > 0 && j > 0) {
	  if (s1[i - 1] == s2[j - 1]) {
		res[ip--] = s1[--i];
		--j;
		continue;
	  }
	  if (dp[i - 1][j] > dp[i][j - 1]) {
		--i;
	  } else {
		--j;
	  }
	}
	return res;
  }

  /*Uses just two lines of general matrix to calculate the size of LCS*/
  int Optimization1FindSizeOfLCS(Object &s1, Object &s2) {
	if (lines_ != 2) {
	  std::cout << "Call FindSizeOfLCS despite this one\n";
	  return -1;
	}
	if (s1.size() < s2.size()) {
	  s1.swap(s2);
	}
	assert(s2.size() + 1 == columns_);
	for (int i = 1; i < s1.size() + 1; ++i) {
	  for (int j = 1; j < columns_; ++j) {
		dp[0][j] = dp[1][j];
		if (s1[i - 1] == s2[j - 1]) {
		  dp[1][j] = 1 + dp[0][j - 1];
		} else {
		  dp[1][j] = std::max(dp[0][j], dp[1][j - 1]);
		}
	  }
	}
	return dp[1][columns_ - 1];
  }

  /*Optimized version for finding LCS itself
   * in addition this algorithm calculates the size of LCS as well
   * */
  Object Optimization2FindLCS(Object &s1, Object &s2) {
	if (lines_ != 2) {
	  std::cout << "Call FindLCS despite this one\n";
	  return Object();
	}
	if (s1.size() < s2.size()) {
	  s1.swap(s2);
	}
	assert(s2.size() + 1 == columns_);
	std::vector<std::vector<bool>> move_up(s1.size() + 1,
										   std::vector<bool>(s2.size() + 1, false));
	std::vector<std::vector<bool>> move_left(s1.size() + 1,
											 std::vector<bool>(s2.size() + 1, false));
	for (int i = 1; i < s1.size() + 1; ++i) {
	  for (int j = 1; j < columns_; ++j) {
		dp[0][j] = dp[1][j];
		if (s1[i - 1] == s2[j - 1] and dp[0][j - 1] + 1 > dp[1][j - 1] and dp[0][j - 1] + 1 > dp[0][j]) {
		  dp[1][j] = 1 + dp[0][j - 1];
		} else if (dp[0][j] > dp[1][j - 1]) {
		  move_up[i][j] = true;
		  dp[1][j] = dp[0][j];
		} else {
		  move_left[i][j] = true;
		  dp[1][j] = dp[1][j - 1];
		}
	  }
	}
	/*Let's get the LCS*/
	int size = dp[1][columns_ - 1];
	Object res(size, 0);
	int ip = res.size() - 1;
	int i = s1.size(), j = s2.size();
	while (ip >= 0) {
	  if (move_up[i][j]) {
		--i;
	  } else if (move_left[i][j]) {
		--j;
	  } else {
		res[ip] = s1[i - 1];
		--ip;
		--i;
		--j;
	  }
	}

#ifdef DEBUG
	for(auto el: detected) {
	  for (auto i: el) {
		std::cout << i << " ";
	  }
	  std::cout << std::endl;
	}
#endif
	return res;
  }

  ~Solution() {
	for (int i = 0; i < lines_; ++i) {
	  delete[] dp[i];
	}
	delete[] dp;
  }

 private:
  int FindSizeOfLCS(const Object &s1, const Object &s2) {
	assert(s1.size() + 1 == lines_ && s2.size() + 1 == columns_);
	for (int i = 1; i < lines_; ++i) {
	  for (int j = 1; j < columns_; ++j) {
		if (s1[i - 1] == s2[j - 1]) {
		  dp[i][j] = std::max({1 + dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
		} else {
		  dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
		}
	  }
	}
	return dp[lines_ - 1][columns_ - 1];
  }

 private:
  int lines_{0};
  int columns_{0};
  /*Represents the options under which we would like to work with LCS
   * 1) type_ == 0 --> basic
   * 2) type_ == 1 --> optimized version with vector of bool
   * */
  int type_{0};
  int **dp = nullptr;
};

/*Tested under Codeforces*/
int main() {
#ifdef FIND_SIZE_LCS_VECTOR
  std::size_t n1, n2;
  std::cin >> n1;
  std::vector<int> vec1(n1, 0);
  for(auto &el: vec1) {
	std::cin >> el;
  }
  std::cin >> n2;
  std::vector<int> vec2(n2, 0);
  for(auto &el: vec2) {
	std::cin >> el;
  }

  Solution<std::vector<int>> sl(1, std::min(vec1.size(), vec2.size()), 0);
  std::cout << sl.Optimization1FindSizeOfLCS(vec1, vec2);
  return 0;
#endif
  std::string s1, s2;
  std::cin >> s1 >> s2;

  Solution<std::string> slOptimized(1, std::min(s1.size(), s2.size()), 0);
  std::cout << slOptimized.Optimization2FindLCS(s1, s2);

  return 0;
}