require "scripts/lua_classes.lua"

--Testing the implementation
Entity = class(Object)
function Entity:initialize(name)
	print "entity init"
	self.name = name
end

function Entity:speak()
	print ("Entity here, my name is: " .. self.name)
end

SillyEntity = class(Entity)
function SillyEntity:speak()
	print ("SillyEntity here, my name is: " .. self.name)
end

entity = Entity:new("Roberto")
local sillyEntity = SillyEntity:new("Rogelio")
entity:speak()
sillyEntity:speak()