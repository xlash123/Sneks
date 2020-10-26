#include "Food.h"

void Food::draw(FoodState *food) {
    SDL_Color color = FOOD_COLOR;
    SDL_SetRenderDrawColor(global::renderer, color.r, color.g, color.b, color.a);

    SDL_Rect rect = { food->pos.x, food->pos.y, 1, 1 };
    SDL_RenderFillRect(global::renderer, &rect);
}