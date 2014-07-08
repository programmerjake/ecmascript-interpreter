#include <iostream>
#include <fstream>
#include "garbage_collector.h"
#include "tokentype.h"
#include "ecmascript.h"

using namespace std;

GarbageCollector gc;

int main()
{
#if 1
    wcout << gc.allocate<ECMAValueNumber>(L"+1.11829343279384721398e123")->toString() << endl;
#else
    try
    {
        Tokenizer tokenizer(make_shared<wifstream>("test.js"));
        while(tokenizer->type != Token::Eof)
        {
            cout << *tokenizer++ << endl;
        }
    }
    catch(ParseError::ParseError & e)
    {
        cout << "Error : " << e.what() << endl;
    }
#endif
    return 0;
}
