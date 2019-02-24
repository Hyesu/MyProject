#include "UIManager.h"
#include "ShootingGame.h"
#include "Utility/JsonUtil.h"
#include <memory>
#include "Paths.h"
#include "UserWidget.h"

void UUIManager::Init(UWorld* owner)
{
	_owner = owner;

	static FString dataTableFilePath{ FPaths::ProjectContentDir().Append(TEXT("Data/ui.json")) };
	auto jsonUtil = std::make_unique<JsonUtil>();
	if (jsonUtil->Init(dataTableFilePath) != JsonUtil::Result::Success) {
		SG_LOG("Json File Init Fail: %s", *dataTableFilePath);
		return;
	}

	jsonUtil->ForEachArray(jsonUtil->GetRootObject(), "UI", [utilPtr = jsonUtil.get(), this](const JsonObjectPtr& jsonObject) {
		FName key;
		utilPtr->GetNameField(jsonObject, "StrID", key);
		_pathMap.Emplace(key, jsonObject->GetStringField("Path"));
		return true;
	});

	SG_LOG("UIManager Init Success: size[%d]", _pathMap.Num());
}

void UUIManager::OpenUI(const FName& pathKey)
{
	UUserWidget* widget = _widgetMap.FindRef(pathKey);
	if (widget != nullptr && widget->GetVisibility() == ESlateVisibility::Collapsed) {
		widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		return;
	}

	FSoftClassPath* pathPtr = _pathMap.Find(pathKey);
	if (pathPtr == nullptr) {
		return;
	}
	
	UClass* widgetClass = pathPtr->TryLoadClass<UUserWidget>();
	if (widgetClass == nullptr) {
		SG_LOG("Fail load widget: %s", *pathKey.ToString());
		return;
	}

	widget = CreateWidget<UUserWidget>(_owner, widgetClass);
	if (widget == nullptr) {
		SG_LOG("Fail create widget: %s", *pathKey.ToString());
		return;
	}

	widget->AddToViewport();
	_widgetMap.Emplace(pathKey, widget);
}

void UUIManager::CloseUI(const FName& pathKey)
{
	UUserWidget* widget = _widgetMap.FindRef(pathKey);
	if (widget == nullptr) {
		return;
	}

	if (widget->IsInViewport() == false) {
		return;
	}

	widget->SetVisibility(ESlateVisibility::Collapsed);	
}

void UUIManager::ToggleUI(const FName& pathKey)
{
	UUserWidget* widget = _widgetMap.FindRef(pathKey);
	if (widget == nullptr || widget->GetVisibility() == ESlateVisibility::Collapsed) {
		OpenUI(pathKey);
		return;
	}
	
	CloseUI(pathKey);
}