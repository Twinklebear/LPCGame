require "LuaRect"
require "Vector2f"

print "Script A!"

function Test (r, r2)
	print "In Test, got: "
	print (r)
	print (r2)
	r3 = LuaRect(5, 4, 3, 2)
	return r3
end