require "Vector2"
require "LuaRect"
require "LuaScript"

print "Script A!"

function Test (p)
	print "Calling Test"
	print ("Test Func in script A! Param: " .. p)
	return 10
end
function TestVector()
	print "ScriptA TestVector"
	local vector = LPC.Vector2i(-10, 10)
	TestRecieveVector(vector)
end
function TestRecieveVector(v)
	print ("Got Vector2: " .. v.x .. ", " .. v.y)
end

function Test3(a, b, printMe, r2)
	LuaRect.add(r2)
	print ("Rect x, y: " .. r2:getX() .. ", " .. r2:getY())
	print ("Rect w, h: " .. r2:getW() .. ", " .. r2:getH())
	--TestVector()
	local r = LuaRect.new()
	r:set(10, 2, 3, 4)
	print ("Rect x, y: " .. r:getX() .. ", " .. r:getY())
	print ("Rect w, h: " .. r:getW() .. ", " .. r:getH())
	print ("Printing string param: " .. printMe)
	return a + b
end