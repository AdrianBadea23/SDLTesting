#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* args[]) {
    
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        std::cout << "SDL failed " << SDL_GetError() << "\n";
    }

    if(!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "SDL image failed " << SDL_GetError() << "\n";
    }
    
    RenderWindow window("Game", 1920, 1080);
    std::cout << window.getRefreshRate() << "\n";
    SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
    
    std::vector<Entity> entities;
    entities.push_back(Entity(Vector2f(100, 100), grassTexture));
    entities.push_back(Entity(Vector2f(132, 100), grassTexture));
    entities.push_back(Entity(Vector2f(164, 100), grassTexture));

    bool running = true;

    SDL_Event e;
    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSeconds();

    while(running){

        int startTick = SDL_GetTicks();
        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while(accumulator > timeStep){
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    running = false;
                }

                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                    running = false;
                    }
                }
            }
            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;
        

        window.clear();
        for (Entity &enti : entities)
        {
            window.render(enti);
        }
        
        
        window.display();

        int frameTicks = SDL_GetTicks();

        if(frameTicks < 1000 / window.getRefreshRate()){
            SDL_Delay(1000 / window.getRefreshRate());
        }

    }

    window.cleanUp();
    SDL_Quit();
    return 0;
}