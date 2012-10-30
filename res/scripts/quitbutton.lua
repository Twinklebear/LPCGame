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
--Testing passing userdata back and forth
require "TestTimer"

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
function Update()
end
function Draw(camera)
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
--Testing cross-lua_State calls
function Test(timer)
	print "Test was called"
	--[[
	print ("Timer status: " .. timer:started())
	ticks = timer:ticks()
	print ("Ticks: " .. ticks)
	print ("Returning # ticks")
	--print ("Test was called, param: " .. str)
	]]
	ticks = 10
	return ticks
end