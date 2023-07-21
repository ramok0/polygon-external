#pragma once
#include <renderer.h>
#include <game.h>
#include <config.h>
#include <imgui/imgui.h>

class HeadCircle : public EntityRenderer, public Singleton<HeadCircle> {
public:
	HeadCircle() : EntityRenderer("ESP") {
		//initialiser les sous options

	};

	void render(Entity_t& ent) override {
		Vector3 headPos = ent.get_bone_with_rotation(Bones::Head);
		if (!headPos) return;
		
		Vector3 bottomPos = ent.get_bone_with_rotation(Bones::Root);
		if (!bottomPos) return;

		Vector2Float headBox = world_to_screen(headPos);
		if (!headBox) return;
		Vector2Float bottomLoc = world_to_screen(bottomPos);
		if (!bottomLoc) return;

		float CornerWidth = abs(headBox.y - bottomLoc.y) * 0.75f;

		ImGui::GetBackgroundDrawList()->AddCircle({headBox.x, headBox.y}, CornerWidth * 0.15f, ImColor(255, 0, 0), (int)(CornerWidth * 0.2f), config::config->data()->skeleton_thickness);
	}

	bool* get_toggle_ptr() override {
		return &config::config->data()->head_circle;
	}
};