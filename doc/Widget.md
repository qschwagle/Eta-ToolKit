# Widget

A Widget is a databinedable, responsive object which handles user inputs through the user interface and displays the data bound to it

## Life Cycle

All widgets are constructed as make_shared pointers and placed on a scene graph, whether through a scene or directly attaching to a widget attached to a scene, or being attached to a widget which is then attached to the scene.

The basic life cycles are as follows

1. The Widget is constructed
2. The Widget is added to a scene (through the ways above).
3. The Widget is initialized
4. The Widget is drawn.
5. The Widget is updated ( mutated in some way )
6. The Wdiget is deconstructed

4 and 5 are repeated in that order for the duration of the lifetime of the Widget.

## Properties of a Widget

Every Widget must have a width and a height. This is exposed by GetExternalWidth() and GetExternalHeight() respectively.

The width and the height of a widget must be available after the widget is initialized, and will always be accurate for the duration of a widgets lifetime after initialzied to deconstruction

Once a Widget is associated with a DrawableFactory, the widget will never be associated with a different DrawableFactory.

When a widget's data or behavior is changed such that the UI dimensions changes, all widgets that contain it must be updated and any other widgets with itself that is dependent on it, must be updated

### A Widget's Eye

The Eye of a widget is the top left point by which the drawable renders the object to screen. The Eye moves to shift the window around the screen. It is used for Scrolling a widget.

The Eye should not be modified by a widget. It should be modified only by A Scroller.

During Drawing, the widgets bound to the current widget should have an eye passed, that eye being the sum of the previously passed eye and the eye of the current widget

Any events coming from screen coordinate space must be adjusted with the current Eye as the Eye shifts the screen coordinate space when drawing.

### A Widget's Scroller

The Scroller of a widget defines the behavior of reacting to a OnScroll Event.

By Default, the scroller scroller will not respond to the current event.

If the Scroller is set to Horizontal or Vertical, it will adjust the eye accordingly. 

OnScroll must look for children objects reacting to the event then itself.

### OnRightClick and OnLeftClick

OnRightClick and OnLeftClick are pointers to callbacks for the associated event.

A Widget will check for children objects responding to the above events before itself.

If the callbacks are nullptrs, the events will be ignored

