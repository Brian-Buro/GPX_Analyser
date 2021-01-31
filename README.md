# GPX_Analyser

GPX_Analyser was created as the capstone project as part of the Udacity C++ nano degree.

The command line program analyses GPS data in GPX format and outputs the results to the command window.  The project had to fulfill certain criteria and use certain programing methods to pass the degree. These are explained below.

Have fun analysing your GPS tracks!

## Dependencies for running locally

* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Build instructions

1. Clone the repository.
2. Create a build folder on the top level: `mkdir build && cd build` Resulting structure: GPX_Analyser/build
3. Compile: `cmake .. && make`
4. Run: `./GPX_Analyser -a ../sampleData/Walchensee.gpx`

## How to use

The program can be called with arguments to analyse a gpx file directly and exit. This is done as follows:
`./GPX_Analyser -a ../sampleData/Walchensee.gpx`
In the other method the program offers a prompt and the user can enter commands, analysing as many file as
they want before leaving the program.
Launch with `./GPX_Analyser`.
The following commands can be entered.

* `a` Prompts to add a file name, which will be analysed
* `h` Display help
* `q` Quit

File paths with empty spaces are not yet supported. The GPX file should contain positional, time and elevation data.

## Program outputs

The outputs are printed to the screen and are as follows;

* GPX file name
* Track name
* Track duration
* Max speed
* Average speed
* Stopped time
* Average speed while moving (this calculation many not be very accurate)
* Max elevation
* Min elevation
* Assended vertical height
* Decended vertical height

## Folders, Class Structure and Rubric Points

### Folders

**.vscode**     Contains settings for visual studio code, for other IDEs it's not required.
**sampleData**  Contains a sample GPX file to analyse.
**src**         All the source code, including header files.

### Class Structure

**main.cpp**    Program entry. Contains logic for the user interface.
**FileManager.h/cpp** Contains the FileManager class, which is responible for the files, loaded data and running the analyses.
**File.h/cpp** Contains the File class, which is responible for a file path. It checks if the entered file path is valid and holds the path.
**Data.h/cpp** Contains the Trk struct, Data class, GpxUtilities namespace and GpxParser. It's responible for loading the gpx data and calculating the speed from the raw data.

* Trk: This is a container for the gpx data and the calculated speed.
* Data: Controls importing the data and the speed calculation.
* GpxUtilities: Low level functions for processing the GPX data.
* GpxParser: Parses the GPX file.

**Analyses.h/cpp** Contains the AnalysisBase, SpeedAnalysis and ElevationAnalysis classes. It contains the analyses logic.

* AnalysisBase: Inherited by SpeedAnalysis and ElevationAnalysis. Contains logic, which can be used for the other classes.
* SpeedAnalysis: Speed specific calculations
* ElevationAnalysis: Elevation specific calculations.

### Rubric Points

Below are the rubric points covered by the project.

#### Loops, Functions, I/O

##### The project demonstrates an understanding of C++ functions and control structures

The following have been implemented:

* Conditional Statements (If else)
* For loops
* While loops
* Functions, classes, a struct and a namespace

##### The project reads data from a file and process the data, or the program writes data to a file

* Project reads an external file

##### The project accepts user input and processes the input

See section How to use.

* The program accepts input arguments when called.
* The program has a command mode, which accepts user input.

#### Object Oriented Programming

##### The project uses Object Oriented Programming techniques

* See section Class Structure for a list of classes.

##### Classes use appropriate access specifiers for class members.

* This has been done in all classes.

##### Class constructors utilize member initialization lists.

* File.h, File class initializes _path.
* Analyses.h, AnalysisBase class initializes _time and _data.

##### Classes abstract implementation details from their interfaces

* Descriptive function names were used to document what they did and they do only that.

##### Classes encapsulate behavior

* Analyses.h, AnalysisBase class, member data _trackTimeSec is private and can be accessed by the functions trackTimeSec() and trackTimeFormatted(). The internal units for track time are seconds and public functions return the track time as a string or in new functions in minutes or hours. I only used seconds and string format.
* Analysis.h, SpeedAnalysis class, member data _meanMovingSpeed is private and is accessed by the public function meanMovingSpeedKmPerH(). Achieves the same as above. The internal units are independent from the units returned by public function.

##### Classes follow an appropriate inheritance hierarchy

* Analyses.h, the AnalysisBase class is inherited by SpeedAnalysis and ElevationAnalysis.

##### Templates generalize functions in the project

* Analyses.h, the AnalysisBase class is a template class. This allows the constructor to take a vector of floats for speed data and a vector of ints for elevation data. Also it's min and max member functions can recieve and return different data types for speed and elevation data.

#### Memory Management

##### The project makes use of references in function declarations

* Data.h, class Data, function readFromFile() takes the string fileName as a reference.
* Data.h, namespace GpxUtilities, function distance() takes the vectors point1xyz and point2xyz as references.

##### The project uses destructors appropriately

* Data.cpp, class GpxParser destructor, line 119. GpxParser opens a file and reads it. The GpxParser destructor checks if the file was closed and if not, closes it.

##### The project uses move semantics to move data, instead of copying it, where possible

* FileManager.cpp, class FileManager, function addFile, line 10. This function creates a new file class on the heap with make_unique and moves it to a vector of type File.
* FileManager.cpp, class FileManager, function loadFile, line 10. This function creates a new data class on the heap with make_unique and moves it to a vector of type Data.

##### The project uses smart pointers instead of raw pointers

* FileManager.cpp, class FileManager manages a vector of unique pointers to Data classes. A smart pointer was used so that the heap memory instead of the stack would be used. FileManager is solely responible for the Data classes, therefor a unique_ptr was chosen.
* Data.h, class GpxParser, member _tracks. _tracks is a vector of Trk structures. Again a smart pointer was used so that the heap memory instead of the stack would be used. A shared_ptr was choosen, because many functions need access to _tracks to add to it and because once all the data is read, it'll be moved to the Data class.