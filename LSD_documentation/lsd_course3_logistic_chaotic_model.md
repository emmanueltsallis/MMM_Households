LSD- Lesson 2: Logistic chaotic model
 LSD- Laboratory for Simulation Development
 Lecture 2- Logistic function and
 chaotic behaviour

 Lecture’s goal
 The use of simulation models allows to assess and compare
 large series of values. This lecture will focus more on the
 module dealing with data, statistical and graphical
 management.
 Wewill focus on a model composed by a simple equation that
 is known to have a highly complex behaviour, generating linear
 and chaotic time series.
 Using the LSD graphical tools we will explore the model and
 generate a representation of the results in order to understand
 the properties of the chaotic function.

 Logistic Chaotic Model
 Consider the model made of the single equation
 Xt = m Xt 1 (1 Xt 1)
 To implement this model follow the usual steps:
 1 Create a new model using the model browser in LMM.
 2 Insert the equation’s code for the model.
 3 Compile and run the model (menu Model/Run).
 4 Using the Lsd model program generate one object and
 place in it variable X with 1 lag and parameter m.

 Logistic Chaotic Model
 The model equation can be written as follows
 EQUATION("X")
 /*
 Logistic equation
 */
 v[0]=VL("X",1);
 v[1]=V("m");
 v[2]=v[1]*v[0]*(1-v[0]);
 RESULT( v[2])
LSD-Lesson2:Logisticchaoticmodel
 Simulatingthelogisticfunction
 AssumingX0=05weobtaindifferentresultsfordifferent
 valuesofm.Whathappensform=2?
 Xt=m Xt 1 (1 Xt 1)
 Xt m=1 m=2 m=25 m=29 m=31 m=34 m=37 m=399
 X0 0.5 0.5 0.5 0.5 0.5 0.5 0.5 0.5
 X1 0.25 0.5 0.625 0.725 0.775 0.85 0.925 0.9975
 X2 0.1875 0.5 0.585938 0.578188 0.540563 0.4335 0.256687 0.00995006
 X3 0.152344 0.5 0.606537 0.707271 0.7699 0.834964 0.705956 0.0393057
 X4 0.129135 0.5 0.596625 0.600412 0.549178 0.468516 0.768053 0.150666
 X5 0.112459 0.5 0.601659 0.695761 0.767503 0.84663 0.659146 0.510582
 X6 0.099812 0.5 0.599164 0.613865 0.553171 0.441482 0.831289 0.997053
 X7 0.0898497 0.5 0.600416 0.6874 0.766236 0.838357 0.518916 0.0117231
 X8 0.0817767 0.5 0.599791 0.623155 0.555267 0.460749 0.923676 0.0462268
 X9 0.0750893 0.5 0.600104 0.681015 0.765531 0.844762 0.260845 0.175918
 X10 0.0694509 0.5 0.599948 0.629977 0.556429 0.445874 0.713378 0.578435

 Logistic Chaotic Model
 The properties of data series can hardly be appreciated by
 reading the numbers. As an example consider the following
 graphs.
 Weshow firstly all the series above, computed over 10 time
 steps.
 Wethen see the 100 series for each couple of series, for easier
 reading
 Remind: menu Run/Sim.Settings sets the number of steps in
 the simulation. Menu Data/Init.Values sets the initial values for
 the data in an object. Menu File/Reload reloads a fresh
 configuration at the end of a simulation run.

 0.9975
 X
 0.750613
 0.503725
 0.256837
 0.00995
 m=3.4
 m=2.5
 m=2
 m=1
 m=3.7
 m=3.1
 m=2.9
 m=3.99
 0
 2
 5
 7
 Time steps
 10

 0.5
 0.377349
 0.254698
 0.132047
 0.009396
 m=2
 m=1
 0
 25
 50
 75
 100

 0.725
 0.66875
 0.6125
 0.55625
 0.5
 m=3.1
 m=2.9
 0
 25
 50
 75
 100

 0.85
 0.745875
 0.64175
 0.537625
 0.4335
 0
 m=3.1
 m=3.4
 25
 50
 75
 100

 0.9975
 0.750613
 0.503725
 0.256837
 0.00995
 m=3.7
 m=3.99
 0
 25
 50
 75
 100

 Logistic Chaotic Model
 The function produces extremely different results depending on
 the value of m. To understand how the results depend on m
 let’s make a systematic analysis of the simulation results.
 Wewill create a large number of series computed
 independently. We will set m to a slightly different value for each
 series, so that we can have an understanding of the function’s
 behaviour as if we were testing the whole continuum for m.
 Finally, we will set the initial points for the X to random values,
 so that results do not depend on specific values of the initial X.

 Logistic Chaotic Model
 Let’s set the configuration to compute 10,000 series over 1,000
 time steps.
 For each series we assign a random value to X chosen in the
 range (0,1).
 For each series we assign a different and increasing value of m
 starting from 2.8 and reaching, for the 10000th series, 3.99.
 Finally, we save all values of m and of X for post-simulation
 analysis. The operations required for the above setting are
 listed below.

 Logistic Chaotic Model
 1 UsemenuData/Set.Obj.Num/All Obj to generate 10000 copies
 of the object.
 2 Place the Browser to show the object’s content.
 3 Openthe initial values interface with Data/Init.Values.
 4 Usethe buttons Set All on the side of m and X to assign values
 to all the elements.
 5 Set musing the option Range between 2.8 and 3.99.
 6 Set X using the option Random (Uniform) between 0.01 and
 0.99.
 7 Exit the initial values window and set the options for m and X to
 be saved
 8 UsemenuRun/Sim.Settings to set 1000 time steps.
 Now, run the simulation using menu Run/Run.

 Analyse the results
 At the end of the simulation open the analysis of results module
 (menu Data/Analysis). The window shows 20000 series
 available (all the m’s and X’s).
 If this is not the case, exit the analysis of results module and set on the option
 to save the missing item. Then re-run the simulation and open the Analysis of
 Results module.
 As suggested from the pilot experiments, choosing a series
 among those computed with m < 3, the series rapidly
 converges. For subsequent values, the series oscillates
 between two values, and for still higher values the series
 becomes chaotic.
 To make sense of the function overall limit behaviour the best
 option is to generate a scatter plot graph with all the values of
 monthe horizontal axis, and the corresponding value of X, at
 the final step, on the vertical one.

 Analyse the results
 LSD is designed intuitively to perform the most common
 operations, but also to provide sophisticated tools for special
 cases.
 Wenowface the problem of selecting all the m’s, that is, 10,000
 series in a list of 20,000. Clicking on each of them is obviously
 impossible. One option is to click on the button Sort to
 re-arrange the series in alphabetical order, and then click on
 the first and last series, keeping the key shift pressed, to select
 all series in between.
 However, even this route this is tedious, and does not solve all
 the possible selection problems one may need. LSD offers a
 more flexible and fast tool for series selection. Click with the
 right button of the mouse when the pointer is over one of the
 series m.

 Analyse the results
 The new window offers many selection criteria. We need the
 simplest, already selected by default, that is, “select all series of
 this type”. Click on Ok to confirm.
 As you will see, all the series with the label m have been placed
 in the central box.
 After this, replicate the same operation, placing all the series for
 X in the Series Selected box.

 Scatter plots
 The analysis of results module is controlled setting the options
 on the lower right side of the window. We need to perform a
 Cross section, XY plot.
 The plot we wish to create is more readable using Points,
 rather than lines. Set these options as indicated and press the
 button Plot.
 A new window will appear asking for the time step at which the
 values of the selected series must be used. Leave the default
 value of 1000, the latest time step of the simulation, and press
 Continue.
 The following graph will be created and shown.
LSD-Lesson2:Logisticchaoticmodel
 0
 0.1
 0.2
 0.3
 0.4
 0.5
 0.6
 0.7
 0.8
 0.9
 1
 2.6 2.8 3 3.2 3.4 3.6 3.8 4
 m1
 X1(1000)

 Scatter plot
 The graph contains one point for each value of X1000 with the
 coordinate of the corresponding m value on the horizontal axis.
 The graph shows that, for increasing values of m, we see firstly
 the convergence of the series to a unique point.
 For larger values of m the series oscillate indefinitely between
 two points, generating a biforcation in the plot because the
 series will be differently located at the two poles of their
 oscillations.
 For a short span of m, the function generates a cycle across 4
 points. Subsequently it becomes chaotic, although in some
 areas the density of the points seem to be very thin.

 Analyse the results: conclusions
 Though LSD’s main goal is to create efficiently simulations, the
 possibility to generate basic graphic representations of
 simulation results is very important to appreciate.
 In particular, LSD graphical tools manage easily massive
 amounts of data generated during simulation runs. More
 sophisticated graphical or statistical analyses can be obtained
 exporting the LSD data in external packages such as STATA or
 R.
 The analysis of results module, included in any LSD model
 program, can be activated both at the end of a simulation, as
 well as during an interrupted simulation run. It is possible to
 plot various types of graphs, generate statistics, or simply
 export data sets for further elaboration. See the Help manual
 page for details.