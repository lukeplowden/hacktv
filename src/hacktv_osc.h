#ifndef HACKTV_OSC_H
#define HACKTV_OSC_H

#ifdef HAVE_LO
#include <lo/lo.h>

#define OSC_SRC_CHANGED   0x01

/* Structure to hold OSC state */
typedef struct {
    lo_server_thread st;   /* OSC server thread */
    int src;
    // You can add more OSC-specific variables here, for example:
    // int last_gain;
    // float last_freq;
    // char current_mode[64];
    unsigned int changed;
} osc_state_t;

/* Initialize and start the OSC server.
 * The osc_state_t pointer can later be used to stop or query the OSC state.
 */
void start_osc_server(osc_state_t *osc, const char *port);
/* Stop and free the OSC server. */
void stop_osc_server(osc_state_t *osc);
#endif

#endif /* HACKTV_OSC_H */
