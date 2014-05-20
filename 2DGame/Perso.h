#ifndef __Zomb__Perso__
#define __Zomb__Perso__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Perso
{
public:
  Perso(SDL_Renderer *renderer);
  ~Perso();
  void render() const;
  void moveRight(bool right);
  void moveDown();
  void jump();
  inline void setJumpTrue() {m_jump = true;}
  
private:
  int m_x;
  int m_y;
  bool m_left;
  bool m_right;
  bool m_jump;
  int m_jumpSpeed;
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
};

#endif
