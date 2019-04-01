#include "stdafx.h"
#include "state_base.h"


StateBase::StateBase(int state_id, StateMachine* state_machine)
    : m_state_id(state_id)
    , m_state_machine(state_machine)
{
}

StateBase::~StateBase()
{
}

void StateBase::OnEnter(void * param)
{
}

void StateBase::OnLeave()
{
}

void StateBase::Update(int dt)
{
}
