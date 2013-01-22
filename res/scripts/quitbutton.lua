require "Entity"
require "Physics"
require "Rectf"
require "Vector2f"
require "Camera"
require "Color"
require "Timer"
require "Image"
require "Window"
require "Math"
require "State"
require "AnimatedImage"
require "Text"
require "Input"

function Init()
	print "\n--------Quitbutton Init--------\n"

	print ("My name is: " .. self:name())
	--Load the button image
	img = Image("../res/img/simplebutton.png")
	box = self:box()
	img:setActiveClip(0)

	--Setup the button text
	local txtColor = Color(0, 0, 0)
	text = Text("Lua Button Test", "../res/fonts/SourceSansPro-Regular.ttf", 
		txtColor, 25)
	textBox = Rectf((box:x() + box:w() / 2 - text:w() / 2),
		(box:y() + box:h() / 2 - text:h() / 2), text:w(), text:h())

	print ("quitbutton box at: " .. box)
end
function Free()
	print "\n--------Quitbutton Free--------\n"
end
function Update()
end
function Draw(camera)
	Window.draw(img, Math.fromSceneSpace(camera, box))
	Window.draw(text, Math.fromSceneSpace(camera, textBox))
end
function OnMouseDown()
	img:setActiveClip(1)
end
function OnMouseUp()
	img:setActiveClip(0)
end
function OnMouseEnter()
end
function OnMouseExit()
	img:setActiveClip(0)
end
function OnClick()
	State.changeScene("quit")
end