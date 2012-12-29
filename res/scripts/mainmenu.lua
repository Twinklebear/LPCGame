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

function Init()
	print "\n--------Main Menu Init--------\n"
	img = Image("../res/img/strip.png")
	print ("Opened image: " .. img:file())
	print ("# of clips: " .. img:clipCount())
	print ("rect of clip 0: " .. img:clip(0))
	print ("setting active clip to 1")
	img:setActiveClip(1)
	print ("size of active clip: " .. img:clip())
	w, h = img:size()
	print ("Image size w, h: " .. w .. ", " .. h)
	print ("Releasing img")
	img:release()
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
