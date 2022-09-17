//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JNumeric.hpp"
#include "Utils.hpp"

namespace jp
{

/*---------------------------------------------------------------
* Numeric json value 
*---------------------------------------------------------------*/
JNumeric::JNumeric(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name)
    : JValue(JValueType::J_NUMERIC, start, end, name) {
        read();
}

void JNumeric::readValue() 
{
    while (start_ != end_ && !Utils::jValueEnd(*start_)) {
        value_ += *start_++;
    }

    checkState();
}

void JNumeric::validate() 
{
    try {
        atoi(value_.c_str());
    } catch (...) {
        Utils::throwJsonParsingException("Invalid numeric value : " + value_);
    }
}

void JNumeric::setJValueType() 
{
    type_ = J_INT;

    if (value_.find('.') != std::string::npos) {
        type_ = J_FLOAT;
    }
}

} //jp
