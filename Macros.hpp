#pragma once

#define BOUNCE_FUNCTION bf
#define BOUNCE_CLASS bc

#define SCAN(a) a
#define CONCAT(a, b) SCAN(a)##SCAN(b)

#define public_GET_public_SET(type, property) public: type property; void Set##property(type value) { this->##property = value; }; type Get##property() { return this->##property; }
#define public_GET_protected_SET(type, property) protected: type property; void Set##property(type value) { this->##property = value; }; public: type Get##property() { return this->##property; }
#define public_GET_private_SET(type, property) private: type property; void Set##property(type value) { this->##property = value; }; public: type Get##property() { return this->##property; }
#define protected_GET_protected_SET(type, property) protected: type property; void Set##property(type value) { this->##property = value; }; type Get##property() { return this->##property; }

#define PROTECTED protected
#define PRIVATE private
#define PUBLIC public

// Serializable class by the engine.
// Engine will throw an error in a future version if you put this identifier without any constructor.
#define BCLASS() class

// Serializable interface by the engine.
// An interface is a class that cannot be instantiated. The engine will throw an error if you put a regular class there.
#define BINTERFACE() class

// Serializable enum.
#define BENUM() enum

// Defines a property and accessors by its: Getting access, Setting access, type, and name.
// Serializable by the engine.
#define BPROPERTY(get_access, set_access, type, property) get_access : type property; CONCAT(CONCAT(get_access, : type Get##property() { return this->##property; }) , CONCAT(set_access , : void Set##property(type value) { this->##property = value; }))
// Defines a property and virtual accessors by its: Getting access, Setting access, type, and name.
// Serializable by the engine.
#define V_BPROPERTY(get_access, set_access, type, property) get_access : type property; CONCAT(CONCAT(get_access, : virtual type Get##property() { return this->##property; }) , CONCAT(set_access , : virtual void Set##property(type value) { this->##property = value; }))