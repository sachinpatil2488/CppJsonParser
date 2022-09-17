//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JObject.hpp"
#include "Utils.hpp"

namespace jp
{

template <typename T>
static std::shared_ptr<T> createJValue(std::string::const_iterator& start,
    std::string::const_iterator& end,
    const std::string& name = std::string(""))
{
    return std::shared_ptr<T>(new T(start, end, name));
}

/*---------------------------------------------------------------
* Object type json value 
*---------------------------------------------------------------*/
JObject::JObject(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name)
    : JValue(JValueType::J_OBJECT, start, end, name) {
        read();
}

void JObject::readValue()
{
    std::stack<char>& jStack = Utils::globalStack();
    jStack.push('{');
    ++start_;

    bool valueFound = false;

    while (start_ != end_) {

        switch(*start_) {
        case ' ': {
            ++start_;
            break;
        }
        case ',': {
            if (!valueFound) {
                Utils::throwJsonParsingException("Json object syntax error");
            }
            ++start_;
            valueFound = false;
            break;
        }
        case '"':  {
            readJObjectAttributes();
            valueFound = true;
            break;
        }
        case '{': { //nested objects
            JObjectPtr object = createJValue<JObject>(start_, end_);
            objectValues_.push_back(object);
            valueFound = true;
            break;
        }
        case '[': { //list
            JListPtr lst = createJValue<JList>(start_, end_);
            listValues_.push_back(lst);
            valueFound = true;
            break;
        }
        case '}': {
            if (jStack.top() != '{' ) {
                Utils::throwJsonParsingException("Json object syntax error");
            }
            jStack.pop();
            ++start_;
            return; // object reading end
        }
        default:
            Utils::throwJsonParsingException("Json object syntax error");
        }
    }
}

JValueType JObject::findJValueType()
{
    while (start_ != end_ && (*start_ == ' ' || *start_ == ':')) {
        ++start_;
    }

    checkState();

    return Utils::findValueType(*start_);
}

void JObject::readJObjectAttributes()
{
    std::string name = readName();
    JValueType type = findJValueType();

    switch(type) {
    case J_OBJECT: {
        JObjectPtr object = createJValue<JObject>(start_, end_, name);
        objectValues_.push_back(object);
        break;
    }
    case J_STRING: {
        JStringPtr str = createJValue<JString>(start_, end_, name);
        stringValues_.push_back(str);
        break;
    } 
    case J_NUMERIC: {
        JNumericPtr num = createJValue<JNumeric>(start_, end_, name);
        numValues_.push_back(num);
        break;
    }
    case J_BOOL: {
        JBooleanPtr bul = createJValue<JBoolean>(start_, end_, name);
        boolValues_.push_back(bul);
        break;
    }
    case J_LIST: {
        JListPtr lst = createJValue<JList>(start_, end_, name);
        listValues_.push_back(lst);
        break;
    }
    case J_NULL: {
        JNullPtr nVal = createJValue<JNull>(start_, end_, name);
        nullValues_.push_back(nVal);
        break;
    }
    default: {
        Utils::throwJsonParsingException("Unknown type object property");
    }
    }
}

} //jp
