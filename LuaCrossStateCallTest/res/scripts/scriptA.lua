--require "LuaRect"

--print "Script A!"

function Test (p)
	print "Calling Test"
	print ("Test Func in script A! Param x: " .. p:x())
	r = LuaRect(3, 4, 2, 1)
	if p == r then
		print "p == r"
	else
		print "p != r"
	end
	print ("p type: " .. p:type())
	return 15
end