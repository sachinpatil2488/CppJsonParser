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
          JsonParser                               JValueType

                                JValue
         __________________________|_________________________________
         |          |         |            |            |           |
       JObject    JList    JString      JNumeric     JBoolean     JNull
                                     (JInt, JFloat)
*/

class JsonParser;

/*------------------------------------------------------------
* class to represent string Value
*-------------------------------------------------------------*/
class JString : public JValue
{
public:
    JString(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name = std::string(""));

    inline std::string value() const { return value_; }

protected:
    /* Virtual methods */
    virtual void readValue();
    virtual void validate() {}
    virtual inline void setJValueType() { type_ = J_STRING; }
};

typedef std::shared_ptr<JString> JStringPtr;

} //jps
