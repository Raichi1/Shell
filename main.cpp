#include <cstdio>
#include <fstream>
#include <string>
#include <map>

#include "grammar/libs/finalLexer.h"
#include "grammar/libs/finalParser.h"
#include "grammar/finalVisitorImpl.h"
#include "antlr4-runtime.h"


int main(int argc, char **argv) {
	finalVisitorImpl eval;
	const char* user = getenv("USER");

	if(!user){
		user = "shell";
	}

	bool mulS = 0;
	std::string sentence;
	std::string fSentence;
	std::string mSetence= "";

	while(1){
		std::cout<<((!mulS)?user:">>>")<<">";
		std::getline(std::cin,sentence);
		if(mulS){
			if(sentence=="<block>"){
				fSentence = mSetence;
				mSetence="";
				mulS=0;
			}else{
				mSetence+=(sentence+" ");
				continue;
			}
		}else{
			if(sentence=="<block>"){
				mulS=1;
				continue;
			}
			fSentence=sentence;
		}
		if(sentence=="exit")
			break;
		if(sentence.empty())
			continue;

		antlr4::ANTLRInputStream input(fSentence);
		finalLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		finalParser parser(&tokens);
		auto tree = parser.program();
		eval.visitProgram(tree);
		// std::cout<<tree->toStringTree(true)<<'\n';
	}
	eval.test();
}
