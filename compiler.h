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

#ifndef COMPILER_H
#define COMPILER_H

#include<iostream>
#include<fstream>
#include<map>
#include"runes/Rune_X.h"
#include"runes/Rune_C.h"
#include"runes/Rune_I.h"
#include"runes/Rune_O.h"
#include"runes/Rune_A.h"
#include"runes/Rune_N.h"
#include"runes/Rune_R.h"
#include"runes/Rune_L.h"




using namespace std;


namespace compiler
{
	extern vector<runetala::Rune_X> X_runes;
	extern vector<runetala::Rune_C> C_runes;
	extern vector<runetala::Rune_L> L_runes;


	void translate(ifstream &src, ofstream &cpp); //Runetala->C++
}

#endif // COMPILER_H
