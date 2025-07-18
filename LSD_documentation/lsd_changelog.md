LSD Changelog

Version 7.2 (Feb 2020)
The version just introduces a few improvements and changes:

·         Variable update time control. LSD Variables can now be updated/recomputed under arbitrary time schemes, deterministic or random. The modeler can now configure update periods larger than 1, including an initial “sleep” for any Variable. Both period and initial times can be set as a fixed number or a uniform random draw from a modeler-defined range.

·         Monte Carlo experiment automatic data consolidation. Simulation models containing stochastic components which require Monte Carlo experiment to evaluate results can have data consolidation automatically performed by LSD before performing the Analysis of Results.

·         Automatic description for new Variable/Function. When adding new Variables and Functions using the name list, any existing description text (comments) existing in the equation file(s) is used to fill the Description field automatically.

·         New example models. New examples on macroeconomics models (Sant’Anna’s K+S and UFRJ Micro-Macro), including in-depth sensitivity analysis.

·         New Hooks button in LSD Debugger. Dynamic hooks in Objects can now be listed and inspected, as well as the static hook.

·         Windows sizes and positions saving. User customizations of LMM and LSD windows may now be preserved among sessions. This behavior is enabled by default but can be disabled in LMM File>Options menu.

·         Model structure size control. The graphical model representation in the LSD Model Structure window can have the space distribution of the Objects finely controlled, including an automatic fit option.

·         New Macros. LAST_CALC(…) allows reading the last time a Variable or Parameter was calculated or updated. MED(…) / PERC(…) computes the median / percentile of a Variable contained in a brotherhood of Objects. UPDATE provides a tool to compute all Variables in a single Object or in an entire subtree of the model, useful for updating aggregates before Object deletions. USE_SAVED allows accessing any lagged value of a Variable being saved, irrespective of the lag number definition.

·         Compiler info on About LSD window. The information about the compiler being used for model compilation in now presented, allowing for easy identification of compiler mismatch problems.

·         Automatic launch of tail / multitail. When starting background execution of simulations (menu Run>Start 'No Window' Batch and Run>Create/Start Parallel Batch), LSD offers to launch tail or multitail applications to follow up the simulation execution. multitail must be installed by the user in all platforms. See readme.txt for installation instructions on each platform.

·         New embedded Tcl/Tk 8.6.10, bug fixes, mainly for macOS users (required for Mojave/Catalina), lattices are working again.

 

Version 7.1 (Dec 2018)
The new version maintains the compatibility with all the models built with previous versions of. Main changes:

·         Web interface. A full HTML/PHP engine and associated tools to make any LSD model available to be used on the web by unexperienced users. Full modeler control of which configuration values are exposed. Complete validation of user settings. On-server simulation running. Extensive web-based analysis of results support, including time series plots. User configurations up and download. Results CSV data download.

·         Fast Object and Variable look-up. Significant search speed-up of larger models by the allocation of high-performance dynamic memory maps to sets of Object instances (bridges), Variables and Parameters. It replaces linked-list sequential searching in most situations at the expense of slightly higher memory footprint. It affects both user generated searches and internal LSD element look ups. User searches (TSEARCH_CND(…)) require the user explicitly initialize the map structure (INIT_TSEARCH_CND(…)), indicating the Variable or Parameter to be fast searched.

·         Pointer checking. By default, LSD now checks all pointers used in Macros for validity. As this may have performance impact for some models, new Macros (USE_POINTER_CHECK and NO_POINTER_CHECK) are available for the modeler control pointer checking.

·         Eigen library. A powerful library for executing linear algebra in Equations code, including native C++ support to matrix and vector containers, numerical solvers, and related algorithms.

·         Standard C++11 random library. Use the new powerful random number generator facilities included in the C++ library, which may be significantly faster, and add several new distributions to draw from (thanks Frederik for the suggestion).

·         New NOLH internal table. Sensitivity analysis of models with up to 100 factors/parameters and 512 samples using near-orthogonal Latin hypercubes is now possible without using external files.

·         New example models. New examples on industrial dynamics, market dynamics, consumer networks, and macroeconomics, including in-depth sensitivity analysis.

·         New Macros. Lattice macros for color reading (V_LAT(…)), window closing (DELETE_LAT(…)), and move in a Object structure organized as a lattice (UP_LAT(…), DOWN_LAT(…), RIGHT_LAT(…), LEFT_LAT(…)). General macros to count object instances (COUNT(…)/COUNT_ALL(…)), access pure data extension C++ objects directly (EXT(…), EXTS(…)), and execute extension C++ objects methods (DO_EXT(…)). Create dummy Equations (EQUATION_DUMMY(…)) for Variables only updated by other Variables. Search for Object instance number (SEARCH_INST(…)). Option to disable/enable the automatic search of Variables and Parameters (NO_SEARCH/USE_SEARCH). New debug-control macros allow finer control of the LSD Debugger activation and log file creation. Please refer to the LSD Macros documentation.

·         Unlimited hook pointers. A modeler-defined number of hook pointers can now be associated to any Object, allowing for the fast processing of multi-connected Objects.

·         No-instance Objects handling. Some Macros now deal with Objects which have all instances deleted (only during run-time), when meaningful (e.g., when counting instances). The modeler has to handle the results coming from those situations to avoid potentially serious errors. See USE_ZERO_INSTANCE Macro documentation.

·         Improved Gnuplot support. Automatic usage of default plotting terminals, supporting contemporaneous options like Qt and wxt. Updated system terminal options, shared with LMM. WARNING: the old Windows 32-bit version of Gnuplot was removed from LSD, now users in all platforms must install Gnuplot, please refer to Readme.txt for details.

·         Smart features. Automatic detection of problems in system options (platform mismatch) and smarter defaults in LMM. Automatic Variable and Parameter name filling during model structure definition in LSD Browser.

·         Many other small improvements and bug fixes.

 

Version 7.0 (Apr 2018)
The new version maintains the compatibility with all the models built with previous versions of LSD (some optimizations require C++11 and fun_head_fast.h). Main changes:

·         Faster code. Several speed improvements were implemented in LSD core. C++11 optimizations support. Optimized Equation lookup (require C++11 and #include “fun_head_fast.h”). Streamlined Fast mode (FAST = 1/2 or Fast button). Full Windows 64-bit support with up-to-date GCC minGW.

·         Parallel processing. The Equation for any multi-instanced Variable can be evaluated in parallel (by default in all CPU cores). Fine parallelization control (per Object type) to allow mixed parallel/serial evaluation in the same model (support any data model). Updated code profiler to indicate key candidate Objects for parallel processing.

·         Network modeling. Full complex networks modeling using Objects as nodes. Complete Pajek file format compatibility, including temporal networks. Complete usage wizard templates in LMM.

·         Advanced sensitivity analysis. Monte Carlo (by range or points), Elementary Effects and Near-orthogonal Latin Hypercube sampling tools (Design of Experiments). External DoE file import. Full integration with R advanced sensitivity analysis package.

·         Integration with R. Two advanced R packages available on CRAN (LSDinterface and LSDsensitivity). Transparent use of LSD Object-oriented hierarchical data in R (multidimensional arrays). Parallel multi-core reading of multiple results files. Automatic handling of compressed results files. Advanced tools for sensitivity analysis and the study of response surfaces of simulation models (Morris Elementary Effects, Sobol Decomposition, Kriging Meta-modelling etc.).

·         Renewed graphical interface. New button bars. New context menus (right-clicks on lists). Automatic windows positioning. Fully hierarchical window system management (properly block of unavailable windows and buttons etc.). System-wide consistent windows decorations, buttons and organization. In-session persistent windows sizes. Unnecessary window redraws eliminated. Faster debugger interface. Easy to change defaults (windows.tcl). New accelerator keys in LSD Log window. Support of larger structures in the LSD Model Structure window.

·         Multiple source files support. Equation files can be split in many “include” files with editing and version control support.

·         Icon access. Scripts for automatic creation of desktop icons to access LMM in all platforms (see Readme.txt for details).

·         Native macOS support. LMM and LSD models are now standard macOS apps. Embedded up-to-date Tcl/Tk libraries. Useless terminal windows eliminated. Much improved graphical user interface (now on par with Windows/Linux). LLDB debugger support.

·         Improved analysis of results tools. New, native Tk plotting engine (faster and better looking). Fully editable plots. Improved plot windows, including zoom. Many more configuration options for plots.

·         Pause/resume run controls. Simulation runs can be paused resumed asynchronously at any time (no preset breakpoint required), including full debugger support.

·         New unsaved configuration indicator. All LSD windows now show configuration name and save status (‘*’ in title bar when unsaved changes are present). Unsaved changes warning dialog in all potential data loss situations.

·         Improved crash handling. Full handling of system signals and exceptions in all modules. Tcl/Tk buffer overrun control.

·         New persistent configuration options. Choose the default external debugger. Define arbitrary directory for new models. Predefine the font type and size (smart defaults by platform) all over LSD. Save other LMM interface options (syntax highlighting, text wrapping, tab size, LMM auto hide).

·         Compressed and CSV results files. All results files are automatically saved in compressed (.gz) format. Transparent loading of compressed results files in LSD and R. Option to save results in CSV format.

·         New LSD macros. Logging (LOG, PLOG), simulation control (FAST, FAST_FULL, OBSERVE, SLEEP, ABORT), time (T, LAST_T), random numbers (RND_GENERATOR, RND_SEED, RND_SETSEED), support for not-a-number handling (USE_NAN, NO_NAN), better control of initialization of Variables in new Objects (WRITELL, ADDxOBJL).

·         User-defined data in Objects. Any C++ data structure can be attached to any LSD Object, including arrays, vectors, STL containers and user-defined class or struct.

·         Updated lattice tools. Improved lattice performance. New easy-to-use lattice macros, including save to disk. Revised lattice windows. New lattice color options (full RGB support).

·         New pseudorandom number generator. A new (default) Mersenne-Twister generator included (old Parks-Miler still available as option).

·         New statistical functions. Random draws from lognormal, beta and asymmetric Laplace distributions. Cumulative distribution functions for the uniform, normal, lognormal, Poisson, gamma, beta and asymmetric Laplace distributions.

·         New and improved automatic document features. Existing HTML and Latex reports fully updated with more options and modern design. New Latex references report.

·         Updated documentation. The entire LSD documentation was updated to the current version.

·         New and revised example models. New examples on industrial dynamics and consumer networks.

·         Lots of small bug fixes and improvements.

 

Version 6.4 (Nov 2015)
The new version maintains the compatibility with all the models built with previous versions of LSD. There are several improvements:

·         New network functions and macros. Added command for the creation and manipulation of a network from Equations. Network is formed by brother Objects and several standard network templates (random, Small World, Power-Law, etc.) are available for quick and automatic network creation.

·         Improvements to LSD language. Improve the handling of WRITE for t ≠ 0 and allow the change of initial values (use negative t).

·         Improved syntax highlighting. All LSD and C++ keywords, identifiers and more are now color-marked in LMM (with disable option)

·         Graphical interface tweaks. Fix resetting of window size, reduce flicker and standardize menu item names. Allow copying from the Log window. Fix tabs management in LMM. Allow disabling Model Structure window. Add direct options (buttons) for deleting model structure elements. New LSD and LMM icons in Windows and Linux. Improved initial windows sizes and placement.

·         Improvements to analysis of results. Support to logarithmic scales. Improve the display of scales with precision control. Add reverse sort to variables under analysis of results.

·         Improved memory management. All run time memory leaks were eliminated.

·         Updated LSD course slides.

·         Other minor bug fixes and documentation improvements.

 

Version 5.2
The new version maintains the compatibility with all the models built with previous versions of LSD. There are several improvements:

·         Faster code. A new (turbo) search function scans the model in a much faster way leap-frogging large sets of objects. This function avoids the necessity for users to optimize their code when running large models.

·         New interfaces to assign initial values and number of objects. It is possible to easily initialize large models with sophisticated data structures.

·         Change number of objects and series of data during a simulation run. The initialization interfaces are accessible also from the data browser window and the debugger. If marked to be saved in the original objects, elements in new objects will also be saved,

·         Editable graphs. The labels in the graphs produced in Analysis of Results can now be edited in their text, fonts and colors, and new labels can be added. Graphs now include also values at time 0 for parameters and lagged variables.

·         New documentation. See the documentation page from the LMM help.

·         New elements’ options. Now the user can specify the variables and parameters more relevant to be initialized and containing the most relevant results. The list of these elements can be printed from the LSD browser and is automatically inserted in the model report.

·         Stricter error catching. The number of errors spotted by LSD model programs is vastly increased. Moreover, detailed information is provided when an error occurs. For example, among other things, the system controls the amount of memory required to save the results, and indicated when it is not sufficient, leaving to the user the decision on whether to reduce the model dimension, simulation length, or amount of data to save.

·         Smoother installation and run under Linux. A number of problems of compatibility with different Linux distribution should be solved.

·         Other minor bug fixes and documentation improvements.