require "scripts/luaclass/class.lua"

State = class(Object)

function State:Init()
	print "State base init"
end

function State:Free()
end

function State:LogicUpdate()
end

function State:RenderUpdate(camera)
end
