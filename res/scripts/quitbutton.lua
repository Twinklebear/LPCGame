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

	--self = State.getEntity("quitbutton")
	--print ("Self name: " .. self:name())
	--[[
	--Load the button image
	img = Image("../res/img/simplebutton.png")
	box = Rectf(100, 500, 200, 100)
	box.x = 100
	img:setActiveClip(0)

	--Setup the button text
	local txtColor = Color(0, 0, 0)
	text = Text("Lua Button Test", "../res/fonts/SourceSansPro-Regular.ttf", 
		txtColor, 25)
	textBox = Rectf((box:x() + box:w() / 2 - text:w() / 2),
		(box:y() + box:h() / 2 - text:h() / 2), text:w(), text:h())
	]]
end
function Free()
	print "Quitbutton free LUA"
	--self:release()
end
function Update()
end
function Draw(camera)
	--Window.draw(img, Math.fromSceneSpace(camera, box))
	--Window.draw(text, Math.fromSceneSpace(camera, textBox))
end
function OnMouseDown()
	--img:setActiveClip(1)
end
function OnMouseUp()
	--img:setActiveClip(0)
end
function OnMouseExit()
	--img:setActiveClip(0)
end
function OnClick()
	--State.changeScene("quit")
end