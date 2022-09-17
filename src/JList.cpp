//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#include "JList.hpp"
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
* List json value 
*---------------------------------------------------------------*/
JList::JList(std::string::const_iterator& start, std::string::const_iterator& end, const std::string& name)
    : JValue(JValueType::J_LIST, start, end, name), contentType_(J_UNKNOWN) {
        read();
}

void JList::readValue() 
{
    std::stack<char>& jStack = Utils::globalStack();;
    jStack.push('[');
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
                Utils::throwJsonParsingException("Invalid list");
            }
            ++start_;
            valueFound = false;
            break;
        }
        case ']': {
            if (jStack.top() != '[' ) {
                Utils::throwJsonParsingException("Invalid list");
            }
            jStack.pop();
            ++start_;
            return; // list reading end
        }
        default:
            readListValues();
        }
    }
}

void JList::setJValueType()
{
    updateContentType();
}

void JList::readObjectList()
{
    bool valueFound = false;

    while (start_ != end_) {

        switch(*start_) {
        case ' ': {
            ++start_;
            break;
        }
        case ',': {
            if (!valueFound) Utils::throwJsonParsingException("Invalid object list");
            ++start_;
            valueFound = false;
            break;
        }
        case '{': {
            JValuePtr object = createJValue<JObject>(start_, end_);
            values_.push_back(object);
            valueFound = true;
            break;
        }
        case ']': {
            return; // list reading end
        }
        default:
            Utils::throwJsonParsingException("Invalid object list");
        }
    }
}

void JList::readStringList()
{
    bool valueFound = false;

    while (start_ != end_) {

        switch(*start_) {
        case ' ': {
            ++start_;
            break;
        }
        case ',': {
            if (!valueFound) {
                Utils::throwJsonParsingException("Invalid string list");
            }
            ++start_;
            valueFound = false;
            break;
        }
        case '"': {
            JValuePtr str = createJValue<JString>(start_, end_);
            values_.push_back(str);
            valueFound = true;
            break;
        }
        case ']': {
            return; // list reading end
        }
        default: {
            Utils::throwJsonParsingException("Invalid string list");
        }
        }
    }
}

void JList::readNumericList()
{
    bool valueFound = false;

    while (start_ != end_) {

        switch(*start_) {
        case ' ': {
            ++start_;
            break;
        }
        case ',': {
            if (!valueFound) {
                Utils::throwJsonParsingException("Invalid numeric list");
            }
            ++start_;
            valueFound = false;
            break;
        }
        case ']': {
            return; // list reading end
        }
        default: {
            JValueType type = findJValueType();

            if (type == J_NUMERIC) {
                JValuePtr num = createJValue<JNumeric>(start_, end_);
                values_.push_back(num);
                valueFound = true;
            } else {
                Utils::throwJsonParsingException("Invalid numeric list");
            }
        }
        }
    }
}

void JList::readBooleanList()
{
    bool valueFound = false;

    while (start_ != end_) {

        switch(*start_) {
        case ' ': {
            ++start_;
            break;
        }
        case ',': {
            if (!valueFound) {
                Utils::throwJsonParsingException("Invalid boolean list");
            }
            ++start_;
            valueFound = false;
            break;
        }
        case ']': {
            return; // list reading end
        }
        default: {
            JValueType type = findJValueType();

            if (type == J_BOOL) {
                JValuePtr bul = createJValue<JBoolean>(start_, end_);
                values_.push_back(bul);
                valueFound = true;
            } else {
                Utils::throwJsonParsingException("Invalid boolean list");
            }
        }
        }
    }
}

void JList::readNestedList()
{
    bool valueFound = false;

    while (start_ != end_) {

        switch(*start_) {
        case ' ': {
            ++start_;
            break;
        }
        case ',': {
            if (!valueFound) {
                Utils::throwJsonParsingException("Invalid nested list");
            }
            ++start_;
            valueFound = false;
            break;
        }
        case '[': {
            JValuePtr lst = createJValue<JList>(start_, end_);
            values_.push_back(lst);
            valueFound = true;
            break;
        }
        case ']': {
            return; // list reading end
        }
        default: {
            Utils::throwJsonParsingException("Invalid nested list");
        }
        }
    }
}

void JList::readListValues()
{
    JValueType type = findJValueType();

    //List contains values of same type only
    if (contentType_ == J_UNKNOWN) {
        contentType_ = type;
    } else if (contentType_ != type) {
        Utils::throwJsonParsingException("Inconsistent list value types");
    }

    switch(type) {
    case J_OBJECT: {
        readObjectList();
        break;
    }
    case J_STRING: {
        readStringList();
        break;
    } 
    case J_NUMERIC: {
        readNumericList();
        break;
    }
    case J_BOOL: {
        readBooleanList();
        break;
    }
    case J_LIST: {
        readNestedList();
        break;
    }
    default: {
        Utils::throwJsonParsingException("Unknown list type");
    }
    }
}

JValueType JList::findJValueType()
{
    while (start_ != end_ && *start_ == ' ') {
        ++start_;
    }

    checkState();

    return Utils::findValueType(*start_);
}

void JList::updateContentType()
{
    if (contentType_ != J_NUMERIC)
        return;

    contentType_ = J_INT;

    for (std::list<JValuePtr>::iterator itr = values_.begin(); itr != values_.end(); ++itr) {
        if ((*itr)->type() == J_FLOAT) {
            contentType_ = J_FLOAT;
            break;
        }
    }
}

} //jp
