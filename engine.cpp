/* BSD 3-Clause License
 *
 *	 Copyright (c) 2016, Arty McLabin
 *	 All rights reserved.
 *
 * 	 Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *
 *	 * Redistributions of source code must retain the above copyright notice, this
 *	   list of conditions and the following disclaimer.
 *
 *	 * Redistributions in binary form must reproduce the above copyright notice,
 *	   this list of conditions and the following disclaimer in the documentation
 *	   and/or other materials provided with the distribution.
 *
 *	 * Neither the name of the copyright holder nor the names of its
 *	   contributors may be used to endorse or promote products derived from
 *	   this software without specific prior written permission.
 *
 *	 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *	 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *	 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *	 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *	 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *	 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *	 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *	 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *	 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include"engine.h"


string engine::custom_cpp_params = "";
bool engine::flag_verbose = 1;


void engine::abort(string message = "compiler aborted.", int error_code = -1)
{
	cout << message << "\t error code: " << error_code << endl;
	exit(error_code);
}



int engine::tryCompile(string expected_dot_rune_file)
{

	if(!isDotRuneFile(expected_dot_rune_file)){
		cerr << "\"" << expected_dot_rune_file << "\" is not *.rune extensioned" << endl;
		return -1;
	}else{ //file is indeed *.rune
		int error_code;

		if((error_code=privates::generateCpp(expected_dot_rune_file)))
			return error_code;
		if((error_code=privates::compileCpp(getCppExtension(removePath(expected_dot_rune_file)))))
			return error_code;

		return 0;
	}
}


bool engine::isDotRuneFile(string filename)
{
	return (filename.substr(filename.find_last_of("."))) == ".rune";
}

string engine::withFrontSlashes(string filename)
{
	replace(filename.begin(),filename.end(),'\\','/');
	return filename;
}

string engine::getCppExtension(string filename)
{
	return (filename.substr(0,filename.find_last_of("."))+".cpp");
}

string engine::removePath(string filename)
{
	return (filename.substr(filename.find_last_of("/")+1));
}


//string engine::privates::getBinaryExtensionName(string filename)
//{
//	#ifdef ON_WINDOWS
//		return (filename.substr(0,filename.find_last_of("."))+".exe")
//	#elif defined(ON_UNIX)
//		return (filename.substr(0,filename.find_last_of(".")))
//	#endif

//	; //syntax valid, deal with that.
//}


int engine::privates::generateCpp(string dot_rune_file)
{
	ifstream source(dot_rune_file);
		if(!source){
			cerr << "couldn't open \"" << dot_rune_file << "\"" << endl;
			return -1;
		}
		VERBOSE(cout << "opened \"" << dot_rune_file << "\"" << endl;)

	ensureDir("build/cpp");
		string fullname_cpp = "build/cpp/"+getCppExtension(removePath(dot_rune_file));
	ofstream cpp(fullname_cpp);
		if(!cpp){
			cerr << "couldn't create \"" << fullname_cpp << "\"" << endl;
			return -1;
		}
		VERBOSE(cout << "created \"" << fullname_cpp << "\"" << endl;)

	cpp <<
	"#include<iostream>"				<< endl <<
	"int main(){"						<< endl <<
	"std::cout<<\"hello world\";"		<< endl <<
	"return 0;"							<< endl <<
	"}"									<< endl
	;

	VERBOSE(cout << "done generating \"" << fullname_cpp << "\"" << endl;)
	return 0;
}



int engine::privates::compileCpp(string cpp_file)
{
	//- reimplement block in qmake
	#define CPP_COMPILER_SETTING "g++ -std=c++1z -static-libgcc -static-libstdc++ -static"
	#ifdef ON_WINDOWS
		#define EXECUTABLE_EXTENSION ".exe"
	#elif defined ON_UNIX
		#define EXECUTABLE_EXTENSION ""
	#endif


	VERBOSE(cout << "starting compilation of \"" << cpp_file << "\"" << endl;)

	string system_string = (string)CPP_COMPILER_SETTING +" -o "+cpp_file.substr(0,cpp_file.length()-4)
							+EXECUTABLE_EXTENSION +" "+custom_cpp_params +" "+ BUILD_CPP_DIR + cpp_file;

	//cerr << CPP_COMPILER_SETTING;
	int error_code = system(system_string.c_str());
	if(error_code==0)
		VERBOSE(cout << "done compilation of \"" << cpp_file << "\"" << endl;)

	return error_code;
}




void engine::ensureDir(string dir)
{
	#if defined(ON_WINDOWS)
		replace(dir.begin(),dir.end(),'/','\\');
		system(((string)"mkdir "+dir).c_str());
	#elif defined(ON_UNIX)
		#include<unistd.h>
		mkdir(dir.c_str());
	#endif
}

void engine::askToRun(string filename)
{
	cout << "would you like to launch it? (y/n)" << endl;

	#ifdef ON_WINDOWS
		string exe_filename = removePath(filename).substr(0,removePath(filename).find_last_of('.'))+".exe";
		while(char option = getch())
		{
			switch(option)
			{
				case 'y':system(exe_filename.c_str());
				case 'n':goto out_of_while;
			}
		}out_of_while:
	#elif defined ON_UNIX
		string exe_filename = removePath(filename).substr(0,removePath(filename).find_last_of('.'));
		while(char option = getchar())
		{
			switch(option)
			{
				case 'y':system(((string)"./"+exe_filename).c_str());
				case 'n':goto out_of_while;
			}
		}out_of_while:
	#endif

	return;
}
