# Bounce
> [!CAUTION]
> Bounce Engine does not provide any graphical rendering at the moment.
> This feature is being developed at this moment.
## What is Bounce ?
Bounce is a small and portable game engine made with C++ and OpenGL.
Bounce also uses SFML to render a simple window.
## Is it working ?
Bounce is not working as a finished product as it doesn't provide any graphical rendering at the moment, but provides a lot of other features.
## What features does Bounce engine provides ?
### Class hierarchy
This engine provides a simple class structure to define different behaviors:
- Object (Engine superclass, every element in the game will inherit from this)
- Body (Is a renderable Object, basically an object which can be placed in a scene)
- Being (An "intelligent" body; movable and can interact with the world on its own)
- Player (A user-controllable being)

- World (Inherits from Object, manages other objects and tells the window which object to render)

### Maths
Bounce provides some mathematical tools to speed up your game or simulation development;
- Dynamic vectors (Vectors in this engine are not limited by any size, you can create vectors as long as you want to)
  - Vector2, Vector3, Vector4 for integers and for floating numbers are also provided for more convenience
- Quaternions
- Degrees to radians, Euler angles to Quaternions and vice-versa are also provided

## What's special about this engine ?
### Physics
It's designed to provide fast and simple physics simulations.
Planned features are:
- Rigid bodies
- Soft bodies ("clothes")
- Fluids

 ### Paradigm
 Bounce Engine is both Object and Component oriented: meaning it uses a hierarchy of objects **and** components on each of these objects to work.
 What that also means is a Being Object is basically a base Object with Physics, Mesh, and AI components. That way, you can decide how you want to create your very custom behavior.
 You're not limited in any way by this architecture. 
