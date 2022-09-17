//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#pragma once

#include "JValue.hpp"

namespace jp
{

/*---------------------------------------------------------------
* Json Parser
*---------------------------------------------------------------*/
class JsonParser
{
public:
    JsonParser();
    ~JsonParser();
    
    JValuePtr parse(const std::string& str);

private:

    JValuePtr read(const std::string& str);
    JValueType findJValueType(std::string::const_iterator& start, std::string::const_iterator& end);
};

} //jp
