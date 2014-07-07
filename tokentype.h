#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

#include <cwchar>
#include <cwctype>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <memory>
#include <sstream>
#include <vector>
#include <cstdio>
#include "convert.h"
#include "unicode_category.h"

using namespace std;

struct Location
{
    size_t startLine, startColumn, endLine, endColumn;
    Location()
        : startLine(1), startColumn(1), endLine(1), endColumn(1)
    {
    }
    Location(size_t line, size_t column)
        : startLine(line), startColumn(column), endLine(line), endColumn(column)
    {
    }
    Location(size_t startLine, size_t startColumn, size_t endLine, size_t endColumn)
        : startLine(startLine), startColumn(startColumn), endLine(endLine), endColumn(endColumn)
    {
    }
    template <typename CharType>
    friend basic_ostream<CharType> & operator <<(basic_ostream<CharType> & os, const Location & l)
    {
        os << string_cast<basic_string<CharType>>(string("Line #"));
        os << l.startLine;
        os << string_cast<basic_string<CharType>>(string(" Column #"));
        os << l.startColumn;
        return os;
    }
    struct CalcState
    {
        bool lastWasCR = false;
        size_t tabWidth = 4;
    };
    Location calcNext(wchar_t ch, CalcState & state) const
    {
        assert(state.tabWidth != 0);
        if(state.lastWasCR && ch == '\n')
        {
            state.lastWasCR = false;
            return Location(endLine, endColumn);
        }
        switch(ch)
        {
        case '\t':
            return Location(endLine, endColumn, endLine, endColumn + state.tabWidth + 1 - (endColumn + state.tabWidth - 1) % state.tabWidth);
        case '\r':
            state.lastWasCR = true;
            // fall through intended
        case '\n':
        case L'\u2028':
        case L'\u2029':
            return Location(endLine, endColumn, endLine + 1, 1);
        default:
            return Location(endLine, endColumn, endLine, endColumn + 1);
        }
    }
    const Location & operator +=(const Location & rt)
    {
        if(rt.startLine < startLine || (rt.startLine == startLine && rt.startColumn < startColumn))
        {
            startLine = rt.startLine;
            startColumn = rt.startColumn;
        }
        if(rt.endLine > endLine || (rt.endLine == endLine && rt.endColumn > endColumn))
        {
            endLine = rt.endLine;
            endColumn = rt.endColumn;
        }
        return *this;
    }
    friend Location operator +(const Location & l, const Location & r)
    {
        Location retval = l;
        retval += r;
        return retval;
    }
    Location end() const
    {
        return Location(endLine, endColumn);
    }
    Location start() const
    {
        return Location(startLine, startColumn);
    }
    wstring toString() const
    {
        wostringstream os;
        os << *this;
        return os.str();
    }
};

struct Token
{
    enum Type
    {
        None,
        Eof,
        Identifier,
        FutureReservedWord,
        LineTerminator,
        FSlash,
        FSlashEqual,
        RegexLiteral,
        NumberLiteral,
        StringLiteral,
        NullLiteral,
        BooleanLiteral,
        LBrace,
        RBrace,
        LParen,
        RParen,
        LBracket,
        RBracket,
        LessEqual,
        Period,
        Semicolon,
        Comma,
        Less,
        Greater,
        GreaterEqual,
        DoubleEqual,
        NotEqual,
        TripleEqual,
        NotDoubleEqual,
        Plus,
        Minus,
        Star,
        Percent,
        Increment,
        Decrement,
        LShift,
        RShiftSigned,
        RShiftUnsigned,
        Ampersand,
        Pipe,
        Caret,
        EMark,
        Tilde,
        LogicAnd,
        LogicOr,
        QMark,
        Colon,
        Equal,
        PlusEqual,
        MinusEqual,
        StarEqual,
        PercentEqual,
        LShiftEqual,
        RShiftSignedEqual,
        RShiftUnsignedEqual,
        AmpersandEqual,
        PipeEqual,
        CaretEqual,
        Break,
        Case,
        Catch,
        Continue,
        Debugger,
        Default,
        Delete,
        Do,
        Else,
        Finally,
        For,
        Function,
        If,
        In,
        InstanceOf,
        New,
        Return,
        Switch,
        This,
        Throw,
        Try,
        TypeOf,
        Var,
        Void,
        While,
        With,
    };
    static wstring getTypeString(Type type)
    {
        switch(type)
        {
        case None:
            return L"<None>";
        case Eof:
            return L"<End Of File>";
        case Identifier:
            return L"<Identifier>";
        case LineTerminator:
            return L"<Line Terminator>";
        case FSlash:
            return L"/";
        case FSlashEqual:
            return L"/=";
        case RegexLiteral:
            return L"<Regular Expression Literal>";
        case NumberLiteral:
            return L"<Number Literal>";
        case StringLiteral:
            return L"<String Literal>";
        case NullLiteral:
            return L"null";
        case BooleanLiteral:
            return L"<Boolean Literal>";
        case FutureReservedWord:
            return L"<Future Reserved Word>";
        case LBrace:
            return L"{";
        case RBrace:
            return L"}";
        case LParen:
            return L"(";
        case RParen:
            return L")";
        case LBracket:
            return L"[";
        case RBracket:
            return L"]";
        case LessEqual:
            return L"<=";
        case Period:
            return L".";
        case Semicolon:
            return L";";
        case Comma:
            return L",";
        case Less:
            return L"<";
        case Greater:
            return L">";
        case GreaterEqual:
            return L">=";
        case DoubleEqual:
            return L"==";
        case NotEqual:
            return L"!=";
        case TripleEqual:
            return L"===";
        case NotDoubleEqual:
            return L"!==";
        case Plus:
            return L"+";
        case Minus:
            return L"-";
        case Star:
            return L"*";
        case Percent:
            return L"%";
        case Increment:
            return L"++";
        case Decrement:
            return L"--";
        case LShift:
            return L"<<";
        case RShiftSigned:
            return L">>";
        case RShiftUnsigned:
            return L">>>";
        case Ampersand:
            return L"&";
        case Pipe:
            return L"|";
        case Caret:
            return L"^";
        case EMark:
            return L"!";
        case Tilde:
            return L"~";
        case LogicAnd:
            return L"&&";
        case LogicOr:
            return L"||";
        case QMark:
            return L"?";
        case Colon:
            return L":";
        case Equal:
            return L"=";
        case PlusEqual:
            return L"+=";
        case MinusEqual:
            return L"-=";
        case StarEqual:
            return L"*=";
        case PercentEqual:
            return L"%=";
        case LShiftEqual:
            return L"<<=";
        case RShiftSignedEqual:
            return L">>=";
        case RShiftUnsignedEqual:
            return L">>>=";
        case AmpersandEqual:
            return L"&=";
        case PipeEqual:
            return L"|=";
        case CaretEqual:
            return L"^=";
        case Break:
            return L"break";
        case Case:
            return L"case";
        case Catch:
            return L"catch";
        case Continue:
            return L"continue";
        case Debugger:
            return L"debugger";
        case Default:
            return L"default";
        case Delete:
            return L"delete";
        case Do:
            return L"do";
        case Else:
            return L"else";
        case Finally:
            return L"finally";
        case For:
            return L"for";
        case Function:
            return L"function";
        case If:
            return L"if";
        case In:
            return L"in";
        case InstanceOf:
            return L"instanceof";
        case New:
            return L"new";
        case Return:
            return L"return";
        case Switch:
            return L"switch";
        case This:
            return L"this";
        case Throw:
            return L"throw";
        case Try:
            return L"try";
        case TypeOf:
            return L"typeof";
        case Var:
            return L"var";
        case Void:
            return L"void";
        case While:
            return L"while";
        case With:
            return L"with";
        }
        assert(false);
        return L"";
    }
    Type type;
    wstring value;
    Location location;
    void identifierToKeyword();
    Token()
        : type(Eof), value(L""), location()
    {
    }
    Token(Type type, Location location = Location())
        : type(type), value(getTypeString(type)), location(location)
    {
    }
    Token(Type type, Location location, wstring value)
        : type(type), value(value), location(location)
    {
    }
    wstring toString() const
    {
        switch(type)
        {
        case Identifier:
        case RegexLiteral:
        case NumberLiteral:
        case BooleanLiteral:
        case NullLiteral:
            return value;
        case StringLiteral:
        {
            wstring retval = L"\"";
            for(size_t i = 0; i < value.size(); i++)
            {
                wchar_t ch = value[i];
                if((unsigned)ch >= 0x10000)
                {
                    unsigned highValue = (((unsigned)ch >> 10) & 0x3FF) + 0xD800;
                    unsigned lowValue = ((unsigned)ch & 0x3FF) + 0xDC00;
                    wchar_t str[32];
                    swprintf(str, sizeof(str) / sizeof(str[0]), L"\\u%04X\\u%04X", highValue, lowValue);
                    retval += str;
                    continue;
                }
                switch(ch)
                {
                case '\"':
                case '\\':
                case '\'':
                    retval += L"\\";
                    retval += ch;
                    break;
                case '\b':
                    retval += L"\\b";
                    break;
                case '\0':
                    if(i + 1 < value.size() && value[i + 1] >= '0' && value[i + 1] <= '9')
                        retval += L"\\x00";
                    else
                        retval += L"\\0";
                    break;
                case '\f':
                    retval += L"\\f";
                    break;
                case '\n':
                    retval += L"\\n";
                    break;
                case '\r':
                    retval += L"\\r";
                    break;
                case '\t':
                    retval += L"\\t";
                    break;
                case '\v':
                    retval += L"\\v";
                    break;
                case L'\u2028':
                    retval += L"\\u2028";
                    break;
                case L'\u2029':
                    retval += L"\\u2029";
                    break;
                default:
                    retval += ch;
                    break;
                }
            }
            retval += L"\"";
            return retval;
        }
        default:
            return getTypeString(type);
        }
    }
    template <typename CharType>
    friend basic_ostream<CharType> & operator <<(basic_ostream<CharType> & os, Token t)
    {
        return os << t.location << string_cast<basic_string<CharType>>(L" : " + t.toString());
    }
};

namespace ParseError
{
class ParseError : public runtime_error
{
    wstring msg;
    Location location;
public:
    ParseError(wstring msg, Location location)
        : runtime_error(string_cast<string>(location.toString() + L" : " + msg)), msg(msg), location(location)
    {
    }
    wstring getMessage() const
    {
        return msg;
    }
    Location getLocation() const
    {
        return location;
    }
};

inline void generic(wstring msg, Location location)
{
    throw ParseError(msg, location);
}

inline void expected(const vector<wstring> & expectedStrings, Location location)
{
    wstring msg = L"expected : ";
    if(expectedStrings.size() == 2)
        msg += expectedStrings[0] + L" or " + expectedStrings[1];
    else
    {
        for(size_t i = 0; i < expectedStrings.size(); i++)
        {
            if(i > 0)
            {
                msg += L", ";
                if(i == expectedStrings.size() - 1)
                    msg += L"or ";
            }
            msg += expectedStrings[i];
        }
    }
    generic(msg, location);
}

inline void expected(const vector<Token::Type> & expectedTokens, Location location)
{
    wstring msg = L"expected : ";
    if(expectedTokens.size() == 2)
        msg += Token::getTypeString(expectedTokens[0]) + L" or " + Token::getTypeString(expectedTokens[1]);
    else
    {
        for(size_t i = 0; i < expectedTokens.size(); i++)
        {
            if(i > 0)
            {
                msg += L", ";
                if(i == expectedTokens.size() - 1)
                    msg += L"or ";
            }
            msg += Token::getTypeString(expectedTokens[i]);
        }
    }
    generic(msg, location);
}

inline void unexpected(wstring msg, Location location)
{
    generic(L"unexpected : " + msg, location);
}

inline void unexpected(Token::Type tokenType, Location location)
{
    unexpected(Token::getTypeString(tokenType), location);
}

inline void unexpected(Token token)
{
    unexpected(token.toString(), token.location);
}
}

class Tokenizer
{
private:
    Token token;
    Location::CalcState locationCalcState;
    wint_t peekChar;
    shared_ptr<wistream> inputStream;
    void nextChar()
    {
        token.location += token.location.calcNext(peekChar, locationCalcState);
        peekChar = inputStream->get();
    }
    static bool isWhiteSpace(wint_t ch)
    {
        switch(ch)
        {
        case ' ':
        case '\v':
        case '\f':
        case '\t':
        case L'\u00A0':
        case L'\u1680':
        case L'\u2000':
        case L'\u2001':
        case L'\u2002':
        case L'\u2003':
        case L'\u2004':
        case L'\u2005':
        case L'\u2006':
        case L'\u2007':
        case L'\u2008':
        case L'\u2009':
        case L'\u200A':
        case L'\u202F':
        case L'\u205F':
        case L'\u3000':
        case L'\uFEFF':
            return true;
        default:
            return false;
        }
    }
    static bool isLineTerminator(wint_t ch)
    {
        switch(ch)
        {
        case '\n':
        case '\r':
        case L'\u2028':
        case L'\u2029':
            return true;
        default:
            return false;
        }
    }
    static bool isUnicodeLetter(wint_t ch)
    {
        return isCharacterCategoryLuLlLtLmLoNl(ch);
    }
    static bool isUnicodeCombiningMark(wint_t ch)
    {
        return isCharacterCategoryMnMc(ch);
    }
    static bool isUnicodeDigit(wint_t ch)
    {
        return isCharacterCategoryNd(ch);
    }
    static bool isUnicodeConnectorPunctuation(wint_t ch)
    {
        return isCharacterCategoryPc(ch);
    }
    static bool isHexDigit(wint_t ch)
    {
        if(ch >= '0' && ch <= '9')
            return true;
        if(ch >= 'A' && ch <= 'F')
            return true;
        if(ch >= 'a' && ch <= 'f')
            return true;
        return false;
    }
    static unsigned getDigitValue(wint_t ch)
    {
        if(ch >= '0' && ch <= '9')
            return (unsigned)ch - (unsigned)'0';
        if(ch >= 'A' && ch <= 'Z')
            return (unsigned)ch - (unsigned)'A' + 0xA;
        else
            return (unsigned)ch - (unsigned)'a' + 0xA;
    }
    wchar_t parseUnicodeEscapeSequence(bool addToValue)
    {
        if(peekChar != 'u')
            ParseError::expected(vector<wstring>{L"u"}, token.location.end());
        if(addToValue)
            token.value += peekChar;
        nextChar();
        wchar_t retval = 0;
        for(int i = 0; i < 4; i++)
        {
            if(!isHexDigit(peekChar))
                ParseError::expected(vector<wstring>{L"Hexadecimal digit"}, token.location.end());
            if(addToValue)
                token.value += peekChar;
            retval *= 0x10;
            retval += getDigitValue(peekChar);
            nextChar();
        }
        return retval;
    }
    wchar_t parseHexEscapeSequence(bool addToValue)
    {
        if(peekChar != 'x')
            ParseError::expected(vector<wstring>{L"x"}, token.location.end());
        if(addToValue)
            token.value += peekChar;
        nextChar();
        wchar_t retval = 0;
        for(int i = 0; i < 2; i++)
        {
            if(!isHexDigit(peekChar))
                ParseError::expected(vector<wstring>{L"Hexadecimal digit"}, token.location.end());
            if(addToValue)
                token.value += peekChar;
            retval *= 0x10;
            retval += getDigitValue(peekChar);
            nextChar();
        }
        return retval;
    }
    bool isNonEscapeIdentifierStart(wint_t ch)
    {
        return ch == '$' || ch == '_' || isUnicodeLetter(ch);
    }
    bool isNonEscapeIdentifierPart(wint_t ch)
    {
        return ch == L'\u200C' || ch == L'\u200D' || isNonEscapeIdentifierStart(ch) || isUnicodeDigit(ch) || isUnicodeCombiningMark(ch) || isUnicodeConnectorPunctuation(ch);
    }
    void parseIdentifierStart()
    {
        if(peekChar == '\\')
        {
            nextChar();
            Location errorLoc = token.location.end();
            wchar_t ch = parseUnicodeEscapeSequence(false);
            if(!isNonEscapeIdentifierStart(ch))
                ParseError::expected(vector<wstring>{L"valid identifier start character"}, errorLoc);
            token.value += ch;
        }
        else if(isNonEscapeIdentifierStart(peekChar))
        {
            token.value += peekChar;
            nextChar();
        }
        else
            ParseError::expected(vector<wstring>{L"valid identifier start character"}, token.location.end());
    }
    void parseIdentifierPart()
    {
        if(peekChar == '\\')
        {
            nextChar();
            Location errorLoc = token.location.end();
            wchar_t ch = parseUnicodeEscapeSequence(false);
            if(!isNonEscapeIdentifierPart(ch))
                ParseError::expected(vector<wstring>{L"valid identifier part character"}, errorLoc);
            token.value += ch;
        }
        else if(isNonEscapeIdentifierPart(peekChar))
        {
            token.value += peekChar;
            nextChar();
        }
        else
            ParseError::expected(vector<wstring>{L"valid identifier part character"}, token.location.end());
    }
    void parseWhiteSpace()
    {
        while(isWhiteSpace(peekChar))
            nextChar();
    }
    static bool isDecimalDigit(wint_t ch)
    {
        return (ch >= '0' && ch <= '9');
    }
    static bool isNonZeroDigit(wint_t ch)
    {
        return (ch > '0' && ch <= '9');
    }
    void parseLineTerminator()
    {
        if(peekChar == '\r')
        {
            nextChar();
            if(peekChar == '\n')
                nextChar();
        }
        else if(isLineTerminator(peekChar))
            nextChar();
        else
            ParseError::expected(vector<Token::Type>{Token::LineTerminator}, token.location.end());
    }
    void parseNumber()
    {
        token.type = Token::NumberLiteral;
        if(peekChar == '0')
        {
            token.value += peekChar;
            nextChar();
            if(peekChar == 'x' || peekChar == 'X') // hex literal
            {
                token.value += L'x';
                nextChar();
                if(!isHexDigit(peekChar))
                    ParseError::expected(vector<wstring>{L"hexadecimal digit"}, token.location.end());
                while(isHexDigit(peekChar))
                {
                    token.value += peekChar;
                    nextChar();
                }
            }
            return;
        }
        assert(isNonZeroDigit(peekChar) || peekChar == '.');
        bool gotDigits = false;
        if(isNonZeroDigit(peekChar))
        {
            gotDigits = true;
            while(isDecimalDigit(peekChar))
            {
                token.value += peekChar;
                nextChar();
            }
        }
        if(peekChar == '.')
        {
            token.value += peekChar;
            nextChar();
            if(!isDecimalDigit(peekChar) && peekChar != 'e' && peekChar != 'E' && !gotDigits)
            {
                token.type = Token::Period;
                return;
            }
            if(!gotDigits && !isDecimalDigit(peekChar))
                ParseError::expected(vector<wstring>{L"decimal digit"}, token.location.end());
            while(isDecimalDigit(peekChar))
            {
                gotDigits = true;
                token.value += peekChar;
                nextChar();
            }
        }
        if(peekChar == 'e' || peekChar == 'E')
        {
            token.value += peekChar;
            nextChar();
            if(!isDecimalDigit(peekChar) && peekChar != '+' && peekChar != '-')
                ParseError::expected(vector<wstring>{L"decimal digit", L"+", L"-"}, token.location.end());
            if(peekChar == '+' || peekChar == '-')
            {
                token.value += peekChar;
                nextChar();
                if(!isDecimalDigit(peekChar))
                    ParseError::expected(vector<wstring>{L"decimal digit"}, token.location.end());
            }
            while(isDecimalDigit(peekChar))
            {
                token.value += peekChar;
                nextChar();
            }
        }
    }
    static bool isEscapeCharacter(wint_t ch)
    {
        if(isDecimalDigit(ch))
            return true;
        switch(ch)
        {
        case '\'':
        case '\"':
        case '\\':
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
        case 'u':
        case 'x':
            return true;
        default:
            return false;
        }
    }
    static bool isNonEscapeCharacter(wint_t ch)
    {
        if(ch == WEOF || isEscapeCharacter(ch))
            return false;
        return true;
    }
    void parseString()
    {
        token.type = Token::StringLiteral;
        if(peekChar != '\"' && peekChar != '\'')
            ParseError::expected(vector<wstring>{L"\"", L"\'"}, token.location.end());
        wchar_t openingQuote = peekChar;
        nextChar();
        for(;;)
        {
            if(peekChar == WEOF || isLineTerminator(peekChar))
                ParseError::expected({wstring() + openingQuote}, token.location.end());
            if(peekChar == '\\')
            {
                nextChar();
                if(isLineTerminator(peekChar))
                {
                    parseLineTerminator();
                    continue;
                }
                if(peekChar == WEOF)
                    ParseError::expected(vector<wstring>{L"valid escape sequence"}, token.location.end());
                switch(peekChar)
                {
                case '\'':
                case '\"':
                case '\\':
                    token.value += peekChar;
                    nextChar();
                    break;
                case '0':
                {
                    Location errorLoc = token.location.end();
                    token.value += L'\0';
                    nextChar();
                    if(isDecimalDigit(peekChar))
                        ParseError::generic(L"can not use octal escape sequences except for \\0", errorLoc);
                    break;
                }
                case 'b':
                    token.value += '\b';
                    nextChar();
                    break;
                case 'f':
                    token.value += '\f';
                    nextChar();
                    break;
                case 'n':
                    token.value += '\n';
                    nextChar();
                    break;
                case 'r':
                    token.value += '\r';
                    nextChar();
                    break;
                case 't':
                    token.value += '\t';
                    nextChar();
                    break;
                case 'v':
                    token.value += '\v';
                    nextChar();
                    break;
                case 'u':
                    token.value += parseUnicodeEscapeSequence(false);
                    break;
                case 'x':
                    token.value += parseHexEscapeSequence(false);
                    break;
                default:
                    assert(isNonEscapeCharacter(peekChar));
                    token.value += peekChar;
                    nextChar();
                    break;
                }
            }
            else if(peekChar == (wint_t)openingQuote)
            {
                nextChar();
                return;
            }
            else
            {
                token.value += peekChar;
                nextChar();
            }
        }
    }
    void parseIdentifier()
    {
        token.type = Token::Identifier;
        parseIdentifierStart();
        while(peekChar == '\\' || isNonEscapeIdentifierPart(peekChar))
        {
            parseIdentifierPart();
        }
        token.identifierToKeyword();
    }
    void nextToken()
    {
        for(;;)
        {
            if(peekChar == WEOF)
            {
                token.type = Token::Eof;
                token.value = L"";
                token.location = token.location.end();
                return;
            }
            parseWhiteSpace();
            token.location = token.location.end();
            token.value = L"";
            if(peekChar == WEOF)
            {
                token.type = Token::Eof;
                return;
            }
            if(isLineTerminator(peekChar))
            {
                parseLineTerminator();
                token.type = Token::LineTerminator;
                return;
            }
            if(isDecimalDigit(peekChar))
            {
                parseNumber();
                return;
            }
            if(isNonEscapeIdentifierStart(peekChar) || peekChar == '\\')
            {
                parseIdentifier();
                return;
            }

            switch(peekChar)
            {
            case '\"':
            case '\'':
            {
                parseString();
                return;
            }
            case '/':
            {
                nextChar();
                token.type = Token::FSlash;
                if(peekChar == '*') // multi-line comment
                {
                    nextChar();
                    token.type = Token::LineTerminator;
                    bool gotLineTerminator = false;
                    while(peekChar != WEOF)
                    {
                        if(peekChar == '*')
                        {
                            while(peekChar == '*')
                                nextChar();
                            if(peekChar == '/')
                                break;
                        }
                        else if(isLineTerminator(peekChar))
                        {
                            gotLineTerminator = true;
                            nextChar();
                        }
                        else
                            nextChar();
                    }
                    if(peekChar == WEOF)
                        ParseError::expected(vector<wstring>{L"*/"}, token.location.end());
                    else
                    {
                        nextChar();
                        if(gotLineTerminator)
                            return;
                        else
                            continue;
                    }
                }
                else if(peekChar == '/') // single-line comment
                {
                    while(peekChar != WEOF && !isLineTerminator(peekChar))
                        nextChar();
                    continue;
                }
                else if(peekChar == '=') // /=
                {
                    token.type = Token::FSlashEqual;
                    nextChar();
                    return;
                }
                return;
            }
            case '{':
            {
                token.type = Token::LBrace;
                nextChar();
                return;
            }
            case '}':
            {
                token.type = Token::RBrace;
                nextChar();
                return;
            }
            case '(':
            {
                token.type = Token::LParen;
                nextChar();
                return;
            }
            case ')':
            {
                token.type = Token::RParen;
                nextChar();
                return;
            }
            case '[':
            {
                token.type = Token::LBracket;
                nextChar();
                return;
            }
            case ']':
            {
                token.type = Token::RBracket;
                nextChar();
                return;
            }
            case '<':
            {
                token.type = Token::Less;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::LessEqual;
                    nextChar();
                }
                else if(peekChar == '<')
                {
                    token.type = Token::LShift;
                    nextChar();
                    if(peekChar == '=')
                    {
                        token.type = Token::LShiftEqual;
                        nextChar();
                    }
                }
                return;
            }
            case '>':
            {
                token.type = Token::Greater;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::GreaterEqual;
                    nextChar();
                }
                else if(peekChar == '>')
                {
                    token.type = Token::RShiftSigned;
                    nextChar();
                    if(peekChar == '=')
                    {
                        token.type = Token::RShiftSignedEqual;
                        nextChar();
                    }
                    else if(peekChar == '>')
                    {
                        token.type = Token::RShiftUnsigned;
                        nextChar();
                        if(peekChar == '=')
                        {
                            token.type = Token::RShiftUnsignedEqual;
                            nextChar();
                        }
                    }
                }
                return;
            }
            case '.':
            {
                parseNumber();
                return;
            }
            case ';':
            {
                token.type = Token::Semicolon;
                nextChar();
                return;
            }
            case ',':
            {
                token.type = Token::Comma;
                nextChar();
                return;
            }
            case '=':
            {
                token.type = Token::Equal;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::DoubleEqual;
                    nextChar();
                    if(peekChar == '=')
                    {
                        token.type = Token::TripleEqual;
                        nextChar();
                    }
                }
                return;
            }
            case '!':
            {
                token.type = Token::EMark;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::NotEqual;
                    nextChar();
                    if(peekChar == '=')
                    {
                        token.type = Token::NotDoubleEqual;
                        nextChar();
                    }
                }
                return;
            }
            case '+':
            {
                token.type = Token::Plus;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::PlusEqual;
                    nextChar();
                }
                else if(peekChar == '+')
                {
                    token.type = Token::Increment;
                    nextChar();
                }
                return;
            }
            case '-':
            {
                token.type = Token::Minus;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::MinusEqual;
                    nextChar();
                }
                else if(peekChar == '-')
                {
                    token.type = Token::Decrement;
                    nextChar();
                }
                return;
            }
            case '*':
            {
                token.type = Token::Star;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::StarEqual;
                    nextChar();
                }
                return;
            }
            case '%':
            {
                token.type = Token::Percent;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::PercentEqual;
                    nextChar();
                }
                return;
            }
            case '&':
            {
                token.type = Token::Ampersand;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::AmpersandEqual;
                    nextChar();
                }
                else if(peekChar == '&')
                {
                    token.type = Token::LogicAnd;
                    nextChar();
                }
                return;
            }
            case '|':
            {
                token.type = Token::Pipe;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::PipeEqual;
                    nextChar();
                }
                else if(peekChar == '|')
                {
                    token.type = Token::LogicOr;
                    nextChar();
                }
                return;
            }
            case '^':
            {
                token.type = Token::Caret;
                nextChar();
                if(peekChar == '=')
                {
                    token.type = Token::CaretEqual;
                    nextChar();
                }
                return;
            }
            case '~':
            {
                token.type = Token::Tilde;
                nextChar();
                return;
            }
            case '?':
            {
                token.type = Token::QMark;
                nextChar();
                return;
            }
            case ':':
            {
                token.type = Token::Colon;
                nextChar();
                return;
            }
            default:
                ParseError::unexpected(wstring() + (wchar_t)peekChar, token.location.end());
                return;
            }
            return;
        }
    }
    void parseRegExEscape()
    {
        assert(peekChar == '\\');
        token.value += peekChar;
        nextChar();
        if(!isLineTerminator(peekChar) && peekChar != WEOF)
        {
            token.value += peekChar;
            nextChar();
        }
        else if(peekChar == WEOF)
            ParseError::unexpected(Token::Eof, token.location.end());
        else
            ParseError::unexpected(Token::LineTerminator, token.location.end());
    }
    void parseRegExClass()
    {
        assert(peekChar == '[');
        token.value += peekChar;
        nextChar();
        while(peekChar != ']')
        {
            if(peekChar == WEOF)
            {
                ParseError::expected(vector<wstring>{L"]"}, token.location.end());
                return;
            }
            if(peekChar == '\\')
            {
                parseRegExEscape();
            }
            else if(!isLineTerminator(peekChar))
            {
                token.value += peekChar;
                nextChar();
            }
            else
                ParseError::expected(vector<wstring>{L"]"}, token.location.end());
        }
        assert(peekChar == ']');
        token.value += peekChar;
        nextChar();
    }
public:
    Tokenizer(shared_ptr<wistream> inputStream)
        : token(Token::None, Location(1, 1)), inputStream(inputStream)
    {
        assert(inputStream != nullptr);
        if(!*inputStream)
            ParseError::generic(L"can not read from file", token.location.end());
        peekChar = inputStream->get();
        nextToken();
    }
    const Token & operator *() const
    {
        return token;
    }
    const Token * operator ->() const
    {
        return &token;
    }
    void changeDivToRegexLiteral()
    {
        assert(token.type == Token::FSlash || token.type == Token::FSlashEqual);
        token.value = L"/";
        if(token.type == Token::FSlashEqual)
            token.value = L"/=";
        token.type = Token::RegexLiteral;
        if(token.value.size() == 1)
        {
            if(peekChar == '[')
            {
                parseRegExClass();
            }
            else if(peekChar == '\\')
            {
                parseRegExEscape();
            }
            else if(!isLineTerminator(peekChar) && peekChar != WEOF)
            {
                token.value += peekChar;
                nextChar();
            }
            else if(peekChar == WEOF)
                ParseError::unexpected(Token::Eof, token.location.end());
            else
                ParseError::unexpected(Token::LineTerminator, token.location.end());
        }
        while(peekChar != '/')
        {
            if(peekChar == '[')
            {
                parseRegExClass();
            }
            else if(peekChar == '\\')
            {
                parseRegExEscape();
            }
            else if(!isLineTerminator(peekChar) && peekChar != WEOF)
            {
                token.value += peekChar;
                nextChar();
            }
            else if(peekChar == WEOF)
                ParseError::unexpected(Token::Eof, token.location.end());
            else
                ParseError::unexpected(Token::LineTerminator, token.location.end());
        }
        assert(peekChar == '/');
        token.value += peekChar;
        nextChar();
        while(peekChar == '\\' || isNonEscapeIdentifierPart(peekChar))
        {
            parseIdentifierPart();
        }
    }
    const Tokenizer & operator ++()
    {
        nextToken();
        return *this;
    }
    struct PostIncrementReturnValue
    {
        Token token;
        PostIncrementReturnValue(Token token)
            : token(token)
        {
        }
        const Token & operator *() const
        {
            return token;
        }
        const Token * operator ->() const
        {
            return &token;
        }
    };
    PostIncrementReturnValue operator ++(int)
    {
        Token retval = token;
        nextToken();
        return PostIncrementReturnValue(retval);
    }
};

#endif // TOKENTYPE_H_INCLUDED
