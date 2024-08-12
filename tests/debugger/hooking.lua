print(package.path)
debug.sethook(function() print('we do some hooking') end, "crl")

-- Define a simple Lua function with multiple lines
function test()
    local x = 1
    x = x + 1
    print(x)
end

test()
