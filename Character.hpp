#ifndef Character_hpp
#define Character_hpp

#include <SDL2/SDL.h>
class Character 
{
    // Types
    public:
        static const int WIDTH = 50;    /* const int for width              */
        static const int HEIGHT = 50;   /* const int for height             */
        static const int VEL = 10;      /* const int for velocity inrements */
        static const int MAX_VEL = 50;  /* const int for maximum velocity   */
    
    protected:
    private:

    // API 
    public:
        Character(SDL_Window* window, SDL_Renderer* renderer);
        ~Character();
        void render();
        void move(SDL_Keycode& key_code);
        void accelerate(SDL_Keycode& key_code);
        void resetVelocity();

    protected:

    private:

    // Modules
    protected:
        SDL_Rect m_body;            /* SDL_Rect representing the character body */
        SDL_Texture* m_texture;     /* Pointer to the texture used              */
        int m_x;                    /* int for x position                       */
        int m_y;                    /* int for x position                       */
        int m_xv;                   /* int for x velocity                       */
        int m_yv;                   /* int for x velocity                       */
        int m_window_width;         /* int for window width                     */
        int m_window_height;        /* int for window height                    */
    
    private:
        SDL_Window* m_window;       /* Pointer to the window for the Game       */
        SDL_Renderer* m_renderer;   /* Pointer to the renderer for the Game     */
};

#endif /* Character_hpp */