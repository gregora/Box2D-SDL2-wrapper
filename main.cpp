#include "wrapper.h"
#include <random>


double randDouble(){

  std::random_device rd{};
  std::mt19937 engine{rd()};
  std::uniform_real_distribution<double> dist{0.0, 1.0};
  double ret = dist(engine);
  return ret;

}

int main(){

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);

  Display* disp1 = new Display(1500, 1000, "Cool boxes", 20);
  (*disp1).loadingScreen("img/loading_screen.png");

  //each object needs to have a unique pointer
  std::vector<PhysicsObject> objects;
  objects.reserve(1000000);

  PhysicsObject groundBody(&world, 0.0f, -20.0f, 50.0f, 10.0f);
  groundBody.setType(b2_staticBody);
  groundBody.createTexture("img/square.png", (*disp1).renderer, 2.5, 0.5);
  (*disp1).addObject(&groundBody);

  PhysicsObject groundBody2(&world, 22.5f, -5.0f, 5.0f, 20.0f);
  groundBody2.setType(b2_staticBody);
  groundBody2.createTexture("img/square.png", (*disp1).renderer, 0.25, 1);
  (*disp1).addObject(&groundBody2);

  PhysicsObject groundBody3(&world, -22.5f, -5.0f, 5.0f, 20.0f);
  groundBody3.setType(b2_staticBody);
  groundBody3.createTexture("img/square.png", (*disp1).renderer, 0.25, 1);
  (*disp1).addObject(&groundBody3);

  DisplayTexture img;
  img.texture = IMG_LoadTexture((*disp1).renderer, "img/background.png");
  img.texture_scalex = 1.3;
  img.texture_scaley = 1.3;
  (*disp1).addTexture(&img, true);


  for(int i = 0; i < 500; i++){

    float height = 1;
    PhysicsObject po(&world, randDouble() * 10.0f - 5.0f, 1*i, 1, height, 1.0f, 0.3f);
    po.createTexture("img/box.png", (*disp1).renderer, 0.05, 0.05*height);
    objects.push_back(po);
    (*disp1).addObject(&(objects[objects.size() - 1]));

  }

  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  float delta = 0;

  while (true){

    now = SDL_GetPerformanceCounter();
    delta = (now - last) / (double)SDL_GetPerformanceFrequency();
    last = now;

    world.Step(delta, 6, 2);
    (*disp1).render();

  }

}
