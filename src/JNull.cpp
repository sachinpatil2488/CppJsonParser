//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JNull.hpp"
#include "Utils.hpp"

namespace jp
{

/*---------------------------------------------------------------
* Null type json value 
*---------------------------------------------------------------*/
JNull::JNull(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name)
    : JValue(JValueType::J_NULL, start, end, name) {
        read();
}

void JNull::readValue() 
{
    while (start_ != end_ && !Utils::jValueEnd(*start_)) {
        value_ += *start_++;
    }

    checkState();
}

} //jp
