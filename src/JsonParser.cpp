//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JsonParser.hpp"
#include "JObject.hpp"
#include "JList.hpp"
#include "Utils.hpp"

#include <stack>

namespace jp
{

/*------------------------------------------------------------------------
 * Jsone Parser
 * Client interface
 *-----------------------------------------------------------------------*/
JsonParser::JsonParser() 
{
}

JValuePtr JsonParser::parse(const std::string& str)
{
    JValuePtr jValue;
    try {

        //clear global stack before parsing
        Utils::clearGlobalStack();

        jValue = read(str);

        //validate json syntax from global stack
        auto jStack = Utils::globalStack();
        if (!jStack.empty()) {
           Utils::throwJsonParsingException("Invalid json file");
        }

    } catch(std::exception & ex) {
        Utils::clearGlobalStack();
        Utils::throwJsonParsingException(ex.what());
    } catch(...) {
        Utils::clearGlobalStack();
        Utils::throwJsonParsingException("Unknown Exception");
    }

    return jValue;
}

JValuePtr JsonParser::read(const std::string& str)
{
    std::string::const_iterator start = str.begin();
    std::string::const_iterator end   = str.end();

    JValuePtr value;

    JValueType type = findJValueType(start, end);

    switch(type) {
    case J_OBJECT: {
        value = std::shared_ptr<JObject>(new JObject(start, end));
        break;
    }
    case J_LIST: {
        value = std::shared_ptr<JList>(new JList(start, end));
        break;
    }
    default: {
        Utils::throwJsonParsingException("Invalid json file. Unknow root value");
    }
    }

    return value;
}

JValueType JsonParser::findJValueType(std::string::const_iterator& start, std::string::const_iterator& end) 
{
    while (start != end && *start == ' ') {
        ++start;
     }

     if (start == end) {
        Utils::throwJsonParsingException("Empty json");
     }

     return Utils::findValueType(*start);
}

JsonParser::~JsonParser()
{
}

} //jp
