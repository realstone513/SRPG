#pragma once
#include "../GameSystem/Stats.h"
#include <vector>

using namespace std;

class AbilityStone
{
public:
	const int count;
	vector<int> successCounts;
	vector<StatsEnum> stats;
	AbilityStone() : count(3) {};
	~AbilityStone() {};

	void SetStone(vector<int> counts, vector<StatsEnum> stats)
	{
		successCounts = counts;
		this->stats = stats;
	}

	void Reset()
	{
		successCounts.clear();
		stats.clear();
		successCounts.resize(count);
		stats.resize(count);
	}
};