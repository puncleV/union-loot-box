// Supported with union (c) 2020 Union team
// Union SOURCE file
#include <vector>
namespace GOTHIC_ENGINE {
	auto lbIterations = 0;
	auto lastAddedItem = Z "none";

	bool IsItemSymbol(zCPar_Symbol* symbol) {
		if (symbol->type != zPAR_TYPE_INSTANCE) {
			return false;
		}

		//  Instance isn't global scope
		if (symbol->name.HasWord(".")) {
			return false;
		}

		auto baseClass = parser->GetBaseClass(symbol);

		// Symbol isn't a item class
		if (baseClass != parser->GetIndex(oCItem::classDef->scriptClassName)) {
			return false;
		}

		return true;
	}
		
	zSTRING getRandomItemName() {
		zSTRING itemName = "ITMI_GOLD";

		auto c_item = parser->GetIndex(oCItem::classDef->scriptClassName);

		if (c_item == -1) {
			return itemName;
		}

		for (int i = 0; i < 228; i++) { 
			auto symTableIndex = randomizer.Random(0, parser->symtab.GetNumInList());
			zCPar_Symbol* symbol = parser->symtab.table[symTableIndex];

			if (symTableIndex == parser->instance_help) {
				continue;
			}

			if (!IsItemSymbol(symbol)) {
				continue;
			}

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, symTableIndex));

			if (item == nullptr || IsIgnoredOrTestItem(item)) {
				continue;
			}


			itemName = item->GetObjectName();

			item->Release();
			lbIterations = i;
			break;
		}
		
		lastAddedItem = itemName;

		return itemName;
	}

	int openLootBox() {
		if (!player || !(player->GetInstanceName() == "PC_HERO")) {
			parser->SetReturn("");
			return 0;
		}
		auto lootToAdd = Loot("ITMI_MONEY", 50, 450);

		if (USE_CONFIG_FILE && lootBoxLoot.size() > 0) {
			lootToAdd = randomizer.getRandomArrayElement(lootBoxLoot);
		}
		else {
			lootToAdd = Loot(getRandomItemName(), randomizer.Random(1, 3), randomizer.Random(1, 10));
		}

		lootToAdd.addToNpc(player);

		parser->SetReturn(lootToAdd.lootName);

		return 1;
	}

	void RegisterExternals_punclev() {
		parser->DefineExternal("punclev_open_loot_box", openLootBox, zPAR_TYPE_STRING, 0);
	}

}