#pragma once
#include <cache.hpp>
#include <ue4.hpp>

#include <functional>

namespace overlay {
	void draw_tracers(Entity_t ent);

	namespace esp {
		void draw_2d_bounding_esp(Entity_t ent);
		void draw_2d_corner(Entity_t ent);
		void draw_2d(Entity_t ent);
		void draw3d_esp(Entity_t ent);
		void draw_player_name(Entity_t ent);
		void draw_skeleton(Entity_t ent);

		std::function<void(Entity_t)> get_method(void);
	}

	void draw(void);
}