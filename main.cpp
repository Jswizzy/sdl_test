#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
};

const int KEY_PRESS_SURFACE_TOTAL = 5;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface *loadSurface(const std::string &path);

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

//The images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//Current displayed image
SDL_Surface *gCurrentSurface = nullptr;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("Hello World!",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
        printf("Failed to load default image!\n");
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
        printf("Failed to load up image!\n");
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
        printf("Failed to load down image!\n");
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
        printf("Failed to load left image!\n");
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

void close() {
    //Deallocate surfaces
    for (auto &gKeyPressSurface : gKeyPressSurfaces) {
        SDL_FreeSurface(gKeyPressSurface);
        gKeyPressSurface = nullptr;
    }

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    //Quite SDL subsystems
    SDL_Quit();
}

SDL_Surface *loadSurface(const std::string &path) {
    SDL_Surface *loadSurface = SDL_LoadBMP(path.c_str());
    if (loadSurface == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadSurface;
}

int main(int argc, char *argv[]) {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool isRunning = true;

            //Event handler
            SDL_Event sdlEvent;

            //Set default surface
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            //While application is running
            while (isRunning) {
                //Handle events on queue
                while (SDL_PollEvent(&sdlEvent) != 0) {
                    //User requests quit
                    if (sdlEvent.type == SDL_QUIT) {
                        isRunning = false;
                    } else if (sdlEvent.type == SDL_KEYDOWN) {
                        //Select surfaces based on key press
                        switch (sdlEvent.key.keysym.sym) {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;

                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;

                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;

                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;

                            default:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                    }
                }

                //Apply the image
                SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}