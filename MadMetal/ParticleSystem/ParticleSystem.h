#pragma once
#include "ParticleEmitter.h"
#include "ParticleUpdater.h"
#include "Objects\RenderableObject.h"

class ParticleSystem : public RenderableObject	
{
private:
	
	GLuint m_bufPos;
	GLuint m_bufCol, m_bufNorm;
	ParticleEmitter emitter;
	std::vector<ParticleUpdater *> updaters;
	size_t m_currentTime;
	
	

public:
	ParticleData * p;
	GLuint m_vao;
	ParticleSystem(size_t count){
		
		p = new ParticleData(count);
		emitter.m_emitRate = 1000;

		PositionGenerator * posGenerator = new PositionGenerator();
		posGenerator->m_pos = glm::vec4(0, -.5, 0, 1);
		posGenerator->m_maxStartPosOffset = glm::vec4(0, 0, 0, 1);
		//emitter.addGenerator(posGenerator);

		CirclePositionGenerator * cposGenerator = new CirclePositionGenerator();
		cposGenerator->m_pos = glm::vec4(0, -.5, 0, 1);
		cposGenerator->m_radius = 3;
		cposGenerator->m_randomStart = true;
		emitter.addGenerator(cposGenerator);

		VelocityGenerator * velGenerator = new VelocityGenerator();
		velGenerator->m_minStartVel = glm::vec4(-.2,.2, 0, 0);
		velGenerator->m_maxStartVel = glm::vec4(.2,.4, 0, 0);
		//emitter.addGenerator(velGenerator);

		TimeGenerator * timeGenerator = new TimeGenerator();
		timeGenerator->m_minStartTime = 5.5;
		timeGenerator->m_maxStartTime = 7;
		emitter.addGenerator(timeGenerator);

		ColorGenerator * colorGenerator = new ColorGenerator();
		colorGenerator->m_minStartColor = glm::vec3(1, .5, 0);
		colorGenerator->m_maxStartColor = glm::vec3(1, 1, 0);
		colorGenerator->m_minEndColor = glm::vec3(0, 0, 0);
		colorGenerator->m_maxEndColor = glm::vec3(0.2, 0.2, 0.2);
		emitter.addGenerator(colorGenerator);

		NormalGenerator * normGenerator = new NormalGenerator();
		normGenerator->m_startNorm = glm::vec3(0, 1, 1);
		emitter.addGenerator(normGenerator);


		PositionUpdater * posUpdater = new PositionUpdater();
		posUpdater->m_globalAcc = glm::vec4(0, .2, 0, 0);
		updaters.push_back(posUpdater);

		TimeUpdater* timeUpdater = new TimeUpdater();
		updaters.push_back(timeUpdater);

		AttractorUpdater * attractUpdater = new AttractorUpdater();
		attractUpdater->m_pos = glm::vec4(0, 0, 0, 1);
		attractUpdater->m_radius = 0.2;
		//updaters.push_back(attractUpdater);

		ColorUpdater * colorUpdater = new ColorUpdater();
		updaters.push_back(colorUpdater);

		
	}
	~ParticleSystem(){}

	void initSystem(size_t time)
	{
		m_currentTime = time;
		const size_t count = p->m_count;
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		glGenBuffers(1, &m_bufPos);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 4 * count, &p->m_pos[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4)*sizeof(float), (void *)((0)*sizeof(float)));


		glGenBuffers(1, &m_bufCol);

		glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * count, &p->m_pos[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3)*sizeof(float), (void *)((0)*sizeof(float)));

		glGenBuffers(1, &m_bufNorm);

		glBindBuffer(GL_ARRAY_BUFFER, m_bufNorm);
		


		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * count, &p->m_norm[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (3)*sizeof(float), (void *)((0)*sizeof(float)));

		
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


	void update(size_t newTime)
	{
		double dt = ((double)(newTime - m_currentTime)) / 1000;
		m_currentTime = newTime;
		emitter.emit(dt, p);
		for (auto &updater : updaters)
		{
			updater->update(dt, p);
		}
		

		const size_t count = p->m_count;

		if (count > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufPos);
			float *ptr = (float *)(p->m_pos.get());
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 4 * count, ptr, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, m_bufCol);
			ptr = (float*)(p->m_col.get());
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * count, ptr, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, m_bufNorm);
			ptr = (float*)(p->m_norm.get());
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * count, ptr, GL_STATIC_DRAW);

			

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
	}

};