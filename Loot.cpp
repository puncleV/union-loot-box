// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <set>
namespace GOTHIC_ENGINE {

	class Loot {
	private:
		int minAmount;
		int maxAmount;

		int getRandomItemAmount(oCItem* item) {
			if (minAmount == maxAmount) {
				return minAmount;
			}

			return randomizer.Random(minAmount, maxAmount);
		}

		oCItem* getItemWithAmount(zSTRING name) {
			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, name));

			if (!item) {
				return nullptr;
			}

			if (item->HasFlag(ITM_FLAG_MULTI)) {
				item->amount = getRandomItemAmount(item);
			}

			return item;
		}
	public:
		zSTRING lootName;

		Loot(zSTRING _lootName, int _minAmount = 1, int _maxAmount = 1) {
			lootName = _lootName;
			minAmount = _minAmount;
			maxAmount = _maxAmount;
		};

		bool addToNpc(oCNpc* npc) {
			if (!npc) {
				return FALSE;
			}

			auto item = getItemWithAmount(lootName);

			if (item == nullptr) {
				return FALSE;
			}

			player->PutInInv(item);

			item->Release();

			return TRUE;
		};
	};
}