#include "../../include.hpp"
#include "./Event.hpp"

// All that the player can interact with.
namespace Bounce::Interactions
{
	enum QuestState
	{
		Incomplete,
		Complete,
		Failed,
		Unknown,
		Active,
		Inactive
	};
	// A simple objective that can be completed.
	BCLASS(Objective)
	{
		BPROPERTY(protected, QuestState, completed);
	public:
		QuestState GetState();
		void Complete();
	};

	// A quest is an object that holds data about one or more objectives that can be completed in order to fire an event.
	BCLASS(Quest)
	{
		BPROPERTY(protected, ::std::vector<RefObjective>, Objectives);
	};
}