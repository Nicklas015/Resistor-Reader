//cluster.h
#pragma once
#include <vector>
#include "line.h"

std::vector<line> clusterByX(std::vector<line> lines, int threshold);
std::vector<line> clusterByY(std::vector<line> lines, int threshold);

bool isHorizontal(const std::vector<line>& lines);
