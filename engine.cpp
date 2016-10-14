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



int engine::tryCompile(CompilationObject* co)
{
	int error_code;

	if((error_code=privates::generateCpp(co)))
		return error_code;
	if((error_code=privates::compile(co)))
		return error_code;

	return 0;
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


int engine::privates::generateCpp(CompilationObject* co)
{
	ensureDir(co->path_root+BUILD_CPP_DIR);
	ofstream cpp(co->path_to_cpp);
		if(!cpp){
			cerr << "couldn't create \"" << co->path_to_cpp << "\"" << endl;
			return -1;
		}
		VERBOSE(cout << "created \"" << co->path_to_cpp << "\"" << endl;)

	cpp <<
	"#include<iostream>"				<< endl <<
	"int main(){"						<< endl <<
	"std::cout<<\"hello world\";"		<< endl <<
	"return 0;"							<< endl <<
	"}"									<< endl
	;

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

	#ifdef ON_WINDOWS
		while(char option = getch())
		{
			switch(option)
			{
				case 'y':system(withBackSlashes(path_to_exe).c_str());
				case 'n':goto out_of_while;
			}
		}out_of_while: return;
	#elif defined ON_UNIX
		while(char option = getchar())
		{
			switch(option)
			{
				case 'y':system(((string)"./"+path_to_exe).c_str());
				case 'n':goto out_of_while;
			}
		}out_of_while: return;
	#endif
}

void engine::ensureDir(string dir)
{
	#if defined(ON_WINDOWS)
		replace(dir.begin(),dir.end(),'/','\\');
		system(((string)"mkdir "+dir).c_str());
	#elif defined(ON_UNIX)
		mkdir(dir.c_str());
	#endif
}

string engine::withFrontSlashes(string path)
{
	replace(path.begin(),path.end(),'\\','/');
	return path;
}


string engine::withBackSlashes(string path)
{
	replace(path.begin(),path.end(),'/','\\');
	return path;
}
