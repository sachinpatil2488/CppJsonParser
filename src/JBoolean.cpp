//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JBoolean.hpp"
#include "Utils.hpp"

namespace jp
{

/*---------------------------------------------------------------
* Boolean type json value 
*---------------------------------------------------------------*/
JBoolean::JBoolean(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name)
    : JValue(JValueType::J_BOOL, start, end, name) {
        read();
}

void JBoolean::readValue() 
{
    while (start_ != end_ && !Utils::jValueEnd(*start_)) {
        value_ += *start_++;
    }

    checkState();
}

void JBoolean::validate()
{
    bValue_ = value_ == "1" || Utils::iequal(value_, "true");

    if (!bValue_) {
        bool validate = value_ == "0" || Utils::iequal(value_, "false");

        if (!validate) {
            Utils::throwJsonParsingException("Invalid boolean value : " + value_);
        }
    }
}

} //jp
