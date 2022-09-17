//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "Utils.hpp"

#include <unordered_set>

namespace jp
{

static std::stack<char> jStack;
std::stack<char>& Utils::globalStack() 
{
    return jStack;
}

void Utils::clearGlobalStack()
{
    while (!jStack.empty()) {
        jStack.pop();
    }
}

bool Utils::jValueEnd(char c)
{
    static std::unordered_set<char> valueEndMarker = {',', ']', '}'};
    return valueEndMarker.find(c) != valueEndMarker.end();
}

void Utils::throwJsonParsingException(std::string message)
{
    throw std::exception(("Json parsing failed : " + message).c_str());
}

JValueType Utils::findValueType(char c)
{
    switch (c) {
    case '{': return J_OBJECT;
    case '[': return J_LIST;
    case '"': return J_STRING;
    case 'T':
    case 't':
    case 'F':
    case 'f': return J_BOOL;
    case 'n':
    case 'N': return J_NULL;
    default:
        if (isdigit(c))
            return J_NUMERIC;
        return J_UNKNOWN;
    }
}

std::string Utils::valueTypeString(const JValueType& type)
{
#define TO_STRING(X) case X: return #X;
    switch (type) {
        TO_STRING(J_OBJECT)
            TO_STRING(J_STRING)
            TO_STRING(J_NUMERIC)
            TO_STRING(J_INT)
            TO_STRING(J_FLOAT)
            TO_STRING(J_BOOL)
            TO_STRING(J_LIST)
            TO_STRING(J_NULL)
            TO_STRING(J_UNKNOWN)
    default:
        return "Unknown";
    }
}

bool Utils::iequal(const std::string& src, const std::string dest)
{    
    auto s = src.begin(), d = dest.begin();
    while ( s != src.end() && d != dest.end()) {
        
        if (tolower(*s) != tolower(*d)) {
            return false;
        }
        
        s++;
        d++;
    }

    return s == src.end() && d == dest.end();
}
} //jp
