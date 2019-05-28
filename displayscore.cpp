#include "displayscore.h"

DisplayScore::DisplayScore(std::string name)
    : name(name), sprite(":/sprites/" + QString(name.c_str()) + ".png")
{
    sprite = sprite.scaledToHeight(20);
}

void DisplayScore::render(Renderer &renderer, unsigned int yCoordinate) {
    renderer.draw(700 - sprite.width() - 20, yCoordinate, sprite);
    Score::render(renderer, yCoordinate);
}
