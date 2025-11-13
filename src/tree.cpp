#include "tree.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <cstdlib>

#define DEFAULT_MAX_DEPTH 3  // VALUE FOR TESTING
#define DEFAULT_MAX_LENGTH 200
#define GROWTH_INCREMENT 5
#define WHITE_COLOR 255, 255, 255, 255
#define GREEN_COLOR 0, 180, 0, 255;

Branch::Branch() {
	max_length = DEFAULT_MAX_LENGTH;
	length = 0.0f;
	angle = M_PI * 2.0f * (static_cast<float>(rand()) / RAND_MAX - 0.5f);
}
Branch::Branch(const int max_length)
	: max_length(max_length) {
	length = 0.0f;
	angle = M_PI * 2.0f * (static_cast<float>(rand()) / RAND_MAX - 0.5f);
}
Branch::Branch(const float angle)
	: angle(angle) {
	max_length = DEFAULT_MAX_LENGTH;
	length = 0.0f;
}
void Branch::draw(SDL_Renderer *renderer, int x, int y, float parent_angle) {
	float total_angle = angle + parent_angle;
	int x2 = x + length * std::sin(total_angle);
	int y2 = y - length * std::cos(total_angle);

	SDL_SetRenderDrawColor(renderer, WHITE_COLOR);

	SDL_RenderLine(renderer, x, y, x2, y2);

	for (auto& child : children) {
		child->draw(renderer, x2, y2, total_angle);
	}
	
	return;
}
void Branch::grow(int depth) {
	if (length < max_length) {
		length += GROWTH_INCREMENT;
	} else {
		if (depth <= 1) return;
		if (children_count == 0) {
			children_count = 2 + rand() % 2;
			for (int i = 0; i < children_count; i++) {
				auto child = std::make_unique<Branch>();
				children.push_back(std::move(child));
			}
		}
		for (auto& child : children) {
			child->grow(depth - 1);
		}
	}
	return;
}

Tree::Tree() {
	max_depth = DEFAULT_MAX_DEPTH;
	root = std::make_unique<Branch>(0.0f);
}
Tree::Tree(const int max_depth)
	: max_depth(max_depth) {
	root = std::make_unique<Branch>();
}
void Tree::draw(SDL_Renderer *renderer) {
	if (!root) return;
	
	int rwidth, rheight;
	SDL_GetCurrentRenderOutputSize(renderer, &rwidth, &rheight);

	root->draw(renderer, rwidth / 2.0f, rheight, 0.0f); 
}
void Tree::grow() {
	if (!root) return;
	root->grow(max_depth);
	return;
}

