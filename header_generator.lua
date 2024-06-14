---@alias signatureData { qualifiers: string?, namespace: string, baseSignature: string, type: string }

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
---@return signatureData[]
function getExportList(dumpbinExports)
    local list = {}

    for name in dumpbinExports:gmatch("%s+%d+%s+%d+%s+%x+%s+([^\n]+)") do
        print(name)
        local signature = unmangleSignature(name)
        local secondSignaturePosition = signature:match("^public: class %S* &()")
        if secondSignaturePosition ~= nil then
            insertSignatureData(list, signature:sub(1, secondSignaturePosition - 3))
            signature = signature:sub(secondSignaturePosition)
        end
        insertSignatureData(list, signature)
    end

    return list
end

---@param list table
---@param signature string
function insertSignatureData(list, signature)
    table.insert(list, getSignatureData(signature))
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
---@return signatureData
function getSignatureData(signature)
    print(signature)
    if signature:sub(1, 7) == "public:" then
        if signature:sub(9, 13) == "class" or signature:sub(9, 14) == "struct" then
            local namespace, class = signature:match(classPattern)
            print(namespace, class)
            return {
                namespace = namespace,
                baseSignature = class,
                type = rightTrim(signature:sub(9, 14))
            }
        end
        local qualifiers, namespace, method = signature:match(namespacedMethodPattern)
        if method == nil then
            qualifiers, namespace, method = signature:match(namespacedPointerReferenceOverloadPattern)
        end
        if method:sub(-7) == "__ptr64" then
            method = method:sub(1, -9)
        end
        print(qualifiers, namespace, method)
        return {
            qualifiers = rightTrim(qualifiers),
            namespace = namespace,
            baseSignature = method,
            type = "function"
        }
    end
    print("not namespaced")
    return {}
end

---Strips whitespace from right of string
---@param str string
---@return string
function rightTrim(str)
    return str:match("^(.*%S)%s*$")
end

local output = io.open("HavokScript_FinalRelease.h", "w")
local signatures = getExportList(getCommandOutput("dumpbin /exports HavokScript_FinalRelease.dll"))
