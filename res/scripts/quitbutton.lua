require "Entity"
--[[
require "Image"
require "Rect"
require "Vector2"
require "Camera"
require "Window"
require "Math"
require "Text"
require "Color"
require "StateManager"
]]
require "TestEntity"
require "TestPhysics"
require "TestRectf"
require "TestVector2f"
require "TestCamera"
require "TestColor"
require "TestTimer"
require "TestImage"
require "TestWindow"
require "TestMath"
require "TestState"

function Init()
	print "Quitbutton Init"
	--Load the button image
	img = Image("../res/img/simplebutton.png")
	print ("Opened image: " .. img:file())
	box = Rectf(100, 500, 200, 100)
	img:setActiveClip(0)
	--Setup the button text
	--[[
	local textColor = LPC.Color(0, 0, 0)
	text = LPC.Text("Lua Button Test", "../res/fonts/SourceSansPro-Regular.ttf", textColor, 25)
	textBox = LPC.Rectf((box.pos.x + box.w / 2 - text:W() / 2), 
		(box.pos.y + box.h / 2 - text:H() / 2), text:W(), text:H())
	]]
end
function Free()
	print "Freeing quitbutton"
end
function Update()
end
function Draw(camera)
	Window.draw(img, Math.fromSceneSpace(camera,box))
	--LPC.Window.Draw(text, LPC.Math.FromSceneSpace(camera, textBox))
end
function OnMouseDown()
	img:setActiveClip(1)
end
function OnMouseUp()
	img:setActiveClip(0)
end
function OnMouseExit()
	img:setActiveClip(0)
end
function OnClick()
	State.changeScene("quit")
end
function TestCall(val1, v2)
	print ("TestCall called with: " .. val1:box() .. " and " .. v2)
	return "yuay", 10
end
--Another cross-state test
function AddVects(v1, v2)
	--v1 = v1 .. " - chicken"
	--print ("Adding: " .. v1 .. " and " .. v2)
	--return v1 + v2
end