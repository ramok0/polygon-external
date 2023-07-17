#pragma once
#include <cache.hpp>
#include <ue4.hpp>

#include <functional>

namespace overlay {
	void draw_tracers(Entity_t ent);

	namespace esp {
		void draw_2d_bounding(Entity_t ent);
		void draw_2d_corner(Entity_t ent);
		void draw_2d(Entity_t ent);
		void draw_3d(Entity_t ent);
		void draw_player_name(Entity_t* ent);
		void draw_weapon_name(Entity_t* ent);
		void draw_health(Entity_t* ent);
		void draw_skeleton(Entity_t ent);
		void draw_filled(ImVec2 top, ImVec2 bottom);
		void draw_filled(Vector2Float top, Vector2Float bottom);

		std::function<void(Entity_t)> get_method(void);
	}

	void draw(void);
}