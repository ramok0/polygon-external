#include "bonecluster.h"
#include <wrappers.h>

void BoneCluster::initialize_array(USkeletalMeshComponent* Mesh)
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
