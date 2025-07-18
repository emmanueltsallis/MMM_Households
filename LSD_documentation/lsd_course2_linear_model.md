LSD- Lesson 1: Linear Model
 LSD- Laboratory for Simulation Development
 Lecture 1- Linear model

 Goal
 In order to familiarize with the procedures required to create
 and use a simulation program in LSD we start with an extremely
 simple model:
 Xt = Xt 1+m
 The simplicity of the model will allow to focus on the use of the
 LSD interfaces.

 Content
 In this lesson we will perform the following steps:
 1 UseLMMtocreate a new model, call it “Simulation 0”.
 2 Write the C++/LSD code for the equation of X and compile
 the LSD model program.
 3 Usethe LSD model program to create:
 1 anobject Obj;
 2 avariable X in Obj;
 3 aparameter m in Obj;
 4 Set the initial values for the number of copies of Obj, the
 X0’s, and m’s.
 5 Runasimulation exercise and read the results.

 LMM-create a new model
 The latest version of LSD can be downloaded from
 https://github.com/marcov64/lsd.
 To start the system run the run.bat file (Windows) or the lmm
 executable (MacOS or Linux, see the readme.txt file).
 You will launch LMM, an editor specialized to code LSD models and
 compile LSD model programs.
 At start time LMM offers the opportunity to browse the existing
 models. Choose this option or, if you already started the system,
 choose the menu entry Model/Browse Models.

 LMM-create a new model
 The models’ browser of LMM shows the available models, and allow
 the creation of new ones. To create a new model follow these steps:
 1 Browse through the available models.
 1 Browse through the available models.

 LMM-create a new model
 The models’ browser of LMM shows the available models, and allow
 the creation of new ones. To create a new model follow these steps:
 1 Browse through the available models.
 2 Choose in which group of models to place the new model. Go in
 the group Work.
 2 Choose in which group of models to place the new model. Go in
 the group Work.

 LMM-create a new model
 The models’ browser of LMM shows the available models, and allow
 the creation of new ones. To create a new model follow these steps:
 1 Browse through the available models.
 2 Choose in which group of models to place the new model. Go in
 the group Work.
 3 OpenmenuEdit/New Model, and choose New Model.
 3 OpenmenuEdit/New Model, and choose New Model.

 LMM-create a new model
 The models’ browser of LMM shows the available models, and allow
 the creation of new ones. To create a new model follow these steps:
 1 Browse through the available models.
 2 Choose in which group of models to place the new model. Go in
 the group Work.
 3 OpenmenuEdit/New Model, and choose New Model.
 4 Assign a model name “Simulation 0”, a version number, 0.1, and
 a directory name, S0.
 4 Assign a model name “Simulation 0”, a version number, 0.1, and
 a directory name, S0.

 LMM-create a new model
 The models’ browser of LMM shows the available models, and allow
 the creation of new ones. To create a new model follow these steps:
 1 Browse through the available models.
 2 Choose in which group of models to place the new model. Go in
 the group Work.
 3 OpenmenuEdit/New Model, and choose New Model.
 4 Assign a model name “Simulation 0”, a version number, 0.1, and
 a directory name, S0.
 5 NowLMMshowstheequation file prepared for the new model.
 At any time you can press Cancel or the Esc key to abort the
 procedure and start again.

 LMM-Theequation file
 Any equation file must contain the following text:
 #include "fun_head.h"
 MODELBEGIN
 MODELEND
 void close_sim(void)
 {
 }
 The code for a model’s equation must always be placed in between
 the MODELBEGIN and MODELEND lines.

 LMM-Theequation file
 Out purpose is to code the equation:
 Xt = Xt 1+m
 .
 The minimal expression for this equation in the LSD equation file is:
 EQUATION("X")
 RESULT(VL("X",1)+V("m") )
 Let’s see the meaning of the commands used in the LSD expression of the
 equation.

 LMM-Theequation file
 In LSD the equations are written as separate blocks of code beginning
 with EQUATION("VarName") and ending with
 RESULT(anyValue).
 These lines correspond to the expression:
 VarNamet = anyValue
 Within the heading and closing commands for an equation the
 modeler can insert any legal C++ code or LSD keyword.

 LMM-Theequation file
 The most frequently used LSD command is: V("Y"), where Y can be
 the label of a variable, parameter or function.
 The most frequently used LSD command is: V("Y"), where Y can be
 the label of a variable, parameter or function.

 LMM-Theequation file
 The most frequently used LSD command is: V("Y"), where Y can be
 the label of a variable, parameter or function.
 This command searches in the model the item with the label specified
 in V("...") and returns its current value, i.e. computed at the
 present time step of the simulation. It is, therefore, the equivalent of
 an element, such as Yt, on the right side of the equation.
 This command searches in the model the item with the label specified
 in V("...") and returns its current value, i.e. computed at the
 present time step of the simulation. It is, therefore, the equivalent of
 an element, such as Yt, on the right side of the equation.

 LMM-Theequation file
 The most frequently used LSD command is: V("Y"), where Y can be
 the label of a variable, parameter or function.
 This command searches in the model the item with the label specified
 in V("...") and returns its current value, i.e. computed at the
 present time step of the simulation. It is, therefore, the equivalent of
 an element, such as Yt, on the right side of the equation.
 The command V("...") has a few variations. The one we need is
 VL("Y",lag), returning the value of the variable Y computed lag
 periods before the present, that is Yt lag. Note that
 V("Y")=VL("Y",0).
 The command V("...") has a few variations. The one we need is
 VL("Y",lag), returning the value of the variable Y computed lag
 periods before the present, that is Yt lag. Note that
 V("Y")=VL("Y",0).

 LMM-Theequation file
 The most frequently used LSD command is: V("Y"), where Y can be
 the label of a variable, parameter or function.
 This command searches in the model the item with the label specified
 in V("...") and returns its current value, i.e. computed at the
 present time step of the simulation. It is, therefore, the equivalent of
 an element, such as Yt, on the right side of the equation.
 The command V("...") has a few variations. The one we need is
 VL("Y",lag), returning the value of the variable Y computed lag
 periods before the present, that is Yt lag. Note that
 V("Y")=VL("Y",0).
 There are many LSD commands available for common computational
 structure. See the LMM help pages on the Macros for LSD Equations.

 LMM-Theequation file
 The equation’s code we wrote earlier was called “minimal” because,
 though working, is too compact.
 Typically, using long variables’ labels and with expressions entailing
 more than a few operators, the expression of the equation within the
 RESULT( ) becomes impractical.
 It is far clearer and more efficient to write the equation over several
 lines, breaking the computation in small pieces, and storing
 intermediate results in temporary variables.
 The modeler can use a vector of values, referred to as v[0], v[1],
 etc., to store intermediate results during the computation of the
 equation for a variable.

 LMM-Theequation file
 The equation Xt = Xt 1 +m can be expressed in a clearer and more
 general format as follows:
 EQUATION("X")
 /*
 The new X is equal to its own past value plus ‘m‘
 */
 v[0]=VL("X",1); //past value of X, lagged of 1 period
 v[1]=V("m"); //current value of m
 v[2]=v[0]+v[1];
 RESULT(v[2] )

 LMM-Theequation file
 The C++ local variables v[0], v[1], v[2], etc. are temporary
 storing places for intermediate calculations. The values stored there
 can be used only within one execution of the equation, and cannot be
 used to transfer values across different equations. These variables
 are created when an equation begins its computation, and are
 destroyed immediately after its conclusion.
 The C++ local variables v[0], v[1], v[2], etc. are temporary
 storing places for intermediate calculations. The values stored there
 can be used only within one execution of the equation, and cannot be
 used to transfer values across different equations. These variables
 are created when an equation begins its computation, and are
 destroyed immediately after its conclusion.

 LMM-Theequation file
 The C++ local variables v[0], v[1], v[2], etc. are temporary
 storing places for intermediate calculations. The values stored there
 can be used only within one execution of the equation, and cannot be
 used to transfer values across different equations. These variables
 are created when an equation begins its computation, and are
 destroyed immediately after its conclusion.
 Notice also the comments added just below the beginning of the
 equation. All the text placed in this position is considered by LSD the
 “official” documentation of the variable, and will be automatically
 included in the documentation of the model.

 LMM-Scripts
 The text for the equations can be inserted manually as in any editor.
 However, LMM is endowed with specific functions to insert
 automatically the most frequently used commands for LSD equations,
 speeding up the coding time and reducing the number of typing
 errors.
 These functions are called scripts, and when activated insert
 automatically text in the position of the cursor in the LMM page,
 asking the modeler for any required for information.

 LMM-Scripts
 Once activated the script place the text starting at the position
 of the text cursor in the equation file.
 The activation of the scripts can be performed in several ways:
 1 using the keyboard combination Control-i;
 2 using the right-button of the mouse;
 In both cases you are offered the whole list of available scripts,
 and then you can choose one using the mouse or pressing a
 letter indicated in the scripts.

 LMM-Scripts
 For example, you can insert the lines for
 EQUATION("VarLabel") ... RESULT( ) pressing
 Control-i to show the available scripts and e for inserting an
 equation.
 Any script shows a specialized window allowing to fill the
 information required for the script. Read the text of the entries,
 and, in case of doubts, accept the proposed default choice.
 Any text entered by a script can be modified later and, if
 necessary, scrapped.

 LMM-Scripts
 To express the equation you need then the following steps:
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;

 LMM-Scripts
 To express the equation you need then the following steps:
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.

 LMM-Scripts
 To express the equation you need then the following steps:
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.
 3 UseControl-i and then v to store m in the temporary
 variable v[1]. Insert the element label m.
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.
 3 UseControl-i and then v to store m in the temporary
 variable v[1]. Insert the element label m.

 LMM-Scripts
 To express the equation you need then the following steps:
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.
 3 UseControl-i and then v to store m in the temporary
 variable v[1]. Insert the element label m.
 4 Type the line v[2]=v[0]+v[1]; (beware of the
 concluding semicolon!)
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.
 3 UseControl-i and then v to store m in the temporary
 variable v[1]. Insert the element label m.
 4 Type the line v[2]=v[0]+v[1]; (beware of the
 concluding semicolon!)

 LMM-Scripts
 To express the equation you need then the following steps:
 1 UseControl-i and then e to create the equation header
 and footer; insert the variable name X;
 2 UseControl-i and then v to store Xt 1 in the temporary
 variable v[0]. Insert the element label X and specify lag 1.
 3 UseControl-i and then v to store m in the temporary
 variable v[1]. Insert the element label m.
 4 Type the line v[2]=v[0]+v[1]; (beware of the
 concluding semicolon!)
 5 Insert in the result value v[2] in the RESULT( )
 concluding line.
 Done!

 LMM-Compiling
 When finished with the equation writing, the file contains the
 computational content of the model expressed in source code, i.e. a
 programming language.
 When finished with the equation writing, the file contains the
 computational content of the model expressed in source code, i.e. a
 programming language.

 LMM-Compiling
 When finished with the equation writing, the file contains the
 computational content of the model expressed in source code, i.e. a
 programming language.
 To turn this into an actual program we need to compile the equations’
 code together with the rest of the LSD code. To do so choose in LMM
 the menu entry Model/Compile and Run to compile the equation
 and generating the program for the new model.
 To turn this into an actual program we need to compile the equations’
 code together with the rest of the LSD code. To do so choose in LMM
 the menu entry Model/Compile and Run to compile the equation
 and generating the program for the new model.

 LMM-Compiling
 When finished with the equation writing, the file contains the
 computational content of the model expressed in source code, i.e. a
 programming language.
 To turn this into an actual program we need to compile the equations’
 code together with the rest of the LSD code. To do so choose in LMM
 the menu entry Model/Compile and Run to compile the equation
 and generating the program for the new model.
 In case of success you will see a new interface appearing on the
 screen. If this is not the case you probably inserted text that has not
 been recognized by the compiler as legal code.

 Compilation errors
 Writing code (and therefore also simulation models) means to
 spend 90% of time fixing errors.
 Writing code (and therefore also simulation models) means to
 spend 90% of time fixing errors.

 Compilation errors
 Writing code (and therefore also simulation models) means to
 spend 90% of time fixing errors.
 A wrong command, for example forgetting the semicolon at the
 end of the lines when requested, prevents the compiler to
 understand the code, and the compilation process fails.
 A wrong command, for example forgetting the semicolon at the
 end of the lines when requested, prevents the compiler to
 understand the code, and the compilation process fails.

 Compilation errors
 Writing code (and therefore also simulation models) means to
 spend 90% of time fixing errors.
 A wrong command, for example forgetting the semicolon at the
 end of the lines when requested, prevents the compiler to
 understand the code, and the compilation process fails.
 In these case, LMM generates a new window with approximate
 indications on the type and location of the error. Read the error
 messages; every line starts with the file name of the equations
 you are using and a number, indicating the line where the error
 was acknowledged, meaning that likely it occurred at that line
 or one immediately above.

 LSD Model Program
 When the compilation succeeds LMM starts automatically the LSD
 model program, containing the equations just written.
 When the compilation succeeds LMM starts automatically the LSD
 model program, containing the equations just written.

 LSD Model Program
 When the compilation succeeds LMM starts automatically the LSD
 model program, containing the equations just written.
 This new program is independent from LMM. Since the equations’
 code has been compiled, changing the equations code in LMM has
 no effect on the behaviour of the LSD model program. To modify the
 equations of a model it is necessary to shut down the model program
 and re-compile a new one.
 This new program is independent from LMM. Since the equations’
 code has been compiled, changing the equations code in LMM has
 no effect on the behaviour of the LSD model program. To modify the
 equations of a model it is necessary to shut down the model program
 and re-compile a new one.

 LSD Model Program
 When the compilation succeeds LMM starts automatically the LSD
 model program, containing the equations just written.
 This new program is independent from LMM. Since the equations’
 code has been compiled, changing the equations code in LMM has
 no effect on the behaviour of the LSD model program. To modify the
 equations of a model it is necessary to shut down the model program
 and re-compile a new one.
 Crucially, never change the file name for the equations. LMM
 associates a specific file to a model. If you edit the equation file and
 save it with a different name LMM will keep on using the old one for
 the equations.

 LSD Browser
 The browser shows the content of an object. An empty model
 contains only the default object Root, so this is the object
 appearing when the model program starts.
 The Browser shows the content of the object separated in two
 lists: one for the variables and parameters of in the object
 (Variables) and the other for the descending objects
 (Descendants).

 LSD Browser
 The LSD model programs accept commands stored into menus,
 whose overall content is the following:
 File: Load and save configuration files.
 Model: Create a model structure (define variables,
 parameters, objects); generate documentation.
 Data: Define and observe initial values; analyse or save
 results.
 Run: Define simulation settings and run simulations.
 Help: Open help pages on LSD interfaces and on the
 model.

 Generate Model Structure
 Let’s use the LSD Browser to generate the model structure. We need
 to define one object containing a variable and a parameter.
 IMPORTANT: to label model entities use only characters (no spaces
 or other symbols). Elements’ labels are case-sensitive.
 1 Model/Add Descending Obj: Create an object Obj.
 2 Click on Obj in the list of Descendants. The Browser shows the
 new object.
 3 Model/Add a Variable: Create an variable X with 1 lag.
 4 Model/Add a Parameter: Create a parameter m.
 5 File/Save as: Save the current configuration in a new file Sim1.

 Fixing Structural Errors
 It is easy to make mistakes in typing the labels of the elements or
 placing them in the wrong object. To correct any error double-click on
 the element and select in the resulting window the button Properties
 under name element’s label.
 There are several options for fixing different types of error. Each
 option needs to be used independently and confirmed when exiting
 the properties.
 To remove an element altogether assign an empty string to its name.

 Generate Initial Data
 Any model can start only when the data for its state at time t=1 are
 assigned. The initial data concern the number of objects, the
 parameters, and the initial values for the variables expressed with a
 lag in the equations. In our case: number of copies for the object
 Obj, values of the X at time 0, and parameters m
 1 (with the Browser showing Obj) Data/Set num. objects/All
 objects (shortcut control-o): there is initially only one copy of
 Obj. Click on the number and insert 10. Press Ok and Exit to
 return to the Browser.
 2 (with the Browser showing Obj) Data/Init. values (shortcut
 control-i): the window shows one cell for each X0 and for
 each m, indicated by an indicator for the copy of Obj. Use Set
 All to generate all X equal to 10 and the m ranging from-5 to 4.

 Help yourself
 All the windows have pretty intuitive graphical interfaces.
 Moreover, each window has a button (or menu item) for help.
 Use these help pages for understanding how to operate the
 windows. Notice that the help pages are linked to others,
 related help pages. The whole LSD hyper-manual is organized
 for the main menu items.
 In doubt, always opt for the default choice offered by
 interfaces.

 Simulation Settings
 Weare now almost ready to run the simulation.
 Weare now almost ready to run the simulation.

 Simulation Settings
 Weare now almost ready to run the simulation.
 LSD automatically discard the values of the variables as soon as they
 are not necessary for the subsequent computation of the model.
 Therefore, users must specifically instruct the model to save the
 series of the variables they want to analyse as relevant result.
 Therefore, users must specifically instruct the model to save the
 series of the variables they want to analyse as relevant result.

 Simulation Settings
 Weare now almost ready to run the simulation.
 LSD automatically discard the values of the variables as soon as they
 are not necessary for the subsequent computation of the model.
 Therefore, users must specifically instruct the model to save the
 series of the variables they want to analyse as relevant result.
 Move the Browser on Obj and double-click on X. The system will
 show the options available for the variable. Select the option Save for
 later analysis and ensure it is checked on. This operation tells the
 system to store the values for all the copies of X’s in memory in order
 to perform post-simulation analysis.

 Simulation Settings
 There are other settings relevant for a simulation run that do not
 concern directly the model content.
 Choose menu Run/Sim.Setting. The window will allow to set several
 options concerning how to manage simulation runs. Ignore all of
 them and assign 10 to the number of steps, replacing the default
 value of 100.

 Simulation run
 Wecan now run the simulation. Choose menu Run/Run and a
 summary window will appear.
 This window reminds the user that the configuration defining the
 model, initial values, options, etc. is going to be saved in a file before
 starting the actual simulation. Any file with the same name possibly
 present will be cancelled and overwritten.
 Saving the configuration allows the user to be able to perfectly
 replicate the last simulation, so that errors or unexpected results can
 be replicated and investigated. To avoid overwriting a file it is
 sufficient to change name of the configuration.
 Confirm and the simulation will start, finishing shortly after.

 Simulation run
 After a simulation run the browser will re-appear. Though nothing
 seems changed as compared to before running the simulation, the
 LSD model program differs in its internal content: the initial
 configuration has been replaced by the configuration of the model at
 the end of the simulation run.
 The system forbids to use this configuration to start directly a new
 simulation (it would overwrite a file meant to contain the initial
 configuration). Try to choose again Run/Run, and an error message
 will appear. Press Cancel to return.

 Analysis of Results
 After a simulation we can observe all values of the model that have
 been saved. In our example all the series X.
 1 OpenmenuData/Analysis Results. The Browser disappears
 showing a module called Analysis of Results.
 1 OpenmenuData/Analysis Results. The Browser disappears
 showing a module called Analysis of Results.

 Analysis of Results
 After a simulation we can observe all values of the model that have
 been saved. In our example all the series X.
 1 OpenmenuData/Analysis Results. The Browser disappears
 showing a module called Analysis of Results.
 2 If the list of available series is empty there are two possible
 reasons: 1) did not set the option to save X, or 2) the simulation
 was not run. Check which is the case and fix the problem.
 2 If the list of available series is empty there are two possible
 reasons: 1) did not set the option to save X, or 2) the simulation
 was not run. Check which is the case and fix the problem.

 Analysis of Results
 After a simulation we can observe all values of the model that have
 been saved. In our example all the series X.
 1 OpenmenuData/Analysis Results. The Browser disappears
 showing a module called Analysis of Results.
 2 If the list of available series is empty there are two possible
 reasons: 1) did not set the option to save X, or 2) the simulation
 was not run. Check which is the case and fix the problem.
 3 Select all series from the list Series Available and move them to
 the list Series Selected using the button >. Press Plot. You are
 expected to obtain a graph as in the following slide.

 50
 27.5
 5
 −17.5
 −40
 0
 2
 X_1 X_2 X_3 X_4 X_5 X_6 X_7 X_8 X_9 X_10
 5
 7
 10

 Summary
 The operations we have performed in this lesson are:
 1 Design a model on paper;
 2 Write the code implementing the equation;
 3 Define the model structure and initialization;
 4 Runthe simulation;
 5 Analyse the results.

 Exercise
 Test the Simulation 0 model with different initializations,
 number of Obj and number of steps. Check that it actually
 provides the expected results.
 Modify the format of the equation, using for example a
 power function or any other discrete-time dynamics.