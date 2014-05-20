#include "Perso.h"

#define BEGIN_X windowWidth/4-16
#define BEGIN_Y windowHeight-400
#define WIDTH_SPRITE 145
#define HEIGHT_SPRITE 295
#define DIST_DEP_SPRITE 15
#define JUMP_HEIGHT 100

void testlogSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Perso::Perso(SDL_Renderer *renderer)
{
  m_left = false;
  m_right = false;
  m_renderer = renderer;
  m_texture = IMG_LoadTexture(m_renderer, "sprite.png");
  if (m_texture == nullptr)
    testlogSDLError(std::cout, "LoadTexture");

  int windowWidth, windowHeight;
  SDL_GetRendererOutputSize(m_renderer, &windowWidth, &windowHeight);
  m_x = BEGIN_X;
  m_y = BEGIN_Y;
  m_jumpSpeed = 10;
}

Perso::~Perso()
{
  SDL_DestroyTexture(m_texture);
}

void Perso::render() const
{
  SDL_Rect size;
  //size.x = (20 + (/*m_up? 1 : */((m_left||m_right)? 2 : 0))) * WIDTH_SPRITE;
  //size.y = 5 * HEIGHT_SPRITE;
  size.x = 0;
  size.y = 0;
  size.w = WIDTH_SPRITE;
  size.h = HEIGHT_SPRITE;
  
  SDL_Rect dst;
  dst.x = m_x;
  dst.y = m_y;
  dst.w = WIDTH_SPRITE;
  dst.h = HEIGHT_SPRITE;
  
  SDL_RenderCopyEx(m_renderer, m_texture, &size, &dst, 0, NULL, (!m_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void Perso::moveRight(bool right)
{
  m_right = right;
  m_left = !right;
  
  int windowWidth, windowHeight;
  SDL_GetRendererOutputSize(m_renderer, &windowWidth, &windowHeight);
  int x = right ? m_x + DIST_DEP_SPRITE : m_x - DIST_DEP_SPRITE;
  m_x = (x < 0)? 0 : ((x > windowWidth - WIDTH_SPRITE)? windowWidth - HEIGHT_SPRITE : x);
}

void Perso::moveDown()
{

}

void Perso::jump()
{
  if(m_jump) 
  {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(m_renderer, &windowWidth, &windowHeight);
    if(m_y >= BEGIN_Y - JUMP_HEIGHT)
      m_y -= m_jumpSpeed;
    if(m_y <= BEGIN_Y - JUMP_HEIGHT)
    {
      m_jumpSpeed = -m_jumpSpeed;
      m_y -= m_jumpSpeed;
    }
    if(m_y >= BEGIN_Y)
    {
      m_jumpSpeed = -m_jumpSpeed;
      m_jump = false;
      m_y = BEGIN_Y;
    }
  }
}
