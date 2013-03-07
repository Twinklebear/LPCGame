require "Entity"
require "Image"
require "Rectf"
require "Color"
require "Text"
require "Window"
require "Math"
require "Camera"
require "scripts/luaclass/entity.lua"

Button = class(Entity)

--Using button requires that you pass the entity to super as well
--via self.super.entity = self.entity
function Button:Init(msg)
	--load up image
	self.img = Image("../res/img/simplebutton.png")
	self.img:setActiveClip(0)
	--setup message
	local txtColor = Color(0, 0, 0)
	self.text = Text(msg, "../res/fonts/SourceSansPro-Regular.ttf", 
		txtColor, 25)
	self.textBox = Rectf((self.entity:box():x() + self.entity:box():w() / 2 - self.text:w() / 2),
		(self.entity:box():y() + self.entity:box():h() / 2 - self.text:h() / 2),
		self.text:w(), self.text:h())
end

function Button:Draw(camera)
	Window.draw(self.img, Math.fromSceneSpace(camera, self.entity:box()))
	Window.draw(self.text, Math.fromSceneSpace(camera, self.textBox))
end

function Button:OnMouseDown()
	self.img:setActiveClip(1)
end

function Button:OnMouseUp()
	self.img:setActiveClip(0)
end

function Button:OnMouseExit()
	self.img:setActiveClip(0)
end
