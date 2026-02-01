//cluster.h
#pragma once
#include <vector>
#include "line.h"

std::vector<line> cluster_by_x(std::vector<line> lines, int threshold);
std::vector<line> cluster_by_y(std::vector<line> lines, int threshold);

bool is_horizontal(const std::vector<line>& lines);
bool orientation(const std::vector<line>& lines, bool is_horizontal);
