#include <cstdio>
#include <fstream>
#include <string>
#include <map>

#include "grammar/libs/finalLexer.h"
#include "grammar/libs/finalParser.h"
#include "grammar/finalVisitorImpl.h"
#include "antlr4-runtime.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define UNDERLINE "\033[4m"
#define BLINK   "\033[5m"
#define REVERSE "\033[7m"
#define HIDDEN  "\033[8m"

#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"



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
		std::cout<<((!mulS)?BLINK:BOLD)<<((!mulS)?CYAN:WHITE)<<((!mulS)?user:">>>")<<"> "<<RESET;
		std::cout<<((!mulS)?BLINK:BOLD);
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
