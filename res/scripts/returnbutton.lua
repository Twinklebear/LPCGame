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
	print "Return to intro button init!"

	--Load the button image
	img = Image("../res/img/simplebutton.png")
	box = self:box()
	img:setActiveClip(0)

	--Configure the position and text depending if we're in the editor or game
	print ("State name is: " .. State.name())
	inGame = (State.name() == "gGame")
	local message = ""

	if not inGame then
		box:set(32, 625, 250, 50)
		self:physics().box = box
		message = "Save & Quit"
	else
		message = "Return"
	end
	--Setup the button text
	local txtColor = Color(0, 0, 0)
	text = Text(message, "../res/fonts/SourceSansPro-Regular.ttf",
		txtColor, 25)

	print ("Box is: " .. box)

	textBox = Rectf((box:x() + box:w() / 2 - text:w() / 2),
		(box:y() + box:h() / 2 - text:h() / 2), text:w(), text:h())

	print ("Text box is: " .. textBox)
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
	Window.draw(text, box)
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