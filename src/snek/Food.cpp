#include "Food.h"

void Food::draw(FoodState *food, float scale) {
    SDL_Rect rect = { (int) (food->pos.x * scale), (int) (food->pos.y * scale), (int) scale, (int) scale };
    SDL_RenderFillRect(global::renderer, &rect);
}