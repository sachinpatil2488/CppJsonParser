//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#pragma once

#include "JValue.hpp"
#include <list>

namespace jp
{
/*
              JValue
          _____|____
         |          |
       JList      ...

*/
/*---------------------------------------------------------------------
*  Class to represent list of values
*---------------------------------------------------------------------*/
class JList : public JValue
{
public:
    JList(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name = std::string(""));

    inline JValueType contentType() { return contentType_; }

    std::list<JValuePtr> values_;

protected:
    /* Virtual methods */
    virtual void readValue();
    virtual void validate() {}
    virtual void setJValueType();

private:
    /* 
      List can be of objects, strings, numbers etc.
      This method deduce type and perform specific types of reading
    */
    void readListValues();

    /* Deduce value type for list */
    JValueType findJValueType();

    /* Reading list of objects */
    void readObjectList();

    /* Reading list of strings */
    void readStringList();

    /* Reading list of numbers */
    void readNumericList();

    /* Reading list of beelean values */
    void readBooleanList();

    /* Reading list of lists*/
    void readNestedList();

    /* Update value type in case of numeric list.
    It checks whether list is of int or float values*/
    void updateContentType();

    //memeber variable
    JValueType contentType_;
};

typedef std::shared_ptr<JList> JListPtr;

} //jp
