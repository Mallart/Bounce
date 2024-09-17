#pragma once

#define BOUNCE_FUNCTION bf
#define BOUNCE_CLASS bc

#define SCAN(a) a
#define CONCAT(a, b) SCAN(a)##SCAN(b)

#define PROTECTED protected
#define PRIVATE private
#define PUBLIC public

// Serializable class by the engine.
// Engine will throw an error in a future version if you put this identifier without any constructor.
#define BCLASS class
#define BCLASS(name) class name; typedef name* Ref##name; class name
// For classes that were already forward-declared.
#define BCLASS_F(name) typedef name* Ref##name; class name
// For template classes.
#define BTCLASS(name, ...) template<__VA_ARGS__> class name

// Serializable interface by the engine.
// An interface is a class that cannot be instantiated. The engine will throw an error if you put a regular class there.
#define BINTERFACE() class
#define BINTERFACE(name) class name; typedef name* Ref##name; class name

// Serializable enum.
#define BENUM() enum

// Defines a property by its visibility, type and name.
// Serializable by the engine.
#define BPROPERTY(visibility, type, property) visibility : type property; 
// Defines accessors by their: Getting access, Setting access, type, and name.
// Serializable by the engine.
#define BACCESSOR(get_access, set_access, type, property) CONCAT(get_access : type Get##property() const { return this->##property; } , CONCAT(set_access , : void Set##property(type value) { this->##property = value; }))
// Shorthand for BPROPERTY and BACCESSOR.
#define BAPROPERTY(get_access, set_access, type, property) BPROPERTY(get_access, type, property) BACCESSOR(get_access, set_access, type, property)
// Defines a property and virtual accessors by its: Getting access, Setting access, type, and name.
// Serializable by the engine.
#define V_BACCESSOR(get_access, set_access, type, property) get_access : type property; CONCAT(CONCAT(get_access, : virtual type Get##property() { return this->##property; }) , CONCAT(set_access , : virtual void Set##property(type value) { this->##property = value; }))

// Flags a method as a Getter (return result will be interpreted as a property)
// A getter method may not have any parameter.
#define BGETTER()
// Flags a method as a Setter (useless at the moment)
#define BSETTER()


#define min(a, b) (a > b ? b : a);
#define max(a, b) (a < b ? b : a);