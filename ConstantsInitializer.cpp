// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		USE_CONFIG_FILE = zoptions->ReadBool("PUNCLEVUTILS", "UseConfigForLootboxes", FALSE);
		ALLOW_LOOT_BOXES = zoptions->ReadBool("PUNCLEVUTILS", "AllowLootboxes", TRUE);
		IS_DEBUG = zoptions->ReadBool("PUNCLEVUTILS", "Debug", FALSE);

		JSON_FILE_NAME = zoptions->ReadString("PUNCLEVUTILS", "LootBoxesFileName", "loot-boxes.json");
	}
}