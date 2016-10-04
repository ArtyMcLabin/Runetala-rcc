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
