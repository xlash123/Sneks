#include "Snek.h"

const SDL_Color PLAYER_COLORS[MAX_SNEKS] = {
    { 0xFF, 0x00, 0x00, 0xFF }, // Player 1 - Red
    { 0x00, 0x00, 0xFF, 0xFF }, // Player 2 - Blue
    { 0xFF, 0xFF, 0x00, 0xFF }, // Player 3 - Yellow
    { 0x00, 0xFF, 0x00, 0xFF }, // Player 4 - Green
    { 0xFF, 0x70, 0x00, 0xFF }, // Player 5 - Orange
    { 0x00, 0xFF, 0xDD, 0xFF }, // Player 6 - Cyan
    { 0xDD, 0x00, 0xFF, 0xFF }, // Player 7 - Magenta
    { 0xFF, 0xFF, 0xFF, 0xFF }, // Player 8 - White
};

void Snek::init(SnekState *snek) {
    Controller::init(&snek->controller);

    // Allocate snek body
    snek->body = NULL;
    snek->body = (Position *) malloc(SNEK_ALLOC_SIZE * sizeof(Position));
    if (snek->body == NULL) {
        printf("Out of heap memory! Cannot create new Snek.\n");
        exit(2);
    }

    // Some placeholder values for the body
    for (int i = 0; i < SNEK_STARTING_LENGTH; i++) {
        snek->body[i] = { SNEK_STARTING_LENGTH - i, 0 };
    }
    snek->alive = true;
    snek->direction = RIGHT;
    snek->lastPolled = 0;
    snek->length = SNEK_STARTING_LENGTH;
}

void Snek::reset(SnekState *snek, int y, bool isRight) {
    // Reinitialize body
    Snek::free(snek);
    snek->body = (Position *) malloc(SNEK_ALLOC_SIZE * sizeof(Position));
    if (snek->body == NULL) {
        printf("Out of heap memory! Cannot create new Snek.\n");
        exit(2);
    }
    snek->length = SNEK_STARTING_LENGTH;

    // Initialize body positioning
    int startX = isRight ? SNEK_STARTING_LENGTH + 2 : WORLD_WIDTH - SNEK_STARTING_LENGTH - 2;
    int dx = isRight ? -1 : 1;
    snek->direction = isRight ? RIGHT : LEFT;
    snek->body[0] = { startX, y };
    for (size_t i = 1; i < SNEK_STARTING_LENGTH; i++) {
        snek->body[i] = { snek->body[i - 1].x + dx, snek->body[i - 1].y };
    }
    snek->alive = true;
}

void Snek::update(SnekState *snek) {
    // Get the players actions for this frame
    Actions actions = snek->controller.actions;

    // Update direction based on input
    // TODO: This is kinda unoptimized. Might be a better way to do this
    if (actions.moveUp && (snek->direction == RIGHT || snek->direction == LEFT)) {
        snek->direction = UP;
    } else if (actions.moveDown && (snek->direction == RIGHT || snek->direction == LEFT)) {
        snek->direction = DOWN;
    } else if (actions.moveRight && (snek->direction == UP || snek->direction == DOWN)) {
        snek->direction = RIGHT;
    } else if (actions.moveLeft && (snek->direction == UP || snek->direction == DOWN)) {
        snek->direction = LEFT;
    }

    // Move each tail piece up
    for (int i = snek->length - 1; i > 0; i--) {
        snek->body[i] = snek->body[i - 1];
    }

    // Move the head based on current direction
    int x = snek->body[0].x,
        y = snek->body[0].y;
    int dx = 0,
        dy = 0;
    switch (snek->direction) {
        case RIGHT:
            dx = 1;
            break;
        case LEFT:
            dx = -1;
            break;
        case UP:
            dy = -1;
            break;
        case DOWN:
            dy = 1;
            break;
    }
    snek->body[0] = { x + dx, y + dy };
}

void Snek::grow(SnekState *snek) {
    // Check if we need to reallocate
    if (snek->length % SNEK_ALLOC_SIZE == 0) {
        snek->body = (Position *)realloc(snek->body, (snek->length + SNEK_ALLOC_SIZE) * sizeof(Position));
        if (snek->body == NULL) {
            fprintf(stderr, "Critical error: Could not allocate memory to grow snek.");
            exit(1);
        }
    }
    // Put new tail on snek and grow length
    // This uses the position of the last 2 tail pieces to spawn the new one
    snek->body[snek->length] = {
        2 * snek->body[snek->length - 1].x - snek->body[snek->length - 2].x,
        2 * snek->body[snek->length - 1].y - snek->body[snek->length - 2].y};
    snek->length++;
}

void Snek::draw(SnekState *snek, int scale) {
    // Set render color for this snek
    SDL_Color color = PLAYER_COLORS[snek->playerNum];
    SDL_SetRenderDrawColor(global::renderer, color.r, color.g, color.b, color.a);

    // Draw body pieces of the snek
    for (size_t i = 0; i < snek->length; i++) {
        Position pos = snek->body[i];
        SDL_Rect body = { pos.x * scale, pos.y * scale, scale, scale };
        SDL_RenderDrawRect(global::renderer, &body);
    }
}

void Snek::free(SnekState *snek) {
    // Free the snake body
    free(snek->body);
    // Null the body pointer to prevent reuse
    snek->body = NULL;
}