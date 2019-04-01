#pragma once
#include "state_machine.h"

class StateBase
{
public:
    StateBase(int state_id, StateMachine* state_machine);
    virtual ~StateBase();

    virtual void OnEnter(void* param);

    virtual void OnLeave();

    virtual void Update(int dt);

    inline int GetStateId() { return m_state_id; }

protected:
    int m_state_id;
    StateMachine* m_state_machine;
};

