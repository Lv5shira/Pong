#include "GameManager.h"


GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance() {

    if (sInstance == NULL)
    {
        sInstance = new GameManager;
    }
    return sInstance;
}

bool GameManager::init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void GameManager::close()
{
    //Destroy window
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;
    TTF_CloseFont(gFont);
    gFont = NULL;

    TTF_Quit();
    //Quit SDL subsystems
    SDL_Quit();
}

void GameManager::pollEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
    }

        if (currentKeyStates[SDL_SCANCODE_W])
        {
            mPlayer1->mPlayer.y -= 5.0f * mPlayer1->mSpeed * mTimer->DeltaTime();
        }
        else if (currentKeyStates[SDL_SCANCODE_S])
        {
            mPlayer1->mPlayer.y += 5.0f * mPlayer1->mSpeed * mTimer->DeltaTime();

        }
        if (mPlayer1->mPlayer.y < mPlayer1->Upbounds)
            mPlayer1->mPlayer.y = mPlayer1->Upbounds;
        if (mPlayer1->mPlayer.y > mPlayer1->Downbounds)
            mPlayer1->mPlayer.y = mPlayer1->Downbounds;
}

GameManager::GameManager()
{
    quit = false;

    currentKeyStates = SDL_GetKeyboardState(NULL);

    mTimer = Timer::Instance();

    mPlayer1 = new Player;
    mPlayer1->mPlayer.x = 0.0f;

    mPlayer2 = new Player;
    mPlayer2->mPlayer.x = 1004.0f;

    mBall = new Ball;

    mAI = new AI(mPlayer2, mBall);

}

GameManager::~GameManager()
{
    Timer::Release();
    mTimer = NULL;

    delete mPlayer1;
    mPlayer1 = NULL;

    delete mPlayer2;
    mPlayer2 = NULL;

    delete mBall;
    mBall = NULL;
}

bool GameManager::loadFromFile(std::string textureText, SDL_Color textColor)
{
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("Assets/emulogic.ttf");
    gFont = TTF_OpenFont(fullPath.c_str(), 28);
    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    else
    {
        SDL_Texture* newTexture = NULL;
        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
        if (textSurface == NULL)
        {
            printf("Unable to render text surface! SDL_ttf Error: %s \n", TTF_GetError());
        }
        else
        {
            mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            if (mTexture == NULL)
            {
                printf("Unable to create texture from rendererd text! SDL Error: %s\n", SDL_GetError());
            }
        }
    }
}

void GameManager::textRender(int x, int y)
{
    SDL_Rect renderQuad = { x, y, 50, 70 };
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void GameManager::CreateRect()
{
    loadFromFile(std::to_string(mPlayer1->GetScore()), { 0,0,0 });
    textRender(SCREEN_WIDTH/4, 20);
    SDL_Rect outline = { 0, SCREEN_HEIGHT / 6, SCREEN_WIDTH, 5};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &outline);

    SDL_Rect line = { SCREEN_WIDTH / 2, 0, 5, SCREEN_HEIGHT / 6 };
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &line);

    loadFromFile(std::to_string(mPlayer2->GetScore()), { 0,0,0 });
    textRender(SCREEN_WIDTH - (SCREEN_WIDTH / 4), 20);

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &mPlayer1->mPlayer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &mPlayer2->mPlayer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(gRenderer, &mBall->mBall);
}

void GameManager::Render()
{
    mTimer->Update();

    if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
    {

        mBall->Update(*mPlayer1, *mPlayer2);
        mAI->Update();
        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        CreateRect();

        //Update screen
        SDL_RenderPresent(gRenderer);

        pollEvents();
        mTimer->Reset();
    }
}