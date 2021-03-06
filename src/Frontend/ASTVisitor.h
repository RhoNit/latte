#pragma once

#include "AST.h"


template <typename T>
class ASTVisitor {

public:
  virtual T visitAST(AST& ast) {
    for (Def *def : ast.definitions)
      visitDef(*def);
    return T();
  }

  virtual T visitDef(Def &def) {
    if (auto *funDef = dyn_cast<FunctionDef>(def))
      return visitFunctionDef(*funDef);
    if (auto *classDef = dyn_cast<ClassDef>(def))
      return visitClassDef(*classDef);
    llvm_unreachable("Unhandled def");
  }

  virtual T visitFunctionDef(FunctionDef &functionDef) = 0;
  virtual T visitClassDef(ClassDef &classDef) = 0;

  virtual T visitBlock(Block &block) {
    for (Stmt* stmt : block.stmts)
      visitStmt(*stmt);
    return T();
  }


  virtual T visitStmt(Stmt &stmt) {
    if (isa<EmptyStmt>(stmt))
      return T();
    if (auto *blockStmt = dyn_cast<BlockStmt>(stmt))
      return visitBlockStmt(*blockStmt);
    if (auto *declStmt = dyn_cast<DeclStmt>(stmt))
      return visitDeclStmt(*declStmt);
    if (auto *assignStmt = dyn_cast<AssignStmt>(stmt))
      return visitAssignStmt(*assignStmt);
    if (auto *incrStmt = dyn_cast<IncrStmt>(stmt))
      return visitIncrStmt(*incrStmt);
    if (auto *decrStmt = dyn_cast<DecrStmt>(stmt))
      return visitDecrStmt(*decrStmt);
    if (auto *retStmt = dyn_cast<ReturnStmt>(stmt))
      return visitReturnStmt(*retStmt);
    if (auto *unrachableStmt = dyn_cast<UnreachableStmt>(stmt))
      return visitUnreachableStmt(*unrachableStmt);
    if (auto *ifStmt = dyn_cast<IfStmt>(stmt))
      return visitIfStmt(*ifStmt);
    if (auto *whileStmt = dyn_cast<WhileStmt>(stmt))
      return visitWhileStmt(*whileStmt);
    if (auto *exprStmt = dyn_cast<ExprStmt>(stmt))
      return visitExprStmt(*exprStmt);

    llvm_unreachable("Unhandled stmt");
  }

  virtual T visitBlockStmt(BlockStmt &blockStmt) {
    return visitBlock(blockStmt.block);
  }

  virtual T visitDeclStmt(DeclStmt &declStmt) = 0;
  virtual T visitAssignStmt(AssignStmt &assignStmt) {
    return visitExpr(*assignStmt.initializer);
  }

  virtual T visitIncrStmt(IncrStmt &incrStmt) = 0;
  virtual T visitDecrStmt(DecrStmt &incrStmt) = 0;
  virtual T visitReturnStmt(ReturnStmt &returnStmt) = 0;
  virtual T visitUnreachableStmt(UnreachableStmt &unreachableStmt) = 0;
  virtual T visitIfStmt(IfStmt &condStmt) = 0;
  virtual T visitWhileStmt(WhileStmt &whileStmt) = 0;
  virtual T visitExprStmt(ExprStmt &exprStmt) {
    return visitExpr(*exprStmt.expr);
  }

  virtual T visitExpr(Expr &expr) {
    if (auto *implicitCast = dyn_cast<RValueImplicitCast>(expr))
      return visitRValueImplicitCast(*implicitCast);
    if (auto *unExpr = dyn_cast<UnaryExpr>(expr))
      return visitUnaryExpr(*unExpr);
    if (auto *binExpr = dyn_cast<BinExpr>(expr))
      return visitBinExpr(*binExpr);
    if (auto *varExpr = dyn_cast<VarExpr>(expr))
      return visitVarExpr(*varExpr);
    if (auto *methodExpr = dyn_cast<MethodExpr>(expr))
      return visitMethodExpr(*methodExpr);
    if (auto *memberExpr = dyn_cast<MemberExpr>(expr))
      return visitMemberExpr(*memberExpr);
    if (auto *classCastExpr = dyn_cast<ClassCastExpr>(expr))
      return visitClassCastExpr(*classCastExpr);
    if (auto *newExpr = dyn_cast<NewExpr>(expr))
      return visitNewExpr(*newExpr);
    if (auto *funExpr = dyn_cast<FunExpr>(expr))
      return visitFunExpr(*funExpr);
    if (auto *constIntExpr = dyn_cast<ConstIntExpr>(expr))
      return visitConstIntExpr(*constIntExpr);
    if (auto *booleanExpr = dyn_cast<BooleanExpr>(expr))
      return visitBooleanExpr(*booleanExpr);
    if (auto *vtableExpr = dyn_cast<VTableExpr>(expr))
      return visitVTableExpr(*vtableExpr);
    if (auto *callExpr = dyn_cast<CallExpr>(expr))
      return visitCallExpr(*callExpr);
    if (auto *memberCallExpr = dyn_cast<MemberCallExpr>(expr))
      return visitMemberCallExpr(*memberCallExpr);
    if (auto *constStringExpr = dyn_cast<ConstStringExpr>(expr))
      return visitConstStringExpr(*constStringExpr);
    if (auto *parenExpr = dyn_cast<ParenExpr>(expr))
      return visitParenExpr(*parenExpr);
    if (auto *nullExpr = dyn_cast<NullExpr>(expr))
      return visitNullExpr(*nullExpr);
    llvm_unreachable("Unhandled expr");
  }

  virtual T visitRValueImplicitCast(RValueImplicitCast &implicitCast) = 0;
  virtual T visitUnaryExpr(UnaryExpr &unaryExpr) = 0;
  virtual T visitBinExpr(BinExpr &binExpr) = 0;
  virtual T visitVarExpr(VarExpr &varExpr) = 0;
  virtual T visitMethodExpr(MethodExpr &methodExpr) = 0;
  virtual T visitMemberExpr(MemberExpr &memberExpr) = 0;
  virtual T visitNewExpr(NewExpr &newExpr) = 0;
  virtual T visitClassCastExpr(ClassCastExpr &classCastExpr) = 0;
  virtual T visitFunExpr(FunExpr &funExpr) = 0;
  virtual T visitConstIntExpr(ConstIntExpr &constIntExpr) = 0;
  virtual T visitBooleanExpr(BooleanExpr &booleanExpr) = 0;
  virtual T visitVTableExpr(VTableExpr &vTableExpr) = 0;
  virtual T visitCallExpr(CallExpr &callExpr) = 0;
  virtual T visitMemberCallExpr(MemberCallExpr &memberCallExpr) = 0;
  virtual T visitConstStringExpr(ConstStringExpr &constStringExpr) = 0;
  virtual T visitParenExpr(ParenExpr &parenExpr) {
    return visitExpr(*parenExpr.expr);
  }
  virtual T visitNullExpr(NullExpr &nullExpr) = 0;

};




