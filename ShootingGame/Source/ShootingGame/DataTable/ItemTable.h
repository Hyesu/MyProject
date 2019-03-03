#pragma once
#include "Singleton.h"
#include "DataTable.h"

enum class ItemType : unsigned char
{
	None,
	Weapon
};

struct ItemData : public Data
{
	FName type;
	FName subType;	
	FString name;
	FString meshPath;
	FVector scale;
	unsigned int spawnWeight{ 0 };

	virtual ~ItemData() { }
	virtual ItemType GetType() const { return ItemType::None; }
};

struct WeaponData : public ItemData
{
	FName ammo;

	WeaponData(const ItemData& data) : ItemData(data) {}
	~WeaponData() {}

	ItemType GetType() const override { return ItemType::Weapon; }
};

class ItemTable : public DataTable
{
	DECL_SINGLETONE(ItemTable);

public:
	void Init() override;
	void PostInit() override;
	void Finalize() override;

	const ItemData* GetData(const DataKey& key) override;
	const ItemData* GetData(const FName& stringKey) override;

private:
	void InitItems();
	void InitWeapons();
};

ItemTable* GetItemTable();