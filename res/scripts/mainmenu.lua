--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestEntity"
require "TestState"
require "TestInput"
require "TestTimer"
require "TestVector2f"

function Init()
	--[[
	print "\n--------Main Menu Init--------\n"
	quitButton = State.getEntity("quitbutton")
	print ("Main menu looked up entity: " .. quitButton:name())

	--Test call with a vector
	v = Vector2f(4, 5)
	v2 = Vector2f(1, 2)
	result = quitButton:callFunction("AddVects", 1, v, v2)
	print ("Got result: " .. result)
	]]
	print "Try to make a new entity"
	e = Entity("../res/entities/npc.json")
	print ("Made entity: " .. e:name())
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
end
function RenderUpdate()
end