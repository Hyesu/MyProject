#include "ResourceManager.h"
#include "DataTable/ItemTable.h"
#include "ShootingGame.h"

void UResourceManager::Init()
{
	GetItemTable()->ForEachData([this](const Data* data) {
		const ItemData* itemData = static_cast<const ItemData*>(data);
		FName pathKey = *itemData->meshPath;
		auto it = _meshMap.Find(pathKey);
		if (it == nullptr) {			
			UStaticMesh* mesh = LoadObject<UStaticMesh>(nullptr, *itemData->meshPath, nullptr, LOAD_None, nullptr);
			if (mesh != nullptr) {
				_meshMap.Emplace(pathKey, mesh);
			}	
			else {
				SG_ERROR("Item Mesh not exist: item[%s]", *pathKey.ToString());
			}
		}
	});
}

class UStaticMesh* UResourceManager::GetMesh(const FName& pathKey)
{
	return _meshMap.FindRef(pathKey);
}