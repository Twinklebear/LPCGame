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
require "AnimatedImage"
require "Text"
require "Input"

function Init()
	--Load the button image
	img = Image("../res/img/simplebutton.png")
	box = entity:box()
	img:setActiveClip(0)

	--Setup the button text
	local txtColor = Color(0, 0, 0)
	text = Text("Editor", "../res/fonts/SourceSansPro-Regular.ttf",
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
	State.changeScene("editor")
end