require "Vector2"
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

function Test3(a, b, printMe)
	TestVector()
	print ("Printing string param: " .. printMe)
	return a + b
end