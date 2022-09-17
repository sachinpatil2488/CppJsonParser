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
/*
             JValue
          ______|____
         |          |
       JNumeric    ...
*/

/*--------------------------------------------------------------
* Class to represent numeric value
* 
* Numeric values can be intege or float. Its value type can be
* deduced by presence of floating point. Value reading mechanism is
* common only difference is in type.
*---------------------------------------------------------------*/
class JNumeric : public JValue
{
public:
    JNumeric(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name = std::string(""));

    inline int intValue() const { return atoi(value_.c_str()); }
    inline double floatValue() const { return atof(value_.c_str()); }

protected:
    /* Virtual methods */
    virtual void readValue();
    virtual void validate();
    virtual void setJValueType();
};
typedef std::shared_ptr<JNumeric> JNumericPtr;

} //jp
