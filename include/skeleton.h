#pragma once
#include <game.h>
#include <array>

typedef std::pair<int, int> BoneConnection;

#define CREATE_CONNECTION(start, end) std::make_pair(start, end)

static std::array<BoneConnection, 18> bone_connections = {
	CREATE_CONNECTION(Bones::Head, Bones::neck_01), //HEAD => NECK
	CREATE_CONNECTION(Bones::neck_01, Bones::upperarm_r), //NECK => RIGHT SHOULDER
	CREATE_CONNECTION(Bones::neck_01, Bones::upperarm_l), //NECK => LEFT SHOULDER,
	CREATE_CONNECTION(Bones::upperarm_r, Bones::lowerarm_r), //SHOULDER => ELBOW
	CREATE_CONNECTION(Bones::upperarm_l, Bones::lowerarm_l),//SHOULDER => ELBOW
	CREATE_CONNECTION(Bones::lowerarm_r, Bones::hand_r),//ELBOW => HAND
	CREATE_CONNECTION(Bones::lowerarm_l, Bones::hand_l),//ELBOW => HAND
	CREATE_CONNECTION(Bones::neck_01, Bones::spine_03), //NECK => CHEST
	CREATE_CONNECTION(Bones::spine_03, Bones::spine_02), //CHEST => TUMMY
	CREATE_CONNECTION(Bones::spine_02, Bones::pelvis), //TUMMY => END PELVIS
	CREATE_CONNECTION(Bones::pelvis, Bones::thigh_r), //END PELVIS => Start of right leg,
	CREATE_CONNECTION(Bones::pelvis, Bones::thigh_l), //END PELVIS => Start of left leg,
	CREATE_CONNECTION(Bones::thigh_r, Bones::calf_r), //Start of leg => knee
	CREATE_CONNECTION(Bones::thigh_l, Bones::calf_l), //Start of leg => knee
	CREATE_CONNECTION(Bones::calf_r, Bones::calf_twist_01_r), //Knee => heel
	CREATE_CONNECTION(Bones::calf_l, Bones::calf_twist_01_l), //Knee => heel
	CREATE_CONNECTION(Bones::calf_twist_01_r, Bones::foot_r), //Heel => toe
	CREATE_CONNECTION(Bones::calf_twist_01_l, Bones::foot_l), //Heel => toe
};

static std::array<BoneConnection, 18> light_bone_connections = {
	CREATE_CONNECTION(Bones::Head, Bones::neck_01),
	CREATE_CONNECTION(Bones::neck_01, lowerarm_r),
	CREATE_CONNECTION(Bones::neck_01, lowerarm_l),
	CREATE_CONNECTION(Bones::lowerarm_l, hand_l),
	CREATE_CONNECTION(Bones::lowerarm_r, hand_r),
	CREATE_CONNECTION(Bones::neck_01, Bones::pelvis),
	CREATE_CONNECTION(Bones::pelvis, Bones::foot_r),
	CREATE_CONNECTION(Bones::pelvis, Bones::foot_l),
	//CREATE_CONNECTION(Bones::calf_r, Bones::foot_r),
	//CREATE_CONNECTION(Bones::calf_l, Bones::foot_l)
};