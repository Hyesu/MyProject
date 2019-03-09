#pragma once

#include "CoreMinimal.h"
#include "FieldObject/FieldObject.h"
#include "WorldManager.generated.h"

UCLASS()
class SHOOTINGGAME_API UWorldManager : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_RetVal_OneParam(bool, FFdObjectSelector, AFieldObject*);

	void AddFieldObject(AFieldObject* fdObject);
	void SelectFieldObjects(EFieldObjectType type, TArray<AFieldObject*>& outArray, FFdObjectSelector&& selector);

private:
	TMap<EFieldObjectType, TArray<AFieldObject*>> _fieldObjects;
};