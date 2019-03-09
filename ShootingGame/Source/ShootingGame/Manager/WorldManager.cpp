#include "WorldManager.h"

void UWorldManager::AddFieldObject(AFieldObject* fdObject)
{
	auto& objs = _fieldObjects.FindOrAdd(fdObject->GetType());
	objs.Add(fdObject);
}

void UWorldManager::SelectFieldObjects(EFieldObjectType type, TArray<AFieldObject*>& outArray, FFdObjectSelector&& selector)
{
	auto& targetObjs = _fieldObjects.FindOrAdd(type);
	for (auto& obj : targetObjs) {		
		if (selector.Execute(obj) == true) {
			outArray.Add(obj);
		}
	}
}