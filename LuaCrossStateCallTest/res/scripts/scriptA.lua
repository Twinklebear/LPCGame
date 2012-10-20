require "LuaRect"

print "Script A!"

function Test (r, r2)
	print "In Test, got: "
	print (r)
	print (r2)
	if r == r2 then
		print "p == r"
	else
		print "p != r"
	end
	r3 = LuaRect(5, 4, 3, 2)
	return r3
end