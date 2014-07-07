#include "tokentype.h"
#include <unordered_map>

using namespace std;
namespace
{
unordered_map<wstring, Token::Type> makeKeywordMap()
{
    unordered_map<wstring, Token::Type> m;
    m[L"break"] = Token::Break;
    m[L"case"] = Token::Case;
    m[L"catch"] = Token::Catch;
    m[L"continue"] = Token::Continue;
    m[L"debugger"] = Token::Debugger;
    m[L"default"] = Token::Default;
    m[L"delete"] = Token::Delete;
    m[L"do"] = Token::Do;
    m[L"else"] = Token::Else;
    m[L"finally"] = Token::Finally;
    m[L"for"] = Token::For;
    m[L"function"] = Token::Function;
    m[L"if"] = Token::If;
    m[L"in"] = Token::In;
    m[L"instanceof"] = Token::InstanceOf;
    m[L"new"] = Token::New;
    m[L"return"] = Token::Return;
    m[L"switch"] = Token::Switch;
    m[L"this"] = Token::This;
    m[L"throw"] = Token::Throw;
    m[L"try"] = Token::Try;
    m[L"typeof"] = Token::TypeOf;
    m[L"var"] = Token::Var;
    m[L"void"] = Token::Void;
    m[L"while"] = Token::While;
    m[L"with"] = Token::With;
    m[L"null"] = Token::NullLiteral;
    m[L"true"] = Token::BooleanLiteral;
    m[L"false"] = Token::BooleanLiteral;
    m[L"class"] = Token::FutureReservedWord;
    m[L"const"] = Token::FutureReservedWord;
    m[L"enum"] = Token::FutureReservedWord;
    m[L"export"] = Token::FutureReservedWord;
    m[L"extends"] = Token::FutureReservedWord;
    m[L"import"] = Token::FutureReservedWord;
    m[L"super"] = Token::FutureReservedWord;
    m[L"implements"] = Token::FutureReservedWord;
    m[L"interface"] = Token::FutureReservedWord;
    m[L"let"] = Token::FutureReservedWord;
    m[L"package"] = Token::FutureReservedWord;
    m[L"private"] = Token::FutureReservedWord;
    m[L"protected"] = Token::FutureReservedWord;
    m[L"public"] = Token::FutureReservedWord;
    m[L"static"] = Token::FutureReservedWord;
    m[L"yield"] = Token::FutureReservedWord;
    return std::move(m);
}
const thread_local unordered_map<wstring, Token::Type> keywordMap = makeKeywordMap();
}

void Token::identifierToKeyword()
{
    assert(type == Type::Identifier);
    auto iter = keywordMap.find(value);
    if(iter != keywordMap.end())
        type = get<1>(*iter);
}
