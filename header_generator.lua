---Functions are full signatures\
---Classes are arrays of functions
---@alias exportDump { namespaces: exportDump[], functions: string[], classes: table<string, string[]> }

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

---@param dumpbinExports string
---@return exportDump globalExportDump
function getExportList(dumpbinExports)
    ---@type exportDump
    local globalExportDump = {
        namespaces = {},
        classes = {},
        functions = {}
    }
    local signatureList = {}

    for name in dumpbinExports:gmatch("%s+%d+%s+%d+%s+%x+%s+([^\n]+)") do
        local signature = unmangleSignature(name)

        ---@diagnostic disable-next-line: unbalanced-assignments
        local className, secondSignaturePosition = signature:match("^public: class (%S*) & ()")
            or signature:match("^public: static class (%S*) & ()")
            or signature:match("^public: struct (%S*) & ()")
            or signature:match("^public: static struct  (%S*) & ()")

        if secondSignaturePosition ~= nil then
            globalExportDump.classes[className] = {}
            signature = signature:sub(secondSignaturePosition)
        end
        table.insert(signatureList, signature)
    end

    return globalExportDump
end

---@param mangledSignature string
---@return string
function unmangleSignature(mangledSignature)
    return getCommandOutput("undname " .. mangledSignature):sub(1, -4):match("is :%- \"(.+)")
end

-- Match 1: Qualifiers\
-- Match 2: Namespace + potential class\
-- Match 3: Operator overload or method name
local namespacedMethodPattern = "^public: ([ %w_*]+ )([%w_:]+)::([%w_+%-*/%%=!<>&|^~,[%]]+%(.+)"

-- Match 1: Namespace\
-- Match 2: Class name
local classPattern = "([%w_:]*):?:?([%w_:]+)"

-- Match 1: Qualifiers\
-- Match 2: Namespace + class\
-- Match 3: Operator overload
local namespacedPointerReferenceOverloadPattern = "^public: ([ %w_*]+ )([%w_:]+)::(operator .+)"

---@param signature string
---@return string
function getSignatureData(signature)
end

---Strips whitespace from right of string
---@param str string
---@return string
function rightTrim(str)
    return str:match("^(.*%S)%s*$")
end

local output = io.open("HavokScript_FinalRelease.h", "w")
local signatures = getExportList(getCommandOutput("dumpbin /exports HavokScript_FinalRelease.dll"))
