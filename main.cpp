#include<iostream>
#include<fstream>


#include"engine.h"

using namespace std;
using namespace engine;

int main(int argc, char *argv[])
{
	if(argc==1){
		abort("please supply input file.",-1);
	}

	string current_filename = withFrontSlashes(argv[1]);
	tryCompile(current_filename); //@


	askToRun(current_filename); //will calculate executable name inside


	cout << endl;
	return 0;
}
