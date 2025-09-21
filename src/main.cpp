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
    // std::cout << window.getRefreshRate() << "\n";
    SDL_Texture* grassTexture = window.loadTexture("../res/gfx/enemy1.png");
    SDL_Texture* shipTexture = window.loadTexture("../res/gfx/ship.png");
    SDL_Texture* bullet_1 = window.loadTexture("../res/gfx/bullet_1.png");
    
    std::vector<Entity> entities;
    entities.push_back(Entity(Vector2f(100, 100), grassTexture));
    entities.push_back(Entity(Vector2f(132, 100), grassTexture));
    entities.push_back(Entity(Vector2f(164, 100), grassTexture));
    entities.push_back(Entity(Vector2f(100, 132), grassTexture));
    entities.push_back(Entity(Vector2f(132, 132), grassTexture));
    entities.push_back(Entity(Vector2f(164, 132), grassTexture));

    Entity ship = Entity(Vector2f(150, 150), shipTexture);

    bool running = true;
    bool fired = false;
    Entity bullet = Entity(Vector2f(-1, -1), bullet_1);

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

                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        /* code */
                        running = false;
                        break;

                    case SDLK_UP:
                        ship.setPos(0.f, -10.f);
                        break;
                        
                    case SDLK_DOWN:
                        ship.setPos(0.f, 10.f);
                        break;
                    
                    case SDLK_LEFT:
                        ship.setPos(-10.f, 0.f);
                        break;

                    case SDLK_RIGHT:
                        ship.setPos(10.f, 0.f);
                        break;
                    
                    case SDLK_SPACE:
                        bullet.getPos().x = ship.getPos().x;
                        bullet.getPos().y = ship.getPos().y;
                        fired = true;
                    
                    default:
                        ship.setPos(0.f, 0.f);
                        break;
                    }
                }
            }
            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;
        

        window.clear();
        for (Entity &enti : entities)
        {
            if(enti.getDestroy()){
                continue;
            }
            window.render(enti);
        }
        
        window.render(ship);
        if(fired){
            bullet.setPos(0.0f, -1.0f);
            window.render(bullet);
        }

        for (Entity &enti : entities)
        {
            enti.checkColision(bullet);
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