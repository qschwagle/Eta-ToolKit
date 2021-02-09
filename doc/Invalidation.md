# Invalidation of Widget and Visual Elements

## Summary

When a UI element changes, whether that is the widget or the visual elements which make up the 
widget, the element must be invalidated. Invalidation tells the object to refresh the cache of 
the visual elements and to tell the owner containers that this widget has changed. The owner  
containers must check sizing and layout details and possibly invalidate their visual elements.

### Invalidate()

Widget::Invalidate() is the virtual function that should be called when an element is 
invalidated. It should be defined in every widget which has visual elements which must be cached 
invalidated. As long as Widget::Invalidate() is called, the sizing, padding, and owner are
recalculated or notified of the invalidation.

### Why this is necessary?
