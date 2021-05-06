#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

class Solution {
 public:
  Solution(const int sz1, const int sz2) : lines_(sz1 + 1), columns_(sz2 + 1) {
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

  std::string FindLCS(const std::string &s1, const std::string &s2) {
	assert(s1.size() + 1 == lines_ && s2.size() + 1 == columns_);
	int size = FindSizeOfLCS(s1, s2);
	std::string res(size, '\0');
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

  ~Solution() {
	for (int i = 0; i < lines_; ++i) {
	  delete[] dp[i];
	}
	delete[] dp;
  }

 private:
  int FindSizeOfLCS(const std::string &s1, const std::string &s2) {
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
  int **dp = nullptr;
};

int main() {
  std::string s1, s2;
  std::cin >> s1 >> s2;
  //we'd like to allocate a double array of integers
  //number of lines == s1.size()
  //number of columns == s2.size()
  Solution sl(s1.size(), s2.size());
  std::cout << sl.FindLCS(s1, s2);

  return 0;
}