#include "Character.hpp"

/**
 * @brief Construct a new Character::Character object
 * 
 * @param renderer: Pointer to the SDL_Renderer for the Game
 */
Character::Character(SDL_Window* window, SDL_Renderer* renderer) : 
      m_body()
    , m_x(0)
    , m_y(0)
    , m_xv(VEL)
    , m_yv(VEL)
    , m_window_width(0)
    , m_window_height(0)
{   
    m_renderer = renderer;
    m_window = window;
    m_body.x = m_x;
    m_body.y = m_y;
    m_body.w = WIDTH;
    m_body.h = HEIGHT;
    SDL_GetWindowSize(m_window, &m_window_width, &m_window_height);
}


/**
 * @brief Destroy the Character::Character object
 * 
 */
Character::~Character()
{
}


/**
 * @brief 
 * 
 */
void Character::render()
{
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 250, 210, 20, 255);
    SDL_RenderFillRect(m_renderer, &m_body);
}


/**
 * @brief Moves the character around
 * 
 * @param key_code - key code recieved
 */
void Character::move(SDL_Keycode& key_code)
{
    switch (key_code)
    {
    case SDLK_RIGHT:
        m_x = ( (m_x + WIDTH) < m_window_width ) ? (m_x + m_xv) : (m_window_width - WIDTH);
        m_body.x = m_x;
        break;
        
    case SDLK_LEFT:
        m_x = ( m_x > 0 ) ? (m_x - m_xv) : 0 ;
        m_body.x = m_x;
        break; 

    case SDLK_UP:
        m_y = ( m_y > 0 ) ? (m_y - m_yv) : 0 ;
        m_body.y = m_y;
        break;
        
    case SDLK_DOWN:
        m_y = ( (m_y + HEIGHT) < m_window_height ) ? (m_y + m_yv) : (m_window_height - HEIGHT) ;
        m_body.y = m_y;
        break;
    
    default:
        break;
    }
}


/**
 * @brief Accelerates the velocity
 * 
 * @param key_code - key code recieved
 */
void Character::accelerate(SDL_Keycode& key_code)
{
    switch (key_code)
    {
    case SDLK_RIGHT:
    case SDLK_LEFT:
        m_xv = ( m_xv < MAX_VEL ) ? m_xv + VEL : m_xv;
        break;

    case SDLK_UP:
    case SDLK_DOWN:
        m_yv = ( m_yv < MAX_VEL ) ? m_yv + VEL : m_yv;
        break;
    
    default:
        break;
    }
}


/**
 * @brief Resets velocity to default
 * 
 */
void Character::resetVelocity()
{
    m_yv = VEL;
    m_xv = VEL;
}