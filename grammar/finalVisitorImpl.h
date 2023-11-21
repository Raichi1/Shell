#ifndef __FINAL_VISITOR_IMPL__
#define __FINAL_VISITOR_IMPL__

#include "libs/finalBaseVisitor.h"
#include "libs/finalParser.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

#include <algorithm>
#include <any>
#include <iostream>
#include <map>
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include <memory>
#include <string>
#include <system_error>

class finalVisitorImpl : finalBaseVisitor{
public:
    finalVisitorImpl()
      : context(std::make_unique<llvm::LLVMContext>()),
        module(std::make_unique<llvm::Module>("SHELL", *context)),
        builder(std::make_unique<llvm::IRBuilder<>>(*context)) {}

    virtual std::any visitProgram(finalParser::ProgramContext *ctx) override;
    
    virtual std::any visitStatement(finalParser::StatementContext *ctx) override;
    
    virtual std::any visitVarVariable(finalParser::VarVariableContext *ctx) override;
    
    virtual std::any visitAsiggn(finalParser::AsiggnContext *ctx) override;
    
    virtual std::any visitFunc(finalParser::FuncContext *ctx) override;

    virtual std::any visitArg_func(finalParser::Arg_funcContext *ctx) override;
    
    virtual std::any visitForSentence(finalParser::ForSentenceContext *ctx) override;
    
    virtual std::any visitWhileSentence(finalParser::WhileSentenceContext *ctx) override;
    
    virtual std::any visitIfelse(finalParser::IfelseContext *ctx) override;
    
    virtual std::any visitIf(finalParser::IfContext *ctx) override;
    
    virtual std::any visitPrint(finalParser::PrintContext *ctx) override;
    
    virtual std::any visitEnvVariable(finalParser::EnvVariableContext *ctx) override;
    
    virtual std::any visitLista(finalParser::ListaContext *ctx) override;
    
    virtual std::any visitFiles(finalParser::FilesContext *ctx) override;
    
    virtual std::any visitEcho(finalParser::EchoContext *ctx) override;

    virtual std::any visitMove(finalParser::MoveContext *ctx) override;
    
    virtual std::any visitShow(finalParser::ShowContext *ctx) override;
    
    virtual std::any visitPlusMinus(finalParser::PlusMinusContext *ctx) override;
    
    virtual std::any visitIdentifier(finalParser::IdentifierContext *ctx) override;
    
    virtual std::any visitNumber(finalParser::NumberContext *ctx) override;
    
    virtual std::any visitRootList(finalParser::RootListContext *ctx) override;
    
    virtual std::any visitMulDiv(finalParser::MulDivContext *ctx) override;
    
    virtual std::any visitNotExpr(finalParser::NotExprContext *ctx) override;
    
    virtual std::any visitParenExpr(finalParser::ParenExprContext *ctx) override;
    
    virtual std::any visitAndOr(finalParser::AndOrContext *ctx) override;
    
    virtual std::any visitComparation(finalParser::ComparationContext *ctx) override;

    void test(){
		std::error_code error;
		llvm::raw_fd_stream outLL("pruebas.ll", error);
		module->print(outLL, nullptr);
	}

private:
    std::map<std::string, std::any> memory;
    std::map<std::string, std::any> externVar;
	std::unique_ptr<llvm::LLVMContext> context;
	std::unique_ptr<llvm::Module> module;
	std::unique_ptr<llvm::IRBuilder<>> builder;
};

#endif