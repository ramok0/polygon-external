#include <ue4.hpp>

void DrawCorneredBox(float X, float Y, float W, float H, const ImColor& color, float thickness) {
	float lineW = W / 3;
	float lineH = H / 3;

	ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
	ImU32 lineColor = ImGui::ColorConvertFloat4ToU32(color);

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

void overlay::draw_2d_bounding_esp(USceneComponent* RootComponent)
{
	FBoxSphereBounds bounds = RootComponent->get_cached_bounds();

	Vector3 topRight = bounds.Origin - bounds.BoxExtent;
	Vector3 bottomLeft = bounds.Origin + bounds.BoxExtent;

	Vector2Float screen_bottom_left = world_to_screen(bottomLeft);
	Vector2Float screen_top_right = world_to_screen(topRight);

	if (config::config->data()->esp_filled)
	{
		float* esp_filled_color = config::config->data()->esp_filled_color;
		ImGui::GetForegroundDrawList()->AddRectFilled({ screen_top_right.x, screen_top_right.y }, { screen_bottom_left.x, screen_bottom_left.y }, ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
	}

	float* esp_color = config::config->data()->esp_color;
	ImGui::GetForegroundDrawList()->AddRect({ screen_top_right.x, screen_top_right.y }, { screen_bottom_left.x, screen_bottom_left.y }, ImColor(esp_color[0], esp_color[1], esp_color[2], esp_color[3]));
}

void overlay::draw_2d_corner(USkeletalMeshComponent* Mesh, FTransform* bones)
{
	Vector3 headPos = Mesh->get_bone_with_rotation(bones[Bones::Head]);
	Vector3 bottomPos = Mesh->get_bone_with_rotation(bones[Bones::Root]);

	Vector2Float headBox = world_to_screen({ headPos.x, headPos.y, headPos.z + 5 });
	Vector2Float headLoc = world_to_screen(headPos);
	Vector2Float bottomLoc = world_to_screen(bottomPos);

	float BoxHeight = (float)(headBox.y - bottomLoc.y);
	float BoxWidth = BoxHeight * BOX_REDUCTION_FACTOR;

	float CornerHeight = abs(headBox.y - bottomLoc.y);
	float CornerWidth = CornerHeight * 0.75f;

	if (config::config->data()->esp_filled)
	{
		float* esp_filled_color = config::config->data()->esp_filled_color;
		float X = headBox.x - (CornerWidth / 2);
		ImGui::GetForegroundDrawList()->AddRectFilled({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
	}

	float* esp_color = config::config->data()->esp_color;

	ImColor color{ esp_color[0], esp_color[1], esp_color[2], esp_color[3] };

	DrawCorneredBox(headBox.x - (CornerWidth / 2), headBox.y, CornerWidth, CornerHeight, color, 1.5f);
}

void overlay::draw_2d(USkeletalMeshComponent* Mesh, FTransform* bones)
{
	Vector3 headPos = Mesh->get_bone_with_rotation(bones[Bones::Head]);
	Vector3 bottomPos = Mesh->get_bone_with_rotation(bones[Bones::Root]);

	Vector2Float headBox = world_to_screen({ headPos.x, headPos.y, headPos.z + 5 });
	Vector2Float bottomLoc = world_to_screen(bottomPos);

	float CornerHeight = abs(headBox.y - bottomLoc.y);
	float CornerWidth = CornerHeight * 0.75f;

	float X = headBox.x - (CornerWidth / 2);

	if (config::config->data()->esp_filled)
	{
		float* esp_filled_color = config::config->data()->esp_filled_color;
		ImGui::GetForegroundDrawList()->AddRectFilled({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
	}

	float* esp_color = config::config->data()->esp_color;
	ImColor color{ esp_color[0], esp_color[1], esp_color[2], esp_color[3] };

	ImGui::GetForegroundDrawList()->AddRect({ (float)X, (float)headBox.y }, ImVec2(X + CornerWidth, headBox.y + CornerHeight), color);
}

void overlay::draw3d_esp(USceneComponent* RootComponent)
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	FBoxSphereBounds EntityBounds = RootComponent->get_cached_bounds();

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
			ImGui::GetForegroundDrawList()->AddRectFilled({ topRightScreen.x, topRightScreen.y }, { bottomRightScreen.x, bottomRightScreen.y }, ImColor(esp_filled_color[0], esp_filled_color[1], esp_filled_color[2], esp_filled_color[3]));
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

void overlay::draw_player_name(USkeletalMeshComponent* Mesh, FTransform* bones, std::string player_name)
{
	float* player_name_color = config::config->data()->esp_player_name_color;
	Vector3 root_location = Mesh->get_bone_with_rotation(bones[Bones::Root]);
	
	Vector2Float root_screen = world_to_screen(root_location);

	ImVec2 text_size = ImGui::CalcTextSize(player_name.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(root_screen.x - (text_size.x / 2), root_screen.y + 2), ImColor(player_name_color[0], player_name_color[1], player_name_color[2], player_name_color[3]), player_name.c_str());
}
