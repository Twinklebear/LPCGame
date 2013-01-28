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
	instance:initialize(...)
	return instance
end

function Object:initialize()
	print "Object init"
end