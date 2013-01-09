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

function Init()
	print "Quitbutton Init"
	--[[
	--Load the button image
	img = LPC.Image("../res/img/simplebutton.png")
	box = entity:Box()
	img:SetActiveClip(0)
	--Setup the button text
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
	--print ("Camera centering: " .. camera:centering())
	--print ("Camera offset: " .. camera:offset())
	--LPC.Window.Draw(img, LPC.Math.FromSceneSpace(camera, box))
	--LPC.Window.Draw(text, LPC.Math.FromSceneSpace(camera, textBox))
end
function OnMouseDown()
	--img:SetActiveClip(1)
end
function OnMouseUp()
	--img:SetActiveClip(0)
end
function OnMouseExit()
	--img:SetActiveClip(0)
end
function OnClick()
	--LPC.StateManager.ChangeScene("quit")
end
function TestCall(val1)
	print ("TestCall called with: " .. val1)
end
--Another cross-state test
function AddVects(v1, v2)
	--v1 = v1 .. " - chicken"
	--print ("Adding: " .. v1 .. " and " .. v2)
	--return v1 + v2
end