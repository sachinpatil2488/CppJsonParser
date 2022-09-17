
#include "ParserTest.hpp"

#include "JsonParser.hpp"


int ParserTest::run()
{
    testE2e();

    return 0;
}

void ParserTest::testE2e()
{
    jp::JsonParser jp;
    jp.parse("{ \"glossary\": { \"title\": \"example glossary\", \"GlossDiv\": { \"title\": \"S\", \"GlossList\": { \"GlossEntry\": { \"ID\": \"SGML\", \"SortAs\": \"SGML\" } } } } }");
}