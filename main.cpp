#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

struct GeneAlgo {
	int 	population;
	double	rate;
	int 	size;
};

struct GenPass {
	std::vector<char>	dna;
	int 			fitness;
};

int main(int argc, char **argv) {
	std::string password("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV");
	if (argv[1])
		password = argv[1];
	GeneAlgo opt = {4000, 0.5, static_cast<int>(password.size())};


	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<char> charac(' ', '~');
	std::uniform_int_distribution<int> parent(0, opt.population/2);
	std::uniform_int_distribution<int> rdPos(0, password.length());
	std::uniform_real_distribution<double> rando(0.0, 1.0);


	std::vector<GenPass> dnas;


	dnas.resize(opt.population);
	for (auto &dna : dnas) {
		for (int i = 0; i < opt.size; i++)
			dna.dna.push_back(charac(gen));
	}

	int nbGen = 0;
	int pere = 0;
	int mere = 0;

	while (dnas[0].fitness != password.size() * 1) {
		for (auto &dna : dnas) {
			dna.fitness = 0;
			for(int i = 0; i < opt.size; i++) {
				//std::cout << dna.dna[i] << password[i] << std::endl;
				if(dna.dna[i] == password[i])
					dna.fitness += 1;
//				if (password.find(dna.dna[i]) != std::string::npos)
//					dna.fitness += 1;
			}
		}

		std::sort (dnas.begin(), dnas.end(), [](GenPass i,GenPass j){ return (i.fitness>j.fitness); });
		std::cout << "GEN: " << nbGen << " fitness: " << dnas[0].fitness << " " << std::endl;
		for (const auto &item1 : dnas[0].dna) {
			std::cout << item1;
		}
		std::cout << std::endl;

		for (int i = opt.population/2; i < opt.population; i += 2) {
			pere = parent(gen);
			mere = parent(gen);
			int pos = 0;
			int posrd = rdPos(gen);
			for (pos = 0; pos < posrd; pos++){
				dnas[i].dna[pos] = dnas[pere].dna[pos];
			}
			for (pos; pos < password.length(); pos++){
				dnas[i].dna[pos] = dnas[mere].dna[pos];
			}

			pos = 0;
			for (pos = 0; pos < posrd; pos++){
				dnas[i + 1].dna[pos] = dnas[mere].dna[pos];
			}
			for (pos; pos < password.length(); pos++){
				dnas[i + 1].dna[pos] = dnas[pere].dna[pos];
			}
		}

		for (auto &dna : dnas) {
			if (rando(gen) < opt.rate)
				dna.dna[rdPos(gen)] = charac(gen);
		}
		nbGen++;
	}

	return 0;
}