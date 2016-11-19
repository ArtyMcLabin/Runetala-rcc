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

#include "Compiler.h"


Compiler::Compiler(ifstream &_src, ofstream &_cpp)
{
    src=&_src;
    cpp=&_cpp;
}

void Compiler::loadChronic(ifstream &chronic, string filename)
{
    string buffer;

    if(chronic.eof()){
        VERBOSE(cout << "done loading chronic \"" << filename << "\"." << endl;)
        return;
    }
    getline(chronic,buffer);

    switch(buffer[0])
    {
        case ';': //comment line
            break;
        case 'X':
            {
                Rune_X x;
                x.size = buffer[1]-'0'; //+ add support for sizes above 1-9 range //@ size==0 bad case
                x.name = buffer.substr(2);
                x.value = buffer.substr(buffer.find(" ")).find_first_not_of(" ");
                X_runes.push_back(x);
                break;
            }
        case 'C':
            {
                Rune_C c;
                c.size = buffer[1]-'0'; //+ add support for sizes above 1-9 range //@ size==0 bad case
                c.name = buffer.substr(2,buffer.find(" "));
                c.value = buffer.substr(buffer.find(" ")).find_first_not_of(" ");
                C_runes.push_back(c);
                break;
            }
        case 'L':
            //+
            break;
        default:
            cerr << "in " << filename << ":" << endl
                 << "\t"  << "no rune \"" << buffer[0] << "\" defined in Runetala." << endl;
    }

}

void Compiler::translate()
{
    for(runetala::Runic_Inscription inscription : inscriptions){
        (*cpp) << inscription.translate();
    }
}
