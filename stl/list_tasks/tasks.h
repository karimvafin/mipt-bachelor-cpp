#pragma once

#include <list>
#include <string>
#include <stdexcept>

int sum(const std::list<int>& l);

void remove_if_even(std::list<int>& l);

std::list<int> flatten(const std::list<std::list<int>>& lists);

void interleave(std::list<int>& a, std::list<int>& b);

bool is_palindrome(const std::list<int>& l);
