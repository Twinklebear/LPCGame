require "Entity"
require "Physics"
require "Rectf"
require "Vector2f"
require "Camera"
require "Color"
require "Image"
require "Window"
require "Math"
require "State"
require "Text"
require "Input"

function Init()
	--Load the button image
	img = Image("../res/img/simplebutton.png")
	box = entity:box()
	img:setActiveClip(0)

	--Configure the position and text depending if we're in the editor or game
	local message = ""
	if State.name() ~= "gGame" then
		box:set(32, 625, 250, 50)
		entity:physics().box = box
		message = "Save & Quit"
	else
		message = "Return"
	end

	--Setup the button text
	local txtColor = Color(0, 0, 0)
	text = Text(message, "../res/fonts/SourceSansPro-Regular.ttf",
		txtColor, 25)
	textBox = Rectf((box:x() + box:w() / 2 - text:w() / 2),
		(box:y() + box:h() / 2 - text:h() / 2), text:w(), text:h())
end
function Free()
end
function Update()
end
function Move(deltaT)
end
function Draw(camera)
	--It's not a UI element so we don't transform
	Window.draw(img, box)
	Window.draw(text, textBox)
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
	State.changeScene("mIntro")
end