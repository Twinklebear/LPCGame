require "LuaRect"

print "Script A!"

function Test (p)
	LuaRect.add(p)
	print "Calling Test"
	print ("Test Func in script A! Param x: " .. p:x())
	return 15
end