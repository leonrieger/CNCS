#include "EntryPoint.hpp"
using namespace ui;

#include "ui_elements/ui_elements.hpp"

void entrypoint::initExecCommand() {

}

void entrypoint::initExecEnviroment() {
    ui_elements::color_table colorado;
    ui_elements::progress_bar init_progress_bar("initialising", 5, colorado.OKCYAN);

    bool requestToStop = false;
    do 
    {
        //input = exit
    } while (!requestToStop);
}
