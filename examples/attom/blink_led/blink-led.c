#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
/* We declare the two processes */
PROCESS(hello_world_process, "Hello world process");
PROCESS(blink_red_process, "RED LED blink process");
PROCESS(blink_green_process, "GREEN LED blink process");
/* We require the processes to be started automatically */
AUTOSTART_PROCESSES(&hello_world_process, &blink_red_process, &blink_green_process);
/*---------------------------------------------------------------------------*/
/* Implementation of the first process */
PROCESS_THREAD(hello_world_process, ev, data)
{
    // variables are declared static to ensure their values are kept
    // between kernel calls.
    static struct etimer timer;
    static int count = 0;
    // any process mustt start with this.
    PROCESS_BEGIN();
    // set the etimer module to generate an event in one second.
    etimer_set(&timer, CLOCK_CONF_SECOND);
    while (1)
    {
        // wait here for an event to happen
        PROCESS_WAIT_EVENT();
        // if the event is the timer event as expected...
        if(ev == PROCESS_EVENT_TIMER)
        {
            // do the process work
            printf("Hello, world #%i\n", count);
            count ++;
            // reset the timer so it will generate an other event
            // the exact same time after it expired (periodicity guaranteed)
            etimer_reset(&timer);
        }
        // and loop
    }
    // any process must end with this, even if it is never reached.
    PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_red_process, ev, data)
{
    static struct etimer timer;

    PROCESS_BEGIN();

    // we set the timer from here every time
    etimer_set(&timer, CLOCK_CONF_SECOND);

    while (1)
    {
        // and wait until the vent we receive is the one we're waiting for
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
        // update the LEDs
        leds_toggle(LEDS_RED);

        etimer_reset(&timer);

    }
    PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_green_process, ev, data)
{
    static struct etimer timer;

    PROCESS_BEGIN();

    // we set the timer from here every time
    etimer_set(&timer, CLOCK_CONF_SECOND / 2.0);
    
    while (1)
    {
        // and wait until the vent we receive is the one we're waiting for
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);
        // update the LEDs
        leds_toggle(LEDS_GREEN);

        etimer_reset(&timer);

    }
    PROCESS_END();
}
/*---------------------------------------------------------------------------*/