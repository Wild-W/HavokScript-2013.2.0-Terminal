-- Functions are full signatures\
-- Classes are arrays of functions
---@alias exportDump { namespaces: table<string, exportDump>, functions: string[], classes: table<string, string[]> }

---@param command string
---@return string
function getCommandOutput(command)
    local handle = io.popen(command, "r")
    if handle == nil then
        error("Error code 1: command \"" .. command .. "\" produced no output")
        os.exit(1)
    end
    local output = handle:read("*a")
    handle:close()
    return output
end

-- Match 1: Return types and calling conventions\
-- Match 2: Namespaces\
-- Match 3: Function name + parameters
local functionSignaturePattern = "([%w*_]* ?[%w*_]* ?[%w*_]* ?[%w*_]+ )([%w:_]+)::([%w_]+%(.+)"

-- Match 1: Return types and calling conventions\
-- Match 2: Namespaces + class name\
-- Match 3: Function name + parameters + unneeded pointer type
local methodSignaturePattern = "([%w*_]* ?[%w*_]* ?[%w*_]* ?[%w*_]+ )([%w:_]+)::([%w_+%-*/%%=!<>&|^~,[%]]+%(.+)"

---@param dumpbinExports string
---@return exportDump globalExportDump
function getExportDump(dumpbinExports)
    ---@type exportDump
    local globalExportDump = {
        namespaces = {},
        classes = {},
        functions = {}
    }

    for name in dumpbinExports:gmatch("%s+%d+%s+%d+%s+%x+%s+([^\n]+)") do
        local signature = unmangleSignature(name)
        local publicSignature = signature:match("^public: (.+)")

        if publicSignature ~= nil then
            -- Holy mother of yikes
            local class, secondSignature = publicSignature:match("^(class %S*) & (.+)")
            if class == nil then
                class, secondSignature = publicSignature:match("^(static class %S*) & (.+)")
                if class == nil then
                    class, secondSignature = publicSignature:match("^(struct %S*) & (.+)")
                    if class == nil then
                        class, secondSignature = publicSignature:match("^(static struct  %S*) & (.+)")
                    end
                end
            end

            if secondSignature ~= nil then
                local structureType, namespacePath, className = class:match("(%S* ?%S+ )([%w_:]+)::([%w_]+)")
                if namespacePath ~= nil then
                    getNamespacePath(globalExportDump, namespacePath).classes[structureType .. className] = {}
                else
                    globalExportDump.classes[class] = {}
                end
                publicSignature = secondSignature
            end

            -- Function is in a class
            local returnType, namespaceClassPath, methodSignature =
                publicSignature:match(methodSignaturePattern)

            if methodSignature ~= nil then
                -- Remove unneeded pointer type
                methodSignature = methodSignature:sub(1, methodSignature:match("() __ptr64$")) or methodSignature

                local namespacePathPosition, className = namespaceClassPath:match("()::([%w_]+)$")
                if namespacePathPosition ~= nil then
                    local dump = getNamespacePath(globalExportDump, namespaceClassPath:sub(1, 1 - namespacePathPosition))
                    table.insert(getClass(dump.classes, className), returnType .. methodSignature)
                else
                    table.insert(getClass(globalExportDump.classes, namespaceClassPath), returnType .. methodSignature)
                end
            else
                -- Some weird shit like
                -- __cdecl LuaPlus::LuaObject::operator struct LuaPlus::LuaPlusBoolType const volatile * __ptr64(void)const __ptr64
                -- Handle manually ig :shrug_emoji:
                print(publicSignature)
            end
        else
            -- Function is in a namespace
            local returnType, namespacePath, functionSignature =
                signature:match(functionSignaturePattern)
            if namespacePath ~= nil then
                -- In a local namespace
                table.insert(getNamespacePath(globalExportDump, namespacePath).functions, returnType .. functionSignature)
            else
                -- In the global namespace
                table.insert(globalExportDump.functions, signature)
            end
        end
    end

    return globalExportDump
end

---@param classes table<string, string[]>
---@param className string
---@return string[]
function getClass(classes, className)
    local classString = "class " .. className
    local structString = "struct " .. className
    local staticClassString = "static class" .. className
    local staticStructString = "static struct " .. className

    classReference = classes[classString] or classes[structString] or classes[staticClassString] or classes[staticStructString]
    if classReference == nil then
        classes[classString] = {}
        classReference = classes[classString]
    end
    return classReference
end

---@param exportDump exportDump
---@param path string
---@return exportDump namespaceDump
function getNamespacePath(exportDump, path)
    -- Navigate exportDump like a linked list
    for namespace in path:gmatch("[^:]+") do
        -- Insert if it does not already exist
        if exportDump.namespaces[namespace] == nil then
            exportDump.namespaces[namespace] = {
                namespaces = {},
                classes = {},
                functions = {}
            }
        end
        exportDump = exportDump.namespaces[namespace]
    end

    return exportDump
end

---@param mangledSignature string
---@return string
function unmangleSignature(mangledSignature)
    return getCommandOutput("undname " .. mangledSignature):sub(1, -4):match("is :%- \"(.+)")
end

---Strips whitespace from right of string
---@param str string
---@return string
function rightTrim(str)
    return str:match("^(.*%S)%s*$")
end

---@param exportDump exportDump
---@param indentation string?
---@return string
function getHeaderText(exportDump, indentation)
    local text = ""
    indentation = indentation or ""

    for _, functionSignature in ipairs(exportDump.functions) do
        text = text .. indentation .. functionSignature .. ";\n"
    end
    for namespace, dump in pairs(exportDump.namespaces) do
        text = text .. indentation .. "namespace " .. namespace .. " {\n" .. getHeaderText(dump, indentation .. "    ")
                    .. indentation .. "}\n"
    end
    for class, methodSignatures in pairs(exportDump.classes) do
        text = text .. indentation .. class .. " {\n"
                    .. indentation .. "    " .. "public:\n"
        for _, methodSignature in ipairs(methodSignatures) do
            text = text .. indentation .. "    " .. methodSignature .. ";\n"
        end
        text = text .. indentation .. "};\n"
    end

    return text
end

local output = io.open("HavokScript_FinalRelease.h", "w")
if output == nil then
    error("Error code 2: failed to get output file \"HavokScript_FinalRelease.h\"")
    os.exit(2)
end

local exportDump = getExportDump(getCommandOutput("dumpbin /exports HavokScript_FinalRelease.dll"))
output:write(getHeaderText(exportDump))
output:close()
