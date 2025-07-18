Basic LMM usage and running example models

This tutorial guides first-time users to open LMM (LSD Model Manager), explore its basic components and test the running of the example models available in the LSD installation.

The only way to learn how to use any software is to try it. Therefore, users are invited to explore any aspect of the several windows appearing while following the tutorial. LSD comes with an extensive manual (see here for a list of the main pages), covering every module in the package, and discussing many issues concerning LSD simulation modelling.

The following guided operations follow the basic steps required for an early exploration of LSD. There are many links to other manual pages, so more in depth information is always available. Use the navigation bar in your screen to access the help links at any time, observe the LSD/LMM windows, and return to this page.

If not already done, please first install LSD following the instructions in the manual.

Operation

Instructions

Open LMM

Double click LSD (LMM) icon in the desktop. The LSD (LMM) icon should have been created during the LSD installation. If the icon was deleted (or otherwise is not available), you may recreate it following the instructions contained in Readme.txt for your operating system (Windows, Linux or macOS).

Alternatively, you may also invoke LMM from the file explorer program by double-clicking the appropriate file in the LSD installation directory (Windows: run.bat or run64.bat, Linux: lmm or lmm32, macOS: lmm[.app] or lmmOSX) or running it from a command prompt or terminal window.

Observe LMM
Interface

For now, close the window named LSD Model Browser that should have open in front of the main LMM window by pressing Esc or clicking on the close window icon (the X on the right side of the title bar).

LMM is mainly a text editor with several menu options to perform the most common computer code editing. Menu File allows the loading of the model to be used, among other file oriented options. Menu Edit includes many commands useful for writing and editing LSD Equations code.

The menu Model is special. It allows performing actions on a LSD model. For example, the menu command Model>Show Equations automatically opens the file containing the model’s Equations. Command Model>Show Description loads the description file for the model, usually including instructions on how to configure and run the model. Note that most of the items in the Model menu are only active when there is a model loaded.

The menu Help offers the manual pages most useful to LSD programmers.

The icon toolbar in LMM offer a shortcut to some of the most used menu commands. Please note that just hovering the mouse cursor over the toolbar buttons will display the associated command names on the right side of the bar.

See the manual for further information on the LMM interface.

Select a model

Select menu option File>Browse Models (or click on the yellow folder icon). The LSD Model Browser window will reopen listing all the models available in the computer. Models are organized in a tree of groups, like directory/folders in the file system. As the user scrolls through the list, a brief description of the model highlighted is shown. Navigation in and out of groups is also possible with the usual file browser commands. Enter the Example Models group, choose one of the example groups available and then select the desired model (e.g., in the Literature Models group, pick Game of Life model).

When the desired model is highlighted (single click or arrow keys), selected it with a double click or pressing Enter. LMM will load the model and present the full model description, if any, or the model Equations’ code, otherwise.

A LSD model is a combination of C++ compiled code (implementing the model Equations) and a LSD-specific data structure implementing the model configuration. Using LMM a modeler can access the equation file containing the code for the equations (i.e., how each of the model’s Variables compute their values) and modify it. LMM permits also changing the model compilation options, and, generally, performing every operation necessary to create the LSD model program. 

When a model is loaded in LMM, the editor shows initially the same description seen in the LSD Model Browser. Moreover, the commands in menu Model become active on the model selected and the header line of LMM reports the model information. Users can use the menu Model to access the most relevant model files and settings.

See the LMM help page for more information on menu Model.

Run the LSD model
program

Create a LSD model program using the command Model>Compile and Run (or click on the second yellow lightning icon, the one with the green arrow). LMM automatically (re) compiles all the required LSD modules including the equation file. If no errors are found, the LSD Browser for the model is launched. Failure to compile is more frequently associated with errors in the model’s code but sometimes is due to a wrong LSD configuration (to be sure, reset your system configurations using the command Model>System Options, and clicking on the button Default XXX appropriate to your computer type). See the manual page on the Compile and Run command. The very first time this command is issued it may take a longer time to complete, once it must also compile the LSD source files. Future compilations will be much faster, having to just refresh the model’s Equations.

A LSD model program is an independent program containing the equations code that tell LSD how to compute each Variable at each time step. Any LSD model program has the same appearance, a common interface used to load and save model configurations, to edit the initialization data and settings, to control a simulation run, and to manage the analysis of the results. However, each model program differs in the Equations it contains and can only run configurations matched to it.

The main interface in the model program is the LSD Browser window. It allows issuing commands before and after a simulation run (during the simulation run it is not active). The menus in this window contain all the commands to control every aspect of a LSD model simulation (see the help page on this).

The LSD Log window presents messages relevant to the simulation configuration and run. Also, it is used to control the simulation run (e.g., interrupt or abort a running simulation). Several other windows are created depending on the actions requested by the user (see the windows list for the most important ones).

Run a test simulation

On the LSD Browser use the menu command File>Load (or click on the yellow folder icon), choose one of the available configuration files, and then select menu command Run>Run (or click on the blue triangle/play icon) to run the simulation. The simulation will show either the LSD Run-time Plot window presenting some of the time series being produced, or will just print messages in the LSD Log window, or both. The data produced during a simulation is stored in the computer memory so it can be analyzed after the simulation run (or during the interruption of a run). These operations will be presented in the next tutorial.

After the simulation is run, close the LSD model program by using the LSD Browser menu File>Quit (or clicking on the close window icon, the X on the right side of the title bar) and confirming that you don’t want to save the produced results. See help on the LSD main Browser, or the general help page on LSD for further details.

Select and test 
other models

Back in LMM, select, compile and run other simulation models. Remember to close the LSD model program before running another model. Multiple models can actually run in parallel, but this may overcrowd your screen and make the windows handling harder for beginners.

End of the tutorial

You are now ready to pass to the next tutorial, where you is going to learn how to use the LSD model program features to control the model configuration and analyze the results from a simulation run.