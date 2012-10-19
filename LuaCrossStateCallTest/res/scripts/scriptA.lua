--require "Vector2"
--require "LuaRect"
--[[
print "Script A!"

--To prove that we're manipulating the desired state
someNum = 10

function Test (p)
	print "Calling Test"
	print ("Test Func in script A! Param: " .. p)
	return 10
end
function Test3(a, b, printMe, r2)
	LuaRect.add(r2)
	print ("Rect x, y: " .. r2:x() .. ", " .. r2:y())
	print ("Rect w, h: " .. r2:w() .. ", " .. r2:h())
	--TestVector()
	local r = LuaRect.new()
	r:set(10, 2, 3, 4)
	print ("Rect x, y: " .. r:x() .. ", " .. r:y())
	print ("Rect w, h: " .. r:w() .. ", " .. r:h())
	print ("Printing string param: " .. printMe)
	return a + b + someNum
end

--]]