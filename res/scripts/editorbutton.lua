require "State"
require "scripts/button.lua"

editorbutton = class(Button)

function editorbutton:Init()
	self.super.entity = self.entity
	self.super:Init("Editor")
end

function editorbutton:OnClick()
	State.changeScene("editor")
end
