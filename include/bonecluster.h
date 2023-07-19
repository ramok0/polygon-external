#pragma once
#include <vectortypes.h>
#include <wrappers.h>
#include <memory>
#include <stdexcept>

class USkeletalMeshComponent;

class BoneCluster {
public:
	BoneCluster() {
		this->m_count = 0;
		this->m_data = nullptr;
	}

	BoneCluster(const BoneCluster& other)
		: m_count(other.m_count),
		m_data(new FTransform[other.m_count])
	{
		std::memcpy(m_data.get(), other.m_data.get(), sizeof(FTransform) * m_count);
	}

	BoneCluster& operator=(const BoneCluster& other)
	{
		if (this != &other)
		{
			m_count = other.m_count;
			m_data = std::unique_ptr<FTransform[]>(new FTransform[m_count]);
			std::memcpy(m_data.get(), other.m_data.get(), sizeof(FTransform) * m_count);
		}
		return *this;
	}

	BoneCluster(USkeletalMeshComponent* Mesh)
	{
		auto array = Mesh->get_bone_array();
		if (!array)
		{
			this->m_count = 0;
			this->m_data = nullptr;
		}
		else {
			this->m_count = array.value().Count;

			FTransform* el = array->read_every_elements();

			this->m_data = std::unique_ptr<FTransform[]>(new FTransform[this->m_count]);
			std::memcpy(this->m_data.get(), el, sizeof(FTransform) * this->m_count);

			delete[] el;
		}
	}

	int size() const {
		return this->m_count;
	}

	FTransform operator[](int Index) {
		if (Index > size()) {
			throw std::runtime_error("Not existing element");
		}

		return this->m_data[Index];
	}

private:
	int m_count;
	std::unique_ptr<FTransform[]> m_data;
};