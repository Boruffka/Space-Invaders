
module;

import FUNCTIONS;
import state;
import <memory>;
import <stack>;

export module stateMachine;

export typedef std::unique_ptr<State> StateRef;

export class StateMachine
{
public:
	StateMachine()
	{
		FUNCTIONS::debugLog("[stateMachine.ixx] Created state machine");
	}

	~StateMachine()
	{

	}

	void AddState(StateRef newState, bool isReplacing = true)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing;
		
		this->_newState = std::move(newState);
	}

	void RemoveState()
	{
		this->_isRemoving = true;
	}

	void ProcessStateChanges()
	{
		if (this->_isRemoving && !this->_states.empty())
		{
			this->_states.pop();

			if (!this->_states.empty())
			{
				this->_states.top()->Resume();
			}

			this->_isRemoving = false;
		}

		if (this->_isAdding)
		{
			if (!this->_states.empty())
			{
				if (this->_isReplacing)
				{
					this->_states.pop();
				}
				else
				{
					this->_states.top()->Pause();
				}
			}

			this->_states.push(std::move(this->_newState));
			this->_states.top()->Init();
			this->_isAdding = false;
		}
	}

	StateRef& GetActiveState()
	{
		return this->_states.top();
	}

private:
	std::stack<StateRef> _states;
	StateRef _newState;

	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};
