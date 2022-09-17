//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#pragma once

#include "JValueType.hpp"
#include "JExport.hpp"

#include <memory>
#include <string>
#include <stack>

namespace jp
{
/*
                                JValue
         __________________________|_________________________________
         |          |         |            |            |           |
       JObject    JList    JString      JNumeric     JBoolean     JNull
                                     (JInt, JFloat)

*/

/*--------------------------------------------------------------------
* Abstract json value type
*
* Its abstract json value with common functions required for reading
* values. Json stores information in key-value pair.
* Note : Throughtout here key is nothing but name.
* Object/List values can come with/without name fiels but rest of the
* data comes with name field.
* Getting actual value is available on concret type
*---------------------------------------------------------------------*/
class JValue
{
public:
    JValue(JValueType type, std::string::const_iterator& start, 
        std::string::const_iterator& end, const std::string& name);

    /* Json value key name*/
    inline std::string name() const { return name_; }
    /* Value type associated with key */
    inline JValueType type() const { return type_; }

    inline std::string rawValue() const { return value_; }

protected:
    /* Value type specific reading */
    virtual void readValue() = 0;

    /* Validate value information */
    virtual void validate() = 0;
     
    /* Deduce value type if needed */
    virtual void setJValueType() = 0;

    /* Template method for reading concrete value */
    void read();

    /* Common defination for reading name field*/
    std::string readName();

    /* Verify associated json stream reader state*/
    void checkState();

    /*Remove leading and preceding unwanted spaces*/
    void trimValue();

    //memeber variables
    JValueType type_;
    std::string::const_iterator& start_;
    std::string::const_iterator& end_;
    std::string name_;
    std::string value_;
};

typedef std::shared_ptr<JValue> JValuePtr;

} //jps
