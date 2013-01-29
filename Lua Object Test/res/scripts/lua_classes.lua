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
end

function Object:instanceOf(class)
	local currentClass = self
	--Check through all parent classes
	while currentClass ~= nil do
		if currentClass == class then
			return true
		end
		currentClass = currentClass.super
	end
	return false
end

--Short demo of using instanceOf
TestObj = class(Object)
Entity = class(Object)
testObj = TestObj:new()

print ("testObj:instanceOf(Object)? " .. tostring(testObj:instanceOf(Object)))
print ("testObj:instanceOf(Object)? " .. tostring(testObj:instanceOf(Entity)))