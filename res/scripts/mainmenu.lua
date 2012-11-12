--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestState"
require "TestVector2f"
require "TestEntity"
--[[
require "TestInput"
require "TestTimer"
require "TestLuaScript"
]]

function Init()
	print "\n--------Main Menu Init--------\n"
	quitButton = State.getEntity("quitbutton")
	print ("Main menu looked up entity: " .. quitButton:name())

	--Test call with a vector
	--val = "string"
	v1 = Vector2f(4, 5)
	--v2 = Vector2f(1, 2)
	--print (v1)
	ret = quitButton:callFunction("TestCall", 1, "howdy!", v1)
	print ("got back ret: " .. ret)
	print ("v1 still: " .. v1)
	--print ("Got result of: " .. v1 .. " + " .. v2 " = " .. result)
	--print (val)
	--LuaScript.stackDump(false, v2)
	
	--print "Try to make a new entity"
	--e = Entity("../res/entities/npc.json")
	--print ("Made entity: " .. e:name())
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	--Testing scene changing
	if Input.keyDown(Input.KEY_Q) then
		print "QUITTING"
		State.changeScene("quit")
	end
	if Input.keyDown(Input.KEY_E) then
		print "Deleting entity npc"
	--	e:destroy()
	end
end
function RenderUpdate()
end
