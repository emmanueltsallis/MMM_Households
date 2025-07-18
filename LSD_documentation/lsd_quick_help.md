LSD Quick Help

General questions
What does an error message mean?
LSD issues an error message whenever it is not able to complete the last task requested by the user. There are several categories of possible errors. The most common are:

·         Compiler errors: presented when the compiler cannot interpret or disambiguate a command in the equation file. It may be caused by several situations, like invalid syntax, typos, undeclared variables, etc. See the most common cases below. When LMM presents a compiler error it also offers the possibility to directly jump to the file and position where the compiler found the error. Note that this error may have occurred before this point (usually not by much) but never after it. Please try to read the message(s) presented in the errors window in the order they are shown to facilitate understanding the origin of the problem (it is common that a single error originates more than one message).

·         Simulation startup errors: displayed when the model configuration is incomplete and the simulation cannot run yet. Typical reasons are: missing (or misspelled) Variables, Parameters or Equations (see here and here), missing initialization data (here). Please check the message provided in the Log window for suggestions on how to fix the problem and run the simulation again.

·         Run time errors: shown when there is an error during the simulation run. There are many circumstances where run time errors may occur and the most frequent are: missing (or misspelled) Variables, Parameters or Equations (see here and here), invalid values produced while computing an Equation (here and here) or generic system crashes. Please check the message provided in the Log window for suggestions on how to fix the problem and run the simulation again.

What is a LSD model program?
A LSD model program is the executable compiled file, including all the Equations code. The LSD model program is usually executed using LMM. The LSD model program can create new or edit existing configurations and analyze results files.

For further details, please check the FAQ.

What is a model configuration?
A model configuration is a collection of interconnected Objects, Variables and Parameters, their initial values (when needed) and the remaining data required to allow the simulation run. A model configuration is stored in special files (with extension .lsd) that are created, saved and loaded by the LSD Browser. Model configurations define the state of the model at time 0, just before starting the simulation. They are created using menu Model in the LSD model programs, and saved or loaded using the menu File.

For further details, please check the FAQ.

What is a simulation run?
To perform a simulation run, LSD requires an equation file and the corresponding model configuration. The simulation run encompasses all the simulated time steps, from t = 1 until the maximum value defined by the modeler (the default is t = 100). For any time step, all the Variables of the model are updated once, and only once, using the associated Equation. At the end of each time step all elements of the model marked to be saved have their values registered for post-simulation analysis.

For further details, please check the FAQ.

What are a Variable, a Parameter, and an Object?
A LSD Variable is a model element to which a simulation run

 associates a real number for each time step (a discrete time t). Modelers control the model dynamics only by means of computations executed in the Variables' Equations.

A Parameter is an element that does not change its value (a real number) unless some Variable's Equation overwrites its value during its computation.

Objects are containers of variables, parameter or other objects, so that a model is structured as a hierarchical (inverted) tree of objects.

For further details, please check the FAQ’s (here, here and here).

What is an Equation?
An Equation is a chunk of code to be executed at any time step to compute the value of a Variable. Equations are stored in an equation text file and are generally written using LMM, the integrated developing environment for LSD models. The same Equation code for a Variable is executed in a given time step as many times as the number of instances (copies) of that Variable exist in the Objects of the model.

Equations can be written using valid LSD keywords (macros or functions) and C++ statements. However, most of the time modelers can resort to simpler LSD macros and avoid the complexity of C++ coding.

For further details, please check the FAQ.

What are initial values, number of objects and simulation settings?
A LSD model configuration requires all the numerical values used to start a simulation run:

·         Initial values for Parameters and lagged values for Variables, to be used in the first step of the simulation run. They are set in the LSD Initial Values Editor invoked by the menu Data>Initial Values option.

·         Number of each Object type, determining how many Objects are present in the model and, therefore, how many Parameters, lagged Variables’ values and groups of descending Objects exist. These values are set in the LSD Object Number Editor opened from the menu item Data>Number of Objects.

·         Other simulation settings, like the number of time steps, the number of simulation run repetitions, the Variable time series to save, and the time series to show during run time.

Options for Variables, Parameters and Objects, may set from the main LSD Browser window or the LSD Model Structure window by right-clicking on the element concerned or yet from menu Model. The simulation settings can be adjusted from menu option Run>Simulation Settings.

For further details, please check the FAQ.

What is LMM?
LMM (LSD Model Manager) is an integrated development environment (IDE) for LSD models. It is composed by:

·         LSD Model Browser. Modelers typically work on several models at different stages of development and the LSD Model Browser allows managing them in organized directory (group) structures. The LSD Model Browser allows also the creation of new models from the scratch or using existing models as templates.

·         Text editor. It is suited for developing LSD code in particular, including syntax highlighting, template wizards to common LSD commands, and multi-source-file projects management.

·         Model compilation and debugging manager. Whenever an equation file has been edited, LMM automatically recompiles your model program and launches the LSD Browser if there is no compilation error. LMM can also create special, high-performance command-line (‘No Window’) versions of the model programs. Launching external C++ debuggers is also supported.

What are the LSD Browser, the LSD Data Browser, and the LSD Debugger?
There are many ways to inspect a model, before, during and after a simulation run. The main ones are:

·         LSD Browser. Shows the structure of the model as well the hierarchical lists containing every element of the model: Variables, Parameters, and parent and descending Objects.

·         LSD Data Browser. Shows the contents of the selected instance (copy) of an Object. It is possible to observe the values stored in all its Variable and Parameter instances. Also, the modeler can change initial values from this interface (when used before the simulation is run).

·         LSD Debugger. During a simulation run it is possible to interrupt the simulation, inspect the model state (as with the LSD Data Browser), and analyze the results generated so far, among other operations. The debugger allows the modeler to follow the simulation dynamics equation-by-equation and step-by-step, and to modify any aspect of the model current state.

What is the LSD Analysis of Results?
After a simulation run the time series from the Variables (and sometimes Parameters) set to be saved are available for post-simulation analysis. It can be activated from the LSD Browser after a simulation run using the menu Data>Analysis of Results.

This module provides the most used tools to analyze the data produced by the simulation run: time series and cross-section plots, sequential and scatter plots including phase diagrams, histograms, descriptive statistics, and more. Plots can be exported as encapsulated postscript (EPS) files, while all the data can be exported in a variety of formats for more sophisticated statistical treatment in packages like R.

For further details, please check the FAQ.

What is a model report?
The HTML model report provides a complete and easy to use description of the model content and structure. It is also possible to produce reports in Latex documents (better for printing). Reports are generated using the menu options Model>Create Model Report, Model>Create Latex Table and Model>Create Latex References.

The descriptions for each element in the different sections of a HTML report are hyperlinked, so users can, for example, pass from the verbal description of a Variable, read its code, see the initial value of a Parameter used in the Equation, read the description of the Parameter, see the list of other equations where the Parameter is used, see all the Variables and Parameters contained in the same Object, etc. All these operations are executed by clicking on the links in the report file.

For further details, please check the FAQ.

 ▲Top

How to
Load a configuration file
Menu File>Load allows choosing one of the available model configuration files (created by the user or received from the model author). These files contain all the necessary information for running the simulation. Once loaded, the configuration file name is shown in the title bar of all LSD windows.

If a configuration is modified (e.g., changing parameters' values), the changes are automatically saved in the present configuration overwriting the previous file. To avoid this it is necessary to save the modified configuration with a different name before running the simulation (meu File>Save).

For further details, please check the FAQ.

Run a simulation
To run a LSD simulation model in LMM choose the menu Run>Run. If the current model configuration is not saved yet, a confirmation dialog is presented, offering to save the current configuration before proceeding. Also, if multiple simulation repetitions were configured in Run>Simulation Settings a dialog box shows before execution informing the location and the names of the files used to save the results of each repetition.

Note that a model configuration must be loaded or created before running a simulation. Moreover, after a simulation is run it is necessary to (re) load a configuration file before being able to run (again) a simulation.

Analyze the simulation results
It is possible to analyze the results only for the time series explicitly saved during a previous simulation run. The menu Data>Analysis of Results option starts the analysis of results module. Users have two options of data to analyze: the results of the latest simulation run (if still stored in the memory), or results previously saved to file(s). If a simulation has not been run yet, only the second option is available. The module for Analysis of Results allow the creation of graphical representation of time series, the computation of some statistics, to export the data in several formats, the creation of EPS graphical files of the produced graphs.

For further details, please check the FAQ.

Browse the model
The main LSD Browser window allows modelers to review and edit the model structure. When a model is loaded the Browser shows the highest-level Object in the model (inverted tree) hierarchy, always called Root.

To move “down” in the model structure, double-click on the name of any Object descending from the current one (left hand side list in the Browser). To move “up” in the structure, click on the name of the parent Object to the current one (just above the two lists in the Browser). It is also possible to click directly in the desired Object on the graphical representation of the model in the LSD Model Structure window.

Set initial values
To change the values of Parameters or lagged Variables initialization for a particular Object, first navigate in the LSD Browser to the desired Object (see above). Then choose menu option Data>Initial Values. This will show the spreadsheet-like LSD Initial Values Editor window. The table containing one row for each Parameter or lagged Variable and one column for each Object instance.

Set the number of Object instances
Choose the menu option Data>Number of Objects to open the LSD Object Number Editor. In the editor it is possible to modify the number of instances for any Object type. When opened, the editor shows the user-created Objects at the top of the model structure (the first level). Using the ‘+’ and ‘-’ buttons the user can show the desired levels in the inverted tree hierarchy. The numbers inside the buttons beside each Object type indicate the existing number of instances. To change the number of instances, simply click on the corresponding button and fill the requested information.

Alternatively, the user can change the number of instances of a given Object by right-clicking it in the desired Object on the graphical representation of the model (LSD Model Structure window) and selecting Number of Objects.

Change an element name, type or number of lags
Any existing model element (Object, Variable or Parameter) can have its name (label), type and the number of required lags (only Variables) modified after its creation. Use menu options Model>Change Object and Model>Change Element to modify the current LSD Browser Object or Variable/Parameter, respectively, and click the Properties button in the dialog window.

Alternatively, the element can also be modified by right-clicking its name in the Browser or the LSD Model Structure windows and selecting option Properties.

Select elements to save data
By default, no Variable (or Parameter) is saved by LSD during a simulation run. Please to change the model configuration to save the required elements before running the simulation. To save the complete time series data for any Variable (or Parameter), please use the associated element’s options window by using the menu option Model>Change Element. In the Change Element window, please check the option box Save and press OK.

As a shortcut, the user can also tick (or untick) the elements to be saved by right-clicking the element name in the LSD Browser and selecting Save in the context menu.

Set other simulation settings
Other than the configuration of the main model’s elements, some additional simulation settings require the user attention. The most relevant items are the number of steps per simulation, the number of simulation runs, and the seed number for the pseudorandom number generator. Their adjustment is done using the menu option Run>Simulation Settings.

Debug a Variable computation
Sometimes it is not easy to grasp why the computation of a given Variable is not producing the expected results. To help the modeler to understand the calculated values, and fix the corresponding Equation if there are problems, LSD offers a debugger.

To use the LSD Debugger, it is necessary, first, to set the Variables whose computation should be analyzed. To set each one, open the Variable’s options window by using the menu option Model>Change Element. In the Change Element window, please check the option box Debug and press OK. Alternatively, tick (or untick) the Variables to be debugged by right-clicking the Variable name in the LSD Browser and selecting Debug in the context menu.

Second, in the window for the simulation settings (menu Run>Simulation Settings), set the time step in which the debugging session shall begin in the field Start debugger at step (a value equal zero disables the debugger).

Third, run the simulation. When the chosen time step is reached, the simulation will stop just after each of the selected Variables’ Equations are computed and present the LSD Debugger window. At this moment the user can inspect the state of any element in the model and also check the values of the intermediary variables used during the Equation computation. When the inspection is done, the user can simply click the button Run to restart the simulation.

Solving common problems
Cannot start the simulation run
·         A model configuration is loaded? Load a configuration file before running the simulation.

·         A model configuration is loaded and I just ran the simulation but cannot run it again. Load (or reload) a fresh configuration to restart the simulation (menu File>Load or File>Reload) even if the configuration is not going to change. If you want to use the current data in the model (i.e., the values at the last time step of the latest simulation) as the start for a new simulation, then first save the current model state as a new configuration file (menu File>Save).

·         A configuration is loaded but I changed some number of Objects and now the simulation refuses to run. When new Object instances are created, LSD assigns “inherited” initial values, but does not allow running a simulation with such values without user confirmation. Move the LSD Browser to the Object whose number you modified and set their initial values (menu Data>Initial Values). If you want to accept the inherited values, simply press Done in the LSD Initial Values Editor to confirm.

Cannot change the initial values or the number of Object instances
·         A model configuration is loaded? Load a configuration file before running the simulation.

·         I have just run a simulation and LSD does not allow me to change the model’s elements. LSD blocks modifications after a simulation run, because the data resulting from the simulation run (the model state currently in memory) may not be suited to restart the simulation. In most of the cases, you should first load (or reload) a fresh configuration (menu File>Load or File>Reload) before modify the model configuration. If you really want to use the current data in the model (i.e., the values at the last time step of the latest simulation) as the base for a new configuration, then first save the current model state as a new configuration file (menu File>Save).

Cannot find a Variable in Analysis of Results list after running the simulation
·         The desired Variable data series was not saved. By default, LSD does not keep the data of Variables for post-simulation analysis. The user must specify which Variables shall be saved.

·         The Variable is marked to be saved, but it is still not visible in the Analysis of Results. It is possible to configure LSD to ignore the updating of Variables in some Objects (and their descendants). This option, turned off by default, allows speeding up a simulation but relies on the modeler to ensure that the variables in the skipped Objects are updated if not explicitly used in other Equations. To turn the option back off, set LSD Browser to the containing Object and select menu Model>Change Object and make sure the check box Compute is ticked.

The Variable is in the series saved list but the values are not a number (NaN)
By default LSD stops the simulation run if any Equation produces an “abnormal” result (infinite or not a number/NaN). However, the user can change this behavior using the USE_NAN macro, which allows the usage of NaN’s as a way to indicate that a value is not available at the time. This may be important to avoid biases in statistical calculations using the produced data series. If this is not your case, please consider removing the USE_NAN from your Equations and use the debugger to understand why the Equation is producing the NaN (as an invalid mathematical operation).

Cannot find the model reports
First make sure that the desired report was created (use menu Model>Create… in LSD Browser). All the model reports are created in the model’s home directory. You can check the home directory using the menu option Model>Model Info in LMM. 

Simulation run aborted
The simulation was running and a small window appeared. When a bug (problem in an Equation’s code) is encountered during a simulation run, most of the times LSD is able to gracefully “capture” it. At this point LSD interrupts the simulation and signals the type of the error in the Log window, together with suggestions for the correction, if possible.

From an aborted simulation run, you have two options:

·         Go back to the LSD Browser: there you can explore the model status to acquire additional information on the problem and change the model configuration or use the debugger to better understand the problem, if needed.

·         Quit the LSD model program and go back to LMM: if you understand what the problem is, change the offending Equation’s code to prevent it and rerun the simulation.

Everything disappeared (all LSD windows simply closed)
·         I simply closed one window and all the rest closed together. The LSD Browser and Log windows cannot be closed without fully exiting the LSD model program (except for LMM). If your current model configuration is not saved, a dialog box will confirm before closing LSD.

·         The simulation was running and crashed suddenly without any message. Most of the times there is a more serious bug in the Equations code which caused the program to crash, sneaking through the LSD bug controls. This is a quite rare case, but it is possible. These are the cases of some rare errors when using C++ libraries (e.g., advanced mathematical functions) or performing unchecked pointer (direct memory access) operations. The only way to solve this class of error is to fiddle with the crashing Equation code (the DEBUG and DEBUG_AT macros may help identifying the culprit).

Errors and possible fixes
Compiler errors
Some of the most frequent errors are:

·         Invalid identifier: in LSD (and C++) any block of alphanumeric characters (except pure numbers) must be defined before it can be used. LSD and C++ predefine a set of commands and temporary variables for the modeler and she must be sure she is using the exact same string of characters when using them.

·         Incorrect or inconsistent use of upper/lower case characters: LSD (and C++) differentiates between upper and lower case letters. So, a Variable named X is completely different from another one labeled as x. The same applies to C++ keywords (always lowercase) and LSD macros (always uppercase), so, for instance, IF, Else, equation, Result are invalid identifiers (the only correct ones are if, else, EQUATION, RESULT).

·         Missing ‘;’ command separators: LSD (and C++) requires a semicolon character (‘;’) between most commands, so it can identify when a command terminates. Note that spaces or new lines do not mark the end of a command. The C++ compiler completely ignores blank spaces and new lines; they are inserted to make the code more understandable by humans.

·         Unbalanced ‘( )’, ‘[ ]’, ‘{ }’ pairs: LSD (and C++) demands that any open block character (an opening parenthesis, bracket or curly bracket) is matched by a following closing block character (exactly a closing opening parenthesis, bracket or curly bracket, respectively) before the end of the equation file. If everything seems correct at the lines indicated in the error message, test the curly brackets and parentheses of the equation file (starting from the very first one) using the command Match{} or Match() in LMM menu Edit (see here for help): each open bracket or parenthesis must match with a closing one. If no match is found, then there is the problem.

·         Unavailable libraries: LSD requires certain code header and library files to be installed in known locations in the computer. If the compiler cannot find those files during the compilation, errors like cannot open XXXX: No such file or directory may be presented. This normally signals that the required files are not installed (see Readme.txt for the precise requirements on each operating system) or LSD is not configured properly. In the last situation, please select Model>System Options in LMM and make sure you select the correct default configuration for your operating system.

Simulation run errors
It is possible that during a simulation run an error occurs, preventing the simulation to continue. Most of these errors are captured by LSD before they crash the whole program. The messages in the Error dialog windows and in the LSD Log window communicate what kind of error occurred and usually provide hints on how to fix it. Read the messages carefully to understand what happened and under which conditions, and try to apply the proposed fixes.

After a simulation run is stopped by an error, the user has two options:

·         Return to LSD Browser: stop the simulation and return to the LSD Browser as in a successful simulation run, so it is possible to browse and analyze the model data at the moment of the crash. Use this option if you don't need (yet) to change the model Equations' code, but maybe just add an element or modify some names. In this case, the user can reload the model configuration and fix the error.

·         Quit LSD program: close the LSD model program. This is necessary if the error must be fixed by modifying the code in the equation file. In this case, the equation file needs to be recompiled in a new LSD model program and it is recommended to close the one still open.

HINT: by far, the most frequent error consists in a mismatch between the names in the model configuration and the names used in the equation file. For example, suppose you have a model configuration containing a Variable Profit, but in the code for an Equation, say Investment, you have typed PrOFit. When the faulty Equation is computed, the LSD Log window will issue the message:

Search for 'PrOFit' failed during the equation of variable 'Investment'

Moreover, the Log window will indicate the time step at which the error occurred, and the list equations currently under computation (for technical details, see LSD Simulation Manager). To fix this error you need to use the same spelling for all the occurrences of each Variable in the Equations' code and in the model configuration. This may entail either to change the equation file (using LMM  to edit the misspelled text in the equations code and recompiling the LSD model program) or modifying the name of the Variable using the in the option window for the element in the LSD Browser.

The simulation cannot start: initial data not available
LSD found that some initial values (for Parameters or lagged Variables) have not been defined by the user. This may happen because a new Parameter or lagged Variable was inserted, but not initialized, or when the number of Object instances is increased, but no initial values for its contained Parameters and lagged Variables were explicitly set. In both cases LSD does assign default values to the new elements but those must be, at least, explicitly confirmed by the modeler.

To fix the error reload the model configuration, move the Browser to show the Object containing the uninitialized elements, and choose menu item Data>Initial Values. Edit the appropriate fields and click Done. This process must to be performed even if all the default values are to be accepted.

The simulation is interrupted: equation not found
The LSD model program tried to compute a Variable but could not find the corresponding Equation. There may be some reasons for this:

·         The Equation does not exist in the equation file. Add an Equation for the variable using LMM to the equation file. See here for an introduction to LSD model writing.

·         The Equation does exist but its name is misspelled. That is, the name for the Variable in the equation file is different from the name in the model configuration. You can either change the label in the equation file or edit the label in the configuration. In the first case, you need to close the current LSD model program and recompile a new LSD model program with the new equations' code.

·         The Equation name is spelled correctly but the LSD model program was compiled with a different equation file. When LMM compiles and runs a LSD model program, it uses the name of the equation file set at menu Model>Model Options, identifier FUN=. If you wrote the Equation in a different (wrong) file, like in modelinfo.txt, the generated LSD model program does not contain the correct Equations. To check which file LMM is using use the menu Model>Show Equations in LMM to see the correct one. If your Equations are placed in a different file you can simply copy and paste its contents back to the correct file in LMM.

The simulation is interrupted: element not found
This error indicates that the indicated Equation contains a reference to an element (Variable or Parameter) that could not be found in the model. Likely, it is a misspelling between the Equation's code and the name of the element in the model configuration. Or, possibly, you forgot to include the element in the model configuration. To fix this error, please review the equation’s code in or the change/add the element in the model configuration.

To correct the error you need either to change the Equations code, or to change the name of the element in the model structure. In the first case, close the LSD model program, edit the equation file using LMM and add or fix the name of the missing Equation. Save the equation file and compile and run the same model configuration file (which caused the error before). In the second case, simply reload the problematic configuration and edit the model configuration causing the problem to correct the name or add the missing element. After the changes, try to run the simulation again with the fixed model configuration.

The simulation is interrupted: lag error
This error causes a message telling that a Variable value was requested in an Equation with a lag number larger than the maximum lag defined in the model configuration. It may be an error in the Equations' code, requesting the wrong lagged value, or in the model configuration, defining an insufficient maximum lag number. In the first case, edit the equation file using LMM and add or fix the wrong Equation. In the second case, follow instructions on how to modify the maximum number of lags.

The simulation is interrupted: deadlock error
This kind of error occurs if an Equation for Variable X requires the value of another Variable Y whose Equation, in turn, requires the computation of Variable X. This is a kind of “egg or chicken” problem that cannot be solved without adjusting one (or both) of the Equations for X and Y. The conventional solution is to have (just) one of the two Variables using the lagged value (t – 1) of the other.

Notice that the error message in the Log window shows the two Variables involved in the deadlock. Close the LSD model program, edit the equation file using LMM and modify the Equation for the chosen Variable. You may have also to follow the instructions on how to modify the maximum number of lags for the other Variable.

Invalid values produced
The result of an Equation computation produced an invalid value. Typically, this happens when an illegal mathematical operation is performed, like having a divisor equal to 0. The error message indicates the Equation producing the invalid value, so please revise its code in LMM. If the problem is not trivial to be identified, using the debugger makes possible to review the values used for the intermediate calculations (v[0], v[1], etc.) to find the error.

Operation requested to a NULL pointer
Most of the LSD commands used in Equations are applied Objects. During the computation of an Equation LSD knows the object containing the Equation under evaluation and the Object which requested the Variable’s value. If an operation has been requested to a non-existing Object (one with a NULL pointer) the operation cannot be concluded. The error message signals the Variable with the faulty Equation and, in the Log window, other information is provided to understand the reason for the failure.

Sudden crash: LSD model program closes abruptly
These errors are rare since LSD is able to capture a potentially disruptive error before crashing the LSD model program, but, when they occur, they are the most difficult to fix once there is no indication on where they occurred. Firstly, therefore, it is necessary to identify the Equation during the computation the problem occurred. To do this insert in the equation file the macro DEBUG or DEBUG_AT(XX)(XX is the time when to start collecting information) immediately after the MODELBEGIN command. Recompile and run the simulation. After the crash, open the new file log.log which contains the list of all Variables successfully computed. The last one will be the variable that caused the system to crash. Once you know which Variable caused the crash inspect the code for the variable. You may also insert the command INTERACT(...) to interrupt the simulation during the computation of the problematic Equation.

For example, let's assume that you have a model that crashes at time 32. You can then insert in the beginning of the equation file the following line:

#include "fun_head_fast.h"

MODELBEGIN
DEBUG_AT( 32 )

This line will cause the system to write all the variables executed after time step 32. Once you discover that the variable causing the crash is Price you may insert use INTERACT(...) to inspect the model. For example:

EQUATION("Price")
/*
Compute the price as the inverse of Q
*/
v[0] = V( "Q" );
if ( t == 32 )
  INTERACT( "Value of Q", v[0] );
v[1] = 1 / v[0];
RESULT( v[1] )