#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Perceptron{
	public:
		vector<Perceptron> inputs;
		vector<double> weights;
		double threshold;
		bool active;

		bool isactive();
};

class Layer{
	public:
		vector<Perceptron> node;
};

class Network{
	public:
		vector<Layer> layers;

		void resizeLayers(int numLayers, int seed);
};
