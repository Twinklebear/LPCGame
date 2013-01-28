--A simple implementation of classes in Lua
local Object

function class(super)
	super = super or Object
	local prototype = setmetatable({}, super)
	prototype.super = super
	prototype.__index = prototype
	return prototype
end

Object = class()

function Object:new(...)
	local instance = setmetatable({}, self)
	instance:intialize(...)
	return instance
end

function Object:intialize()
	print "Object init"
end

--Testing the implementation
Entity = class(Object)
function Entity:initialize(name)
	print "entity init"
	self.name = name
end

function Entity:speak()
	print ("my name is: " .. self.name)
end

SillyEntity = class(Entity)
function SillyEntity:speak()
	print ("SillyEntity here, my name is: " .. self.name)
end

local entity = Entity:new("Roberto")
local sillyEntity = SillyEntity:new("Rogelio")
--entity:speak()
--sillyEntity:speak()