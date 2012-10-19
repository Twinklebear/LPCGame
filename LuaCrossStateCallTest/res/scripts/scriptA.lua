require "LuaRect"

print "Script A!"

function Test (p)
	print "Calling Test"
	print ("Test Func in script A! Param x: " .. p:x())
	print ("p type: " .. p:type())
	return 15
end