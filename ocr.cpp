#include <iostream>
#include <fstream>
#include <endian.h>

using namespace std;
//t10k-images-idx3-ubyte  t10k-labels-idx1-ubyte  train-images-idx3-ubyte  train-labels-idx1-ubyte
int main(int argc, char* argv[]){
	if(argc<4){
		cerr<<"Not enough arugments.\n";
		return -1;
	}
	int index=atoi(argv[1]);
	string file=argv[2];
	string fileLabel=argv[3];

	ifstream source;
	ifstream label;
	ofstream output;
	
	source.open(file, ios::binary | ios::in);
	label.open(fileLabel, ios::binary | ios::in);
	output.open("image.pgm");

	if(!source.is_open()){
		cout<<"File failed to open\n";
		return -1;
	}
	if(!label.is_open()){
		cout<<"Labels faild to open\n";
		return -1;
	}
	output<<"P2\n";

	//read magic number
	int magic=0;
	source.read((char*)&magic,sizeof(magic));
	magic=be32toh(magic);
	if(magic !=2051){
		cout<<"Invaild magic number for image file: "<<argv[2]<<endl;
		return -1;
	}
	label.read((char*)&magic,sizeof(magic));
	magic=be32toh(magic);
	if(magic !=2049){
		cout<<"Invaild magic number for label file: "<<argv[3]<<endl;
		return -1;
	}

//	int labelLoc=label.tellg();
//	labelLoc+=index;
//	label.seekg(labelLoc, label.beg);

	//read number of images,
	int images=0;
	source.read((char*)&images,sizeof(images));
	images=be32toh(images);
	
	if(index>=images){
		cout<<"The index is not found in: "<< argv[2]<<endl;
		return -1;
	}
	
	label.read((char*)&images,sizeof(images));
	images=be32toh(images);
	if(index>=images){
		cout<<"The index is not found in: "<< argv[3]<<endl;
		return -1;
	}

	int labelLoc=label.tellg();
	labelLoc+=index;
	label.seekg(labelLoc, label.beg);
	
	//read label
	unsigned char labelChar=0;
	label.read((char*)&labelChar,sizeof(labelChar));
	int labelVal=labelChar;
	output<<"#"<<file<<" "<<argv[1]<<" "<<labelVal<<'\n';

	//read rows
	int rows=0;
	source.read((char*)&rows,sizeof(rows));
	rows=be32toh(rows);
	output<<rows<<' ';

	//read cols
	int cols=0;
	source.read((char*)&cols,sizeof(cols));
	cols=be32toh(cols);
	output<<cols<<'\n';

	output<<"255\n";

	int start=source.tellg();
	start+=(rows * cols * index);
	source.seekg(start , source.beg);


	unsigned char pixel=0;
	for(unsigned int i=0; i<rows; ++i){
		for(unsigned int j=0; j<cols; ++j){
			source.read((char*)&pixel,sizeof(pixel));
			int val=pixel;
			output<<val<<'\n';
		}
	}

	return 1;
}
