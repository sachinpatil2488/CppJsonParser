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
         _______|____
         |           |
        JNull       ...

*/

/*-----------------------------------------------------------------
* Class to represent null value
* If content is null then value type is null
*------------------------------------------------------------------*/
class JNull : public JValue
{
public:
    JNull(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name = std::string(""));
    inline std::string value() const { return value_; }

protected:
    /* Virtual methods */
    virtual void readValue();
    virtual void validate() {}
    virtual void setJValueType() { type_ = J_NULL; }
};

typedef std::shared_ptr<JNull> JNullPtr;

} //jp
