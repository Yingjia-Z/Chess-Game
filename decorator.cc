#include "decorator.h"

#include "pieces.h"

Decorator::Decorator(Board* b) : b{b} {}

Decorator::~Decorator() { delete b; }