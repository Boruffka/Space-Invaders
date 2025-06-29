
module;

import <string>;
import <SFML/Graphics.hpp>;

export module CONSTANTS;

// LOGS
export constexpr const char* LOG_FILE_PATH = "Logs/log.txt";
export constexpr const char* HIGHSCORES_FILE_PATH = "Logs/highscores.txt";

// BASE RENDERING
export constexpr unsigned int SCREEN_WIDTH = 320; //320
export constexpr unsigned int SCREEN_HEIGHT = 180; //180
export constexpr unsigned int DISPLAY_SCREEN_WIDTH = 1280;
export constexpr unsigned int DISPLAY_SCREEN_HEIGHT = 720;
export constexpr int BASE_SIZE = 16;
export constexpr double DELTA_TIME = 1.0 / 60.0;

// FONTS
export const sf::Font PIXEL_FONT("Textures/Fonts/PIXEL_FONT.ttf");

// SPLASH SCREEN
export constexpr unsigned int SPLASH_STATE_SHOW_TIME = 1;
export constexpr const char* SPLASH_STATE_BACKGROUND_PATH = "Textures/Backgrounds/SPLASH_SCREEN_STATE_BACKGROUND.png";

// MAIN MENU
export constexpr const char* MAIN_MENU_STATE_BACKGROUND_PATH = "Textures/Backgrounds/MAIN_MENU_STATE_BACKGROUND.png";
export constexpr const char* MAIN_MENU_PLAY_BUTTON_PATH = "Textures/Buttons/MAIN_MENU_PLAY_BUTTON.png";
export constexpr const char* MAIN_MENU_EXIT_BUTTON_PATH = "Textures/Buttons/MAIN_MENU_EXIT_BUTTON.png";

// GAME
export constexpr const char* GAME_STATE_BACKGROUND_PATH = "Textures/Backgrounds/GAME_STATE_BACKGROUND.png";

export constexpr const char* PLAYER_SPRITE_PATH = "Textures/Sprites/PLAYER.png";
export constexpr const char* HEART_SPRITE_PATH = "Textures/Sprites/HEART.png";
export constexpr const char* BULLET_SPRITE_PATH = "Textures/Sprites/BULLET.png";
export constexpr const char* ENEMY_SPRITE_PATH = "Textures/Sprites/ENEMY3.png";

export constexpr float PLAYER_SPEED = 50.f;
export constexpr float PLAYER_BULLET_SPEED = 60.f;
export constexpr float PLAYER_RELOAD_SPEED = 1.f;

export constexpr float ENEMY_BULLET_SPEED = 70.f;
export constexpr float ENEMY_RELOAD_SPEED = 6.f;

export constexpr float ENEMY_STEP_TIMER = 3.f;
export constexpr float ENEMY_STEP_COUNTER = 8;

export constexpr float TINY_DELAY = 2.f;

// PAUSE
export constexpr const char* PAUSE_STATE_BACKGROUND_PATH = "Textures/Backgrounds/PAUSE_STATE_BACKGROUND.png";
export constexpr const char* PAUSE_STATE_ICON_PATH = "Textures/Icons/PAUSE_STATE_ICON.png";

