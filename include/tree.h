#pragma once
#include <vector>
#include <memory>

struct SDL_Renderer;

class Branch {
public:
	Branch();

	void draw(SDL_Renderer *renderer, int x, int y, float parent_angle);
	void grow(int depth);
private:
	std::vector<std::unique_ptr<Branch>> children;
	int children_count;
	float length;
	float max_length;
	float angle;
};

class Tree {
public:
	Tree();

	void draw(SDL_Renderer *renderer);
	void grow();
private:
	std::unique_ptr<Branch> root = nullptr;
	int max_depth;
};

