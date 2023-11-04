// Supported with union (c) 2020 Union team
// Union SOURCE file
#include <vector>
namespace GOTHIC_ENGINE {
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
		
	std::vector<zSTRING> getItemsList() {
		std::vector<zSTRING> weapons_list;

		auto c_item = parser->GetIndex(oCItem::classDef->scriptClassName);
		if (c_item == -1) {
			return weapons_list;
		}

		int itemsCreated = 0;
		for (int i = 0; i < parser->symtab.GetNumInList(); i++) {
			zCPar_Symbol* symbol = parser->symtab.table[i];

			if (i == parser->instance_help) {
				continue;
			}

			if (!IsItemSymbol(symbol)) {
				continue;
			}

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

			if (item == nullptr || IsIgnoredOrTestItem(item)) {
				continue;
			}


			weapons_list.push_back(item->GetObjectName());

			item->Release();
		}

		return weapons_list;
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
			lootToAdd = Loot(randomizer.getRandomArrayElement(getItemsList()), randomizer.Random(1, 3), randomizer.Random(1, 5));
		}

		lootToAdd.addToNpc(player);

		parser->SetReturn(lootToAdd.lootName);

		return 1;
	}

	void RegisterExternals_punclev() {
		parser->DefineExternal("punclev_open_loot_box", openLootBox, zPAR_TYPE_STRING, 0);
	}

}