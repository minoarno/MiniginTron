#pragma once
#include "HelperStructs.h"

bool IsOverlapping(const Rect& rect1, const Rect& rect2);
bool IsOverlapping(const Rect& rect, const Vector2& p);

void SetColor(const Color& color);
void DrawRect(const Rect& rect);