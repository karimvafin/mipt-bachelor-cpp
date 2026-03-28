#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

std::unordered_map<int, int> count_elements(const std::vector<int>& v);

int most_frequent(const std::vector<int>& v);

std::vector<int> two_sum(const std::vector<int>& v, int target);

std::vector<std::vector<std::string>> group_anagrams(const std::vector<std::string>& words);

std::vector<int> top_k_frequent(const std::vector<int>& v, int k);
