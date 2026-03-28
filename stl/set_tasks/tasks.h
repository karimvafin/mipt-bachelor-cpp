#pragma once

#include <set>
#include <vector>
#include <stdexcept>

std::set<int> unique_elements(const std::vector<int>& v);

std::set<int> intersection(const std::set<int>& a, const std::set<int>& b);

std::set<int> symmetric_difference(const std::set<int>& a, const std::set<int>& b);

bool has_pair_with_sum(const std::set<int>& s, int target);

std::set<int> k_closest(const std::set<int>& s, int x, int k);
