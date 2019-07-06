#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

class Game 
{
    // Types
    public:
        //Screen dimension constants
        const int SCREEN_WIDTH = 700;
        const int SCREEN_HEIGHT = 700;
    protected:
    private:

    // API 
    public:
        Game();
        virtual ~Game();

        bool init(const char* title, int x, int y, int height, int width, bool fullscreen);
        bool isRunning();
        void update();
        
    protected:
        void stopGame();
        virtual bool initPostHook();
        virtual void handleKey(SDL_KeyboardEvent& key_event);
        virtual void handleMouse(SDL_MouseButtonEvent& mouse_button);
        virtual void renderPreHook();
        virtual void renderMidHook();
        virtual void renderPostHook();

    private:
        void eventHandler();
        void render();

    // Modules
    
    protected:
        bool            m_running;         /* Boolean for if the game is running            */
        SDL_Window*     m_window;          /* Pointer to the window being rendering to      */
        SDL_Surface*    m_screen_surface;  /* Pointer to the surface the window will be on  */
        SDL_Renderer*   m_renderer;        /* Pointer to the renderer                       */
};
#endif /* Game_hpp */