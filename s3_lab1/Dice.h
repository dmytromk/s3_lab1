#pragma once

#include <iostream>
#include <vector>

namespace gambling
{
	struct Dice
	{
		int amount;
		std::vector<double> weight_distribution;

		Dice(int N) {
			amount = N;
			weight_distribution.reserve(amount);
		}
		int Throw() {
			double counter = 1;
			double randomNumber = double(rand()) / RAND_MAX;
			for (int i = 0; i < amount; i++) {
				if (counter < randomNumber) return i + 1;
				counter -= weight_distribution[i];
			}
			return 0;
		}
		void setWeightDistribution()
		{
			std::cout << "Enter " << amount << " weights\n";
			for(int i = 0; i < amount; i++)
			{
				double to_add;
				std::cin >> to_add;
				this->weight_distribution.push_back(to_add);
			}
		}
		void randomWeightDistribution()
		{
			weight_distribution.clear();
			int chance = 0;
			for (int i = 0; i < amount; i++)
			{
				chance = std::rand();
				this->weight_distribution.push_back(chance);
			}
			double sum = 0;
			for (auto num : weight_distribution)
				sum += num;
			for (auto& num : weight_distribution)
				num /= sum;		
		}
		double checkProbabilities()
		{
			double res = 0;
			for (auto i : this->weight_distribution)
				res += i;
			return res;
		}
	};

	struct DiceSet
	{
		std::vector<Dice> dices;
		std::map<int, double> probabilityDictionary;
		void copyDice(Dice to_copy)
		{
			Dice copy(to_copy.amount);
			for (auto num : to_copy.weight_distribution)
				copy.weight_distribution.push_back(num);
			this->dices.push_back(copy);
		}
		void add(Dice to_copy)
		{
			this->dices.push_back(to_copy);
		}
		void countSums(int idx = 0, int key = 0, double probability = 1)
		{
			if (idx == dices.size())
			{
				auto it = probabilityDictionary.find(key);
				if (it == probabilityDictionary.end())
				{
					probabilityDictionary[key] = probability;
				}
				else
				{
					probabilityDictionary[key] += probability;
				}
				return;
			}

			// Iterate over all dice values
			for (int i = 0; i < dices[idx].amount; ++i)
			{
				countSums(idx + 1, key + i + 1, probability* dices[idx].weight_distribution[i]);
			}
		}
	};
}

