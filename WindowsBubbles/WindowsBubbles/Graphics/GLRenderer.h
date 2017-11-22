#pragma once

class GLRenderer {
	
public:
	GLRenderer() = default;

	void init(const unsigned width, const unsigned height);
	void update();

	void resize(const unsigned width, const unsigned height);

private:
};