#include "Game.hpp"

/**
 * @brief Construct a new Game object
 * 
 */
Game::Game(): m_running(false)
    , m_window(NULL)
    , m_screen_surface(NULL)
    , m_renderer(NULL)
    , m_character(NULL)
{
}


/**
 * @brief Destroy the Game object
 * 
 */
Game::~Game()
{
    delete m_character;
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
    printf("Exit.\n");
}


/**
 * @brief 
 * Initializes game with the following parameters
 * @param title 
 * @param x 
 * @param y 
 * @param height 
 * @param width 
 * @param fullscreen 
 * @return true if game is running
 */
bool Game::init(const char* title, int x, int y, int height, int width, bool fullscreen)
{  
    
    //Initialize SDL Video 
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Error: Unable to init SDL Video.\nSDL_Error: %s\n", SDL_GetError() );
        m_running = false;
        return m_running;
    }
    printf( "Subsystems initialized.\n" );
    
    //Create Window
    Uint32 flags = 0;
    if( !(m_window = SDL_CreateWindow(title, x, y, width, height, flags)) )
    {
        printf( "Error: Unable to create SDL Window.\nSDL_Error: %s\n", SDL_GetError() );
        m_running = false;
        return m_running;
    }
    printf( "Window created.\n" );
    
    //Create Renderer
    flags = 0;
    if( !(m_renderer = SDL_CreateRenderer(m_window, -1, flags)) )
    {   
        printf( "Error: Unable to create SDL Renderer.\nSDL_Error: %s\n", SDL_GetError() );
        m_running = false;
        return m_running;
    }
    
    printf( "Renderer created.\n" );
    
    m_character = new Character(m_window, m_renderer);

    m_running = true;
    return m_running;
}


/**
 * @brief Check if game is running
 * 
 * @return true if game is running
 * @return false otherwise
 */
bool Game::isRunning()
{
    return m_running;
}


/**
 * @brief Handle events such as keyboard / mouse button
 * 
 */
void Game::eventHandler()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type)
    {
        case SDL_QUIT:
            m_running = false;
            break;
        
        case SDL_KEYDOWN:
            if(e.key.repeat == 0)
            {
                m_character->resetVelocity();
                m_character->move(e.key.keysym.sym);
            }
            else
            {
                m_character->accelerate(e.key.keysym.sym);
                m_character->move(e.key.keysym.sym);
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            printf("Mouse x: %d, Mouse y: %d\n", e.button.x, e.button.y);    
            break;

        default:
            break;
    }
}


/**
 * @brief Render onto screen
 * 
 */
void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    /* Render stuff in this block */
    m_character->render();
    /******************************/
    SDL_RenderPresent(m_renderer);
}


/**
 * @brief Update Game
 * 
 */
void Game::update()
{
    eventHandler();
    render();
}


int main(int argc, char const *argv[])
{
    Game* game = new Game();

    game->init("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->SCREEN_WIDTH, game->SCREEN_HEIGHT, false);

    while( game->isRunning() )
    {
        game->update();
        SDL_Delay(5);
    }
    delete game;
    return 0;    
}
