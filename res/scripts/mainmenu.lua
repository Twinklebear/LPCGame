--require "AnimatedImage"
--We must use dofile as the file is not in Lua's search path
dofile("../res/scripts/calltest.lua")

function Init()
	--print("Lua search path: " .. package.path)
	print("state init")
	--Test.TestFunc()
	TestCall()
end
function Free()
	print("state free")
end
function LogicUpdate()
	--print("state logic update")
end
function RenderUpdate()
	--print("state render update")
end