#include "read.h"

int getNumImages(string file){
	ifstream source;
	source.open(file, ios::binary | ios::in);

	int magic =0;
	source.read((char*)&magic,sizeof(magic));
	magic=be32toh(magic);

	int images =0;
	source.read((char*)&images, sizeof(images));
	images=be32toh(images);

	source.close();
	return images;
}

image readFile(int index, string file, string fileLabel){
	vector<image>list;
	image output;
	output.index=index;

	ifstream source;
	ifstream label;

	source.open(file, ios::binary | ios::in);
	label.open(fileLabel, ios::binary | ios::in);

	int magic=0;
	source.read((char*)&magic, sizeof(magic));
	magic=be32toh(magic);
	label.read((char*)&magic,sizeof(magic));
	magic=be32toh(magic);

	int images=0;
	source.read((char*)&images, sizeof(images));
	images=be32toh(images);

	label.read((char*)&images,sizeof(images));
	images=be32toh(images);

	int labelLoc=label.tellg();
	labelLoc+=index;
	label.seekg(labelLoc, label.beg);

	//read label
	unsigned char labelChar=0;
	label.read((char*)&labelChar,sizeof(labelChar));
	int labelVal=labelChar;
	output.label=labelVal;

	//read rows
	int rows=0;
	source.read((char*)&rows,sizeof(rows));
	rows=be32toh(rows);
	output.height=rows;

	//read cols
	int cols=0;
	source.read((char*)&cols,sizeof(cols));
	cols=be32toh(cols);
	output.width=cols;

	int start=source.tellg();
	start+=(rows * cols * index);
	source.seekg(start , source.beg);

	unsigned char pixel=0;
	for(unsigned int i=0; i<rows; ++i){
		for(unsigned int j=0; j<cols; ++j){
			source.read((char*)&pixel,sizeof(pixel));
			double val=pixel;
			output.pixels.push_back(val/255);
		}
	}
	return output;
}
