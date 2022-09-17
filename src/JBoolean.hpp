//==========================================================================
//
// author : sachinpatil
// date   : 2022
// description : 
//==========================================================================

#pragma once

#include "JValue.hpp"

namespace jp
{
/*
            JValue
          _____|______
         |           |
       JBoolean     ...

*/

/*--------------------------------------------------------------------
* Class to represent boolean value
*
* Note : Boolean values with value format true/false (case insensitive)
* would be identified. 1/0 wont be marked as boolean.
*--------------------------------------------------------------------*/
class JBoolean : public JValue
{
public:
    JBoolean(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name = std::string(""));
    inline bool value() const { return bValue_; }

protected:
    /* Virtual methods */
    virtual void readValue();
    virtual void validate();
    virtual void setJValueType() { type_ = J_BOOL; }

    // variables
    bool bValue_;
};

typedef std::shared_ptr<JBoolean> JBooleanPtr;

} //jps
