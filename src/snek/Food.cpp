#include "Food.h"

void Food::draw(FoodState *food, int scale) {
    SDL_Rect rect = { food->pos.x * scale, food->pos.y * scale, scale, scale };
    SDL_RenderFillRect(global::renderer, &rect);
}