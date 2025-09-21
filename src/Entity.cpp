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

void Entity::setPos(float x, float y){
    pos.x += x;
    pos.y += y;
}

void Entity::setDestroy(bool destr){
    destroy = destr;
}

bool Entity::getDestroy(){
    return destroy;
}

void Entity::checkColision(Entity entity){
    if(entity.getPos().x < getPos().x + 16 && entity.getPos().x > getPos().x - 16 &&
        entity.getPos().y < getPos().y + 16 && entity.getPos().y > getPos().y - 16){
            setDestroy(true);
        }
}