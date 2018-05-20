#include "stdafx.h"
#include "Timer.h"

namespace cpplib {
namespace utility {

Timer::Timer()
    : m_start_time(0)
    , m_total_time(0)
    , m_running(false)
    , m_pause(false)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
    m_total_time = 0;
    m_start_time = clock();
    m_pause = false;
    m_running = true;
}

void Timer::Stop()
{
    if (m_running)
    {
        clock_t end_time = clock();
        m_total_time += end_time - m_start_time;
        m_running = false;
    }
}

void Timer::Reset()
{
    m_start_time = 0;
    m_total_time = 0;
    m_running = false;
    m_pause = false;
}

void Timer::Pause()
{
    if (m_running && !m_pause)
    {
        clock_t end_time = clock();
        m_total_time += end_time - m_start_time;
        m_pause = false;
    }
}

void Timer::Resume()
{
    if (m_running && m_pause)
    {
        m_start_time = clock();
        m_pause = false;
    }
}

long Timer::Milliseconds() const
{
    return m_total_time / (CLOCKS_PER_SEC / 1000);
}

double Timer::Seconds() const
{
    return m_total_time / (double)CLOCKS_PER_SEC;
}

} // namespace utility
} // namespace cpplib
