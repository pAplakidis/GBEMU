#include "renderer.h"

Renderer::Renderer(int32_t sdl_context){
  this->sdl_context = sdl_context;

  if(sdl_context != 0){
    printf("Unable to initialize SDL2: %s\n", SDL_GetError);
    exit(1);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  window = SDL_CreateWindow(
    "GBEMU",                // title
    SDL_WINDOWPOS_CENTERED, // initial x position
    SDL_WINDOWPOS_CENTERED, // initial y position
    1024,                   // width, in pixels
    512,                    // height, in pixels
    SDL_WINDOW_OPENGL       // flags
  );

  if(window == NULL){
    printf("Could not create window: %s\n", SDL_GetError());
    exit(1);
  }

  glClearColor(0., 0., 0., 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}

Renderer::~Renderer(){
  // glDeleteVertexArrays(1, &vertex_array_object);
  // glDeleteShader(vertex_shader);
  // glDeleteShader(fragment_shader);
  // glDeleteProgram(program);
}

void Renderer::draw(){

}

void Renderer::display(){

}
