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

void Snek::update(SnekState *snek) {
    // Get the players actions for this frame
    PlayerActions actions = snek->controller->getPlayerActions();

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
    for (int i = snek->length - 1; i > 0; i++) {
        snek->body[i] = snek->body[i + 1];
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
    if (snek->length % 100 == 0) {
        snek->body = (Position *)realloc(snek->body, (snek->length + 100) * sizeof(Position));
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

void Snek::draw(SnekState *snek) {
    // Set render color for this snek
    SDL_Color color = PLAYER_COLORS[snek->playerNum];
    SDL_SetRenderDrawColor(global::renderer, color.r, color.g, color.b, color.a);
    // Draw body pieces of the snek
    for (size_t i = 0; i < snek->length; i++) {
        Position pos = snek->body[i];
        SDL_Rect body = { pos.x, pos.y, 1, 1 };
        SDL_RenderDrawRect(global::renderer, &body);
    }
}