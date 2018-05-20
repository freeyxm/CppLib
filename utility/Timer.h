#ifndef __CPPLIB_UTILITY_TIMER_H__
#define __CPPLIB_UTILITY_TIMER_H__
#include <ctime>

namespace cpplib {
namespace utility {

class Timer
{
public:
    Timer();
    ~Timer();

    void Start();
    void Stop();
    void Reset();

    void Pause();
    void Resume();

    bool IsRunning() const { return m_running; };
    bool IsPause() const { return m_pause; };

    long Milliseconds() const;
    double Seconds() const;

private:
    clock_t m_start_time;
    clock_t m_total_time;
    bool m_running;
    bool m_pause;
};

} // namespace utility
} // namespace cpplib
#endif // !__CPPLIB_UTILITY_TIMER_H__
