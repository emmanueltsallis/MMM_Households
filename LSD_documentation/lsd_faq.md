Frequently Asked Questions about LSD

What is LSD?
LSD (Laboratory for Simulation Development) is a language and a platform to write simulation models, which appear as stand-alone programs complete with graphical based interfaces for all possible applications of the model (from running the simulation to preparing scientific publications). Two characteristics make LSD particularly useful in order to use simulation models in social sciences:

1)    A LSD model is a simple to use, stand-alone program that even non-expert computer users can use to run and test the results from simulation models.

2)    Model writers need to write just the code directly linked to the content of the model, having LSD automatically creating all the interfaces that allow accessing any aspect of the model, accelerating and simplifying the process of building simulation models and allowing for their easy distribution.

LSD tries to remove the trade-off between the simplicity to use a simulation model and the complexity to build it. This is obtained by allowing modelers to just write pieces of code (independently) for each Equation (i.e., Variable) of the model. In this way, the process of code writing is greatly simplified because a complex model is decomposed in individually coded Equations. When the Equations are (supposed to be) ready, the system automatically generates an executable program, complete with an easy-to-use graphical interface. The system automatically executes the Variables' code as required during a simulation run, storing the results, signaling errors, and allowing the model inspections, without any need for the modeler to write specific code for these operations.

Although very simple to use, LSD is also extremely powerful, since it is based on C++11, and therefore the resulting simulations are fast, virtually unlimited in their dimensioning and employing the full capabilities of modern hardware (large memory space, parallel multi-core processing etc.).

LSD models are based on the difference equations system approach: modelers write each Variable's Equation in order to compute its generic value at time t using Parameters and other models Variables at times t, t – 1, t – 2, etc. Any legal C++ statement can be included in a Variable's Equation, allowing the use of the large set of libraries available for this language.

LSD is particularly useful for agent based modeling (ABM), since it entails models based on a hierarchy of entities, with fast and automatic search through the “tree” of entities for the correct scheduling of the code calculating the elements.

See the LSD documentation for full information.

How much does LSD cost?
LSD is distributed as open source code and is completely free to use under the GNU general public license.

LSD makes use of Tcl/Tk libraries and of the GCC C++ compiler, among other tools, all of which are freely available under the same GNU general public license.

See the license details in Readme.txt.

What is LMM?
LMM (LSD Model Manager) is an integrated development environment (IDE) created to develop and manage LSD models. LMM is composed by a text editor, particularly suited for LSD macro coding, and by an extensive set of tools for the management of LSD models. The editor is used to write the LSD Equations. The tools available make automatic the procedures of documenting, compiling, debugging and running LSD programs in an easy but powerful way, so that even non-expert modelers can use C++ compiled code for their simulation models.

See the LMM Manual for further information.

Where do I start using a LSD model?
The distribution of LSD includes several example models, some of which are for purely teaching purposes, while others are complex models with scientific purposes. The simplest way is to play with them is to use LMM to compile and run them. To do so, please follow the following steps:

1)    Run LMM.  In Windows, search for the installation directory where LSD is located. (e.g., C:\LSD) and execute (double click) the file run.bat. In Linux execute the terminal command ./lmm in the LSD installation directory. In macOS, double click the application LMM in LSD installation folder (e.g., ~/LSD).

2)    LMM will show the list of available models. Choose a model among the ones available in the Example Models subgroups.

3)    In LMM, choose menu Model>Run. The selected LSD model is compiled, if necessary, and run. Finally, the LSD Browser graphical interface will appear.

4)    in LSD, choose menu File>Load, to load an existing configuration;

5)    Explore the menus of the LSD Browser (e.g., menu Run>Run starts the simulation). You may keep the LSD Browser help pages open for additional information.

LSD manual includes a tutorial for the basic operations for running a LSD model.

Where do I start writing a LSD model?
To create a LSD model you need to write few Equations to be compiled in order to generate the executable program (a custom version of the LSD Browser). Next, you must generate a model structure with the LSD Browser.

It is usually better to run some example models before creating your own models. It is strongly recommended that you create new models in a gradual way, in particular when beginning:

·                write one, or very few, Equation(s);

·                create a model structure with only the Variable(s) corresponding to the written Equation(s) and the rest of the elements defined as Parameters;

·                test the working of the code, and fix the likely errors;

·                add one or few additional Equations, either transforming some Parameters into Variables, or adding new Variables;

·                re-test the model;

·                and so on.

LSD manual includes a tutorial for the basic operations of creating a simple LSD model.

What is a model in LSD?
An abstract definition of a simulation model is: a collection of variables that change values through simulation time according to specified rules. However, this definition leaves a lot at an implicit level.

A more pedantic definition is maybe better to understand how LSD works. Usually a model includes several Variables (and associated Equations) and Parameters. These elements are “stored” inside Objects which can be thought of as containers for Variables and Parameters. After providing the above items with initial data (values for the Parameters and lagged Variables, the number of each Object copies, etc.), a simulation run can be executed.

The model's set of difference equations are implemented as pieces of code employing a basic subset of the C++ language. Equations are defined independently from each other and together implement a LSD model. The customized version of the LSD Browser produced from each LSD model program can be used to create, load or modify the model structure, which contains the definitions for all the elements in the model, the initial data, etc.

LSD is based on the concept that just producing data is still not sufficient to explore and exploit simulation models. Yet, it is necessary to fully understand the results. For this, LSD also generates the complete documentation for the model, in the form of Latex and HTML reports, EPS plots, statistics tables, and so on.

What is the model home (sub) directory?
Every LSD model is composed by a set of files which are stored in a single location (a directory/folder) in the computer file system (contained in a hard disk, a SSD, an USB pen drive etc.). By default, new LSD models are created in the Work subdirectory which is kept inside the LSD installation directory (usually C:\Lsd-X.Y in Windows or ~/LSD-X.Y in Linux/macOS, see the installation details for more information).

When a new model is created in LMM, the user has the option to name its home directory (the default being newmodel). After the model is created, its home directory can be easily retrieved by using the LMM command Model>Model Info (check the LMM manual for details).

What are a simulation run and a time step?
A simulation run is a virtual history of a simulated reality whose study can provide insights on the real counterpart to the model. In LSD a simulation run is the sequence of time steps during which each Variable in the model has its Equation applied to compute an updated value (except if special update rules are set).

LSD is based on the concept that it is not sufficient for a simulation to just produce data. Results must be fully understood and this is linked to the functional content of the model and its configuration. For this reason, during a simulation run users must be able to interrupt, investigate the model, observe the data generated up to that time, modify values, and resume. Moreover, any LSD model comes with full documentation (automatically generated) to make easier to grasp the connections between the model’s elements even in very complex cases.

Technically, when a user runs a LSD simulation, the following steps are performed:

1)    If required, save the current model configuration. This avoids that interesting results are produced by an unsaved configuration.

2)    Initialize the simulation repetition counter and the seed for the pseudorandom number generator. Most frequently a model is run only once, but LSD allows the running of batteries of simulation repetitions under the same configurations using different seeds to test the robustness of the results.

3)    Initialize the counter for the simulation time steps. That is, make t = 1.

4)    For every Variable in each Object instance in the model compute the corresponding Equation, except if special update rules are set, following the order automatically determined by the LSD scheduler based on the (implicit) lag relations among the Equations.

5)    Update the simulation time step: t = t + 1.

6)    Repeat steps 4 and 5 until reaching the simulation span (duration) set in the model configuration.

7)    Save the results produced to a file, if more than one simulation run was configured.

8)    Reload the configuration, update the simulation counter, and set a new seed (increase by 1).

9)    Repeat steps from 3 to 8 until reaching the number of simulation runs set in the configuration.

During a simulation run, LSD controls for possible errors, in case issuing messages indicating what type of error occurred and in which Equation. LSD is endowed with its own debugger (for equation-by-equation running) and can optionally also integrate with the more advanced GDB debugger for line-by-line execution.

At the end of a single or a set of simulation run, the user can analyze the results of the last simulation run, still stored in memory, or load result files from any previous run.

How does LSD run a simulation and who decides the priorities of the computations?
LSD does not require modelers to explicit the full sequence of computation of each of the model’s Variables. Such requirement, a basic one when programming in traditional languages, is annoying, complicated and (mostly) redundant.

In fact, for large models you may have hundreds of different Equations, with thousands of Objects instances where Variables must be updated. It may be difficult to (correctly) draw the complete map of interactions among Variables and mistakes in determining the order of execution are frequent. However, in most cases this is a redundant task, once in many cases the order of computation can be univocally determined from the set of difference equations itself. Also, several computations may potentially run in parallel, without the necessity to follow a specific order, speeding up the model computation.

LSD relies on an automatic scheduling engine allowing modelers to decide the order of computation except in special circumstances, as when ambiguity is present. Only if there is a specific need to keep a certain evaluation sequence, then the model can be explicitly configured to follow it. For example, writing the Equation x = f(y) forces the system to compute y before x. Otherwise, the code for x = f( y(t – 1) ) tells the system to use a lagged value of y in the Equation for x and thus the Equation for y may be computed before or after that for x.

Anyway, the order of the computations follows a simple rule. LSD starts each simulation time step computing the first Variable, if any, in the topmost Object for the model structure (root). If this Variable’s Equation requires contemporaneous values from other Variables, these are computed on demand. As soon as the first Variable is calculated, LSD moves on to compute the second Variable, if any and if not already computed before. When all Variables in the topmost Object, if any, are updated, LSD moves to the first descending (son) Object and computes all Variables in all of its instances. Next, LSD goes down again to evaluate the son own descending Objects (grandsons of root). This downward-recursive path goes ahead until the last Variable in the last instance of the bottommost Object is reached and, so, all the Variables in the model are updated for the current time step.

Considering the downward-recursive algorithm used by LSD to schedule the computations, the user can influence the sequence of evaluation of the Variables by the order the elements are listed in the Descending Objects list box and the Variables list box in the LSD Browser. When Variables are not updated because of previous Variables’ computation, LSD uses the list boxes order to update them (from top to bottom). The list boxes can be easily reordered in the LSD Browser, element-by-element and overall.

What is an Equation?
An Equation in a LSD model can be understood as a difference equation that computes a numerical value for a Variable as a function of the present and the past values of all Variables and Parameters of the model. Technically, it is a piece of code (C++ extended by a library of LSD specific macros and functions) that is executed once for each instance of each Object containing the Variable it refers to, at every time step of the simulation (except if special update rules are set). Users of a model do not need to deal with the Equations, though they have access to the code implementing the Equations including all the explanations and comments provided by the author of the model.

The necessity to write C++ code for the Equations is the major difficulty for writing LSD models. This is necessary because, after all, a simulation is a program and model writers must be aware of the content of their model, and LSD does not pose any limitation on the family of models that can be implemented with it. On the other hand, LSD facilitates enormously the code writing in respect of writing a pure C++ program. In fact, it takes the burden of two major difficulties in writing simulation programs. The first, it is to ensure that Variables' values updating is consistent, that is, that the Equations be computed at the right time so that lagged and updated values are used appropriately. The second difficulty is to be sure that Variables contained in different instances of the same Objects use the correct values (a big source of troubles for agent-based, micro-founded models where the same entity is replicated many times in the models).

The problem of the scheduling of the operations during a simulation time step is solved in LSD by writing Equations as difference equations. That is, model writers use a lag notation that implicitly provides the correct scheduling. A powerful debugger helps to solve the problem of scheduling errors even under the most extreme conditions.

The problem of multiple Variables with the same name is solved by using a hierarchical structure. That is, if model writers do not specify which instance they need to use in their Equations, the system automatically provides the value of the "closest" instance of the requested element. Overruling systems allow anyway modelers to access any value of the model they may necessitate.

All in all, writing the Equations' code for a LSD model has the same difficulty of writing the C++ equivalent of the set of difference equations expressing the model, and therefore the complexity depends on the model only. Moreover, an Equation can contain any legal C++ code besides computing numerical values. For example, an Equation can overwrite other Variables' or Parameters' values of the model, create or remove Objects, quit the simulation, trigger messages under particular circumstances, etc.

What is a LSD equation file?
The equation file is the C++ source code file containing all the Equations of the model written using LSD macros or functions. The Equations are implemented as sections of this file and are independent from each other. Model writers fill this file with the code representing the set of difference equations for all the Variables in the model. The order in which the sections for the Equations are included in the equation file is irrelevant.

Being a standard C++ source code to be compiled and linked with the LSD libraries, the equation file may contain any legal C++ statement, for example, C++ functions of any sort. However, an equation file must be organized in a format it can be understood as a set of Equations using the appropriate LSD macros or functions. Also, larger models can be split in more than one equation file, given all the secondary equation files are reunited by a (single) main equation file by the use of C++ preprocessor #include directives. Multi-file models can be easily managed by LMM.

What is a LSD macro or function?
An equation file must provide the model’s Equations clearly defined by the usage of predefined C++ code constructs. Such constructs are usually provided in the form of pre-defined macros. Pure C++ coding using library functions directly is also possible for special cases (and skilled programmers). A macro function is a predefined set of C++ instructions that can be executed by the usage of a single name attributed to it, hiding much of the coding complexity required to write programs. A convention in the C++ language is to use all capital names for macros, as in EQUATION or RESULT examples.

What is C++ and C++11?
C++ is a general-purpose, high-performance, object-oriented computer language. It was created as an extension to the C language. Because of its technical attributes, C++ is particularly suited for system programming where the full capabilities of the embedded hardware are to be exploited. A significant share of the largest and more sophisticated large scale software projects are currently developed using C++, at least on their core parts. Typical examples are all modern operating systems (Windows, Linux, macOS, Android, etc.) and most complex desktop applications (Office-like, internet browsers) and advanced technical tools (compilers, performance-critical applications).

C++ is standardized by the International Standards Organization (ISO) and have the standard versions named as C++XX, where XX represents the last two digits from the year of its ratification by ISO. The recommended minimum version for LSD is C++11 (under GCC 4.9 or newer), being operation under C++98 possible under some limitations.

What does it mean “compiler” or “recompile”?
The compilation of LSD equation files, and the possible dealing with the associated error messages, is automatically performed by LMM whenever a modeler tries to run a model.

The so-called “compiled” languages, like C++, are based on a compiler. That is, programmers write normal text files (called “source” files) containing commands that must comply with a given (strict) syntax (like C, C++, Java, etc.). When programmers (believe to) have finished the coding, they compile it by using a compiler program which converts the source file into an executable program file. The compiler reads the commands in the exact sequence in the source file and, if there are no errors, produces as output a file containing the actual “executable code” that can be run on any computer sharing the same operating system (OS). Different OS’s require specific recompilation. The executable code translates the commands written in the source code in the actual operations to be performed by the computer, in the same sequence.

If the source file(s) containing the program is (are) modified, the changes do not immediately affect the executable program, unless the programmer re-compiles the edited file(s), producing a new executable file. In LSD, all the changes concerning the structure of the model or the settings of the model can be done during the “run time”, that is, they do not require changes to the executable code and so can have immediate effect on the simulation program behavior. Instead, the Equations' code is a compiled part of the executable file, and changes to the equation file(s) do not affect the model operation unless this source file is recompiled.

What is a LSD model program?
A LSD model program is an executable compiled file with all the Equations defined in the equation file (usually written using LMM) and LSD code. The LSD model program is usually executed using LMM but can be directly invoked if necessary (the setting of environment variables may be necessary in this case).

The LSD model program has the same interface for all models, but the embedded Equations are different. Any LSD model program can create new or edit existing configurations and analyze results files. An LSD model program can execute simulation runs only when a proper model configuration, containing the Variables matching the Equations in the equation file, is loaded.

How do I name my model’s elements?
The names of (or the labels for) Objects, Parameters and Variables in LSD must be unique strings of standard Latin letters and numerals. They should not contain spaces or any other non-alphanumerical symbol (a – z, A – Z and 0 – 9) except for the underscore ‘_’.

Upper and lower cases are treated as different (e.g., a ≠ A and car ≠ Car). Labels cannot start with numbers so Var1 is fine as an element name but 1Var is not. C++ imposes no limit to the size of labels but only the first 31 characters of a name are used by the compiler. LSD imposes a hard limit of 99 characters for any element label.

What is an Object, an Object type and an Object instance?
In broad terms, an object in a computer language is the representation of a set of heterogeneous information. In particular, LSD Objects are data containers defined by a set of Variables, Parameters and other Objects:

Object Obj
{
   Variables: x, y, z, ...
   Parameters: a, b, c, ...
   Objects: O, P, Q, ...
}

Since an Object can be composed by other Objects, a model is made of a collection of Objects in the form of a hierarchical (“inverted-tree”) structure. Any LSD model "starts" on an uppermost and unique Object called Root, which cannot be renamed. Root, in general, does not contain elements as Variables and Parameters and is used to “house” the remaining model’s Objects. Other than Root, Objects in LSD are freely defined by the modeler and can be named as desired and replicated in many instances (copies). An Object instance is a particular copy of any defined Object type. All instances of a same Object type have the same internal structure, that is, contain the same Variables, Parameters and descending Objects types. However, each instance may have completely different values for its (state) Variables and Parameters, as well as different contents on the (and numbers of) descending Objects.

The hierarchical Object structure is used during a simulation to “induce” where the data required by an Equation must be retrieved. In fact, in general there are many instances of each Object type, and therefore there are many instances of the same Variables and Parameters (same label) in different Object instances. Consider the case of the Equation for Variable A using the value of Parameter B. If B is defined as a member of the same Object as A, then the Equation for A will use the instance of B in the same Object. However, if B is not contained in the same Object type as A and there may be many instances of the Object containing B the structure of the model becomes crucial. LSD has an automatic scheduling system that tries to always provide the required values for computation by searching through the entire model. The modeler, when designing the model, must ensure that the correct instance is used according to the LSD scheduler rules. Most of the times, LSD points to the correct Variable/Parameter instance. But modelers can always overrule the automatic scheduler and implement model-specific data retrieving arrangements.

Generally speaking, any Object (except Root) must be represented as a descendant from a parent Object. This parenthood relation is usually permanent and defined during the model configuration. However, Objects can also be created or removed during simulation time. In this case, a child Object “inherits” the values of an identical existing instance (as chosen by the modeler) in the parent Object.

Objects names are subject to certain rules and are case sensitive.

What are a Variable and a lagged Variable?
A Variable is the key element of a LSD model that (potentially) changes its value at all time steps of a simulation run, except if special update rules are set. Variables may be used when calculating other Variables in the corresponding Equations of the model. Variables are defined as elements of Objects, so that, if a model contains many instances of the same type of Object, it has also several instances of the corresponding Variable, all of which using the same Equation for their updating.

Technically speaking, a Variable is made of an Equation, attached to a (finite) list of numerical real values (LSD implements only double-precision IEEE 754 float-point Variables), each tagged with a time lag index. Different instances of the same Variable, despite using the same Equation to compute their value, in general may differ because they use different Object instances during the calculation.

Notice that a given Variable instance is calculate once, an only once, at every time step. If many Equations use the value of a certain Variable instance, it is calculated the first time it is needed and this value is reused in the subsequent requests. If a Variable is not used in any Equation, then LSD will automatically request its calculation once (except if explicitly disabled).

The numerical values of Variables are computed using the associated Equation and the past (lagged) values can be used in the calculations. Variables that are never used with lagged (past) values in the model (i.e., in none of the Equations) do not require to be initialized before the simulation run. Instead, Variables used with lags in any Equation requires that the initial values to be used at the very beginning of the simulation run be explicitly defined by the model configuration.

Variable names are subject to certain rules and are case sensitive.

What is a Parameter?
A Parameter is a numerical (double-precision IEEE 754 float-point real value) element of a LSD model that is not associated with any Equation. Therefore, a Parameter must have its value set during the model configuration and usually remain constant along the simulation run. However, in special circumstances any of the Variables’ Equations may change the value associated with any Parameter.

Technically, a Parameter is a kind of Variable without an Equation and with no lagged values.

Parameter names are subject to certain rules and are case sensitive.

What is a Function?
A Function is a way to invoke the code in an Equation (not associated with a Variable) to perform a certain computation. Technically, a Function is a label connected to a piece of code (in an Equation). In most of the LSD documentation Functions are not explicitly introduced. However, in many situations a Variable may be applied, also does a Function.

Differently from a Variable, the Equation computing a Function is never automatically executed by LSD. Rather, the code of a Function is executed only, and every time it is explicitly invoked. If it is invoked multiple times during the same time step, the code of the associated Equation is run the corresponding number of times, potentially producing different values for the same Function instance during the same time step (but just the last one can be saved). Also, a Function does not have lagged values.

Function names are subject to certain rules and are case sensitive.

What are initial values and a model configuration?
The configuration of a model consists of all the definitions required for a simulation run, except the Equations' code. In general terms, the configuration contains:

·                the model structure (Objects, Variables and Parameter definitions and how they are organized);

·                the numerical initialization (how many Objects of each type, the Parameters' values and the lagged Variables' initial values);

·                other simulation settings (e.g., number of time steps per simulation, number of simulation runs, which series must be saved for analysis, etc.).

In more detail, a LSD configuration is kept in a single special file, bearing an .lsd extension that should never be edited manually. A single model may have as many different configurations (files) as required, allowing the easy comparison of different parametrizations, experiments, tests, etc.

A LSD configuration files contains the following data, filled by the corresponding options in the LSD Browser:

·                The structure of the model (Object hierarchy, labels and locations of Variables and Parameters)

·                Number of instances for each Object type

·                One value for each Parameter instance (that is, for each instance of the Object type containing the Parameter)

·                One value for each lag for each lagged Variable instance

·                Flags for saving and debugging Variables and Parameters.

·                Number of simulation run repetitions

·                Seed value for the pseudorandom number generator

·                Number of time steps for each simulation run

·                Name of the C++ file containing the Equations of the model

·                Documentation information for each model’s elements

The model structure, defined by the modeler and contained in a configuration file, should never be changed by the end-users, since this may affect the operation of the Equations' code. Usually, the same model structure is replicated in all the configuration files, which normally contain different numerical initialization values and/or simulation settings.

What is the LSD model structure?
The LSD model structure is the functional organization of the Objects composing a model. Typically, each Object represents an entity of the “virtual reality” captured by the model. An Object can contain other “nested” Objects, and so on, forming a hierarchical structure (besides other Objects, an Object may also contain Variables and Parameters). In simpler terms, the model structure is a hierarchy which represents “what contains what”.

The Objects in the model can be hierarchically (parenthood relation) or parallel (brotherhood relation) linked. In the first case, the parent Objects (higher in the hierarchy) can access one or many instances of the same son Objects, descending from them, so that they can easily compute aggregate values produced by the whole set of descendants. Descending Objects, instead, have access to only one instance of the parent Object, and this same instance is shared by all the same descendants (brothers), so that they can access the same values contained in the parent. This system allows modelers to easily write Equations code relying on the hierarchical links to individuate the correct instance to use. In the second case, brothers, or parallel instances, can access each other’s values as long as they are unique instances and can be properly addressed.

The general rule is that Equations for Variables in descending Objects must make use of elements in parent (or grandparent) Objects when brothers must refer to a single instanced value for all of them. If, instead, descending Objects need more frequently to access different instanced values, then such Objects may be better not hierarchically linked and the modeler must explicitly provide the addressing for which instance to access in each situation.

For example, consider a model where many instances of an Object of type Firm have the Variable Quantity. Suppose the Equation for Quantity makes use of the lagged value of a Variable Price. Suppose Objects Firm are defined as descendants from a single Object Supply, that is, many firms are part of the supply side in a market, which, in turn, is defined as having a parallel (brother) Object Demand. We can imagine three situations: Variable Price is located in the same Object Firm, or in the Object Supply, or in Object Demand. Wherever it is placed, in the Equation for Quantity is always able to refer to values for Price without specifying where this Variable is contained. The difference is about how the model considers the price to be formed. In case Price is contained in each Firm there will be as many prices as firms (independent and heterogeneous prices), with demand represented as price-taker.

It also makes a difference whether the Variable Price is placed as part of Object Firm or as part of Object Supply. In the first case, each firm will use the value of a different instance of Variable Price (one for each firm), while, in the second case, all firms will use the same instance, since they will find the same Variable Price contained in the Object Supply containing them. The same applies also if there are multiple Objects of type Supply (or several markets), each with its own set of firms (sons). In this case (under a centralized price) each firm will use the instance of Price in its own market, with no risk of a wrong instance of Price being used.

A final warning: the structure of a model is created together with the coding of the Equations of the model. Therefore, the model structure should not be changed without considering its effects on the Equations' code.

What is a LSD lattice?
The LSD lattice window represents a bi-dimensional graph in which the simulation model may dynamically present graphical results during the simulation run. The lattice is formed by points organized in rows and columns and each point may have its color set independently from the rest. The lattice size is arbitrary and is defined by the model program.

The lattice may be understood as a tabular data structure. The information in the lattice, defining its points’ colors, may be stored and retrieved by the Equations’ code. There is a single lattice for each executing LSD simulation. Other than being observed during the simulation run, the lattice image may be saved to a file by either the user or the Equation’s code. The lattice cannot be used during ‘No Window’ simulation runs.

What is a LSD network?
In LSD a network is a structure composed by nodes interconnected by links. The nodes of a network must instances of the same Object type, that is, homogeneous brother Objects descending from the same common parent Object. Each Object type can participate in a single network but a LSD model may contain as many networks as desired. Directed weighted links can be created among any pairs of nodes (Object instances).

Each network node is attributed a unique (fixed and integer) serial number and may have also an optional name assigned (the usual restrictions to LSD names apply). Network links are identified by a pair of (integer) serial numbers representing the origin and the destination nodes. Each link is attributed an (integer) weight value, being the default zero value a convention for an unweighted link. Links may also have a probability value assigned, for use during operations on probabilistic networks.

LSD offers a series on network generators for some of the most common network types: disconnected, fully connected, star, circle, lattice, fully random (directed and undirected), uniform random, Renyi-Erdos, scale-free, and Small World. The modeler can also create its own network generator and embed it into the appropriate Equation(s). The most common network LSD macro commands can be interactively constructed using LMM templates.

The network structure (optional nodes names, links and links weights) can be saved and retrieved to/from files Pajek-formatted files (.net extension, see Pajek documentation at http://mrvar.fdv.uni-lj.si/pajek). Notice that the network structure is not saved to the LSD model configuration file. The modeler must explicitly create the desired network structure, or load it from a file, during the computation of the appropriate Equation(s).

Please check the documentation on the network LSD macros for a full reference.

Why should a model writer use LSD?
LSD offers two significant advantages to modelers: the ease of use of the final model and efficacy of the model development process. LSD has been built on the belief that the two main reasons hindering the use of the simulation methodology in the social sciences are (1) the technical complexity involved with the building of the models and (2) the difficulty to share the models’ results with an academic audience traditionally not trained in the use of computational techniques.

The simplicity of use of LSD models permits their distribution to non-expert users who can easily understand and replicate the models’ results. LSD can run virtually on any computer and it is very easy to run a model created in a different environment. The complete LSD installation is simple and quick. It does not require any additional software for basic Windows users, while under Linux or macOS just standard and open access tools are required. Also, as pure C++ high-performance compiled code, LSD models do exploit the full power of any computer.

Last, but not least, LSD specifically addresses the problem of model documentation, which causes the majority of potential users to discredit simulations once it is not clear what a model really does. Any LSD model is accompanied by an automatically created HTML document, the Model Report, showing the code used for the Equations and their connections with other elements of the model. Moreover, the Model Report lists all elements of the model, so that the modeler can easily include comments and indications on the element's meaning. The entire Model Report is automatically cross-referenced with links between each section.

What do I need to run a LSD model?
Just any desktop computer made during this decade (or even a good one from the previous decade) would do.

What can I do with a LSD model?
The most basic use of LSD is to run a model replicating simulations using the configurations provided by the model author. This can be done “on the spot” by downloading the model and pressing one button. Or, even simpler, using a web version of the model (there is a fully developed LSD web server version for this purpose).

Besides that, users can change any aspect of the model, according to their level of expertise. In particular, users can use the simple, intuitive and efficient graphical interface provided by LSD (with no intervention of the model writer) to:

·                Observe the model content at different levels of detail (overall structure, individual elements, numerical values, Equations code)

·                Run the simulations for any time span and how many times as desired

·                Change any numerical value in the model, including the number of instances of Objects and the Parameters and lagged Variables values to simulate different settings

·                Select which Variables are to be saved and analyzed the simulation run

·                Analyze the results by plotting graphs of the time series, making cross section graphs, obtaining statistics and exporting them

·                Export simulation results data to other packages for further statistical analysis (e.g., R, Stata, SPSS, SAS, Excel, etc.)

·                Natively integrate the output of LSD with R, avoiding conversion problems and allowing the ease exporting of multi-dimensional, hierarchical data

·                Modify and create new configurations for distribution to other users

·                Fully debug a simulation run, exploring the state of the model, analyzing the data produced data produced up to any time step, proceed step-by-step, abort the simulation or resume the full-speed run

·                Continue the simulation after the end of a previous simulation run (the status of the model after a simulation must be saved as a new configuration, and reloaded)

·                Automatically create HTML and Latex documentation on the model, to be used for explanation purposes or as appendices to scientific publications

What are the results of a LSD simulation run, and what can I do with that?
As a matter of principle, LSD is based on the assumptions that simulation models do not serve (only) to produce data series, but to understand a complex system evolving through time according to pre-defined computational “behaviors”. Therefore, a simulation result is supposed to be analyzed together with the model documentation so the analyst can be able to trace back the sources of the behavioral patterns obtained from the simulation. Given the hierarchical structure of LSD models, it is easy to build microfounded models that, while the many small entities behave (almost) wildly, at the macro level non-obvious patterns may emerge from the aggregation. This is the core tool to study the “Holy Grail” of agent-based models, the emergent properties, even though, at the end of the day, all simulation models do is to produce (large) streams of data.

LSD is endowed with a powerful Analysis of Result module that allows the generation of sophisticated graphs and produces some statistics from the generated time series. The same module exports data in a variety of formats for more sophisticated statistical or graphical elaboration. In case the select configuration asks for many simulation runs to be done in a sequence (typically, for robustness analysis), the system saves on files the data at the end of each simulation. Each of these files (extension .res) can be used in the Analysis of Result module in LSD (or even directly in R). Moreover, in the case of multiple simulation runs, the system saves also the values of all series at the very last time step for each simulation run in a single file (the extension .tot file). This file, also to be used with the Analysis of Result module, can be easily used to compare the final status of the model in each simulation run.

What is the LSD Web Interface (LWI)?
This manual presents the user-friendly, web-based interface to LSD (LWI). LWI make a basic subset of the LSD tools available for web browser users, allowing the configuration, execution, and analysis of results produced by LSD models and the export of such data. LWI web front-end is compatible with any computer platform equipped with a modern HTML5 browser and can be configured in closed (intranet) or open (internet) networks.

What are the R packages for LSD?
LSD has two dedicated packages (or libraries) in the R statistical computing program (see https://www.r-project.org). These packages are available at CRAN (the Comprehensive R Archive Network) for transparent download and usage by R users. Please check R documentation on how to download and load packages.

Package LSDinterface provides transparent access to LSD results files (no format conversion required) in the R data analysis environment. Users may retrieve LSD data organized according to the model structure hierarchical data directly into R multidimensional arrays. This allows using the same object-oriented data organization during the model design and the data analysis, simplifying significantly the management of data-rich, multilayered LSD models. Also, to accelerate data reading from multiple files, parallel multi-core file reading is automatically enabled, turning the reading of hundreds or thousands of LSD results files much faster on servers or high-performance computers. Automatic handling of compressed results files (.res.gz extension) is also supported.

Package LSDsensitivity offers several tools for performing sensitivity analysis and the study of response surfaces of LSD models. Among the included resources the package provides Morris Elementary Effects screening, Sobol Variance Decomposition analysis and Kriging meta-modelling. The package is an interface to many other R packages and is optimized for the analysis of simulation data.

For the package usage details and examples, please refer to the documentation included with them.

What is sensitivity analysis?
In a broader sense, the sensitivity analysis (SA) evaluate how uncertainty in the results of a simulation run can be apportioned to the sources of uncertainty in the model Equations and configuration. In practical terms, SA allow the modeler explain what is the role of (1) stochastic events (random draws), (2) Parameters and lagged Variables initial values, and the (3) chosen Equations’ functional form, in the results produced during a typical simulation run.

Presenting the SA results of a simulation model is considered an important practice, to prevent que (usual) criticism that simulation results are mainly driven by the modeling decisions and the configuration values adopted by the modeler. LSD offers a full set of tools to perform sophisticated sensitivity analysis, divided in two groups. The first one covers the sampling tools required to collect samples of the model’s results across its parametric space (i.e., all the possible combinations of its initial values and Equations’ functional forms) or, in formal terms, create a Design of Experiments (DoE). Please check the manual pages on the configuration of the SA options in LSD for further details.

The second group of SA tools, to perform the statistical analysis on the DoE sample data produced by LSD, is provided by means of the LSDsensitivity R package.

The SA exploration of the parametric space in LSD is done by the configuration of a SA test set. This data set defines for each tested Parameter or lagged Variable either a range or a set of values in which the element should be explored. According to the selected SA method, this test set may be explored by varying one element at a time or by jointly varying all the involved elements. SA test sets are saved separately from the model configuration file, so a single configuration may be explored over several different parametric spaces.

What is a model report?
The HTML model report provides a complete and easy to use description of the model content and structure. It is also possible to produce reports in Latex documents (better for printing).

A HTML model report contains four or five sections. Except for the first and the second (optional) sections, all of them begin with the complete list of links to the model elements (Objects, Variables and Parameters) described in the section. The model report sections are:

1.    Description section. It is written by the model writer, usually summarizing the goal of the model. This section contains also a list of the elements that the modeler suggests as relevant to initialize and to observe (these options are set in the respective elements' options window).

2.    User section (optional). It includes an optional user supplied HTML file with arbitrary content, including HTML tags. By default, the user section is disabled and must be enabled when the report is created.

3.    Model structure section. It lists all model elements showing where they are located in the model structure along a textual description of their role in the model and how to set the initial values, if applicable.

4.    Initial values section. It lists the numerical values used to initialize each instance of every Object, Parameter and lagged Variable in the model.

5.    Equations code and other details section. It contains all the Equations’ code for each Variable in the model plus other relevant information to understand the connection between the model elements.

The descriptions for each element in the different sections are hyperlinked, so users can, for example, pass from the verbal description of a Variable, read its code, see the initial value of a Parameter used in the Equation, read the description of the Parameter, see the list of other equations where the Parameter is used, see all the Variables and Parameters contained in the same Object, etc. All these operations are executed by clicking on the links in the report file.

How do I document the elements of a LSD model?
The documentation of the elements of a LSD model is composed by text section associated with any Object, Variable, Parameter and Function in the model (including the model itself). These text sections are called Description in the LSD windows dealing with the model documentation. These sections of text are presented (and can be edited) whenever the user edits the respective element in the model configuration. The content of the description sections are also used to produce the model reports. They are not used during the simulation run or affect whatsoever the simulation numerical operation.

Model writers are free to include any comment in the description sections. The documentation for an element can be automatically appended by the list of Equations using it, and by the list of other elements used by its own Equation. This way, one is immediately aware where the item affects or is affected by the model structure. See the documentation on the LSD Browser for details.

What documentation does exist on LSD?
LSD has a single and consistent interface for all models and provides integral documentation on all its coding and operational aspects. Please see the guide for LSD documentation.

Concerning the documentation of any software, in general, the best way to learn LSD is to use it. A manual is available, with all the aspects of LSD. The documentation is particularly useful for the beginner because it uses the real interfaces of LSD to explain the functioning of the system.

Concerning the specific documentation for each LSD model, it depends on the model writer. LSD offers the tools to automatically create most of the required documents at different levels of detail (overall model structure, individual elements, the whole code of the model's Equations, each numerical value used, etc.

What is the LSD XXX window?
Please check the LSD windows help page for a pictorial introduction to the main windows used in LSD.

Who wrote LSD, and why?
Marco Valente (marco.valente@univaq.it) is the writer of LSD, initially as part of the TED project in IIASA, Austria (led by Prof. G. Dosi) and later as an activity related to my studies for a PhD in Economics in the University of Aalborg, Denmark, under the supervision of Esben S. Andersen.

Since my graduate dissertation (“tesi di Laurea”, supervised by Prof. G. Dosi) I have being using simulation models, both for my own studies or under contract for other researchers. The basic motivation of LSD (I mean, my own motivations) is laziness. I simply did not want to write twice the same code for different models. Since it is pretty common that a computer program uses 90% of the code for non-core operations, I found myself writing programs 90% of which were similar to previously written code every time I started a model. The basic idea of LSD is to separate the model content from the “service” simulation code. In this way, writing the few lines of code corresponding to the Equations of a model you obtain a fully serviced program, with interfaces, file management, debug control etc.

The history of evolution of LSD is made of too many small steps to be reported in detail. However, it is made of two different, although related, purposes. I want LSD to:

·                be a powerful and simple-to-use language for simulation modelling;

·                bring economists, and social scientist in general, to use simulations.

Because of the first goal I cumulated more and more functions that, used in a model’s Equations, facilitate their writing. Because of the second goal (to understand whose importance I am grateful especially to E. S. Andersen), I worked to refine interfaces, to produce the manual, and to push modelers (myself included) to fully document every model and every single part of a model.

From 2014 onwards, Marcelo Pereira (mcper@unicamp.br) started to contribute to LSD development, still in version 6.x. He took the lead on the development of version 7 which further pushed in the two directions listed above, bringing new advanced capabilities to LSD (like parallel processing, networks, sensitivity analysis, integration with R, etc.) and improving the non-technical user experience (renewed GUI, a web interface, updated documentation, etc.). See what is new.