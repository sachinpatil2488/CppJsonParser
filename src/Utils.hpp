//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#pragma once

#include "JValueType.hpp"
#include <string>
#include <stack>

namespace jp
{

/*---------------------------------------------------------------
* Json Parser
*---------------------------------------------------------------*/
class Utils
{
public:
    /* Check if character is value end marker*/
    static bool jValueEnd(char c);

    /* Return value type from given character */
    static JValueType findValueType(char c);
    static std::string valueTypeString(const JValueType& type);
    static void throwJsonParsingException(std::string message);

    static bool iequal(const std::string& src, const std::string dest);

    static std::stack<char>& globalStack();
    static void clearGlobalStack();
};

} //jp
