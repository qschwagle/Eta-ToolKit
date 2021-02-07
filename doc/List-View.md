# List View

## Summary

List View is a widget which is bound to a model and displays that model based on a given set of methods within the model and a scene

## Note

The current design is using a homemode iterator design which should be replaced with std Iterator.

## General Use Case

A User has a data collection which is relatively uniform and best displayed as a list. The User chooses a list view as the containing widget, creates and provides a scene for a given item within the list, and implements the model api to map their collection to the scene.

The User will have access to the following features.

### Dynamic Item Update

If the data for a given element changes, the associated List Item View mapped to that data will automatically update if notified.

### Dynamic Wide Update

If the data order changes or the entire collection needs to be reloaded, the user can notify ListView through the model to reload all data elements

### Dynamic Loading / Unloading

Only the that is displayed on screen or prepared to be onscreen is kept loaded into memory. When an item is moved offscreen and is not expected to be loaded in the near future, the item will be unloaded. When items are expected to be loaded, the item will be loaded. This feature can be configured at runtime to either
be entirely disabled (all items will be loaded and kept for the duration of the widget's lifetime or updated) or partially disabled ( items loaded will not be unloaded).


