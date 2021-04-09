# Texture Atlas

## What is a Texture Atlas?

A Texture atlas is a large texture comprised of many smaller textures. They are relatively tightly packed together and 
are loaded as a single texture into the texture buffer. The textures are then used by their relative positions within 
the atlas


## Purpose

The purpose of a texture atlas is to reduce the number of small images and merge together draw calls. This will increase
the efficiency of cpu/gpu utilization.

## 