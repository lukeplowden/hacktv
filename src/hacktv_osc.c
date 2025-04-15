#ifdef HAVE_LO
#include "hacktv_osc.h"
#include <stdio.h>

/* Handler functions remain the same */
int osc_gain_handler(const char *path, const char *types, lo_arg **argv,
                     int argc, void *data, void *user_data)
{
    (void)path; (void)types; (void)argc; (void)data; (void)user_data;
    float new_gain = argv[0]->f;
    fprintf(stderr, "[OSC] /gain -> %d\n", (int)new_gain);
    return 0;
}

int osc_freq_handler(const char *path, const char *types, lo_arg **argv,
                     int argc, void *data, void *user_data)
{
    (void)path; (void)types; (void)argc; (void)data; (void)user_data;
    float new_freq = argv[0]->f;
    fprintf(stderr, "[OSC] /freq -> %d\n", (int)new_freq);
    return 0;
}

int osc_deviation_handler(const char *path, const char *types, lo_arg **argv,
                     int argc, void *data, void *user_data)
{
    (void)path; (void)types; (void)argc; (void)data; (void)user_data;
    float new_deviation = argv[0]->f;
    fprintf(stderr, "[OSC] /dev -> %d\n", (int)new_deviation);
    return 0;
}

int osc_offset_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    (void)path; (void)types; (void)argc; (void)data; (void)user_data;
    float new_offset = argv[0]->f;
    fprintf(stderr, "[OSC] /off -> %d\n", (int)new_offset);
    return 0;
}

int osc_source_handler(const char *path, const char *types, lo_arg **argv,
    int argc, void *data, void *user_data)
{
    osc_state_t *osc = (osc_state_t*)user_data;
    (void)path; (void)types; (void)argc; (void)data; (void)user_data;
    int new_src = argv[0]->i;
    osc->src = new_src;
    osc->changed |= OSC_SRC_CHANGED;
    fprintf(stderr, "[OSC] /source -> %d\n", new_src);
    return 0;
}

/* Initialize and start the OSC server using the osc_state_t structure */
void start_osc_server(osc_state_t *osc, const char *port)
{
    if (!osc) return;
    osc->st = lo_server_thread_new(port, NULL);
    // lo_server_thread_add_method(osc->st, "/gain", "f", osc_gain_handler, osc);
    // lo_server_thread_add_method(osc->st, "/freq", "f", osc_freq_handler, osc);
    // lo_server_thread_add_method(osc->st, "/off", "f", osc_offset_handler, osc);
    // lo_server_thread_add_method(osc->st, "/dev", "f", osc_deviation_handler, osc);
    lo_server_thread_add_method(osc->st, "/source", "i", osc_source_handler, osc);
    lo_server_thread_start(osc->st);
    fprintf(stderr, "[OSC] Server started on port %s\n", port);
}

/* Stop the OSC server and clean up */
void stop_osc_server(osc_state_t *osc)
{
    if (osc && osc->st) {
        lo_server_thread_stop(osc->st);
        lo_server_thread_free(osc->st);
        osc->st = NULL;
    }
}
#endif  // HAVE_LO
