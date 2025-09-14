#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), texture(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

SDL_Texture* Entity::get_Texture(){
    return texture;
}

SDL_Rect Entity::get_Rect(){
    return currentFrame;
}