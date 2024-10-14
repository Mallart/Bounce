#include "Component.hpp"


namespace Bounce::Components
{
	// Defines the behavior of a basic player and its statistics.
	BINTERFACE(PlayerStats) : public Component
	{
		BAPROPERTY(public, protected, float, BaseHealth);
		BAPROPERTY(public, protected, float, CurrentHealth);
		BAPROPERTY(public, protected, float, HealthMult);

		BAPROPERTY(public, protected, float, BaseStamina);
		BAPROPERTY(public, protected, float, CurrentStamina);
		BAPROPERTY(public, protected, float, StaminaMult);

		BAPROPERTY(public, protected, float, BaseMana);
		BAPROPERTY(public, protected, float, CurrentMana);
		BAPROPERTY(public, protected, float, ManaMult);

		BAPROPERTY(public, protected, uint64_t, Level);

	public:
		Events::Event OnLevelUp;
		Events::Event OnLevelDown;

		// Levels up the player by n levels.
		virtual void LevelUp(uint64_t n_levels = 1)
		{
			Level += n_levels;
			if(OnLevelUp.HasMethods())
				OnLevelUp.FireEvent();
		}

		// Levels down the player by n levels.
		virtual void LevelDown(uint64_t n_levels = 1)
		{
			Level -= n_levels;
			if(OnLevelDown.HasMethods())
				OnLevelDown.FireEvent();
		}

		inline virtual float GetHealth()
		{
			return GetCurrentHealth() * GetHealthMult();
		}

		inline virtual void ReduceHealth(float amount)
		{
			CurrentHealth -= (amount / GetHealthMult());
		}

		inline virtual float GetStamina()
		{
			return GetCurrentStamina() * GetStaminaMult();
		}

		inline virtual void ReduceStamina(float amount)
		{
			CurrentStamina -= (amount / GetStaminaMult());
		}

		inline virtual float GetMana()
		{
			return GetCurrentMana() * GetManaMult();
		}

		inline virtual void ReduceMana(float amount)
		{
			CurrentMana -= (amount / GetManaMult());
		}
	};

}