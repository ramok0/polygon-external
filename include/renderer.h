#pragma once
#include <cache.h>
#include <singleton.h>
#include <string>

class EntityRenderer {
public:
	EntityRenderer(std::string name) {
		this->m_name = name;
	}

	std::string get_name() { return this->m_name; };

	virtual ~EntityRenderer() {}
	virtual void render(Entity_t& entity) = 0;
	virtual bool* get_toggle_ptr(void) = 0;

	void draw(Entity_t& ent) {
		if (is_enabled())
			render(ent);
	}

	bool is_enabled() {
		return *get_toggle_ptr() == true;
	}

protected:
	std::string m_name;
	std::vector<std::unique_ptr<EntityRenderer>> misc_features;
};