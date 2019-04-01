#include "stdafx.h"
#include "state_machine.h"
#include "state_base.h"
#include <assert.h>


StateMachine::StateMachine()
    : m_cur_state(nullptr)
{
}

StateMachine::~StateMachine()
{
    for (auto it = m_state_map.begin(); it != m_state_map.end(); ++it)
    {
        delete it->second;
    }
    m_state_map.clear();
    m_cur_state = nullptr;
}

void StateMachine::Init()
{
    // register all state
    // AddState(state);

    // init state
    // ChangeState(state_id, nullptr);
}

void StateMachine::ChangeState(int state_id, void* param)
{
    auto it = m_state_map.find(state_id);
    if (it == m_state_map.end())
    {
        return;
    }

    if (m_cur_state)
    {
        m_cur_state->OnLeave();
    }

    m_cur_state = it->second;
    m_cur_state->OnEnter(param);
}

void StateMachine::Update(int dt)
{
    if (m_cur_state)
    {
        m_cur_state->Update(dt);
    }
}

void StateMachine::Destroy()
{
    if (m_cur_state)
    {
        m_cur_state->OnLeave();
        m_cur_state = nullptr;
    }
}

void StateMachine::AddState(StateBase* state)
{
    assert(state);
    m_state_map.insert(std::make_pair(state->GetStateId(), state));
}
