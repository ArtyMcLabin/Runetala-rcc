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

#ifndef ENGINE_H
#define ENGINE_H

#include<iostream>
#include<fstream>
#include<algorithm>

#include"settings.h"
#include"CompilationObject.h"
#include"ChronicsFile.h"
#include"Compiler.h"


#ifdef ON_WINDOWS
	#include<conio.h>
#elif defined(ON_UNIX)
	#include<unistd.h>
#endif

using namespace std;

class CompilationObject;
class ChronicsFile;

namespace engine
{
	extern vector<CompilationObject*> cobjects;
	extern vector<ChronicsFile*> dot_chr_files;
	extern string custom_cpp_params;


	void abort(string message, int error_code);
	void parseArgs(vector<string> &args);
	int tryCompile(CompilationObject *co); //@
	void askToRun(string path_to_exe);

	// file/format works
	void ensureDir(string dir);
	string withFrontSlashes(string path); //replace microsoft directory backslashes with valid.
	string withoutPath(string filename);
	string pathOnly(string filename);
#ifdef ON_WINDOWS
	string withBackSlashes(string path); //replace valid directory slashes with microsoft backslashes.
#elif defined ON_UNIX
	//nothing special needed yet
#endif

	char getChar(); //crossplatform getch()

	//private functions (for use by engine:: functions)
	namespace privates
	{
		int generateCpp(CompilationObject *co); // Runetala -> C++
		int compileCpp(CompilationObject* co); // C++ -> machine code
	}

}

#endif // ENGINE_H
