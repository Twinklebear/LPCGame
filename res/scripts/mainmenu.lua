--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestState"
require "TestVector2f"
require "TestEntity"
require "TestRectf"
require "TestPhysics"
require "TestMath"

function Init()
	print "\n--------Main Menu Init--------\n"
	--[[
	quitButton = State.getEntity("quitbutton")
	print ("Main menu looked up entity: " .. quitButton:name())
	print ("Getting physics component")
	qBPhys = quitButton:physics()
	print ("quitbutton box: " .. qBPhys:box())
	print ("quitbutton position: " .. qBPhys:position())
	quitButton:callFunction("TestCall", 0, quitButton, qBPhys)
	quitButton:release()
	]]
	vA = Vector2f(0, 0)
	vB = Vector2f(1, 0)
	dist = Math.distance(vA, vB)
	print ("distance betw vA and vB:  " .. dist)
	print ("Math.LEFT: " .. Math.LEFT)
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
	end
end
function RenderUpdate()
end
