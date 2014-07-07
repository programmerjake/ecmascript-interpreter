#include <iostream>
#include <fstream>
#include "garbage_collector.h"
#include "tokentype.h"
#include "ecmascript.h"

using namespace std;

GarbageCollector gc;

int main()
{
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
    return 0;
}
