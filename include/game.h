#pragma once
typedef int offset;

namespace offsets {
	inline offset world = 0x7FE3C50;
	inline offset names = 0x7DE4500;
	inline offset objects = 0x7E8ABB0;
	inline offset bone_array = 0x600;
	inline offset component_to_world = 0x240;
	inline offset ref_skeleton = 0x2E0;
	inline offset FinalRefBoneInfo = 0x20;

	inline offset ustruct_childproperties = 0x50;

	inline offset ffield_name = 0x28;
	inline offset ffield_next = 0x20;

	inline offset fproperty_offset = 0x4C;
}

enum Bones {
    Root = 0,
    ik_foot_root = 1,
    ik_foot_l = 2,
    ik_foot_r = 3,
    ik_hand_root = 4,
    ik_hand_gun = 5,
    ik_hand_l = 6,
    ik_hand_r = 7,
    pelvis = 8,
    spine_01 = 9,
    spine_02 = 10,
    spine_03 = 11,
    clavicle_l = 12,
    upperarm_l = 13,
    lowerarm_l = 14,
    hand_l = 15,
    index_metacarpal_l = 16,
    index_01_l = 17,
    index_02_l = 18,
    index_03_l = 19,
    middle_metacarpal_l = 20,
    middle_01_l = 21,
    middle_02_l = 22,
    middle_03_l = 23,
    pinky_metacarpal_l = 24,
    pinky_01_l = 25,
    pinky_02_l = 26,
    pinky_03_l = 27,
    ring_metacarpal_l = 28,
    ring_01_l = 29,
    ring_02_l = 30,
    ring_03_l = 31,
    thumb_01_l = 32,
    thumb_02_l = 33,
    thumb_03_l = 34,
    lowerarm_twist_01_l = 35,
    upperarm_twist_01_l = 36,
    clavicle_r = 37,
    upperarm_r = 38,
    lowerarm_r = 39,
    hand_r = 40,
    index_metacarpal_r = 41,
    index_01_r = 42,
    index_02_r = 43,
    index_03_r = 44,
    middle_metacarpal_r = 45,
    middle_01_r = 46,
    middle_02_r = 47,
    middle_03_r = 48,
    pinky_metacarpal_r = 49,
    pinky_01_r = 50,
    pinky_02_r = 51,
    pinky_03_r = 52,
    ring_metacarpal_r = 53,
    ring_01_r = 54,
    ring_02_r = 55,
    ring_03_r = 56,
    thumb_01_r = 57,
    thumb_02_r = 58,
    thumb_03_r = 59,
    lowerarm_twist_01_r = 60,
    upperarm_twist_01_r = 61,
    neck_01 = 62,
    Head = 63,
    thigh_l = 64,
    calf_l = 65,
    calf_twist_01_l = 66,
    foot_l = 67,
    ball_l = 68,
    thigh_twist_01_l = 69,
    thigh_r = 70,
    calf_r = 71,
    calf_twist_01_r = 72,
    foot_r = 73,
    ball_r = 74,
    thigh_twist_01_r = 75,
    camera_bone = 76,
    VB_CarryingWeaponSocket = 77,
    VB_Watch = 78
};