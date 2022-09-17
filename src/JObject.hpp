//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#pragma once

#include "JNull.hpp"
#include "JBoolean.hpp"
#include "JNumeric.hpp"
#include "JString.hpp"
#include "JList.hpp"

namespace jp
{
/*
            JValue
         _____|_____
         |          |
       JObject     ...
*/

/*------------------------------------------------------------------
* Class to represent object
*------------------------------------------------------------------*/
class JObject : public JValue
{
public:
    JObject(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name = std::string(""));

    /* Different values that can present in object */
    std::list<JNullPtr> nullValues_;
    std::list<JStringPtr> stringValues_;
    std::list<JNumericPtr> numValues_;
    std::list<JBooleanPtr> boolValues_;
    std::list<std::shared_ptr<JObject> > objectValues_;
    std::list<JListPtr> listValues_;

protected:
    /* Virtual methods */
    virtual void readValue();
    virtual void validate() {}
    virtual void setJValueType() { type_ = J_OBJECT; }

private:
    /* Identify value type and based on its type it invokes the 
      concret type reading */
    void readJObjectAttributes();

    JValueType findJValueType();
};

typedef std::shared_ptr<JObject> JObjectPtr;

} //jps
