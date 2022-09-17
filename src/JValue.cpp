//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JValue.hpp"
#include "Utils.hpp"

#include <algorithm>

namespace jp
{

JValue::JValue(JValueType type,
    std::string::const_iterator& start, 
    std::string::const_iterator& end,
    const std::string& name)
    : type_(type), start_(start), end_(end), name_(name)
{
}

void JValue::read() 
{
    readValue();

    trimValue();

    validate();

    setJValueType();
}

std::string JValue::readName() 
{
    std::string name;
    ++start_;
    
    while( start_ != end_ && *start_ != '"') {
        name += *start_++;
    }

    checkState();

    ++start_;

    return name;
}

void JValue::checkState()
{
    if (start_ == end_) {
        Utils::throwJsonParsingException("Invalid end");
    }
}

void JValue::trimValue()
{
    //trim white spaces from both end
    value_.erase(value_.find_last_not_of(' ') + 1);         //suffixing spaces
    value_.erase(0, value_.find_first_not_of(' '));       //prefixing spaces
}

} //jp
