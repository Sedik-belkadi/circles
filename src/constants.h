// General constants
#define SCREEN_WIDTH  (0.5 * 2048)
#define SCREEN_HEIGHT (0.5 * 1535)

// Menu constants
#define BACKGROUND_FILENAME "../assets/background-small.png"
#define BACKGROUND_X 0
#define BACKGROUND_Y 0
#define TITLE_FILENAME "../assets/title-small.png"
#define TITLE_WIDTH 588
#define TITLE_X (0.5 * (SCREEN_WIDTH - TITLE_WIDTH))
#define TITLE_Y (0.05 * SCREEN_HEIGHT)
#define PLAY_FILENAME "../assets/play-small.png"
#define PLAY_WIDTH 122
#define PLAY_X (0.25 * SCREEN_WIDTH - 0.5 * PLAY_WIDTH)
#define PLAY_Y (0.45 * SCREEN_HEIGHT)
#define QUIT_FILENAME "../assets/quit-small.png"
#define QUIT_WIDTH 160
#define QUIT_X (0.75 * SCREEN_WIDTH - 0.5 * QUIT_WIDTH)
#define QUIT_Y (0.45 * SCREEN_HEIGHT)
#define DIFFICULTY_FILENAME "../assets/difficulty-small.png"
#define DIFFICULTY_WIDTH 325
#define DIFFICULTY_X (0.5 * SCREEN_WIDTH - 0.5 * DIFFICULTY_WIDTH)
#define DIFFICULTY_Y (0.8 * SCREEN_HEIGHT)
// Difficulty Option Constants (Positioned just above the difficulty button)
#define EASY_FILENAME "../assets/easy-small.png"
#define EASY_WIDTH 100
#define EASY_X (DIFFICULTY_X)  // Start exactly where the difficulty button starts
#define EASY_Y (DIFFICULTY_Y - EASY_WIDTH * 0.5)  // Slightly above the difficulty button

#define MEDIUM_FILENAME "../assets/medium-small.png"
#define MEDIUM_WIDTH 100
#define MEDIUM_X (EASY_X + EASY_WIDTH + (DIFFICULTY_WIDTH - 3 * EASY_WIDTH) / 3 - 10)
#define MEDIUM_Y EASY_Y  // Same vertical position as Easy

#define HARD_FILENAME "../assets/hard-small.png"
#define HARD_WIDTH 100
#define HARD_X (DIFFICULTY_X + DIFFICULTY_WIDTH - HARD_WIDTH)  // End exactly where the difficulty button ends
#define HARD_Y EASY_Y  // Same vertical position as Easy
