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
vector<CompilationObject*> engine::cobjects;
vector<ChronicsFile*> engine::dot_chr_files;

bool engine::flag_verbose = 1;


void engine::abort(string message = "compiler aborted.", int error_code = -1)
{
	cout << message << "\t error code: " << error_code << endl;
	exit(error_code);
}



int engine::tryCompile(CompilationObject* co)
{
	int error_code;

	if((error_code=privates::generateCpp(co)))
		return error_code;
	if((error_code=privates::compile(co)))
		return error_code;

	return 0;
}


int engine::privates::generateCpp(CompilationObject* co)
{
	ensureDir(co->path_root+BUILD_CPP_DIR);
	ofstream cpp(co->path_to_cpp);
		if(!cpp){
			cerr << "couldn't create \"" << co->path_to_cpp << "\"" << endl;
			return -1;
		}
		VERBOSE(cout << "created \"" << co->path_to_cpp << "\"" << endl;)

	ifstream src(co->path_to_rune);



	cpp <<
	"#include<iostream>"				<< endl <<
	"int main(){"						<< endl;

	compiler::translate(src,cpp); //actual Runetala->C++ processing

	cpp <<
	"}"									<< endl;

	VERBOSE(cout << "done generating \"" << co->path_to_cpp << "\"" << endl;)
	return 0;
}



int engine::privates::compile(CompilationObject *co)
{
	VERBOSE(cout << "starting compilation of \"" << co->name << "\"" << endl;)

	string system_string = (string)CPP_COMPILER_SETTING +" -o " +co->path_root +co->name +EXECUTABLE_EXTENSION;
		   system_string += " "+custom_cpp_params+" "+co->path_to_cpp;

	int error_code = system(system_string.c_str());

	if(error_code==0){
		VERBOSE(cout << "done compilation of \"" << co->name << "\"" << endl;)
	}
	return error_code;
}






void engine::askToRun(string path_to_exe)
{
	cout << "would you like to launch it? (y/n)" << endl;

		while(char option = getChar())
		{
			switch(option)
			{
			#ifdef ON_WINDOWS
				case 'y':system(withBackSlashes(path_to_exe).c_str());
			#elif defined ON_UNIX
				case 'y':system(((string)"./"+path_to_exe).c_str());
			#endif
				case 'n':goto out_of_while;
			}
		}out_of_while: return;
}

void engine::ensureDir(string dir)
{
	#ifdef ON_WINDOWS
		replace(dir.begin(),dir.end(),'/','\\');
		system(((string)"mkdir "+dir).c_str());
	#elif defined ON_UNIX
		mkdir(dir.c_str());
	#endif
}

string engine::withFrontSlashes(string path)
{
	#ifdef ON_UNIX
		return path; //unix don't have backslashes anyway
	#elif defined ON_WINDOWS
		replace(path.begin(),path.end(),'\\','/');
		return path;
	#endif
}

string engine::withoutPath(string filename)
{
	return (filename.substr(filename.find_last_of("/")+1));
}

string engine::pathOnly(string filename)
{
	return (filename.substr(0,filename.find_last_of("/")+1));
}



string engine::withBackSlashes(string path)
{
	replace(path.begin(),path.end(),'/','\\');
	return path;
}

char engine::getChar()
{
	#ifdef ON_WINDOWS
		return getch();
	#elif defined ON_UNIX
		return getchar();
	#endif
}

void engine::parseArgs(vector<string> &args)
{
	for(string arg : args){
		//+ if(arg is compiler flag){} else:

		if(CompilationObject::isDotRuneFile(arg)){
			try{
				cobjects.push_back(new CompilationObject(withFrontSlashes(arg)));
			}catch(CompilationObject*){ // constructor failure
				exit(-1);
			}
		}else if(ChronicsFile::isDotChrFile(arg)){
			try{
				dot_chr_files.push_back(new ChronicsFile(withFrontSlashes(arg)));
			}catch(ChronicsFile*){ // constructor failure
				exit(-1);
			}
		}else{
			abort("unexpected command line argument: \""+arg+"\"",-1);
		}
	}
}
