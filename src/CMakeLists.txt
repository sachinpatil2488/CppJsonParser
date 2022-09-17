add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-D SA_UNICODE)

##----------------------------------------------------------------
## Platform Independent Sources
##----------------------------------------------------------------

set(SRC
    JExport.hpp
    JsonParser.cpp
    JsonParser.hpp
    JValueType.hpp
    JValue.hpp
    JValue.cpp
    JString.hpp
    JString.cpp
    JBoolean.hpp
    JBoolean.cpp
    JNumeric.hpp
    JNumeric.cpp
    JList.hpp
    JList.cpp
    JObject.hpp
    JObject.cpp
    JNull.hpp
    JNull.cpp
    Utils.hpp
    Utils.cpp)

add_library(${PROJECT_NAME}-bits STATIC ${SRC})

#target_compile_definitions(${PROJECT_NAME} PRIVATE "_CPP_EXPORT_=1")

add_subdirectory(test)