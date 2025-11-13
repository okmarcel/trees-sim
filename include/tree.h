#pragma once
#include <vector>
#include <memory>

struct SDL_Renderer;

class Branch {
public:
	Branch();
	Branch(const int max_length);
	Branch(const float angle);

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
	Tree(const int max_depth);

	void draw(SDL_Renderer *renderer);
	void grow();
private:
	std::unique_ptr<Branch> root = nullptr;
	int max_depth;
};

