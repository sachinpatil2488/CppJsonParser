//==========================================================================
//
// author : sachinpatil
// date   : 2020
// description : 
//==========================================================================

#pragma once

namespace jp
{

/*
 Supported value types in json serialization/deserailization 
*/
enum JValueType
{
    J_UNKNOWN,           /* Value format not known*/
    J_OBJECT,            /* Values enclosed in {} */
    J_STRING,            /* Values enclosed in "" */
    J_NUMERIC,           /* Plain values without quote */
    J_INT,               /* Numeric valies without . */
    J_FLOAT,             /* Numeric valies with . */
    J_BOOL,              /* Valuies in true/false format */
    J_LIST,              /* Values enclosed in [] */
    J_NULL               /* Values with null data */
};

} //jp
