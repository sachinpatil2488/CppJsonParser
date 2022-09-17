//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JString.hpp"
#include "Utils.hpp"

namespace jp
{

/*---------------------------------------------------------------
* String json value 
*---------------------------------------------------------------*/
JString::JString(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name)
    : JValue(JValueType::J_STRING, start, end, name) {
        read();
}

void JString::readValue() {

    ++start_; //starting "

    while (start_ != end_ && *start_ != '"') {
        value_ += *start_++;
    }

    checkState();

    //Information shared by REST API can contains escape charactes in string value types
    //Json value with escape character i.e "\\" becomes "\\" in output value but expected is single '\'
    //Following line will take care of that. it will convert "\\" to '\'
    //std::algorithm::replace_all(value_, "\\\\", "\\");

    ++start_; //ending "
}

} //jp
