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

#include "compilationobject.h"


bool CompilationObject::isDotRuneFile(string filename)
{
	return (filename.substr(filename.find_last_of("."))) == ".rune";
}



string CompilationObject::withoutPath(string filename)
{
	return (filename.substr(filename.find_last_of("/")+1));
}

string CompilationObject::pathOnly(string filename)
{
	return (filename.substr(0,filename.find_last_of("/")+1));
}


CompilationObject::CompilationObject(string _path_to_rune)
{
	//check ".rune" format
	if(!isDotRuneFile(_path_to_rune)){
		cerr << "couldn't open \"" << _path_to_rune << "\"" << endl;
		throw this;
	}

	//check file is available (exists, visible etc..)
	ifstream source(_path_to_rune);
	if(!source){
		cerr << "\"" << _path_to_rune << "\" unavailable" << endl;
		throw this;
	}else{
		VERBOSE(cout << "opened \"" << _path_to_rune << "\"" << endl;)
		path_to_rune = _path_to_rune;
	}

	//get name
	string without_path = withoutPath(path_to_rune);
	name = without_path.substr(0,without_path.find_last_of("."));

	//get root path
	path_root = pathOnly(path_to_rune);

	//get path to ".cpp" (getting created later)
	path_to_cpp = path_root+BUILD_CPP_DIR+name+".cpp";

	//get path to executable (getting created later)
	path_to_exe = path_root+BUILD_EXE_DIR+name+EXECUTABLE_EXTENSION;
}
