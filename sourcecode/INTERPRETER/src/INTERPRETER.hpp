#pragma once

#include <stdint.h>
#include <string.h>
#include <vector>

using namespace std;

namespace interpreter_system {

    class interpreter {
    public:

    private:
        uint64_t current_state; //the designated indicator how far the program has progressed
        Axis_3d currentPosition;
        Axis_3d machineZeroPoint;
        Axis_3d workpieceZeroPoint;
        Axis_3d currentToolOffset;
        vector<Command> allCommandsArr;
    };

    class gcode_interpreter {
    public:
    private:
    };

    class mcode_interpreter {
    public:
    private:
    };

    struct Axis_3d {
        double X;
        double Y;
        double Z;
    };
    /*
    struct Axis_6d {
        double X;
        double Y;
        double Z;

        double A;
        double B;
        double C;
    };
    */
    struct Command {// currently build for 3d
        bool gcode;
        bool mcode;
        bool direct_command;

        uint16_t command;
        uint32_t N;

        double I;// Interpolation Parameters
        double J;
        double K;

        double X;// Coordinates
        double Y;
        double Z;

        double F;// feed (Vorschub)

        uint32_t P;// pause in ms

        uint16_t T;// tool to be selected
    };
}
