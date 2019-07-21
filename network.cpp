#include "read.h"
#include "perceptron.h"

int main(){

	string filename = "train-images-idx3-ubyte";
	vector<image> images;
	int numImages = getNumImages(filename);
	cerr<<numImages<<endl;

	vector<layer> network;
	network.resize(3);

	return 0;
}
