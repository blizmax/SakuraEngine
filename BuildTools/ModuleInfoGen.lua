lfs = require "lfs"
json = require "BuildTools/json"
-- arg[1] prefix
-- arg[2] script-path 
-- arg[3] root-path
function main(...)
    arg = ...
    JsonFileModify = nil
    for file in lfs.dir(arg[2]) do
        local ff = arg[2].."/"..file
        if file == arg[1]..".json" or file == "main"..arg[1]..".json" then
            if file == "main"..arg[1]..".json" then
                bMainModule = true;
            end
            local attr = lfs.attributes(ff)
            JsonFile = ff
            JsonFileModify = attr.modification
        end
        if file == arg[1]..".h" then
            local attr = lfs.attributes(ff)
            MetaHeader = ff
            MetaHeaderModify = attr.modification
        end
    end

    if JsonFileModify == nil then
        print("No meta.json in the dir "..arg[2].." of Plugin.")
    else
        JsF = io.open(JsonFile, "r")
        jsonContent = JsF:read("*a")
        if MetaHeaderModify == nil or MetaHeaderModify <= JsonFileModify then
            print(arg[2].." Refreshing meta header.")
            HdrF = io.open(arg[2].."/"..arg[1]..".h", "w")
            io.output(HdrF)
            io.write([[//A header file genereate by Sakura J2H tool
//Contains the infomation of a module of Sakura Engine
//With the MIT License Copyright!\n")
#pragma once
#include <string>
#include <cstddef>

const std::string sp_meta = 
R"(]]..jsonContent..")\";\n")
            io.write("inline const char* __GetMetaData(void)\n{\n    return sp_meta.c_str();\n}\n")
            io.write("public:\nvirtual const char* GetMetaData(void) override\n")
            io.write("{return __GetMetaData();}\n")
            io.close(JsF)
            io.close(HdrF)
        end
        ModuleMeta = json.decode(jsonContent)
        if ModuleMeta["linking"] == "static" then
            -- include static module files
            GenHeader = io.open(arg[3].."/".."Modules.generated.h", "a") 
            io.output(GenHeader)
            if bMainModule == true then
                io.write([[
//A header file genereate by Sakura J2H tool
//Contains the header of static modules of Sakura Engine
//With the MIT License Copyright!]].."\n")
            end
            io.write([[
#pragma once
#include "]]..arg[2].."/"..ModuleMeta["name"]..".h\"\n")
            io.close(GenHeader)
        end
    end
end

main(arg)