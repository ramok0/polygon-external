#include <overlay.hpp>
#include <skeleton.h>

#include <map>

void DrawCorneredBox(float X, float Y, float W, float H, const ImColor& lineColor, float thickness) {
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
//	lineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f / 255, 1.f / 255, 1.f / 255, 1.f));
	DrawList->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), lineColor, 3.f);
	DrawList->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), lineColor, 3.f);
}

void overlay::esp::draw_2d_bounding_esp(Entity_t ent)
{
	if (!config::config->data()->esp) return;
	FBoxSphereBounds bounds = ent.RootComponent->get_cached_bounds();

	Vector3 topRight = bounds.Origin - bounds.BoxExtent;
	Vector3 bottomLeft = bounds.Origin + bounds.BoxExtent;

	Vector2Float screen_bottom_left = world_to_screen(bottomLeft);
	Vector2Float screen_top_right = world_to_screen(topRight);

	if (config::config->data()->esp_filled)
	{
		float* esp_filled_color = config::config->data()->esp_filled_color;
		ImGui::GetBackgroundDrawList()->AddRectFilled({ screen_top_right.x, screen_top_right.y }, { screen_bottom_left.x, screen_bottom_left.y }, ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
	}

	float* esp_color = config::config->data()->esp_color;
	ImGui::GetBackgroundDrawList()->AddRect({ screen_top_right.x, screen_top_right.y }, { screen_bottom_left.x, screen_bottom_left.y }, ImColor(esp_color[0], esp_color[1], esp_color[2], esp_color[3]));
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

	if (config::config->data()->esp_filled)
	{
		float* esp_filled_color = config::config->data()->esp_filled_color;
		float X = headBox.x - (CornerWidth / 2);
		ImGui::GetBackgroundDrawList()->AddRectFilled({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
	}

	float* esp_color = config::config->data()->esp_color;

	ImColor color{ esp_color[0], esp_color[1], esp_color[2], esp_color[3] };

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

	if (config::config->data()->esp_filled)
	{
		float* esp_filled_color = config::config->data()->esp_filled_color;
		ImGui::GetBackgroundDrawList()->AddRectFilled({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
	}

	float* esp_color = config::config->data()->esp_color;
	ImColor color{ esp_color[0], esp_color[1], esp_color[2], esp_color[3] };

	ImGui::GetBackgroundDrawList()->AddRect({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), color);
}

void overlay::esp::draw3d_esp(Entity_t ent)
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
	ImColor color = ImColor(esp_color[0], esp_color[1], esp_color[2], esp_color[3]);

	if (topFrontLeftScreen.x || topFrontLeftScreen.y) {
		if (config::config->data()->esp_filled) {
			float* esp_filled_color = config::config->data()->esp_filled_color;
			drawList->AddRectFilled({ topRightScreen.x, topRightScreen.y }, { bottomRightScreen.x, bottomRightScreen.y }, ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
		}

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

void overlay::esp::draw_player_name(Entity_t ent)
{
	if (!config::config->data()->esp || !config::config->data()->esp_player_name) return;
	float* player_name_color = config::config->data()->esp_player_name_color;
	/*SAFE_W2S(ent.Mesh, root_screen, Bones::Root);*/

	Vector3 root_world_loc = ent.get_bone_with_rotation(Bones::Root);
	if (!root_world_loc) return;

	Vector2Float root_screen = world_to_screen(root_world_loc);

	ImVec2 text_size = ImGui::CalcTextSize(ent.player_name.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(root_screen.x - (text_size.x / 2), root_screen.y + 2), ImColor(player_name_color[0], player_name_color[1], player_name_color[2], player_name_color[3]), ent.player_name.c_str());
}

void overlay::esp::draw_skeleton(Entity_t ent)
{
	auto& configData = *config::config->data();
	if (!configData.esp || !configData.skeleton_esp)
		return;

	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	std::map<int, Vector2Float> bone_cache;

	float* skeleton_color = configData.skeleton_esp_color;
	float skeleton_thickness = configData.skeleton_thickness;

	ImColor SkeletonColor = get_color_from_float_array(skeleton_color);

	for (BoneConnection connection : bone_connections) {
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

		draw_list->AddLine(ImVec2(firstBoneScreen.x, firstBoneScreen.y), ImVec2(secondBoneScreen.x, secondBoneScreen.y), SkeletonColor, skeleton_thickness);
	}
}
//
//void overlay::esp::draw_skeleton(Entity_t ent)
//{
//	if (!config::config->data()->esp || !config::config->data()->skeleton_esp) {
//		return;
//	}
//
//
//
//	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
//
//	Bones HeadValue = Bones::Head;
//	Bones RightShoulderValue = Bones::upperarm_r;
//	Bones LeftShoulderValue = Bones::upperarm_l;
//	Bones ChestValue = Bones::spine_03;
//
//	Bones RightStartOfLegValue = Bones::thigh_r;
//	Bones LeftStartOfLegValue = Bones::thigh_l;
//
//	USkeletalMeshComponent* Mesh = ent.Mesh;
//
//
//
//
//	SAFE_W2S(Mesh, HeadPosition, HeadValue);
//	SAFE_W2S(Mesh, NeckPosition, HeadValue - 1);
//	SAFE_W2S(Mesh, RootPosition, Bones::Root);
//
//	SAFE_W2S(Mesh, RightShoulder, RightShoulderValue);
//	SAFE_W2S(Mesh, LeftShoulder, LeftShoulderValue);
//	SAFE_W2S(Mesh, RightElbow, RightShoulderValue + 1);
//	SAFE_W2S(Mesh, LeftElbow, LeftShoulderValue + 1);
//	SAFE_W2S(Mesh, RightArm, RightShoulderValue + 2);
//	SAFE_W2S(Mesh, LeftArm, LeftShoulderValue + 2);
//
//	SAFE_W2S(Mesh, EndPelvis, Bones::pelvis);
//	SAFE_W2S(Mesh, Chest, ChestValue);
//	SAFE_W2S(Mesh, Tummy, ChestValue - 1);
//	SAFE_W2S(Mesh, Pelvis, ChestValue - 2);
//
//	SAFE_W2S(Mesh, RightStartOfLeg, RightStartOfLegValue);
//	SAFE_W2S(Mesh, LeftStartOfLeg, LeftStartOfLegValue);
//	SAFE_W2S(Mesh, RightKnee, RightStartOfLegValue + 1);
//	SAFE_W2S(Mesh, LeftKnee, LeftStartOfLegValue + 1);
//	SAFE_W2S(Mesh, RightHeel, RightStartOfLegValue + 2);
//	SAFE_W2S(Mesh, LeftHeel, LeftStartOfLegValue + 2);
//	SAFE_W2S(Mesh, RightToe, RightStartOfLegValue + 3);
//	SAFE_W2S(Mesh, LeftToe, LeftStartOfLegValue + 3);
//
//	float* skeleton_esp_color = config::config->data()->skeleton_esp_color;
//
//	ImColor SkeletonColor = ImColor(skeleton_esp_color[0], skeleton_esp_color[1], skeleton_esp_color[2], skeleton_esp_color[3]);
//	float SkeletonTickens = config::config->data()->skeleton_thickness;
//
//	draw_list->AddLine(ImVec2(HeadPosition.x, HeadPosition.y), ImVec2(NeckPosition.x, NeckPosition.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DE LA TÊTE AU COU
//	draw_list->AddLine(ImVec2(NeckPosition.x, NeckPosition.y), ImVec2(Chest.x, Chest.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU COU AU DÉBUT DE LA POITRINE
//	draw_list->AddLine(ImVec2(Chest.x, Chest.y), ImVec2(Tummy.x, Tummy.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU DÉBUT DE LA POITRINE AU VENTRE
//	draw_list->AddLine(ImVec2(Tummy.x, Tummy.y), ImVec2(EndPelvis.x, EndPelvis.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU VENTRE À L'ENTREJAMBE
//	draw_list->AddLine(ImVec2(EndPelvis.x, EndPelvis.y), ImVec2(RightStartOfLeg.x, RightStartOfLeg.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DE L'ENTREJAMBE AU DÉBUT DE LA JAMBE DROITE
//	draw_list->AddLine(ImVec2(EndPelvis.x, EndPelvis.y), ImVec2(LeftStartOfLeg.x, LeftStartOfLeg.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DE L'ENTREJAMBE AU DÉBUT DE LA JAMBE GAUCHE
//	draw_list->AddLine(ImVec2(RightStartOfLeg.x, RightStartOfLeg.y), ImVec2(RightKnee.x, RightKnee.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU DÉBUT DE LA JAMBE DROITE AU GENOU
//	draw_list->AddLine(ImVec2(LeftStartOfLeg.x, LeftStartOfLeg.y), ImVec2(LeftKnee.x, LeftKnee.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU DÉBUT DE LA JAMBE GAUCHE AU GENOU
//	draw_list->AddLine(ImVec2(RightKnee.x, RightKnee.y), ImVec2(RightHeel.x, RightHeel.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU GENOU AU TALON DROIT
//	draw_list->AddLine(ImVec2(LeftKnee.x, LeftKnee.y), ImVec2(LeftHeel.x, LeftHeel.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU GENOU AU TALON GAUCHE
//	draw_list->AddLine(ImVec2(RightHeel.x, RightHeel.y), ImVec2(RightToe.x, RightToe.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU TALON À L'ORTEIL DROIT
//	draw_list->AddLine(ImVec2(LeftHeel.x, LeftHeel.y), ImVec2(LeftToe.x, LeftToe.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU TALON À L'ORTEIL GAUCHE
//	draw_list->AddLine(ImVec2(NeckPosition.x, NeckPosition.y), ImVec2(RightShoulder.x, RightShoulder.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU COU À L'ÉPAULE DROITE
//	draw_list->AddLine(ImVec2(NeckPosition.x, NeckPosition.y), ImVec2(LeftShoulder.x, LeftShoulder.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU COU À L'ÉPAULE GAUCHE
//	draw_list->AddLine(ImVec2(RightShoulder.x, RightShoulder.y), ImVec2(RightElbow.x, RightElbow.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DE L'ÉPAULE DROITE AU COUDE DROIT
//	draw_list->AddLine(ImVec2(LeftShoulder.x, LeftShoulder.y), ImVec2(LeftElbow.x, LeftElbow.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DE L'ÉPAULE GAUCHE AU COUDE GAUCHE
//	draw_list->AddLine(ImVec2(RightElbow.x, RightElbow.y), ImVec2(RightArm.x, RightArm.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU COUDE DROIT À LA MAIN DROITE
//	draw_list->AddLine(ImVec2(LeftElbow.x, LeftElbow.y), ImVec2(LeftArm.x, LeftArm.y), SkeletonColor, SkeletonTickens); // DESSINE LA LIGNE DU COUDE GAUCHE À LA MAIN GAUCHE
//
//}

std::function<void(Entity_t)> overlay::esp::get_method(void)
{
	switch (config::config->data()->esp_mode) {
	case ESP_2D:
		return draw_2d;
		break;
	case ESP_2DBOUNDING:
		return draw_2d_bounding_esp;
		break;
	case ESP_2DCORNER:
		return draw_2d_corner;
		break;
	case ESP_3D:
		return draw3d_esp;
		break;
	}

	return draw_2d;
}
