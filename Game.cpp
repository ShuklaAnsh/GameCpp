#include "Game.hpp"

/**
 * @brief Construct a new Game object
 * 
 */
Game::Game(): m_running(false)
    , m_window(NULL)
    , m_screen_surface(NULL)
    , m_renderer(NULL)
{
}


/**
 * @brief Destroy the Game object
 * 
 */
Game::~Game()
{
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

    m_running = initPostHook();
    return m_running;
}


/**
 * @brief meant to be overwritten by derived class
 * 
 * @return true
 * @return false 
 */
bool Game::initPostHook()
{
    return false;
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
 * @brief Stops running the game
 * 
 */
void Game::stopGame()
{
    m_running = false;
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
            handleKey(e.key);
            break;

        case SDL_MOUSEBUTTONDOWN:
            handleMouse(e.button);
            break;

        default:
            break;
    }
}


/**
 * @brief meant to be overriden
 * 
 * @param mouse_button 
 */
void Game::handleKey(SDL_KeyboardEvent& key_event)
{

}


/**
 * @brief meant to be overriden
 * 
 * @param mouse_button 
 */
void Game::handleMouse(SDL_MouseButtonEvent& mouse_button)
{

}
/**
 * @brief Render onto screen
 * 
 */
void Game::render()
{
    renderPreHook();
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    /******************************/
    /* Render stuff in this block */
    renderMidHook();
    /******************************/
    SDL_RenderPresent(m_renderer);
    renderPostHook();
}


/**
 * @brief meant to be overwritten by derived class
 * 
 */
void Game::renderPreHook()
{
    return;
}


/**
 * @brief meant to be overwritten by derived class
 * 
 */
void Game::renderMidHook()
{
    return;
}


/**
 * @brief meant to be overwritten by derived class
 * 
 */
void Game::renderPostHook()
{
    return;
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