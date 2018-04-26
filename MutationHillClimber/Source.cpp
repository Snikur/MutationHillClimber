#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <algorithm>

class RMHC
{
public:
	std::string rep, target;
	const int SHOW_EVERY = 100000, MIN_ASCII = 32, MAX_ASCII = 127;

	RMHC(std::string tar)
	{
		target = tar;
		srand((unsigned int)time(NULL));
		randomStart();
	}

	void randomStart()
	{
		for (size_t i = 0; i < target.length(); ++i)
		{
			rep += (char)rand() % (MAX_ASCII - MIN_ASCII) + MIN_ASCII;
		}
	}

	void run()
	{
		std::cout << "Iteration\tFitness\t\tSolution" << std::endl;

		double bestFitness = std::numeric_limits<double>::max();

		int iter = 1;

		while (rep != target)
		{
			std::string oldRep = rep;

			smallChange();

			double newFitness = fitness();

			if (newFitness < bestFitness)
			{
				bestFitness = newFitness;
			}
			else
			{
				rep = oldRep;
			}

			if (iter % SHOW_EVERY == 0)
			{
				std::cout << iter << "\t\t" << round(bestFitness) << "\t\t" << rep.c_str() << std::endl;
			}

			++iter;
		}
		std::cout << iter << "\t\t" << round(bestFitness) << "\t\t" << rep.c_str() << '\n';
	}

	void smallChange()
	{
		int index = rand() % rep.length();
		int currentChar = rep[index];

		if (currentChar == MIN_ASCII || (float)(rand() / RAND_MAX) > 0.5f)
		{
			++currentChar;
			currentChar = std::min(currentChar, MAX_ASCII);
		}
		else
		{
			--currentChar;
			currentChar = std::max(currentChar, MIN_ASCII);
		}
		rep[index] = (char)currentChar;
	}

	double fitness()
	{
		int diff = 0;

		for (size_t i = 0; i < rep.length(); ++i)
		{
			int targetChar = target[i];
			int currentChar = rep[i];
			diff += std::abs(targetChar - currentChar);
		}

		return diff;
	}
};

int main()
{
	RMHC rmhc("Hello World");
	clock_t begin = clock();
	rmhc.run();
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Total time: " << elapsed_secs << "s\n";
	char c;
	std::cin >> c;
	return 0;
}