# Prediction in Part II

## 1 triangle, small

There's one triangle, only 3 vertices, so vertex placement is doing small work.
And that triangle is small, so fragment placement is doing small work.

## 1 triangle, fullscreen

There's one triangle, only 3 vertices, so vertex placement is doing small work.
And that triangle is big (fullscreen), so fragment placement is doing lot of work.

## 100k instances, small

There's 100k triangle, so there's 300k vertices. The vertex placement is doing lot of work.
Each triangle is small. But there's lot of triangle, meaning many pixels to write on screen. So fragment placement is doing lot of work.
