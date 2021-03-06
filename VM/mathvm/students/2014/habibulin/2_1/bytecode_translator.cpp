#include "mathvm.h"
#include "my_utils.h"
#include "parser.h"
#include "typechecking.h"
#include "bytecode_generator.h"

using namespace mathvm;

Status* BytecodeTranslatorImpl::translate(const string& program, Code* *code) {
    Parser parser;
    Status* status = parser.parseProgram(program);
    if (status->isError()) {
        return status;
    }
    delete status;
    DEBUG_MSG("parsing finished");

    TypeChecker typeChecker;
    InfoDeletter infoDeletter;
    typeChecker.check(parser.top());
    if(typeChecker.status().isError()) {
        string cause = typeChecker.status().errCause();
        size_t pos = typeChecker.status().errPos();
        infoDeletter.run(parser.top());
        return Status::Error(cause.c_str(), pos);
    }
    DEBUG_MSG("typechecking finished");

    InterpreterCodeImpl* iCode = new InterpreterCodeImpl();
    BytecodeGenerator bcGenerator(iCode);
    bcGenerator.gen(parser.top());
    if(bcGenerator.status().isError()) {
        string cause = bcGenerator.status().errCause();
        size_t pos = bcGenerator.status().errPos();
        infoDeletter.run(parser.top());
        return Status::Error(cause.c_str(), pos);
    }
    infoDeletter.run(parser.top());
    DEBUG_MSG("translation finished");
//    iCode->disassemble();

    *code = iCode;
    return Status::Ok();
}
