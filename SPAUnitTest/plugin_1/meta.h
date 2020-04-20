//A header file genereate by Sakura J2H tool
//Contains the infomation of a module of Sakura Engine
//With the MIT License Copyright!
#pragma once
#include <string>
#include <cstddef>

const std::string sp_meta = 
R"({
    "api" : "0.1.0",
    "name" : "plugin_1",
    "prettyname" : "Plugin 1",
    "version" : "1.0.0",
    "linking" : "shared",
    "dependencies" : [{"name":"plugin_0", "version":"1.0.0"}],
    "author" : "",
    "url" : "",
    "license" : "",
    "copyright" : ""
}
)";
inline const char* __GetMetaData(void)
{
    return sp_meta.c_str();
}
public:
virtual const char* GetMetaData(void) override
{return __GetMetaData();}
