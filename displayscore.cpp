#include "displayscore.h"

DisplayScore::DisplayScore(std::string name)
    : name(name), sprite(":/sprites/" + QString(name.c_str()) + ".png")
{
    sprite = sprite.scaledToHeight(20);
}

void DisplayScore::render(Renderer &renderer, unsigned int xCoordinate, unsigned int yCoordinate, int padding) {
    renderer.draw(xCoordinate - sprite.width() - padding, yCoordinate, sprite);
    Score::render(renderer, xCoordinate, yCoordinate);
}
