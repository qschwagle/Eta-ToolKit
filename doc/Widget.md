# Widget

A Widget is a databinedable, responsive object which handles user inputs through the user interface and displays the data bound to it

## Life Cycle

All widgets are constructed as make_shared pointers and placed on a scene graph, whether through a scene or directly attaching to a widget attached to a scene, or being attached to a widget which is then attached to the scene.

The basic life cycles are as follows

1. The Widget is constructed ( std::make_shared\<Widget>())
2. The Widget is added to a scene (through the ways above).
3. The Widget is attached to a Window ( which gives it a factory and initializes it)
4. The Widget is drawn.
5. The Widget is updated ( mutated in some way )
6. The Wdiget is deconstructed

4 and 5 are repeated in that order for the duration of the lifetime of the Widget.

## Properties of a Widget

### Positioning

Widgets must never be given a position directly. A widget is positioned by inserting into a container. 

A container maybe a window or maybe another widget.

If the container which recieves a widget is initializes, it will attempt to place the widget appropriately. 

If the container is not initialized, the placement will be defered to initialization.

The Position of every widget is the cached position assigned by the container. 

If the dimensions of a widget is changed, it must update the containing widget to update the positions.

