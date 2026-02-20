#include <iostream>
#include <jack/jack.h>
#include <unistd.h>

jack_client_t *client;

int process_callback(jack_nframes_t nframes, void *arg) {
    jack_nframes_t cur_frames = jack_last_frame_time(client);
    auto sample_rate = jack_get_sample_rate(client);
    
    double seconds = (double)cur_frames / sample_rate;
    
    static jack_nframes_t last_print = 0;
    if (cur_frames - last_print > sample_rate) {
        printf("\r[time] %.2f sec.", seconds);
        fflush(stdout);
        last_print = cur_frames;
    }
    return 0;
}

int main() {
    jack_status_t status;
    client = jack_client_open("Arch_LRC_Engine", JackNullOption, &status);
    
    if (!client) {
        std::cerr << "Unable to install the dependencies." << std::endl;
        return 1;
    }

    jack_set_process_callback(client, process_callback, nullptr);

    if (jack_activate(client)) {
        std::cerr << "Unable to start the device." << std::endl;
        return 1;
    }

    std::cout << ">>> Test Passed!<<<" << std::endl;
    std::cout << ">>> Press ENTER to continue." << std::endl;
    
    std::cin.get();

    jack_client_close(client);
    return 0;
}
