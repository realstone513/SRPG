#include <SFML/Graphics.hpp>
#include "SFML_Framework/Frameworks.h"

int main()
{
    Vector2f windowSize(1280, 960);
    FRAMEWORK->Init(windowSize.x, windowSize.y, "realstone SRPG");
    FRAMEWORK->Do();
    return 0;
}