#include "finalVisitorImpl.h"

#include "../commands/dirs.h"
#include "../commands/cmd.h"
#include "../commands/echo.h"
#include "../commands/move.h"

#include <filesystem>

std::any finalVisitorImpl::visitProgram(finalParser::ProgramContext *ctx){
    // std::cout<<"visitProgram\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitStatement(finalParser::StatementContext *ctx){
    // std::cout<<"visitStatement\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitVarVariable(finalParser::VarVariableContext *ctx){
    std::string key= ctx->ID()->getText();
    llvm::Value *val = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    memory[key]=val;
    return nullptr;
}

std::any finalVisitorImpl::visitAsiggn(finalParser::AsiggnContext *ctx){
    std::string key= ctx->ID()->getText();
    llvm::Value *val = std::any_cast<llvm::Value*>(visit(ctx->expression()));
    memory[key]=val;
    return nullptr;
}

std::any finalVisitorImpl::visitFunc(finalParser::FuncContext *ctx){
    std::cout<<"visitFunc\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitArg_func(finalParser::Arg_funcContext *ctx){
    std::cout<<"visitArg_func\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitForSentence(finalParser::ForSentenceContext *ctx){
    std::cout<<"visitForSentence\n";
    std::string key = ctx->ID()->getText();
    bool defined = (memory.count(key))?1:0;
    std::vector<llvm::Value *> vals = std::any_cast<std::vector<llvm::Value *>>(visit(ctx->list()));
    for(llvm::Value* e: vals){
        memory[key] = e;
        for(auto e: ctx->statement()) visit(e);
    }
    if(!defined)memory.erase(key);
    return nullptr;
}

std::any finalVisitorImpl::visitWhileSentence(finalParser::WhileSentenceContext *ctx){
    std::cout<<"visitWhileSentence\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitIfelse(finalParser::IfelseContext *ctx){
    // std::cout<<"visitIfelse\n";
    llvm::Value *bCondition = std::any_cast<llvm::Value *>(visit(ctx->expression()));

    llvm::FunctionType *FT = llvm::FunctionType::get(builder->getVoidTy(), false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "_anonIFELSE_", module.get());

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "entry", F);
    builder->SetInsertPoint(BB);

    llvm::BasicBlock* TB = llvm::BasicBlock::Create(*context, "then_Block", F);
    llvm::BasicBlock* EB = llvm::BasicBlock::Create(*context, "else_Block", F);
    llvm::BasicBlock* MB = llvm::BasicBlock::Create(*context, "merge_Block", F);

    builder->CreateCondBr(bCondition, TB, EB);

    // Construir el bloque 'then'
    builder->SetInsertPoint(TB);
    visit(ctx->statement(0));
    builder->CreateBr(MB);

    // Construir el bloque 'else'
    builder->SetInsertPoint(EB);
    visit(ctx->statement(1));
    builder->CreateBr(MB);

    builder->SetInsertPoint(MB);

    return nullptr;
}

std::any finalVisitorImpl::visitIf(finalParser::IfContext *ctx){
    // std::cout<<"visitIf\n";
    llvm::Value *bCondition = std::any_cast<llvm::Value *>(visit(ctx->expression()));

    llvm::FunctionType *FT = llvm::FunctionType::get(builder->getVoidTy(), false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "_anonIF_", module.get());

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "entry", F);
    builder->SetInsertPoint(BB);

    llvm::BasicBlock* TB = llvm::BasicBlock::Create(*context, "then_Block", F);
    llvm::BasicBlock* MB = llvm::BasicBlock::Create(*context, "fi_Block", F);

    builder->CreateCondBr(bCondition, TB, MB);

    // Construir el bloque 'then'
    builder->SetInsertPoint(TB);
    visit(ctx->statement(0));
    builder->CreateBr(MB);
    builder->SetInsertPoint(MB);
    return nullptr;
}

std::any finalVisitorImpl::visitPrint(finalParser::PrintContext *ctx){
    // std::cout<<"visitPrintExpr\n";
    std::vector<double> Args;
    std::vector<llvm::Type *> Doubles(Args.size(), llvm::Type::getDoubleTy(*context));

    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getDoubleTy(*context), Doubles, false);

    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "_anon_", module.get());

    llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "entry", F);
    builder->SetInsertPoint(BB);

    llvm::Value *val = std::any_cast<llvm::Value *>(visit(ctx->expression()));
    
    builder->CreateRet(val);
	return nullptr;
}

std::any finalVisitorImpl::visitEnvVariable(finalParser::EnvVariableContext *ctx){
    std::cout<<"visitEnvVariable\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitLista(finalParser::ListaContext *ctx){
    std::vector<llvm::Value *> values;
    for(auto e: ctx->expression()){
        llvm::Value* vl= std::any_cast<llvm::Value *>(visit(e));
        values.push_back(vl);
    }
    return std::any(values);
}

std::any finalVisitorImpl::visitFiles(finalParser::FilesContext *ctx){
    std::string content = ctx->optt->getText();
    std::string command = ctx->opt->getText(); 
    category(command,content);
    return nullptr;
}

std::any finalVisitorImpl::visitEcho(finalParser::EchoContext *ctx){
    std::string enVar = ctx->ID()->getText();
    echo(enVar);
    return nullptr;
}

std::any finalVisitorImpl::visitMove(finalParser::MoveContext *ctx){
    std::string fID = ctx->ID(0)->getText();
    std::string sID = ctx->ID(1)->getText();
    move(fID,sID);
    return nullptr;
}

std::any finalVisitorImpl::visitShow(finalParser::ShowContext *ctx){
    if(ctx->opt->getType() == finalParser::PWD){
        std::filesystem::path current_path = std::filesystem::current_path();
        std::cout<<current_path<<'\n';
    }
    else listShow();
    return nullptr;
}

std::any finalVisitorImpl::visitPlusMinus(finalParser::PlusMinusContext *ctx){
    llvm::Value *L = std::any_cast<llvm::Value *>(visit(ctx->expression(0)));
    llvm::Value *R = std::any_cast<llvm::Value *>(visit(ctx->expression(1)));
    if (ctx->opt->getType() == finalParser::PLUS) {
        return std::any(builder->CreateFAdd(L, R, "addTemp"));
    } else if(ctx->opt->getType() == finalParser::MINUS){
        return std::any(builder->CreateFSub(L, R, "subTemp"));
    }else{
        llvm::Value *LI = builder->CreateFPToSI(L, builder->getInt64Ty());
        llvm::Value *RI = builder->CreateFPToSI(R, builder->getInt64Ty());
        llvm::Value *RS = builder->CreateFRem(LI, RI);
        return std::any(builder->CreateSIToFP(RS, builder->getDoubleTy()));
    }
}

std::any finalVisitorImpl::visitIdentifier(finalParser::IdentifierContext *ctx){
    // std::cout<<"identifier\n";
    std::string key = ctx->ID()->getText();
    if(memory.count(key)) return std::any(memory[key]);
    return std::any(nullptr);
}

std::any finalVisitorImpl::visitNumber(finalParser::NumberContext *ctx){
    auto numVal = std::stod(ctx->NUMBER()->getText());
    llvm::Value *val = llvm::ConstantFP::get(*context, llvm::APFloat(numVal));
    return std::any(val);
}

std::any finalVisitorImpl::visitRootList(finalParser::RootListContext *ctx){
    std::cout<<"visitRootList\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitMulDiv(finalParser::MulDivContext *ctx){
    llvm::Value *L = std::any_cast<llvm::Value *>(visit(ctx->expression(0)));
    llvm::Value *R = std::any_cast<llvm::Value *>(visit(ctx->expression(1)));
    if(ctx->opt->getType() == finalParser::TIMES){
        return std::any(builder->CreateFMul(L, R, "mulTemp"));
    }else{
        return std::any(builder->CreateFDiv(L,R, "divTemp"));
    }
}

std::any finalVisitorImpl::visitNotExpr(finalParser::NotExprContext *ctx){
    std::cout<<"visitNotExpr\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitParenExpr(finalParser::ParenExprContext *ctx){
    llvm::Value *val = std::any_cast<llvm::Value *>(visit(ctx->expression()));
    return std::any(val);
}

std::any finalVisitorImpl::visitAndOr(finalParser::AndOrContext *ctx){
    std::cout<<"visitAndOr\n";
    return visitChildren(ctx);
}

std::any finalVisitorImpl::visitComparation(finalParser::ComparationContext *ctx){
    std::cout<<"visitComparation\n";
    llvm::Value *L = std::any_cast<llvm::Value *>(visit(ctx->expression(0)));
    llvm::Value *R = std::any_cast<llvm::Value *>(visit(ctx->expression(1)));
    if(ctx->opt->getType() == finalParser::COMP) return std::any(builder->CreateFCmpOEQ(L, R, "equalTemp"));
    else if(ctx->opt->getType() == finalParser::DIFF) return std::any(builder->CreateFCmpONE(L, R, "diffTemp"));
    else if(ctx->opt->getType() == finalParser::LESS) return std::any(builder->CreateFCmpULT(L, R, "lessTemp"));
    else if(ctx->opt->getType() == finalParser::GREAT) return std::any(builder->CreateFCmpOGT(L, R, "greaterTemp"));
    else if(ctx->opt->getType() == finalParser::LTE) return std::any(builder->CreateFCmpULE(L, R, "ltequalTemp"));
    else if(ctx->opt->getType() == finalParser::GTE) return std::any(builder->CreateFCmpOGE(L, R, "gtequalTemp"));
    return nullptr;
}