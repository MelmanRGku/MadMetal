#pragma once

#define LOADING_BAR_BORDER_SIZE  0.2f

class LoadingBar
{
private:
	float percentageDone;
public:
	LoadingBar(glm::vec3 size, glm::vec3 position, Model *completeBarModel);
	~LoadingBar();
	void setPercentage(float percentage);
	void draw(Renderer *renderer);
	void setProgress(float percentage);
};

