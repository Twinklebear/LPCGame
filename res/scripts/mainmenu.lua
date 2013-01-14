--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestState"
require "TestVector2f"
require "TestEntity"
require "TestRectf"
require "TestPhysics"
require "TestMath"
require "TestCamera"
require "TestImage"
require "TestWindow"
require "TestInput"
require "TestColor"
require "TestTimer"
require "TestAnimatedImage"

function Init()
	print "\n--------Main Menu Init--------\n"
	--[[
	animImg = AnimatedImage("../res/img/walking.png")
	animImg:play("run-right")
	drawPos = Rectf(0, 0, 64, 64)
	]]
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	--Testing scene changing
	if Input.keyDown(Input.KEY_Q) then
		State.changeScene("quit")
	end
	--animImg:update()
end
function RenderUpdate()
	--Window.draw(animImg, drawPos, 45, Vector2f(0, 0), Window.FLIP_VERTICAL)
end
function TestCall(v)
	print ("Test call called")
	print ("Param: " .. v)
end
function Test2(v1, v2)
	print "Test2"
	print ("v1: " .. v1 .. " v2: " .. v2)
end