#ifndef ENGINE_H
#define ENGINE_H

#include<iostream>
#include<fstream>
#include<algorithm>

#ifdef ON_WINDOWS
	#include<conio.h>
#endif

using namespace std;

//debug macros
#define D(X) cerr << X << endl;
#define PRE  cerr << "PRE";
#define POST cerr << "POST";


#define BUILD_CPP_DIR "build/cpp/"

namespace engine
{
	extern string custom_cpp_params;

	extern bool flag_verbose;
		#define VERBOSE(X) if(engine::flag_verbose) X;

	void abort(string message, int error_code);
	int tryCompile(string expected_dot_rune_file);
	bool isDotRuneFile(string filename);
	string withFrontSlashes(string filename); //replace microsoft directory backslashes with valid.
	string getCppExtension(string filename);
	string removePath(string filename);
	void ensureDir(string dir);
	void askToRun(string filename);



	//private functions (for use by engine:: functions)
	namespace privates
	{
		//- string getBinaryExtensionName(string filename);

		int generateCpp(string dot_rune_file);
		int compileCpp(string cpp_file);
	}

}

#endif // ENGINE_H
