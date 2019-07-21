#include <endian.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct image{
	public:
		int index;
		int label;
		int width;
		int height;
		vector<double> pixels;
};

int getNumImages(string file);
image readFile(int index, string file, string fileLable);
