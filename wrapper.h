#ifndef BOX2D_SDL2_WRAPPER
#define BOX2D_SDL2_WRAPPER

#include "include/box2d/box2d.h"
#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>




class PhysicsObject {

  public:

    //texture stuff
    SDL_Texture* texture = nullptr;

    float texture_scalex = 1;
    float texture_scaley = 1;

    //box2d stuff
    b2World * object_world = nullptr;
    b2Body* body = nullptr;


    PhysicsObject(b2World *world, float x = 0.0f, float y = 0.0f, float w = 0.5f, float = 0.5f, float d = 1.0f, float f = 1.0f);

    void setAsPolygon(b2PolygonShape polygon, float d = 1.0f, float f = 1.0f);

    void setAsCircle(b2CircleShape circle, float d = 1.0f, float f = 1.0f);

    SDL_Texture* createTexture(std::string path, SDL_Renderer* renderer, float scalex = 1, float scaley = 1);

    float *getPosition();

    void setType(b2BodyType type);


};


class DisplayTexture {

  public:

    SDL_Texture* texture;
    float texture_scalex = 1;
    float texture_scaley = 1;

    float x = 0;
    float y = 0;
    float rotation = 0.0f;

    DisplayTexture(std::string path = "", SDL_Renderer* renderer = nullptr, float scalex = 1, float scaley = 1);

};

class Display {

  public:

    SDL_Window *window;
    SDL_Renderer* renderer = NULL;

    int window_width;
    int window_height;
    float ppm;

    float camerax = 0;
    float cameray = 0;

    bool fullscreen = false;

    std::vector<PhysicsObject*> objects;
    std::vector<DisplayTexture*> background_textures;
    std::vector<DisplayTexture*> foreground_textures;

    Display(int w, int h, char title[], float pixelspermeter);

    void render(bool to_screen = true);

    void loadingScreen(std::string path);

    void addObject(PhysicsObject* obj);

    void addTexture(DisplayTexture* texture, bool background = false);

    void setFullscreen(bool set = true);

    bool saveScreenshotBMP(std::string filepath);

};




#endif
