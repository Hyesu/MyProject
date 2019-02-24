#pragma once

#include "CoreMinimal.h"
#include "UIManager.generated.h"

UCLASS()
class SHOOTINGGAME_API UUIManager : public UObject
{
	GENERATED_BODY()

public:
	void Init(UWorld* owner);
	void OpenUI(const FName& pathKey);
	void CloseUI(const FName& pathKey);
	void ToggleUI(const FName& pathKey);

private:
	UWorld* _owner;
	TMap<FName, FSoftClassPath> _pathMap;
	TMap<FName, UUserWidget*> _widgetMap;
};