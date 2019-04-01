#pragma once
#include <map>

class StateBase;

class StateMachine
{
public:
    StateMachine();
    virtual ~StateMachine();

    virtual void Init();

    virtual void ChangeState(int state_id, void* param);

    virtual void Update(int dt);

    virtual void Destroy();

protected:
    virtual void AddState(StateBase* state);

protected:
    std::map<int, StateBase*> m_state_map;
    StateBase* m_cur_state;
};

