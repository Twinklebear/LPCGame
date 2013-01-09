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

function Init()
	print "\n--------Main Menu Init--------\n"

	quitbutton = State.getEntity("quitbutton")
	phys = quitbutton:physics()
	print ("Physics box: " .. phys:box())
	quitbutton:callFunction("TestCall", 0, phys)
	--[[
	img = Image("../res/img/strip.png")
	print ("Opened image: " .. img:file())
	print ("# of clips: " .. img:clipCount())
	print ("rect of clip 0: " .. img:clip(0))
	print ("setting active clip to 1")
	img:setActiveClip(0)
	print ("size of active clip: " .. img:clip())
	w, h = img:size()
	print ("Image size w, h: " .. w .. ", " .. h)
	--print ("Releasing img")
	--img:release()
	drawPos = Rectf(0, 0, 32, 32)
	drawPos2 = Rectf(32, 0, 32, 32)
	drawPos3 = Rectf(32, 40, 32, 32)
	pivot = Vector2f(0, 0)
	rotation = 0

	print ("Window box size: " .. Window.box())
	]]
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
	--[[
	if Input.keyDown(Input.KEY_2) then
		img:setActiveClip(0)
	elseif Input.keyDown(Input.KEY_3) then
		img:setActiveClip(1)
	end

	if Input.keyDown(Input.KEY_A) then
		rotation = rotation - 2
	elseif Input.keyDown(Input.KEY_D) then
		rotation = rotation + 2
	end
	if rotation < 0 then
		rotation = 360 + rotation
	elseif rotation > 360 then
		rotation = 360 - rotation
	end
	]]
end
function RenderUpdate()
	--[[
	Window.draw(img, drawPos)
	Window.draw(img, drawPos2, img:clip(2))
	Window.draw(img, drawPos3, img:clip(5), rotation, pivot, Window.FLIP_NONE)
	]]
end
