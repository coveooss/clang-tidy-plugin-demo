#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang-tidy/ClangTidy.h"
#include "clang-tidy/ClangTidyCheck.h"
#include "clang-tidy/ClangTidyModule.h"
#include "clang-tidy/ClangTidyModuleRegistry.h"

using namespace clang;
using namespace clang::tidy;
using namespace clang::ast_matchers;

class ReviseLibV2APICheck : public ClangTidyCheck
{
public:
    ReviseLibV2APICheck(StringRef Name, ClangTidyContext* Context) : ClangTidyCheck(Name, Context)
    {
    }
    void registerMatchers(ast_matchers::MatchFinder* Finder) override;
    void check(const ast_matchers::MatchFinder::MatchResult& Result) override;
};

void ReviseLibV2APICheck::registerMatchers(MatchFinder* Finder)
{
    Finder->addMatcher(callExpr(callee(functionDecl(hasName("ProcessRecord"))), hasArgument(0, cxxNewExpr())).bind("api_v1_call"), this);
}

void ReviseLibV2APICheck::check(const MatchFinder::MatchResult& result)
{
    const auto* matchedDecl = result.Nodes.getNodeAs<CallExpr>("api_v1_call");

    if (matchedDecl != nullptr) {
        const auto        arg1            = matchedDecl->getArg(0);
        const auto        arg1Type        = arg1->getType()->getPointeeType()->getTypeClassName();
        const std::string fixText         = std::string("std::make_shared<") + arg1Type + ">";
        const auto        startNewTypeLoc = arg1->child_begin()->getBeginLoc();
        const auto        endFixLoc       = startNewTypeLoc.getLocWithOffset(strlen(arg1Type) - 1);
        const auto        sourceRange     = SourceRange(arg1->getBeginLoc(), endFixLoc);

        constexpr char message[] = "Use `std::make_shared<Record>` instead of `new Record`.";
        const auto     fix       = FixItHint::CreateReplacement(sourceRange, fixText);
        diag(matchedDecl->getBeginLoc(), message, DiagnosticIDs::Warning) << fix;
    }
}

namespace {

class ReviseLibV2APICheckModule : public ClangTidyModule
{
public:
    void addCheckFactories(ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<ReviseLibV2APICheck>("revise-libv2-api");
    }
};

}  // namespace

namespace clang::tidy {

// Register the module using this statically initialized variable.
static ClangTidyModuleRegistry::Add<::ReviseLibV2APICheckModule> X("revise-libv2", "Revise libv2 API calls.");

// This anchor is used to force the linker to link in the generated object file and thus register the module.
volatile int ReviseLibV2APICheckAnchorSource = 0;

}  // namespace clang::tidy
