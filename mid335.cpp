//Gerardo Peregrina
//Cmps 335
//
//
//
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;

//frequency definitions
#define A4 440.0
#define F0 A4
#define F0_note A
#define F0_octave 4

double value[] = {16.35,17.32,18.35,19.45,20.60,21.83,23.12,24.50,25.96,27.50,29.14,30.87,32.70,34.65
                    ,36.71,38.89,41.20,43.65,46.25,49.00,51.91,55.00,58.27,61.74,65.41,69.30,73.42,77.78
                    ,82.41,87.31,92.50,98.00,103.83,110.00,116.54,123.47,130.81,138.59,146.83,155.56,164.81
                    ,174.61,185.00,196.00,207.65,220.00,233.08,246.94,261.63,277.18};

int noteArray[] = {1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12};

/*
char noteArray[] = {"C0", "C#0/Db0","D0","D#0/Eb0","E0","F0", "F#0/Gb0","G0", "G#0/Ab0","A0","A#0/Bb0","B0","C1"
                    ,"C#1/Db1", "D1", "D#1/Eb1","E1", "F1", "F#1/Gb1", "G1", "G#1/Ab1", "A1", "A#1/Bb1", "B1", "C2"
                    ,"C#2/Db2", "D2", "D#2/Eb2", "E2", "F2", "F#2/Gb2", "G2", "G#2/Ab2", "A2", "A#2/Bb2", "B2", "C3"
                    ,"C#3/Db3" , "D3", "D#3/Eb3" , "E3", "F3", "F#3/Gb3", "G3", "G#3/Ab3","A3", "A#3/Bb3","B3","C4", "C#4/Db4"};
*/

int octValue[] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1};

typedef enum {
    C = 1,
    Cs,
    D,
    Ds,
    E,
    F,
    Fs,
    G,
    Gs,
    A,
    As,
    B,
    Z = 0,
    END = B,
    HALF_STEPS_PER_OCTAVE = B
} note_t;

double freq(note_t note, int octave_delta);
int unitTest(double value[], int noteArray[], int octValue[], double tolerance);

int main(int argc, char *argv[])
{
    note_t note;
    int octave_delta;
    double tolerance;
    int element;
    //char tolerance = *argv[3];
    //cout << tolerance << endl;
    //if (argc != 6)    
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <NOTE>  <OCTAVE_DELTA>" << endl;
        return 0;
    }

    //
    note = (note_t)(toupper(argv[1][0]) - 64);
    switch(toupper(argv[1][0])) {
        case 'A': note = A; break;
        case 'B': note = B; break;
        case 'C': note = C; break;
        case 'D': note = D; break;
        case 'E': note = E; break;
        case 'F': note = F; break;
        //case 'Z': note = Z; break;
    }

    //You may call your unit test here...
    if (*argv[1] == 'Z' && *argv[2] == '0') {
        cout << "Enter a tolerance: ";
        cin >> tolerance;
        cout << "\nFreq function unit-test\n";
        element = unitTest(value, noteArray, octValue, tolerance);
        cout << "bad element count: " << element << endl;
        cout << "unit test complete. " << endl;
        return 1;
    }

    if (note > END) {
        cout << "Invalid note!" << endl;
        return 1;
    }

    octave_delta = atoi(argv[2]);
    cout << HALF_STEPS_PER_OCTAVE << endl;
    cout << freq(note, octave_delta) << endl;
    return 0;
}

int unitTest(double value[], int noteArray[], int octValue[], double tolerance)
{
    int element = 0;
    cout << "note " << " octave " << " value\t" << "diff\n";
    cout << "---- " << " ------ " << " ------\t" << "-----------\n";
    //while(value[0] != NULL) 
    for (int i=0;i<1;i++) {
        note_t note;
        note = (note_t)(toupper(noteArray[i]) - 64);
        float ret = freq(note, octValue[i]);
        float diff = ret - value[i];
        diff = fabs(diff);
        if (diff > tolerance) {
            cout << noteArray[i] << "\t" << octValue[i] << "\t" << value[i] << "\t" << diff << "\t" << "<------- bad\n";
            element++;
        } else
            cout << noteArray[i] << "\t" << octValue[i] << "\t" << value[i] << "\t" << diff << "\t" << "good\n";

    }

    return element;
}


//-----------------------------------------------------------
//Generate a frequency in hz that is half_steps away from C_4
//Do not modify this function.
//-----------------------------------------------------------
double freq(note_t note, int octave_delta)
{
    double freq;
    double factor;
    double a;
    int n;
    int octave = octave_delta - F0_octave;

    a = pow(2.0, 1.0/(double)HALF_STEPS_PER_OCTAVE);
    n = note - F0_note;
    freq = F0 * pow(a, (double)n);
    factor = pow(2.0, (double)octave);
    freq = freq * factor;
    return freq;
}
~          
