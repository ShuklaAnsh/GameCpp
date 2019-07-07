#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

class Game 
{
    // Types
    public:
        //Screen dimension constants
        const static int MAX_SCREEN_WIDTH = 1000;
        const static int MAX_SCREEN_HEIGHT = 1000;
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
        virtual void handleMouse(SDL_MouseMotionEvent& mouse_motion);
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
        int             m_screen_width;    /* int to the screen width                       */
        int             m_screen_height;   /* int to the screen height                      */
};
#endif /* Game_hpp */