#include <overlay.hpp>
#include <skeleton.h>
#include <imgui/imgui_internal.h>
#include <map>

void DrawCorneredBox(float X, float Y, float W, float H, ImColor lineColor, float thickness) {
	float lineW = W / 3;
	float lineH = H / 3;

	ImDrawList* DrawList = ImGui::GetBackgroundDrawList();

	// Lignes extérieures
	DrawList->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), lineColor, thickness);
	DrawList->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), lineColor, thickness);
	DrawList->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), lineColor, thickness);
	DrawList->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), lineColor, thickness);
	DrawList->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), lineColor, thickness);
	DrawList->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), lineColor, thickness);
	DrawList->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), lineColor, thickness);
	DrawList->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), lineColor, thickness);

	// Lignes intérieures
	lineColor = ImColor(1.f / 255, 1.f / 255, 1.f / 255, 1.f);
	DrawList->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), lineColor, 3.f);
}

void overlay::esp::draw_2d_bounding(Entity_t ent)
{
	if (!config::config->data()->esp) return;
	FBoxSphereBounds bounds = ent.RootComponent->get_cached_bounds();

	Vector3 topRight = bounds.Origin - bounds.BoxExtent;
	Vector3 bottomLeft = bounds.Origin + bounds.BoxExtent;

	Vector2Float screen_bottom_left = world_to_screen(bottomLeft);
	Vector2Float screen_top_right = world_to_screen(topRight);

	esp::draw_filled(screen_top_right, screen_bottom_left);

	float* esp_color = config::config->data()->esp_color;
	ImColor color = config::config->data()->vis_check && ent.is_visible ? get_color_from_float_array(config::config->data()->esp_visible_color) : get_color_from_float_array(esp_color);

	ImGui::GetBackgroundDrawList()->AddRect({ screen_top_right.x, screen_top_right.y }, { screen_bottom_left.x, screen_bottom_left.y }, color);
}

void overlay::esp::draw_2d_corner(Entity_t ent)
{
	if (!config::config->data()->esp) return;
	Vector3 headPos = ent.get_bone_with_rotation(Bones::Head);
	if (!headPos) return;
	Vector3 bottomPos = ent.get_bone_with_rotation(Bones::Root);
	if (!bottomPos) return;
	Vector2Float headBox = world_to_screen({ headPos.x, headPos.y, headPos.z + 5 });
	Vector2Float headLoc = world_to_screen(headPos);
	Vector2Float bottomLoc = world_to_screen(bottomPos);

	if (!headBox || !headLoc || !bottomLoc) return;

	float BoxHeight = (float)(headBox.y - bottomLoc.y);
	float BoxWidth = BoxHeight * BOX_REDUCTION_FACTOR;

	float CornerHeight = abs(headBox.y - bottomLoc.y);
	float CornerWidth = CornerHeight * 0.75f;
	float X = headBox.x - (CornerWidth / 2);

	esp::draw_filled({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight));

	float* esp_color = config::config->data()->esp_color;

	ImColor color = config::config->data()->vis_check && ent.is_visible ? get_color_from_float_array(config::config->data()->esp_visible_color) : get_color_from_float_array(esp_color);

	DrawCorneredBox(headBox.x - (CornerWidth / 2), headBox.y, CornerWidth, CornerHeight, color, 1.5f);
}

void overlay::esp::draw_2d(Entity_t ent)
{
	if (!config::config->data()->esp) return;

	Vector3 headPos = ent.get_bone_with_rotation(Bones::Head);
	if (!headPos) return;

	Vector3 bottomPos = ent.get_bone_with_rotation(Bones::Root);
	if (!bottomPos) return;

	Vector2Float headBox = world_to_screen({ headPos.x, headPos.y, headPos.z + 5 });
	if (!headBox) return;
	Vector2Float bottomLoc = world_to_screen(bottomPos);
	if (!bottomLoc) return;

	float CornerHeight = abs(headBox.y - bottomLoc.y);
	float CornerWidth = CornerHeight * 0.75f;

	float X = headBox.x - (CornerWidth / 2);

	esp::draw_filled({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight));

	float* esp_color = config::config->data()->esp_color;
	ImColor color = config::config->data()->vis_check && ent.is_visible ? get_color_from_float_array(config::config->data()->esp_visible_color) : get_color_from_float_array(esp_color);

	ImGui::GetBackgroundDrawList()->AddRect({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), color);
}

void overlay::esp::draw_3d(Entity_t ent)
{
	if (!config::config->data()->esp) return;
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	FBoxSphereBounds EntityBounds = ent.RootComponent->get_cached_bounds();

	Vector3 bottomRight = EntityBounds.Origin - EntityBounds.BoxExtent;
	Vector3 topRight = EntityBounds.Origin + EntityBounds.BoxExtent;
	// Top box
	Vector3 topFrontLeft = Vector3(bottomRight.x, topRight.y, bottomRight.z);
	Vector3 topFrontRight = Vector3(topRight.x, topRight.y, bottomRight.z);
	Vector3 topBackLeft = Vector3(bottomRight.x, topRight.y, topRight.z);

	// Bottom box
	Vector3 bottomBackRight = Vector3(topRight.x, bottomRight.y, topRight.z);
	Vector3 bottomBackLeft = Vector3(topRight.x, bottomRight.y, bottomRight.z);
	Vector3 bottomFrontRight = Vector3(bottomRight.x, bottomRight.y, topRight.z);

	Vector2Float bottomRightScreen = world_to_screen(bottomRight);
	Vector2Float topRightScreen = world_to_screen(topRight);
	Vector2Float topFrontLeftScreen = world_to_screen(topFrontLeft);
	Vector2Float topFrontRightScreen = world_to_screen(topFrontRight);
	Vector2Float topBackLeftScreen = world_to_screen(topBackLeft);
	Vector2Float bottomBackRightScreen = world_to_screen(bottomBackRight);
	Vector2Float bottomBackLeftScreen = world_to_screen(bottomBackLeft);
	Vector2Float bottomFrontRightScreen = world_to_screen(bottomFrontRight);

	float* esp_color = config::config->data()->esp_color;
	ImColor color = config::config->data()->vis_check && ent.is_visible ? get_color_from_float_array(config::config->data()->esp_visible_color) : get_color_from_float_array(esp_color);

	if (topFrontLeftScreen.x || topFrontLeftScreen.y) {
		esp::draw_filled(topRightScreen, bottomRightScreen);

		drawList->AddLine({ bottomRightScreen.x, bottomRightScreen.y }, { bottomFrontRightScreen.x, bottomFrontRightScreen.y }, color);
		drawList->AddLine({ bottomRightScreen.x, bottomRightScreen.y }, { bottomBackLeftScreen.x,bottomBackLeftScreen.y }, color);
		drawList->AddLine({ bottomBackRightScreen.x, bottomBackRightScreen.y }, { bottomBackLeftScreen.x,bottomBackLeftScreen.y }, color);
		drawList->AddLine({ bottomBackRightScreen.x, bottomBackRightScreen.y }, { bottomFrontRightScreen.x,bottomFrontRightScreen.y }, color);

		drawList->AddLine({ topFrontLeftScreen.x,topFrontLeftScreen.y }, { topBackLeftScreen.x,topBackLeftScreen.y }, color);
		drawList->AddLine({ topFrontLeftScreen.x,topFrontLeftScreen.y }, { topFrontRightScreen.x, topFrontRightScreen.y }, color);
		drawList->AddLine({ topRightScreen.x,topRightScreen.y }, { topFrontRightScreen.x, topFrontRightScreen.y }, color);
		drawList->AddLine({ topRightScreen.x, topRightScreen.y }, { topBackLeftScreen.x,topBackLeftScreen.y }, color);

		drawList->AddLine({ bottomFrontRightScreen.x, bottomFrontRightScreen.y }, { topBackLeftScreen.x,topBackLeftScreen.y }, color);
		drawList->AddLine({ bottomRightScreen.x,bottomRightScreen.y }, { topFrontLeftScreen.x, topFrontLeftScreen.y }, color);
		drawList->AddLine({ bottomBackRightScreen.x,bottomBackRightScreen.y }, { topRightScreen.x, topRightScreen.y }, color);
		drawList->AddLine({ bottomBackLeftScreen.x, bottomBackLeftScreen.y }, { topFrontRightScreen.x, topFrontRightScreen.y }, color);
	}

}

void overlay::esp::draw_player_name(Entity_t* ent)
{
	if (!config::config->data()->esp || !config::config->data()->esp_player_name) return;
	float* player_name_color = config::config->data()->esp_player_name_color;
	/*SAFE_W2S(ent.Mesh, root_screen, Bones::Root);*/

	Vector3 root_world_loc = ent->get_bone_with_rotation(Bones::Root);
	if (!root_world_loc) return;

	Vector2Float root_screen = world_to_screen(root_world_loc);
	if (!root_screen) return;

	ImVec2 text_size = ImGui::CalcTextSize(ent->player_name.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(root_screen.x - (text_size.x / 2), root_screen.y + ent->current_text_offset), get_color_from_float_array(player_name_color), ent->player_name.c_str());
	ent->current_text_offset = ent->current_text_offset + 14;
}

void overlay::esp::draw_weapon_name(Entity_t* ent)
{
	float* player_name_color = config::config->data()->esp_player_name_color;

	Vector3 root_world_loc = ent->get_bone_with_rotation(Bones::Root);
	if (!root_world_loc) return;

	Vector2Float root_screen = world_to_screen(root_world_loc);
	if (!root_screen) return;

	ImVec2 text_size = ImGui::CalcTextSize(ent->weapon_name.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(root_screen.x - (text_size.x / 2), root_screen.y + ent->current_text_offset), get_color_from_float_array(player_name_color), ent->weapon_name.c_str());
	ent->current_text_offset = ent->current_text_offset + 13;
}

void overlay::esp::draw_health(Entity_t* ent)
{
	if (!config::config->data()->esp_health_text && !config::config->data()->esp_health_box) return;
	float Health = (float)ent->HealthComponentData.Health;

	float red = (100.f - Health) * 255.f / 100.f;
	float green = Health * 255.f / 100.f;
	
	ImColor color = ImColor(red, green, 0.f, 1.0f);

	Vector3 root_world_loc = ent->get_bone_with_rotation(Bones::Root);
	if (!root_world_loc) return;

	Vector2Float root_screen = world_to_screen(root_world_loc);
	if (!root_screen) return;

	if (config::config->data()->esp_health_box)
	{
		Vector3 headPos = ent->get_bone_with_rotation(Bones::Head);
		if (!headPos) return;

		Vector2Float headBox = world_to_screen({ headPos.x, headPos.y, headPos.z + 5 });
		if (!headBox) return;

		float CornerHeight = abs(headBox.y - root_screen.y); //hauteur
		float CornerWidth = CornerHeight * 0.75f; // width = hauteur / 0.75 (pour avoir une width constante ??)

		float X = (headBox.x - (CornerWidth / 2)); //coordonnée de la boite en haut (ajoute environ une demi box pour la width)

		float width = CornerWidth / 1.6f;
		float SizeOfHealthBar = headBox.y;
		float EndOfHealthBar = headBox.y + CornerHeight;
		float SizeOfHealthBarScaled = (CornerHeight / 100) * Health;
		ImGui::GetBackgroundDrawList()->AddRect({ ((float)X - (CornerWidth / 10)) + 1, (float)headBox.y + 1.f }, ImVec2((X - (width - (CornerWidth / 10))) - 1.f, (EndOfHealthBar)-1.f), ImColor(0, 0, 0, 255), 0, 0, 1.2f);
		ImGui::GetBackgroundDrawList()->AddRectFilled({ (float)X - (CornerWidth / 10), EndOfHealthBar - SizeOfHealthBarScaled }, ImVec2(X - (width - (CornerWidth / 10)), EndOfHealthBar), color);

	}

	if (config::config->data()->esp_health_text)
	{
		std::string data = std::to_string((int)ent->HealthComponentData.Health) + " HP";

		ImVec2 text_size = ImGui::CalcTextSize(data.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(root_screen.x - (text_size.x / 2), root_screen.y + ent->current_text_offset), color, data.c_str());
		ent->current_text_offset = ent->current_text_offset + 14;
	}
}

void overlay::esp::draw_skeleton(Entity_t ent)
{
	auto& configData = *config::config->data();
	if (!configData.esp || !configData.skeleton_esp)
		return;

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	float* skeleton_color = configData.skeleton_esp_color;
	float skeleton_thickness = configData.skeleton_thickness;

	ImColor SkeletonColor = get_color_from_float_array(skeleton_color);

	for (BoneConnection connection : config::config->data()->esp_skeleton_full ? bone_connections : light_bone_connections) {
		Vector2Float firstBoneScreen;
		Vector2Float secondBoneScreen;

		Vector3 bone_loc = ent.get_bone_with_rotation(connection.first);
		if (!bone_loc) continue;
		firstBoneScreen = world_to_screen(bone_loc);
		if (!firstBoneScreen) {
			continue;
		}

		bone_loc = ent.get_bone_with_rotation(connection.second);
		if (!bone_loc) continue;
		secondBoneScreen = world_to_screen(bone_loc);
		if (!secondBoneScreen) {

			continue;
		}

		if (config::config->data()->esp_skeleton_bezier)
		{
			// Calcul des points de contrôle pour la courbe de Bézier
			ImVec2 p0 = ImVec2(firstBoneScreen.x, firstBoneScreen.y);
			ImVec2 p3 = ImVec2(secondBoneScreen.x, secondBoneScreen.y);
			float control_distance = std::sqrtf(std::powf(p3.x - p0.x, 2.f) + std::powf(p3.y - p0.y, 2.f)) * 0.33f;
			ImVec2 p1 = ImVec2(p0.x + control_distance, p0.y);
			ImVec2 p2 = ImVec2(p3.x - control_distance, p3.y);

			// Dessin de la courbe de Bézier
			int num_segments = config::config->data()->num_of_bezier_segments;
			const float t_step = 1.0f / num_segments;
			for (int i = 0; i < num_segments; ++i) {
				float t0 = i * t_step;
				float t1 = (i + 1) * t_step;
				ImVec2 p_start = ImBezierCubicCalc(p0, p1, p2, p3, t0);
				ImVec2 p_end = ImBezierCubicCalc(p0, p1, p2, p3, t1);
				draw_list->AddLine(p_start, p_end, SkeletonColor, skeleton_thickness);
			}
		}
		else {
			draw_list->AddLine(ImVec2(firstBoneScreen.x, firstBoneScreen.y), ImVec2(secondBoneScreen.x, secondBoneScreen.y), SkeletonColor, skeleton_thickness);
		}
	}
}

void overlay::esp::draw_filled(ImVec2 top, ImVec2 bottom)
{
	if (!config::config->data()->esp_filled)
		return;

	float* esp_filled_color = config::config->data()->esp_filled_color;
	ImColor color = get_color_from_float_array(esp_filled_color);
	ImGui::GetBackgroundDrawList()->AddRectFilled(top, bottom, color);
}

void overlay::esp::draw_filled(Vector2Float top, Vector2Float bottom)
{
	return draw_filled(ImVec2(top.x, top.y), ImVec2(bottom.x, bottom.y));
}

std::function<void(Entity_t)> overlay::esp::get_method(void)
{
	switch (config::config->data()->esp_mode) {
	case ESP_2D:
		return draw_2d;
		break;
	case ESP_2DBOUNDING:
		return draw_2d_bounding;
		break;
	case ESP_2DCORNER:
		return draw_2d_corner;
		break;
	case ESP_3D:
		return draw_3d;
		break;
	}

	return draw_2d;
}
