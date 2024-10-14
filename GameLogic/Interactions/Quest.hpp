#include "../../include.hpp"
#include "./Event.hpp"

// All that the player can interact with.
namespace Bounce::Interactions
{
	enum ObjectiveState
	{
		// Quest is in quest log
		Inactive,
		Incomplete = Inactive,
		// Quest has been successfully completed
		Complete,
		// Quest has been failed
		Failed,
		// Quest hasn't been discovered by the player yet
		Unknown,
		// Player is actively following this quest
		Active,
	};

	// A simple objective that can be completed.
	BCLASS(Objective)
	{
		// The objective ID, among the others in the same quest.
		// Computed automatically.
		BAPROPERTY(public, protected, uint64_t, ID);
		// The objective's name
		BAPROPERTY(public, protected, ::std::string, Name);
		// The objective's description
		BAPROPERTY(public, protected, ::std::string, Description);
		// The objective state
		BPROPERTY(protected, ObjectiveState, State);
	public:
		Objective(RefQuest parentQuest, ::std::string name, ::std::string description = "", ObjectiveState os = Unknown)
		{
			ID = parentQuest->RequestNewID();
			Name = name;
			Description = description;
			State = os;
		}

		// Returns the objective's state.
		ObjectiveState GetState() const
		{
			return State;
		}

		// If an objective still can be interacted with.
		bool CanChange() const
		{
			return !(State == Failed || State == ObjectiveState::Complete);
		}

		// Makes this objective the followed and highlited one.
		void Highlight()
		{
			if (CanChange())
				State = ObjectiveState::Active;
		}

		// Opposite of making this highlighted.
		void Ignore()
		{
			if (CanChange())
				State = ObjectiveState::Inactive;
		}

		// Makes this objective unknown.
		void Forget()
		{
			if (CanChange())
				State = Unknown;
		}

		// Makes this objective available
		void Discover()
		{
			if (State == Unknown)
				State = Active;
		}

		void Fail()
		{
			if (State != ObjectiveState::Complete)
				State = ObjectiveState::Failed;
		}

		void Complete()
		{
			if(State != Failed)
				State = ObjectiveState::Complete;
		}
	};

	// A quest is an object that holds data about one or more objectives that can be completed in order to fire an event.
	BCLASS(Quest)
	{
		// The quest ID.
		BAPROPERTY(public, protected, uint64_t, ID);
		// The quest's name
		BAPROPERTY(public, protected, ::std::string, Name);
		// The quest's description
		BAPROPERTY(public, protected, ::std::string, Description);
		// The list of every quest's objective
		BPROPERTY(protected, ::std::vector<RefObjective>, Objectives);

		uint64_t lastID = 0;
		static uint64_t questID;
	public:
		Quest(uint64_t ID, ::std::string name, ::std::string description)
		{

		}
		// Get a global state over several objectives
		virtual ObjectiveState GetState()
		{
			bool active = false;
			bool complete = 1;
			bool totallyfailed = 1;
			bool totallycomplete = 1;
			for (RefObjective _o : Objectives)
			{
				if (_o->GetState() != Failed)
					totallyfailed = 0;
				if (_o->GetState() != ObjectiveState::Complete)
					totallycomplete= 0;
				switch (_o->GetState())
				{
				case Active: active = 1; break;
				case ObjectiveState::Incomplete: complete = 0; break;
				};
			}
			if (totallycomplete)
				return ObjectiveState::Complete;
			if (totallyfailed)
				return ObjectiveState::Failed;
			if (active && !complete)
				return ObjectiveState::Active;
			return Incomplete;
		}

		void Complete()
		{
			for (RefObjective _o : Objectives)
				_o->Complete();
		}

		// Returns the last available ID and increments it.
		uint64_t RequestNewID()
		{
			return lastID++;
		}
	};
}