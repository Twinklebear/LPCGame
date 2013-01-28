require "LuaRect"
require "Vector2f"

print "Script A!"

function Test (r)
	print ("ScriptA Test, r: " .. r)
	return "Hi how are you?"
end
function TestVoid (r)
	print ("ScriptA TestVoid, r: " .. r)
end