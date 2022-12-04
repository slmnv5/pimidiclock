#include "pch.hpp"
#include "utils.hpp"
#include "MidiClockClient.hpp"

void MidiClockClient::run()
{
    LOG(LogLvl::DEBUG) << "Start prepare clock event, type: " << SND_SEQ_EVENT_CLOCK;
    float sleep_time = bar_time / 96;
    LOG(LogLvl::DEBUG) << "Prepared clock event, sleep time: " << sleep_time;
    while (!ended)
    {
        send_event(&event_start);
        LOG(LogLvl::DEBUG) << "Wait to start MIDI clock for 2 sec.";
        usleep(2000000);
        while (!stopped)
        {
            LOG(LogLvl::DEBUG) << "Sent one bar of MIDI clock";
            for (int k = 0; k < 96; k++)
            {
                usleep(sleep_time * 1000000.0);
                send_event(&event_clock);
            }
        }
    }
    send_event(&event_stop);
}
