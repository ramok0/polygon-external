#pragma once
#include <names.h>
#include <cstdint>
#include <vector>
#include <memory>
#define M_PI       3.14159265358979323846
#define DEG_TO_RAD 0.01745329251994329576924
#define DEG_TO_RAD2 0.008726646259971647884619
#define DEG_TO_RAD3 57.2957795130823208768

template <typename T>
struct TArray {
	T* Data;
	__int32 Count;
	__int32 Max;

	T operator[](int index) {
		T buffer;

		if (!driver::read((uintptr_t)Data + (sizeof(T) * index), (uintptr_t)&buffer, sizeof(T))) {
			return T{ 0 };
		}

		return buffer;
	}

	T get(int Index, size_t size) {
		T buffer;

		if (!driver::read((uintptr_t)Data + (size * Index), (uintptr_t)&buffer, sizeof(T))) {
			return T{ 0 };
		}

		return buffer;
	}

	T* read_every_elements() {
		T* bufferData = new T[Count];

		if (!driver::read((uintptr_t)Data, (uintptr_t)bufferData, (uintptr_t)(sizeof(T) * Count)))
		{
			delete[] bufferData;
			return nullptr;
		}

		return bufferData;
	}
};

struct FString : TArray<wchar_t> {
	std::string to_string()
	{
		if (!Data || Count == 0) return std::string();
		wchar_t buf[1024];

		if (!driver::read((uintptr_t)Data, (uintptr_t)buf, this->Count * 2ull))
		{
			return std::string();
		}

		//std::wstring wStr;
		//wStr.assign(buf, sizeof(buf));
		//wStr.resize(this->Count);

		int bufferSize = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
		char* narrowString = new char[bufferSize];
		WideCharToMultiByte(CP_ACP, 0, buf, -1, narrowString, bufferSize, NULL, NULL);

		std::string out = std::string(narrowString, bufferSize);

		delete[] narrowString;

		return out;
	}
};

struct Vector3 {
	double x;
	double y;
	double z;

	Vector3 operator-(Vector3 other) const {
		return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
	}

	Vector3 operator+(Vector3 other) {
		return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
	}

	double Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	double Size() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	double Distance(Vector3 Other) const
	{
		return (*this - Other).Size();

		//	return ().Size();
	}

	operator bool() {
		return x != 0 && y != 0 && z != 0;
	}
};

struct Vector2 {
	double x;
	double y;

	operator bool() {
		return x != 0 && y != 0;
	}
};

struct Vector2Float {
	float x;
	float y;

	float Size() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2Float operator-(Vector2Float other) {
		return Vector2Float{
			x - other.x,
			y - other.y
		};
	}

	operator bool() {
		return x != 0 && y != 0;
	}

	float Distance(Vector2Float other) {
		return (*this - other).Size();
	}
};

struct FRotator {
	double Pitch;
	double Yaw;
	double Roll;

	FRotator operator-(FRotator other) {
		return FRotator{
			Pitch - other.Pitch,
			Yaw - other.Yaw,
			Roll - other.Roll
		};
	}

	FRotator clamp() {
		Yaw = fmod(Yaw, 360.0);
		if (Yaw < 0.0)
			Yaw += 360.0;

		if (Pitch < -85.0) {
			Pitch = -85.0;
		}
		else if (Pitch > 85.0) {
			Pitch = 85.0;
		}

		return FRotator(Pitch, Yaw, Roll);
	}

	FRotator operator*(float scalar) {
		return FRotator(Pitch * scalar, Yaw * scalar, Roll);
	}

	FRotator operator+(FRotator other) {
		return FRotator{
			Pitch + other.Pitch,
			Yaw + other.Yaw,
			Roll + other.Roll
		};
	}

	FRotator lerp(FRotator other, float t)
	{

		

		//double LerpedPitch = Pitch + (other.Pitch - Pitch) * Alpha;
		//double LerpedYaw = Yaw + (other.Yaw - Yaw) * Alpha;
		//double LerpedRoll = Roll + (other.Roll - Roll) * Alpha;


		return (*this + (other - *this) * t).clamp();
	}
};

struct FMinimalViewInfo {
	Vector3 Location;
	FRotator Rotation;
	float FOV;
};

struct FCameraCacheEntry {
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	struct FMinimalViewInfo POV; // 0x10(0x7c0)
};

struct FQuat {
	double X; // 0x00(0x08)
	double Y; // 0x08(0x08)
	double Z; // 0x10(0x08)
	double W; // 0x18(0x08)

	operator bool() {
		return X && Y && Z && W;
	}
};

struct FMatrix {
	double M[4][4];

	static FMatrix from_rotator(FRotator rotation) {
		double radPitch = rotation.Pitch * DEG_TO_RAD;
		double radYaw = rotation.Yaw * DEG_TO_RAD;
		double radRoll = rotation.Roll * DEG_TO_RAD;

		double SP = sin(radPitch);
		double CP = cos(radPitch);
		double SY = sin(radYaw);
		double CY = cos(radYaw);
		double SR = sin(radRoll);
		double CR = cos(radRoll);

		FMatrix matrix;

		matrix.M[0][0] = CP * CY;
		matrix.M[0][1] = CP * SY;
		matrix.M[0][2] = SP;
		matrix.M[0][3] = 0;

		matrix.M[1][0] = SR * SP * CY - CR * SY;
		matrix.M[1][1] = SR * SP * SY + CR * CY;
		matrix.M[1][2] = -SR * CP;
		matrix.M[1][3] = 0;

		matrix.M[2][0] = -(CR * SP * CY + SR * SY);
		matrix.M[2][1] = CY * SR - CR * SP * SY;
		matrix.M[2][2] = CR * CP;
		matrix.M[2][3] = 0;

		matrix.M[3][0] = 0;
		matrix.M[3][1] = 0;
		matrix.M[3][2] = 0;
		matrix.M[3][3] = 1;

		return matrix;
	}

	FMatrix operator*(FMatrix other)
	{
		FMatrix pOut;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				pOut.M[i][j] = 0;
				for (int k = 0; k < 4; k++) {
					pOut.M[i][j] += M[i][k] * other.M[k][j];
				}
			}
		}
		return pOut;
	}
};

struct FTransform {
	struct FQuat Rotation; // 0x00(0x20)
	struct Vector3 Translation; // 0x20(0x18)
	char pad_38[0x8]; // 0x38(0x08)
	struct Vector3 Scale3D; // 0x40(0x18)
	char pad_58[0x8]; // 0x58(0x08)

	//operator bool() {
	//	return false;
	//}

	FMatrix ToMatrixWithScale() const
	{
		FMatrix OutMatrix;
		OutMatrix.M[3][0] = Translation.x;
		OutMatrix.M[3][1] = Translation.y;
		OutMatrix.M[3][2] = Translation.z;

		const double x2 = Rotation.X + Rotation.X;
		const double y2 = Rotation.Y + Rotation.Y;
		const double z2 = Rotation.Z + Rotation.Z;
		{
			const double xx2 = Rotation.X * x2;
			const double yy2 = Rotation.Y * y2;
			const double zz2 = Rotation.Z * z2;

			OutMatrix.M[0][0] = (1.0f - (yy2 + zz2)) * Scale3D.x;
			OutMatrix.M[1][1] = (1.0f - (xx2 + zz2)) * Scale3D.y;
			OutMatrix.M[2][2] = (1.0f - (xx2 + yy2)) * Scale3D.z;
		}
		{
			const double yz2 = Rotation.Y * z2;
			const double wx2 = Rotation.W * x2;

			OutMatrix.M[2][1] = (yz2 - wx2) * Scale3D.z;
			OutMatrix.M[1][2] = (yz2 + wx2) * Scale3D.y;
		}
		{
			const double xy2 = Rotation.X * y2;
			const double wz2 = Rotation.W * z2;

			OutMatrix.M[1][0] = (xy2 - wz2) * Scale3D.y;
			OutMatrix.M[0][1] = (xy2 + wz2) * Scale3D.x;
		}
		{
			const double xz2 = Rotation.X * z2;
			const double wy2 = Rotation.W * y2;

			OutMatrix.M[2][0] = (xz2 + wy2) * Scale3D.z;
			OutMatrix.M[0][2] = (xz2 - wy2) * Scale3D.x;
		}

		OutMatrix.M[0][3] = 0.0f;
		OutMatrix.M[1][3] = 0.0f;
		OutMatrix.M[2][3] = 0.0f;
		OutMatrix.M[3][3] = 1.0f;

		return OutMatrix;
	}
};

struct BoneArray {
	TArray<FTransform> ComponentSpaceTransformsArray[2];
};

struct FMeshBoneInfo
{
	// Bone's name.
	FName Name;

	// INDEX_NONE if this is the root bone. 
	int32_t ParentIndex;
};

struct FBoxSphereBounds {
	struct Vector3 Origin; // 0x00(0x18)
	struct Vector3 BoxExtent; // 0x18(0x18)
	double SphereRadius; // 0x30(0x08)
};
