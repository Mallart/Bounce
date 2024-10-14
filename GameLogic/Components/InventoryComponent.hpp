#include "Component.hpp"
#include "../Interactions/Item.hpp"

namespace Bounce::Components
{
	using namespace Interactions;
	// Defines the behavior of basic inventory.
	// Can be used both by playable and non-playable objects, such as containers and NPCs.
	BINTERFACE(InventoryComponent) : public Component
	{
		// The inventory content.
		BAPROPERTY(public, protected, ::std::vector<RefItem>, Items);
		// The inventory max size.
		BAPROPERTY(public, protected, uint32_t, Capacity);
		
	public:
		// Returns a pointer on an object similar to the one given, if contained in this inventory.
		RefItem GetItem(Item item)
		{
			for (size_t i = 0; i < Items.size(); ++i)
				if (item == Items[i])
					return Items[i];
			return 0;
		}

		size_t GetItemIndex(Item item)
		{
			for (size_t i = 0; i < Items.size(); ++i)
				if (Items[i] == item)
					return i;
			return -1;
		}

		// Removes an item from the inventory.
		// ITEM WILL STILL BE REFERENCED IN MEMORY AND CAN BE GOT BY THE RETURNED VALUE.
		// NULL RETURN VALUE MEANS NOTHING HAS BEEN AFFECTED.
		[[nodiscard("ITEM REFERENCE IN MEMORY")]] RefItem PopItem(Item item)
		{
			size_t _index; 
			if (_index = GetItemIndex(item) == (size_t)-1)
				return 0;
			RefItem refItem = Items[_index];
			Items.erase(Items.begin() + _index, Items.begin() + _index + 1);
			return refItem;
		}

		// Removes an item from the inventory.
		// ITEM WILL STILL BE REFERENCED IN MEMORY AND CAN BE GOT BY THE RETURNED VALUE.
		// NULL RETURN VALUE MEANS NOTHING HAS BEEN AFFECTED.
		[[nodiscard("ITEM REFERENCE IN MEMORY")]] RefItem PopItem(size_t itemIndex)
		{
			if (itemIndex > Capacity)
				return 0;
			RefItem refItem = Items[itemIndex];
			Items.erase(Items.begin() + itemIndex, Items.begin() + itemIndex + 1);
			return refItem;
		}

		// Simply removes an item from the inventory.
		// Returns a bool saying if the operation was successful or not.
		bool RemoveItem(Item item)
		{
			size_t _index;
			if (_index = GetItemIndex(item) == (size_t)-1)
				return 0;
			RefItem refItem = Items[_index];
			Items.erase(Items.begin() + _index, Items.begin() + _index + 1);
			return 1;
		}

		// Simply removes an item from the inventory.
		// Returns a bool saying if the operation was successful or not.
		bool RemoveItem(size_t itemIndex)
		{
			if (itemIndex > Capacity)
				return 0;
			RefItem refItem = Items[itemIndex];
			Items.erase(Items.begin() + itemIndex, Items.begin() + itemIndex + 1);
			return 1;
		}

		// Transfers an item from this inventory to an other.
		// Prevents duplication bug, because removes the Item from one inventory before adding to the other one.
		void TransferItem(size_t itemIndexInInventory, RefInventoryComponent otherInventory)
		{
			if (itemIndexInInventory > Items.size() || otherInventory->Capacity <= otherInventory->Items.size())
				return;
			RefItem _item = Items[itemIndexInInventory];
			Items.erase(Items.begin() + itemIndexInInventory, Items.begin() + itemIndexInInventory + 1);
			otherInventory->Items.push_back(_item);
		}

		// Transfers an item from this inventory to an other.
		// Prevents duplication bug, because removes the Item from one inventory before adding to the other one.
		void TransferItem(Item item, RefInventoryComponent otherInventory)
		{
			if (!GetItem(item) || otherInventory->Capacity <= otherInventory->Items.size())
				return;
			size_t _index = GetItemIndex(item);
			RefItem _item = Items[_index];
			Items.erase(Items.begin() + _index, Items.begin() + _index + 1);
			otherInventory->Items.push_back(_item);
		}
	};

}