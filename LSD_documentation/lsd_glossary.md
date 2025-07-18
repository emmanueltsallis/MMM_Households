Glossary of LSD Model Elements

A model in LSD is composed by a hierarchical collection of Objects organized in an inverted tree structure and each defined as containing elements as Variables, Parameters and/or descending Objects.

Though a LSD model is rather intuitive, it is crucial to understand the difference between the content of the model in terms of structure (i.e., the definitions of the different elements) and of data (number of element instances/copies and initial values).

The structure of the model is defined by the modeler (see menu Model) and cannot be changed (in general) without modifying also the Equations of the model, which requires a (minimal) programming expertise. Instead, once a model is built and a structure defined, the data of a model can be modified by any user, being guided by user-friendly interfaces (menu Data). At last, the fully configured model can be easily simulated (menu Run).


Object
It is the basic entity of a LSD model. It represents an entity of the virtual reality simulated in the model. It is composed by: a label, flags for computation options, some (or even none) Variables, some (or even none) Parameters, and ancestor and descendant Objects.

An Object is defined when the model is built and its definition cannot change during a simulation run. A specific configuration of a model can implement as many copies, or instances, of a specific Object type, and this number can also vary during a simulation run. Each instance of an Object replicates exactly the same structure of any other instance of the same Object type, but, of course, may assign different numerical values to the elements it contains (i.e., Variables and Parameters). The descendants, as well, must share the same structure for each instance of an Object type, though their number (of instances) can vary.

See more details about Objects in the FAQ.

Object label
The Object label is the name used to identify an Object type. The label must be unique for each Object type, irrespective of its position in the model structure (i.e., the inverted tree), and, so, no other Object, Variable or Parameter in the model may share the same label. The label is a string of up to 99 characters which cannot contain non-alphanumeric symbols, like spaces (‘ ’), slashes (‘/’ and ‘\’), tabs, end-of-string or other special characters. In LSD, labels are case sensitive.

Object flags for computation options
Normally, these options can be ignored, since they are useful only to increase the speed of the simulation runs under certain circumstances. For huge models, it can be the case that some Objects are used only for storing data. If there are very many instances of these Objects it is possible to force the simulation to ignore them during the simulation time step, so that they are not (uselessly) explored for updating Variables. It is safe to leave the default option (on).


Variables
Variables are the main LSD element and are used to store numerical (real) values obtained as result of the computation of an Equation. An Equation normally uses the values of Parameters and other Variables contained in the model. Variables’ values are not restricted to the contemporaneous ones (same current time t) but can also involve lagged values (from time t = t – h, h = 1, 2,…).

A Variable is defined by its label, the number of lags and the associated Equation. See more details in the FAQ.

Since LSD is based on the object-oriented programing (OOP) paradigm, it is not recommended (or natively supported) the use of vectors and matrices of Variables. In order to use many instances of a given Variable (or Parameter), similarly to elements of a vector/matrix in the traditional paradigm, in OOP it is required the creation of several instances of the Object type containing the Variable or Parameter of interest. Note that this means the whole content of the Object (all its elements) will be replicated in many instances. If the modeler finds out that part of the replicated Object is useless for the model (or demand too much memory), this may indicate that the model structure can be better designed and the model more likely needs to be revised (e.g., splitting the data two different Object types).

Variable label
The Variable label is the name used to identify a Variable. The label must be unique for each Variable, even if contained in different Objects, and, so, no other Object, Variable or Parameter in the model may share the same label. The label is a string of up to 99 characters which cannot contain non-alphanumeric symbols, like spaces (‘ ’), slashes (‘/’ and ‘\’), tabs, end-of-string or other special characters. In LSD, labels are case sensitive.

Number of lags of a Variable
Each Variable is assigned a numerical value at each time step. In most cases, some Variables in their computation need to use the past value(s) of itself or other Variables. Therefore, all the Variables having their past values used in the computation of an Equation must have such “lagged” values (i.e., computed in previous time steps) saved. So, when creating a Variable, modelers have to inform LSD up to how many “lags” the Variable values are required.

If a Variable is defined as having no (zero) lags, it does not need any initial value set at the beginning of the simulation, since its value can be computed at the beginning of the simulation run (t = 1). However, in case a Variable has lagged values used in any Equation in the model, users need to assign numerical initial values to it. Initial values are used during the initial time steps of the simulation run while the lagged values cannot be computed yet (e.g., the value at t = 0 during time t = 1).

See also how to set initial values and the FAQ about the management of time in a simulation run.

Equation associated to a Variable
The values for Variables are computed at each time step using the associated Equation code. The code of all the Equations in a model is contained in an equation file, which is compiled by LMM in order to obtain a LSD model program.

The code for an Equation can be any legal C++ piece of code plus the LSD defined macros or functions. Note that the Equations can also be used to perform other tasks besides providing the (required) numerical values to Variables. For example, they can create or destroy Objects, sort sets of Object instances, overwrite previously computed values of Variables or modify the values of Parameters. Since it is regular C++ code, an Equation can also be used to access external packages and libraries.

The code for an Equation must be written as the computations to be executed during a generic time step. During a simulation run, LSD takes care of updating the different Variables in order to respect the precedence order implied by the set of difference equations used to define the Equations' code. That is, to compute the equation xt = f(yt), the system will automatically compute the equation for y before the equation for x, because the updated value of y is necessary for calculating x. If, instead, the equation is like xt = f(yt -1), then the system may compute x before y, because Variable y has its value for the previous time step already stored. Warning: LSD macros to overwrite the automatically-calculated values must be used with extreme care because they may inhibit the automatic updating order control.

See the FAQ for further details.


Parameters
A Parameter is one of the elements of an Object. It must have a numerical (real) value assigned and it is not modified by LSD during the simulation run. Therefore, a Parameter is basically a special kind of Variable without an Equation or lags with a (more likely) constant numerical value attached. It also requires a naming label (same restrictions to the naming of Variables apply).

Though LSD does not explicitly compute new values for Parameters during a simulation run, the Equation’s code for any Variable can overwrite the value of a Parameter at any time step.

In order to run a simulation, it is necessary that each Parameter (contained in every instance of all Objects) have a numerical value assigned before the simulation is run. See also how to set initial values.

See more details in the FAQ.


Ancestor and descendants
A model in LSD can be considered as a collection of Objects organized in a hierarchical inverted tree structure. That is, each Object has one and only one parent/ancestor (from which it directly descends) and, possibly, a set of son/descendant (brother) Objects. The structure of the model must be designed on the basis of the meaning attributed by the modeler to the Objects. In general, an Object is defined as a descendant of another Object if it can be interpreted as a component of its parent Object.

Technically, the hierarchy tree is used by LSD at run time to allow the Equation for a Variable contained in an Object to easily find the values of other Variables and Parameters contained in the same or different Objects. For example, consider a model that contains many instances of an Object named Market, from each of which descends many Object instances of type Firm. If Equations for Variables contained in Firm needs to retrieve values in Market, each son Firm can directly use the (single) values stored in their parent Market without ambiguity.

In the Equation’s code, modelers refer to other Variables or Parameters of the model by simply using their labels, without any form of indexing like the ones used for vectors or matrices. However, of course, in general there may be many instances of any Variable or Parameter contained in multiple brother-Object instances. In order to choose which instance to use, LSD exploits the hierarchical structure in a precise manner:

1.     A value to any element is requested to the same specific Object where the Equation for the requesting Variable is located.

2.     If this Object contains the requested element, the value for it is returned.

3.     If it does not contain the requested element, the request is then sent to its descending Objects, if any, in the same order they are listed or were created.

4.     If one son Object contains the requested element, the value for the first one found (first instance) is returned.

5.     In case no descending Object contains the requested element, the request is sent to its parent Object

6.     If the parent Object contains the requested element, the value for it is returned.

7.     If the parent does not contain the requested element, the request is sent to its own parent Object (the grandparent of the original requestor Object).

8.     Strategy in steps 6 and 7 is repeated until the Root object is reached.

LSD Object search strategy has the property that, if the model is well defined, modelers can write the Equations' code by simply using the label of the necessary Parameters or Variables, despite the number of instances they can replicated in the model and where they are located.

For example, consider a model where an Object named Market is defined as having one Parameter called Price and several instances of a son Object type named Firm. If the model data define Market as being replicated in several instances (e.g., an economy with many markets), each of them will be created as having a set of descending (brother) Firm Objects. If the Equations for the Variables in Firm request the value of Price, each of them will refer to the same instance of Price contained in their own instance of the parent Market Object. So, the modeler does not have to worry for specifying which prices among the several markets are to be considered by any firm present in the model, irrespective to which particular market it may pertain.

LSD also provides ways to overrule the default Object search mode. Suppose that, for an extension of the above example, the modeler wants Firm's to choose the Market on which they operate. Therefore, Firm will not be any longer a “component” of Market, so each time Price is used in the Equations an algorithm to decide which Market instance to refer to must be created. In this situation, a better model structure could be having the set of Firm Object instances defined as “parallel” to the set of Market Objects.


Models' split representation
A LSD model is split in two distinct parts: the Equations' code (in the equation file) and the model structure and data (in the model configuration file). The Equations are expressed as C++ code which is compiled by LMM to produce the LSD model program. The model structure and the associated data are instead loaded dynamically from a model configuration (many may coexist). 

Under this split arrangement, the resulting simulation program is as fast as any (well designed) regular C++ program. However, differently from most traditional simulation programs, the model configuration becomes extremely flexible because every value (and many different setups) of the model can be easily changed (and maintained). Still, as in any compiled coding approach, in order to change even slightly the Equations of a model, the recompilation of the changed parts is required before the simulation can run again. To keep the process simple, LMM becomes most of this process transparent to the modeler.

The information on the structure of the model and on the initial values used for the simulations is kept together in the configuration file(s) (.lsd extension). These files should never be edited manually, as they are created and used automatically by LSD. See more details in the FAQ.

When the LSD Browser loads a configuration file, it recreates in the computer memory the structure of the corresponding model. The in-memory structure includes all the required initial values for the corresponding elements as well the other needed simulation settings. When running the simulation, each Variable in every Object instance of the model is connected to the piece of code corresponding to its Equation. In other words, each LSD model program is executable software which contains the code of the Equations for a given set of Variables. It can load any LSD model configuration associated to that particular model, but not a configuration from a different model which contains other Variables or Parameters. Note that the Equations’ code embedded in a LSD model program may contain code for computing variables not used in a particular model configuration (this “extra” code will simply be never used). Still, it is not possible to run a LSD model program using a Variable whose Equation’s code was not included when the program was compiled.

The split arrangement allows, for all LSD simulation programs, containing any set of Equations (even no Equation at all), to load and edit the structure of any model (but not to run it). Only when the simulation is actually run, the possible inconsistency among the Variables in the model configuration and the Equations in the model program will issue an error.