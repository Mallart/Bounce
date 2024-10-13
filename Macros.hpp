#pragma once

#define BOUNCE_FUNCTION bf
#define BOUNCE_CLASS bc

#define SCAN(a) a
#define CONCAT(a, b) a ## b

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
// An interface should be derived from.
#define BINTERFACE() class
#define BINTERFACE(name) class name; typedef name* Ref##name; class name

// Serializable enum.
#define BENUM() enum

#define BSET(visibility, type, prop) visibility: void CONCAT(Set, prop) (type value) { prop = value ; }
#define BGET(visibility, type, prop) visibility: type CONCAT(Get, prop) (void) { return prop; }
// without visibility
#define WV_BSET(type, prop) void CONCAT(Set, prop) (type value) { prop = value ; }
#define WV_BGET(type, prop) type CONCAT(Get, prop) (void) { return prop ; }

// Defines a property by its visibility, type and name.
// Serializable by the engine.
#define BPROPERTY(visibility, type, prop) visibility : type prop; 
// Defines accessors by their: Getting access, Setting access, type, and name.
// Serializable by the engine.
#define BACCESSOR(get_access, set_access, type, prop) BGET(get_access, type, prop) BSET(set_access, type, prop)
// Shorthand for BPROPERTY and BACCESSOR.
#define BAPROPERTY(get_access, set_access, type, prop) BPROPERTY(get_access, type, prop) BACCESSOR(get_access, set_access, type, prop)
// Defines a property and virtual accessors by its: Getting access, Setting access, type, and name.
// Serializable by the engine.
#define V_BACCESSOR(get_access, set_access, type, prop) BPROPERTY(get_access, type, prop) get_access : virtual WV_BGET(type, prop) set_access : virtual WV_BSET(type, prop)

// Flags a method as a Getter (return result will be interpreted as a property)
// A getter method may not have any parameter.
#define BGETTER()
// Flags a method as a Setter (useless at the moment)
#define BSETTER()


#define b_min(a, b) (a > b ? b : a);
#define b_max(a, b) (a < b ? b : a);