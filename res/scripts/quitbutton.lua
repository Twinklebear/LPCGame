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
require "TestAnimatedImage"
require "TestText"

function Init()
	print "Quitbutton Init"
	--Load the button image
	img = Image("../res/img/simplebutton.png")
	print ("Opened image: " .. img:file())
	box = Rectf(100, 500, 200, 100)
	print ("drawing to box: " .. box)
	box.x = 100
	img:setActiveClip(0)

	--Setup the button text
	local txtColor = Color(0, 0, 0)
	print ("Text color: " .. txtColor)
	print "Making text"
	text = Text("Lua Button Test", "../res/fonts/SourceSansPro-Regular.ttf", 
		txtColor, 25)
	print ("Made text with message: " .. text:message())
	textBox = Rectf((box:x() + box:w() / 2 - text:w() / 2),
		(box:y() + box:h() / 2 - text:h() / 2), text:w(), text:h())
	print ("Text box: " .. textBox)
end
function Free()
	print "Freeing quitbutton"
end
function Update()
end
function Draw(camera)
	Window.draw(img, Math.fromSceneSpace(camera, box))
	Window.draw(text, Math.fromSceneSpace(camera, textBox))
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
function TestCall(val1)
	print ("TestCall called with anim img file: " .. val1:file())
end
--Another cross-state test
function AddVects(v1, v2)
	--v1 = v1 .. " - chicken"
	--print ("Adding: " .. v1 .. " and " .. v2)
	--return v1 + v2
end