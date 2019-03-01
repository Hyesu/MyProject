#pragma once

#include "CoreMinimal.h"
#include "ResourceManager.generated.h"

UCLASS()
class SHOOTINGGAME_API UResourceManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	class UStaticMesh* GetMesh(const FName& pathKey);

private:
	UPROPERTY()
	TMap<FName, UStaticMesh*> _meshMap;
};