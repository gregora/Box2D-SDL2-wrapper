#include "wrapper.h"


PhysicsObject::PhysicsObject(b2World *world, float x, float y, float w, float h, float d, float f){

  object_world = world;

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x, y);
  body = (*object_world).CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(w/2, h/2);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = d;
  fixtureDef.friction = f;

  body->CreateFixture(&fixtureDef);

}

void PhysicsObject::setAsPolygon(b2PolygonShape polygon, float d, float f){

  body -> DestroyFixture((*body).GetFixtureList());

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &polygon;
  fixtureDef.density = d;
  fixtureDef.friction = f;
  body->CreateFixture(&fixtureDef);

}

void PhysicsObject::setAsCircle(b2CircleShape circle, float d, float f){

    body -> DestroyFixture((*body).GetFixtureList());

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = d;
    fixtureDef.friction = f;
    body->CreateFixture(&fixtureDef);

}

SDL_Texture* PhysicsObject::createTexture(std::string path, SDL_Renderer* renderer, float scalex, float scaley){

  texture_scalex = scalex;
  texture_scaley = scaley;

  //const char img_path[8] = *path;
  const char *cstr = path.c_str();
  texture = IMG_LoadTexture(renderer, cstr);
  return texture;
}

float* PhysicsObject::getPosition(){

  (*body).SetAwake(true);
  b2Vec2 position = body->GetPosition();
  float ang = body->GetAngle();


  float data[3] = {position.x, position.y, ang};
  float* ptr = data;

  return ptr;

}

void PhysicsObject::setType(b2BodyType type){
  (*body).SetType(type);
}




Display::Display(int w, int h, char title[], float pixelspermeter){

  const char* tit = title;

  SDL_Init(SDL_INIT_VIDEO);

  window_width = w;
  window_height = h;
  ppm = pixelspermeter;

  window = SDL_CreateWindow(
      tit,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      w,
      h,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

  renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_GetWindowSize(window, &window_width, &window_height);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

}

void Display::loadingScreen(std::string path){

  const char *cstr = path.c_str();
  SDL_Texture* loading_texture = IMG_LoadTexture(renderer, cstr);

  SDL_GetWindowSize(window, &window_width, &window_height);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  int tex_width;
  int tex_height;
  SDL_QueryTexture(loading_texture, nullptr, nullptr, &tex_width, &tex_height);

  SDL_Rect pl;
  pl.w = tex_width;
  pl.h = tex_height;
  pl.x = window_width/2 - tex_width/2;
  pl.y = window_height/2 - tex_height/2;


  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopyEx(renderer, loading_texture, NULL, &pl, 0, NULL, SDL_FLIP_NONE);

  SDL_RenderPresent(renderer);

}

void Display::render(){

  SDL_GetWindowSize(window, &window_width, &window_height);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);



  for(int i = 0; i < background_textures.size(); i++){

    DisplayTexture tex = *(background_textures[i]);
    SDL_Texture *texture = (*(background_textures[i])).texture;

    int tex_width;
    int tex_height;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_width, &tex_height);

    SDL_Rect pl;
    pl.w = tex_width * tex.texture_scalex * ppm/10;
    pl.h = tex_height * tex.texture_scaley * ppm/10;
    pl.x = tex.x - pl.w/2 + window_width/2;
    pl.y = -tex.y - pl.h/2 + window_height/2;


    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopyEx(renderer, texture, NULL, &pl, tex.rotation, NULL, SDL_FLIP_NONE);

  }





  for(int i = 0; i < objects.size(); i++){

    PhysicsObject ob = *(objects[i]);
    SDL_Texture *texture = (*(objects[i])).texture;

    int tex_width;
    int tex_height;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_width, &tex_height);


    float *ptr = ob.getPosition();
    float pos[] = {*ptr, *(ptr + 1), *(ptr + 2)};

    SDL_Rect pl;
    pl.w = tex_width * ob.texture_scalex * ppm/10;
    pl.h = tex_height * ob.texture_scaley * ppm/10;
    pl.x = pos[0]*ppm - pl.w/2 + window_width/2;
    pl.y = -pos[1]*ppm - pl.h/2 + window_height/2;


    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopyEx(renderer, texture, NULL, &pl, -pos[2]*57.296, NULL, SDL_FLIP_NONE);


  }



  for(int i = 0; i < foreground_textures.size(); i++){

    DisplayTexture tex = *(foreground_textures[i]);
    SDL_Texture *texture = (*(foreground_textures[i])).texture;

    int tex_width;
    int tex_height;
    SDL_QueryTexture(texture, nullptr, nullptr, &tex_width, &tex_height);

    SDL_Rect pl;
    pl.w = tex_width * tex.texture_scalex * ppm/10;
    pl.h = tex_height * tex.texture_scaley * ppm/10;
    pl.x = tex.x - pl.w/2 + window_width/2;
    pl.y = -tex.y - pl.h/2 + window_height/2;


    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopyEx(renderer, texture, NULL, &pl, tex.rotation, NULL, SDL_FLIP_NONE);

  }



  SDL_SetRenderTarget(renderer, NULL);

  SDL_RenderPresent(renderer);

  //close on x
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT){
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_SUCCESS);
      };
  }

}

void Display::addObject(PhysicsObject* obj){

  objects.push_back(obj);

}

void Display::addTexture(DisplayTexture* texture, bool background){

  if(background){
    background_textures.push_back(texture);
  }else{
    foreground_textures.push_back(texture);
  }


}



DisplayTexture::DisplayTexture(){



}
