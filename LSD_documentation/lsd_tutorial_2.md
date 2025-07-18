Using an existing LSD Model

This is a tutorial presenting the main steps to start using LSD models for practical purposes. The goal of a simulation exercise is to obtain interesting results and understand why they have been produced. Therefore it is not sufficient to obtain fancy plots, but it is also necessary to get into the code of the model, and understand how it is functioning.

After all, the best way to learn how to use a LSD model is, like any software, by trial and error. This tutorial should enable you to fully exploit an existing model, and to explore the LSD interface even in the parts not explicitly covered here.

To run a simulation exercise with LSD it is necessary:

1.    If not already done, please first install LSD following the instructions in the manual.

2.    A LSD model program. This is a program implementing the Equations for a given model and the LSD internal code. The modeler has created the code for the Equations, and users typically do not modify it if the just want to run the simulation model.

3.    A matched model configuration. This is (at least one of) the configuration for the model prepared by the modeler. It contains details of the model in terms of the model structure (the Objects tree) and the initial data required by Variables and Parameters. The configuration contains also all the remaining information necessary to run a simulation: the number of time steps, etc. Users can easily modify each of these values to test different configurations.

The table below contains the detailed steps used in this tutorial. It consists of three columns:

1.    Operation: a summary of the operations to perform in each step.

2.    Window: indicates the target window to be used in the step: the many LSD windows, the web browser, or the operating system (Windows, Linux or macOS).

3.    Instructions: This cell contains the commands to perform (menu choices, mouse actions etc.) followed by an explanation on the operation performed.

WARNING: Using LSD entails the access to several windows opened at the same time and sometimes the one to be used is hidden just behind the others. It is strongly advised to the user to make use of the computer taskbar to switch among LSD windows.

Operation

Window

Instructions

Open LMM

Operating system

Double-click LSD (LMM) icon in the desktop.

The LSD (LMM) icons should have been created during the LSD installation. If the icon was deleted (or otherwise is not available), you may (re)create it following the instructions contained in Readme.txt for your operating system (Windows, Linux or macOS).

Alternatively, you may also invoke LMM from the file explorer program by double-clicking the appropriate file in the LSD installation directory (Windows: run.bat or run64.bat, Linux: lmm or lmm32, macOS: lmm[.app] or lmmOSX) or running it from a command prompt or terminal window.

Run the LSD model program for the selected model

LMM
and
LSD Model Browser

Select menu option File>Browse Models (or click on the yellow folder icon). The LSD Model Browser window will reopen listing all the models available in the computer. Models are organized in a tree of groups, like directory/folders in the file system, and navigation is done using the usual file browser commands. The user may have to navigate into the groups until the desired model is listed.

When the desired model is highlighted (single click or arrow keys), selected it with a double click or pressing Enter. LMM will load the model and present the full model description, if any, or the model Equations’ code otherwise.

Create the LSD model program for the model using the command Model>Compile and Run Model (or click on the second yellow lightning icon, the one with the green arrow). LMM automatically (re) compiles all the required LSD modules including the equation file. If no errors are found, the LSD Browser for the model is launched. Failure to compile is more frequently associated with errors in the model’s code but sometimes is due to a wrong LSD configuration (to be sure, reset your system configurations using the command Model>System Options, and clicking on the button Default XXX appropriate to your computer type).

When the LSD model program is launched, it opens two windows, the LSD Browser and the LSD Log. However, the model configuration is initially empty, once no configuration is loaded yet.

Load a model configuration file

LSD Browser

Use the menu command File>Load (or click on the yellow folder icon) and choose one of the proposed configuration files.

A complete model configuration contains the model description, the initial data, and (supposedly) everything else required for running the simulation model. The modeler (should) have prepared at least one configuration, and more can be created with the LSD Browser.

The LSD Browser now shows the Object named Root as containing some elements. A graphical representation of the model is shown in a LSD Model Structure window. The LSD Browser is thought as a control center to issue commands to LSD and to inspect the model configuration details, like an Object properties. The LSD Browser is always pointed to an (current) Object, as indicated in the information bar, and lists its contained Variables, Parameters and descending (son) Objects.

Take a first look at the model

LSD Browser
and
LSD Model Structure

Although you may already run the simulation, spend some time to look at how LSD represents the model. 

Check the graphical representation of the model structure on the LSD Model Structure window. Hovering over the Object you can uncover the list of contained Variables and Parameters. The numbers below the Object types indicate the respective number of instances. The context menu (right click) of each Object allows directly changing its properties. It is still possible to click on any Object to move the current LSD Browser Object there.

The “skeleton” of the model is made of Objects, elements containing Variables, Parameters, or other (descending) Objects. Therefore, a model is represented by a (inverted tree) hierarchy of Objects whose “top” element is conventionally called Root. Root is the only Object that is always present in a model with a single instance (no copies), while all other Objects can be multiplied in as many instances as desired. Users can change these values, as we will see later.

Variables and Parameters are names (labels) attached to (real) numerical values. The key difference is that a Variable in principle changes its value at each time step using a specific Equation, while a Parameter do not have an Equation and typically has a constant value (although an Equation for a Variable can change the value of a Parameter during the simulation run). The purpose of Objects in a LSD model is to contain and organize its Variables and Parameters. Multiplying the number of instances of an Object type, also multiply the instances of the contained Variables, Parameters and son Objects. This is similar to using vectors and matrices in conventional programing, but far more efficient in most applications.

It is possible to explore the model with the LSD Browser, which shows one single Object's content at a time. There is a bar presenting the current Object and its parent and two list boxes: the descending (son) Objects, at the left, and the Variables and Parameters, at the right. Variables (V) which are indicated with a number (V_X) of X lagged values (used in the model for computations involving this Variable) and Parameters (P). Any element in the Browser can be double clicked to set their options and see their documentation (see below). The context menu (right click) for each element is also available for quick changing most settings. The current Object in the Browser can be changed to another one by double-clicking the desired (son) descendant (to go down in the hierarchy tree) or on the name of its parent (to go up). You can also use the arrow keys, Enter and Backspace (as in a file browser) to move along Objects, Variables and Parameters. 

Generate and analyze the model report

LSD Browser
and
Web browser

Now, select option Model>Create Model Report to generate a detailed report about the model. Accept the default options in the Report Generation window and click in OK. The produced report should be automatically presented in your web browser. At any time the model report can be retrieved again using the menu option Help>Model Report.

The exact role of each element (Object, Variable or Parameter) in the model depends not only on its own content but also on its relation with the rest of structure of the model. To grasp this aspect of a LSD model, one valuable tool is the model report. It is a standard HTML document that can be loaded in any web browser (e.g., Chrome). The model report is a hyperlinked document containing the entire model information in a convenient format. The hyperlinks permit to see:

·         a textual description of the model, with an indication of the key elements to observe and configure (if provided by the modeler);

·         the hierarchy tree of Objects;

·         details on each Object and its content;

·         details on each Parameter and lagged Variable initial values;

·         where each element is used (e.g., the Variables using a specific Parameter);

·         which elements are used to calculate each Variable (e.g., the Parameters used in a Variable's Equation);

·         the Equation code for each Variable, with links to the used elements.

Spend some time to play with the links on the model report, to see how they uncover the model structure and content. Do not try, at least for complex models, to read systematically the document and to understand the whole model structure. Just start from one component, look at its equations, or the equations that use it, and continue along creating your own path through the model structure. 

Run the simulation

LSD Browser
and
LSD Log

Select menu command Run>Run (or click on the blue triangle/play icon) to run the simulation. If there are no unsaved changes, the simulation will start and show either the LSD Run-time Plot window presenting some of the time series being produced, or just print messages in the LSD Log window, or both.

This will run the simulation using all the configuration settings defined by the modeler (as we just browsed the model without changing anything). Before running the simulation, the system may issue a confirmation message, telling how the results data will be handled and/or confirming the saving of any unsaved change in the model configuration.

A simulation run consists in several time steps, during each of which all the Variables of the model are updated, using the associated Equations to compute the new values. During the simulation run, some Variables time series may be plotted in the LSD Runt-time Plot window, if they are configured so. If no Variable is set to be plot during the simulation run, the Log window may still print information about the ongoing status.

During a simulation run it is possible to use the buttons in the LSD Log window to control the process:

·         Stop: abort the simulation run (press ‘S’ as a shortcut);

·         Pause/Resume: allow the temporary suspension and resume of an ongoing simulation run (shortcut is ‘P’ or ‘R’), the LSD Debugger being available during the pause period;

·         Fast: hides the Run-time Plot window and set Log verbosity to a minimum to speed-up simulation run (same as the ‘F’ key);

·         Observe: show the Run-time Plot windows and enable more verbosity in the Log window (same as ‘O’);

·         Debug: interrupt the simulation run, if not already paused, when an equation marked to be debugged is computed (the simulation run may be resumed) (same as ‘D’);

·         Copy: copy the selected text in the Log window to the clipboard (same as ‘C’ or Ctrl+C);

·         Help: help on the Log window (same as ‘H’).

Analyze the simulation run results

LSD Browser
and
LSD Analysis of Results

After the simulation is finished or aborted, select the menu option Data>Analysis of Results (or click in the plot icon) in the LSD Browser. This command presents the list of all the time series stored in memory after the last simulation run in the LSD Analysis of Results window. Previously saved data files, from older simulation runs, can also be loaded in memory for analysis using the Add… button.

The run-time plot may have given you some intuition about the simulation results. However, the modeler is likely to have set more data to be saved, besides the time series shown during run time. In fact, LSD models allow choosing the Variables and Parameters values to be saved for later analysis (by default, none is saved).

The overall structure of the LSD Analysis of Results window is composed by the list box, on the left, of the elements with available time series for analysis. Some (or all) of these must be selected by double clicking the desired series, using the vertical button bar or using the context (right click) menu. Once one (or more) series are selected, it is shown in the central list box and is ready for further elaboration. Using the buttons in the lower part of the window, the user can create plots, produce statistics on and export the selected series. The right box contains the list of the plots already produced in the current session, for quick reload. For instance, select one of the available series (double click) and click on the Plot button to generate a time series plot of all the simulation run time steps. Next, click on Statistics to see some descriptive statistics about the series printed in the LSD Log window.

You may try to further explore the data available (see the manual on this topic for details). There are a large number of possible options to produce time series and cross-section plots, XY scatterplots, histograms, and more. Moreover, users can save selected data to files in a variety of formats. It is also possible to launch Gnuplot, a package for advanced function and data plotting.

Further and more advanced statistical analysis and data-charting resources are available at the R platform, including transparent usage of LSD hierarchical results data and sensitivity analysis, using the LSD-specific R packages.

Interpret the simulation run results

LSD Analysis of Results
and
Web browser

Plot graphs and statistics of the simulation data and use the model report to make sense of the time series meaning. Search in the documentation the elements of interest and look at their functioning in the model to understand the reasons for the obtained results.

When finished, close the LSD Analysis of Results window using the Exit>Qui and Return to Browser menu entry or simply click on the X in the title bar. If you have produce any plot, a confirmation dialog informing that unsaved plots will be lost, will show up.

Reload the model configuration

LSD Browser

Back on the LSD Browser, select File>Reload in the menu (or click on the green recycle icon). This will reset the model configuration to the values for beginning a simulation run again or for editing the configuration.

After a simulation run, LSD contains in memory the values for all elements as computed at the last simulated time step. To prevent mistakes, LSD prevents the immediate use of these final values as the starting values for a new simulation run. So, to run the simulation again or to modify its configuration a configuration file must be (re) loaded.

Note that, if you really want to continue the simulation from where it stopped, it is possible to save the current configuration status as a new configuration, which can, in turn, be loaded to continue the simulation exercise. However, this is not a common simulation situation, so be careful.

Modify the number of instances of an Object

LSD Browser
or
LSD Model Structure

In the LSD Browser, make the Object you desire to modify the current one and then select Data>Number of Objects in the menu (or click the white on green plus icon). Alternatively, in the LSD Model Structure, right click directly on the target Object and select Number of Objects in the context menu.

After selection this command, a new window opens, prompting you about the details on the desired change. Update the Number of instances field to the new number of instances desired for the selected Object. A number larger than the current one means increasing the number of instances (and you may choose from which of the existing instances the new ones should be copied). Conversely, a smaller than the current value means deleting some of the existing instances (and LSD will give the opportunity to choose which ones should be removed).

One obvious request to test a simulation model is to modify the number of Objects and, therefore, the number of Variables, Parameters and other Objects they contain. Using the interface described above it is possible to modify any group of Objects, yet always maintaining the same model structure. That is, any new Objects at higher level in the hierarchy will still contain the same type(s) of descending Objects at the lower levels. For details, please see the LSD help. 

Define the initial values of Parameters and lagged Variables

LSD Browser
or
LSD Model Structure

In the LSD Browser, make the Object which contains the Parameter or Variable you want to edit the current and then select Data>Initial Values in the menu (or click the spreadsheet with a pencil icon). Alternatively, in the LSD Model Structure, right click directly on the target Object and select Initial Values in the context menu.

When choosing the above command, LSD Initial Values Editor window opens and you may edit the initial values for all Parameters and Variables, used to start the simulation, contained in the current Object. When starting a simulation LSD needs to know the values to assign to the Parameters and to the Variables used with lagged values. Note that the hierarchical structure of the LSD models requires the usage of indexing to identify the Object instance containing the elements requiring initial values, so the first (brother) Object is number 1, the second, 2 and so on. This way the user can set different initial values for the same Parameter or lagged Variable across different (brother) Object instances.

The initialization of values is necessary also for the Object instances created when increasing their number (see above). The new instances are assigned a default value (copied from the selected existing instance), but usually the user must confirm this choice (just opening the LSD Initial Values Editor and clicking the Done button). Although the data may be inserted manually for each Object instance (up to 100), when there are many instances it is convenient to use the Set All button to set all the initial values at once. See the LSD manual for more details. 

When finished, click on Done to return to the LSD Browser.

Choose which Variables (and Parameters) to save data series, to plot at run-time, or to debug

LSD Browser 

Make the Object which contains the Variable (or Parameter) the current Object and then double click the desired element. This will open the Change Element dialog window, from where you can edit or modify any property of a Variable or Parameter.

For the chosen Variable or Parameter it is possible to decide whether:

·         it is be included in the data saved for analysis (mark the Save checkbox);

·         it appears in the run-time plot (mark the Run-time plot checkbox);

·         it triggers the LSD Debugger, interrupting the simulation run immediately after its computation (mark the Debug checkbox).

See the LSD manual for details on these and the remaining element configuration options.

These choices can also be changed quickly by means of the context menu by right clicking on its name on the Variables and Parameters list box in the LSD Browser.

Edit the simulation settings

LSD Browser

Use the menu option Run>Simulation Settings (or click the wrench icon) to adjust the remaining simulation settings.

In the Simulation Settings dialog window you may choose the number of time steps per simulation, the seed for the pseudorandom number generator, and number of simulation exercises to be run in a sequence. Sequential simulation runs use the same model configuration except for a different random generator seed (increased by 1 each turn). Running more than one sequential simulation runs cause LSD to automatically save the results data to files.

See the LSD manual for more information on these and some further advanced simulation settings available.

Save the modified model configuration

LSD Browser

The menu option File>Save (or click the blue floppy disk icon) saves the current model configuration in memory to a file, overwriting the last loaded configuration file (with the .lsd extension), if any, or under the default name Sim1.lsd otherwise.

If you want to preserve the original configuration file (which is frequently the case), the modified configuration may be saved using the option File>Save As, which allows the user to type a new file name or overwrite an arbitrary existing file. To preserve the existing configuration file, it is important to use the File>Save As command before trying to run the new unsaved configuration. Otherwise, LSD will prompt to automatically overwrite the originally loaded configuration file.

Run the modified model configuration

LSD Browser

After (optionally) saving the modified model configuration under a new name, you can use the command Run>Run (or click on the blue triangle/play icon) to run the simulation again.

It is possible that an attempt to run a modified model does not succeed. LSD may prevent running incomplete or inadequate model configurations. In these cases, messages indicating the problem and the possible fixes are printed in the LSD Log window. Typical errors are:

·         Model already run. The model configuration in memory is the last step of a simulation run, and not from a “fresh” configuration file. Load the original configuration file, make the changes indicated above, save the configuration under a new name, and, finally, run the newly configured model.

·         Data not initialized. If the number of Object instances is increased, the newly created instances contain Parameters and/or lagged Variables that must be initialized (or confirmed) before they can be used for a simulation run. Move the LSD Browser to point to the Object indicated in the error message (in the LSD Log window) and choose Data>Initial Values.

·         Inconsistent initial values. Inadequate values were chosen for Parameters or lagged Variables initialization. These may be causing, for example, divisions by zero during the computation of some Equation. The simulation results may be erratic in these cases, according to the random generator seed used, for instance, and may even cause sudden crashes of LSD. Revert to the unmodified original configuration file and try the changes again with different values.

For a more complete overview of the possible errors and their fixes, please check the quick help.

Test other aspects of LSD

Any LSD window

Explore any menu entry of the LSD Browser. As general advice:

·         the menu Model modifies the structure of the model, and should be used only by modelers since it likely entails required modifications of the Equations' code;

·         remember that when running a simulation the configuration is written on file, overwriting the last configuration loaded with the same name;

·         keep the LSD help pages open, helping to understand in detail the effects of any operation.

All other LSD windows are also open for experimentation. Just be careful when overwriting configuration files: everything else can be easily recovered by quitting LSD and restarting it.

Try another model

LMM

Select menu option File>Browse Models (or click on the yellow folder icon) to pick another model.

Create the LSD model program for the model using the command Model>Compile and Run Model (or click on the second yellow lightning icon, the one with the green arrow).

Use the menu command File>Load (or click on the yellow folder icon) and choose one of the proposed configuration file.

Select menu command Run>Run (or click on the blue triangle/play icon) to run the simulation.

Follow the instructions above to understand the differences (and the common stuff) between two LSD models.

Create your own model

LMM

As you have seen, using an existing model permit to modify every numerical aspect of the simulation. However, you are still constrained to keep the same model structure (Objects, Variables and Parameters) and Equations. This is because the structure influences the way the Equations compute their values for the Variables.

Follow to the last tutorial to learn how to create a new LSD model.