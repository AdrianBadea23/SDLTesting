#include "RenderWindow.hpp"
#include <iostream>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if(window == NULL){
        std::cout << "Error creating window " << SDL_GetError() << "\n";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL){
        std::cout << "Failed to load texture " << SDL_GetError() << "\n";
    }

    return texture;
}

void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}

void RenderWindow::clear(){
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity){

    SDL_Rect src;
    src.x = p_entity.get_Rect().x;
    src.y = p_entity.get_Rect().y;
    src.w = p_entity.get_Rect().w;
    src.h = p_entity.get_Rect().h;

    SDL_Rect dst;
    dst.x = p_entity.getPos().x * 4;
    dst.y = p_entity.getPos().y * 4;
    dst.w = p_entity.get_Rect().w * 4;
    dst.h = p_entity.get_Rect().h * 4;

    SDL_RenderCopy(renderer, p_entity.get_Texture(), &src, &dst);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    
    return mode.refresh_rate;
}