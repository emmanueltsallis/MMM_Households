 LSD- Laboratory for Simulation Development
 Lecture 3- Replicator dynamics model

 Lecture objective
 In this lecture we will implement a model with an economic
 interpretation.
 As we will see, though the model is extremely simple it can
 generate results not immediately intuitive.
 Wewill use LSD to implement the model, analyse the results,
 debug the model, and address a basic methodological issue
 with simulation models.

 Replicator Dynamics Model
 Let’s consider a model made of a market and several firms.
 Firms are assigned a constant level of quality. Firms’ sales are
 computed according to the equation:
 Salest = Salest 1 1+a Quality AvQualityt
 AvQualityt
 That is, sales change of aSalest 1
 100
 for each percentage of
 difference between the firms’ own quality and the market
 average quality.
 Create a new model in LMM, call it RD. Insert the code for this
 equation.

 Replicator Dynamics Equation
 EQUATION("Sales")
 /*
 Level of sales, computed as the past sales plus a share of the
 difference of quality in respect of the average quality
 */
 v[0]=V("Quality");
 v[1]=V("a");
 v[2]=VL("Sales",1);
 v[3]=V("AvQuality");
 v[4]=v[2]*(1+v[1]*(v[0]-v[3])/v[3]);
 RESULT(v[4] )

 Replicator Dynamics Model
 The average quality is the weighted average of firms’ qualities, where
 sales are used as weights.
 This makes sure that the contribution of each firm to the average is
 proportional to its relevance in the market: firms with higher level of
 sales are more relevant in defining the quality of goods in a market.

 Replicator Dynamics Model
 If we have N firms on which to compute the average of the
 quality weighted with the sales, the equation is:
 N
 AvQualityt =
 i=1 Salesi
 t 
Qualityi
 N
 i=1 Salesi
 t

 Average quality: the use of cycles
 In computational terms the average is implemented with the
 following steps:
 1 Set to 0 two temporary variables where to cumulate values
 for the numerator and denominator, call them Num and
 Denum;
 2 goin the first object Firm;
 3 compute the values of Quality and and Sales for the
 object;
 4 increase the numerator by Quality x Sales;
 5 increase the denominator by Sales;
 6 moveto the next object Firm. If there is one goto 3.
 7 Otherwise (no more Firm), return the ratio Num:Denum.

 Use of cycles
 The Lsd code equivalent is the following:
 EQUATION("AvQuality")
 /*
 Average quality, weighted with the value of sales
 */
 v[0]=0;
 v[1]=0;
 CYCLE(cur, "Firm")
 {
 v[2]=VS(cur,"Quality");
 v[3]=VS(cur,"Sales");
 v[0]=v[0]+v[2]*v[3];
 v[1]=v[1]+v[3];
 }
 RESULT(v[0]/v[1] )

 Use of cycles
 Let’s see in detail the code for the equation.
 ...
 v[0]=0;
 v[1]=0;
 ...
 These two lines set to 0 two local variables. These variables
 are used as containers for the cumulated values of Sales x
 Quality (numerator) and Sales (denominator).
 They need to be explicitly set to 0 because C++ does not
 initialize variables.

 Use of cycles
 CYCLE(cur, "Firm")
 {
 v[2]=VS(cur,"Quality");
 v[3]=VS(cur,"Sales");
 ...
 }
 This code implements a cycle. That is, the lines within the cycle are repeated
 again and again as many times as many copies of object Firm are contained
 into the object containing the computing variable, in this case AvQuality.
 At each repetition, the local pointer cur refers to a different copy of a Firm;
 cur is the similar to local variables v[.], but, instead of containing numerical
 values, pointers deal with object.
 The LSD command VS(cur, "VarLabel") is like V("VarLabel") but
 instead of searching the element VarLabel in the object where the equation
 is executed (AvQuality is contained in Market) it searches in the element
 pointed to by cur, which is an object of type Firm.

 Replicator Dynamics Model: cycle
 In LSD it is possible to generate many different computational structure acting
 on the position of the variables within the structure of objects.
 In general, objects “up” in the hierarchy contains elements affecting, or
 affected by, many copies of other elements contained in the entities “down” in
 the hierarchy.
 LSD the code automatically executes the most sensible operation depending
 on the position of the object containing the variable whose equation is
 executed.

 Replicator Dynamics Model: cycle
 In our case the model is composed by an object, Market, containing several
 copies of object Firm. The equation for AvQuality is to be located in Market,
 since it is collective property of all firms, not a specific one.
 It its code requested generically Quality, as in V("Quality"), without
 pointing to a specific copy of an (using object cur), the system would be
 erroneously return always the value read from the very first copy in the set of
 objects Firm.
 Market
 AvQuality
 Firm
 Firm
 Sales
 Quality
 Sales
 Quality
 Firm
 Sales
 Quality
 Firm
 Sales
 Quality

 Replicator Dynamics Model: cycle
 The solution is to use the expression VS(cur,"Quality"), which
 forces the code to search Quality not in Market but in the object
 pointed to by cur.
 Pointers are temporary variables where modellers store objects
 instead of numbers. When the command line CYCLE(cur,"Firm")
 is used, the system repeats the lines of code that follow as many
 times as many objects Firm are found in Market. During each
 repetition cur will contain a different copy of Firm.
 Market
 AvQuality
 CYCLE(cur, "Firm")
 {
 ...
 }
 cur=
 Firm
 cur=
 Firm
 Sales
 Quality
 Sales
 Quality
 cur=
 Firm
 Sales
 Quality
 cur=
 Firm
 Sales
 Quality

 Replicator Dynamics Model: cycle
 CYCLE(cur, "Firm")
 {
 v[2]=VS(cur,"Quality");
 v[3]=VS(cur,"Sales");
 v[0]=v[0]+v[2]*v[3];
 v[1]=v[1]+v[3];
 }
 RESULT(v[0]/v[1] )
 The lines for v[0] and v[1] in the cycles computes the values
 for the weighted average, using the values of each firm v[2]
 and v[3].

 Use of cycles
 Note that the LSD command CYCLE(cur, "ObjLabel")
 works correctly only if object executing the equation is above
 (i.e., contains) the group of objects to scan with the cycle.
 The command works as follows. Firstly, it searches the group of objects
 ObjLabel among the objects contained within the object whose variable is
 updated. When it is found, the first copy of the group is assigned to the
 pointer cur, and the body of the cycle is executed. When finished, the cycle
 controls whether there is another copy of object next to the one just used. If
 there is another copy, this is assigned to cur and the body is repeated again.
 IMPORTANT: control always that the variable whose equation
 contains a cycle is located in the correct object.

 Model Compilation and Configuration
 Wecan now compile the model: menu Model/Run will create
 the Lsd model program for this model, or give messages on the
 grammar errors preventing the compilation.
 If this is case, check the number on the error message next to
 the file name. It indicates the line number where the error has
 been detected, so you can easily fix equation checking the
 code immediately before the location.
 In case of success, create the model structure using the
 commands in menu Model to create the variables, parameters
 and objects necessary for the model. Beware to have the LSD
 Browser showing the correct object before including new items.

 Replicator Dynamics Model
 The model must be composed by:
 Object Market containing variable AvQuality (0 lags),
 parameter a and object Firm.
 Object Firm containing variable Sales (1 lags) and
 parameter Quality.
 Finally, generate 10 copies of object Firm initializing their
 content as follows:
 assign to each Quality an increasing value from 10 to 19;
 assign to each Sales[-1] (lagged value of Sales) the same
 value 1000.
 assign value 0.2 to parameter a;
 Wecan now run the model, but...

 Dead lock errors
 If no other error appeared, the model program shows a small
 window signaling the occurrence of a fatal error preventing the
 continuation of the simulation. As in any instance of error the
 Log window contains extensive information on the reason for
 the problem. In this case it will read:

 Dead lock errors
 Dead lock! Variable:
 AvQuality
 requested by Object:
 Firm
 Fatal error detected at time 1.
 Offending code contained in the equation for Variable: Sales
 ... (deleted text) ...
 Level Variable Label
 2 Sales
 1 AvQuality
 0 Lsd Simulation Manager

 Dead-lock errors
 The dead-lock error is an example of a logical error. The two
 equations have a perfectly legal implementation, considered
 independently. But they cannot work in the same model.
 To see why let’s consider again the equations.
 N
 AvQualityt =
 i=1 Salesi
 t 
Qualityi
 N
 i=1 Salesi
 t
 Salest = Salest 1 1+a Quality AvQualityt
 AvQualityt
 (1)
 (2)

 Dead-lock errors
 Suppose that at the beginning of the simulation 1 the model starts to
 compute equation (1). In order to execute the code for the equation it
 needs the values of Sales and Quality for each firm.
 The system can access the value of Quality immediately, since it is a
 parameter. But Sales is not computed yet, so the system cannot
 access its value.
 In this case the system interrupts the computation of AvQuality and
 starts the execution of the equation (2) in order to get the value of
 Sales from the first Firm.
 This is the way LSD determines automatically the priority of execution
 for the equations within a time step.

 Dead-lock errors
 The problem is that, in order to compute equation (2), the system
 needs, among other values, also the value of AvQuality at time t = 1.
 But this is not available, because its execution has been interrupted.
 Even if we start from equation (2) we have the same problem: neither
 of the two equations can be computed before the other!
 This is essentially a chicken-egg problem rooted not in the code of a
 single equation, but in the logic of the model itself, which is a
 limitation, and a strength, of computational models.

 Dead-lock errors
 Dead-locks can appear only in computational models, not in
 mathematical ones. In mathematics it is perfectly normal to have a
 system of equations like:
 Xt = 2+3Yt
 Yt = 4 2Xt
 (1)
 (2)
 The mathematical meaning of the system is: find the values of Xt and
 Yt such that the conditions (1) and (2) are satisfied.
 In computational terms, however, such system is “illegal”, in the
 sense that generates an impossible computational structure. The
 computer reads the equations as: to compute X first you need to
 compute Y. To compute Y first you need to compute X. Locked.

 Mathematics vs. Computers
 Mathematical models and simulation models are different
 because the second unfold irreversibly through time, while
 mathematical models express a-temporal relations.
 Which modeling style is better in Economics? Depends on the
 phenomenon you want to represent.
 Mathematical models represent laws deemed universal.
 For example, a demand curve P = 1
 Q (or Q = 1
 P?)
 Computational models represent dynamical phenomena
 depending on many local conditions. For example, the
 development of a market.

 Learning by coding
 The logic of time consistency, necessary for computation
 models, requires the modeler to consider the timing of events,
 besides their computational structure.
 In our example the two equations are computationally correct to
 implement the variables’ content, but the model cannot work
 because timing we involuntarily imposed is inconsistent.
 Many economic phenomena depend crucially on time, and the
 need to implement a model in computational format forces
 modelers to consider this aspect.

 Solving dead-lock errors
 How do wesolve a dead-lock error? We need to allow the system to
 f
 ind a viable priority, completing first one equation and then the other.
 Wehave two options: first equation (1) and then equation (2), or the
 other way round. Let’s have the model to compute first AvQuality.
 That is, our model becomes:
 N
 AvQualityt =
 i=1 Salesi
 t-1 
Qualityi
 N
 i=1 Salesi
 t-1
 Salest = Salest 1 1+a Quality AvQualityt
 AvQualityt
 (1)
 (2)
 In this way, equation (1) can be computed because it does not need
 to compute Salest. When (1) computes AvQualityt then the system
 can compute (2).

 Solving dead-lock errors
 Notice that in LSD the modeler does not need to produce the
 whole list of variables to be updated, which can be annoying in
 case of large models.
 Rather, modelers simply provide local indications, telling the
 system that one value may be computed before of another.
 The system automatically generates one of the many possible
 sequences of variables’ computation guaranteeing that the
 constraints indicated are respected.

 Fixing the dead-lock error
 The equation for average quality becomes:
 EQUATION("AvQuality")
 /*
 Average quality, weighted with the value of sales
 */
 v[0]=0;
 v[1]=0;
 CYCLE(cur, "Firm")
 {
 v[2]=VS(cur,"Quality");
 v[3]=VLS(cur,"Sales",1); //use lagged values
 v[0]=v[0]+v[2]*v[3];
 v[1]=v[1]+v[3];
 }
 RESULT(v[0]/v[1] )
LSD-Lecture3:Replicatordynamicsmodel
 Runningthemodel
 Nowthemodelworks.The10firmswithqualitiesrangingfrom10to
 19andinitialsalesat100producethefollowingresult.
 0 100 200 300 400
 0
 246.707
 493.414
 740.121
 986.828
 Sales_1_1 Sales_1_2 Sales_1_3 Sales_1_4 Sales_1_5 Sales_1_6 Sales_1_7 Sales_1_8 Sales_1_9 Sales_1_10

 Interpretation
 Simulation results gives the possibility to reach conclusions
 difficult to appreciate without executing simulations.
 The model can be interpreted as expressing the fact that
 high-quality firms eventually gain shares at the expenses of low
 quality ones.
 Note that this is not a model of competition, at least in the long
 term. It is a model representing the path leading to a monopoly,
 since it is impossible to prevent the highest quality firm to
 dominate the market.

 Question
 Moreover, even extremely simple models, such as this one,
 have the potential to generate puzzles, which the very nature of
 the model as computer program can help to solve.
 QUESTION: The model states, essentially, that sales’ dynamics
 depend quality. However some series, such as the 9th show
 initially an increase in sales followed by a decrement. How is
 this possible, given that quality is a constant parameter?

 Debugging Lsd models
 LSD allows to inspect each and every aspect of a model during
 a simulation run. This is performed using a module called Lsd
 Debugger. This module starts automatically in case of errors.
 Moreover, users can activate it under two, joint, conditions:
 1 Onevariable marked with the option Debug concluded its
 computation.
 2 Thesimulation is executed in debug mode.

 Debugging Lsd models
 The debug mode is activated during a simulation run by one of
 several possibilities:
 1 Clicking on the button Debug in the Log window.
 2 Pre-setting a specific time step before a simulation run
 (among Simulation Settings).
 3 Pre-setting a future time step during a debugging session.
 4 Specify a condition on the value of an element, e.g. when
 a variable is negative.
 5 Writing in the code of one equation a command triggering
 the debugging session (command INTERACT(...)).

 Debugging Lsd models
 During a debugging session the modeler can:
 Analyse the results available.
 Inspect the content of every copy of every object, reading
 the current values of the elements.
 Proceed the simulation run step-by-step, with each step
 being the completed computation of a variable with the flag
 Debug set on.
 Set/remove settings for debugging (flag, conditions, etc.).
 Modify the current values of the elements.
 Add/remove objects (DANGEROUS).
 Force the computation of equations.
 ...

 Interpretation and Question
 As an exercise tries to use the LSD debugger to track the instant
 in which the sales of the 9th firms changes slope, so as to
 clarify the motivations for the puzzle.
 After doing so, use the Analysis of Results module to present
 the solution in a fool-proof way

 
 Lesson 4
 '
 This lesson answers some of the questions posed by the model
 developed in the previous lesson. Moreover, shows how a model can
 easily be extended. The parameter Quality is replaced by a variable,
 represented by a random walk.
 The new model becomes a stochastic model, and its results can be
 tested running several simulations runs and comparing their results.
 &
 Marco Valente
 1
 $
 Analysing and extending a model
 %
 
Lesson 4
 '
 Questions:
 1. Why is the result like that? What is the relation between
 Quality and Sales?
 2. Why Sales9, that is, the variable Sales in the 9th firm first
 increases and then decreases?
 3. What is the effect of a different value for a?
 4. Are there limits to the values of a to obtain sensible results?
 5. What do you think happens to the sum of all Sales in the model?
 &
 
 2
 $
 Excercises
 %
 
Lesson 4
 '
 Question:
 1. Why is the result like that? What is the relation between Quality
 and Sales?
 Answer:
 Sales increases with the percentage of difference between Quality
 and AvQuality
 &
 
 3
 $
 Replicator Dynamics Model
 %
 
Lesson 4
 '
 Question:
 2. Why Sales9, that is, the variable Sales in the 9th firm first
 increases and then decreases?
 Answer:
 Quality’s are constant but Sales are not. Therefore,
 PN
 AvQualityt =
 i=1 
Salesi
 t−1×Qualityi
 PN
 i=1 
Salesi
 t−1
 Sales of the higher quality firms increase. Therefore, the Quality9 is
 before below the average, and after above average.
 &
 
 4
 $
 Replicator Dynamics Model
 changes, increasing since the
 %
 
Lesson4 5
 '
 &
 $
 %
 0 100 200 300 400
 14.5
 15.6216
 16.7433
 17.8649
 18.9865
 (13.0062)
 (72.8096)
 (132.613)
 (192.416)
 (252.22)
 Sales_1_9
 AvQuality_1
 Quality_1_9
 MarcoValente Universit`adell’Aquila
Lesson 4
 '
 Question:
 5. What do you think happens to the sum of all Sales in the model?
 Answer:
 Remain constant. The increment of one variable is identical to the
 decrement of the others. Try to introduce a variable summing up all
 Sales to prove it.
 &
 
 6
 $
 Replicator Dynamics Model
 %
 
Lesson 4
 '
 Let’s extend the model. Let’s assume that Quality is no longer a
 constant parameter, but a variable.
 Let’s assume that Quality changes as a Random Walk. A random
 walk is a variable that changes according to the following function:
 RWt =RWt−1+U(−k,+k)
 where U(−k,+k) is a random number chosen between −k and +k.
 &
 
 7
 $
 Extending the R.Dyn. Model
 %
 
Lesson 4
 '
 Random walks are frequently used random functions because they
 change slowly, at most k, but are impossible to predict where they
 end up (tech. they have infinite variance random variables). They
 look like many real economic series.
 11
 8
 6
 4
 2
 &
 
 0
 8
 $
 Extending the R.Dyn. Model
 Random Walk [−1,1]
 25
 50
 75
 100
 %
 
Lesson 4
 '
 Randomness cannot be generated by computers. To obviate to this
 problem there are programs that generate pseudo random numbers.
 That is, series of numbers that appear to come from a random event,
 though they are generated with rather sophisticated, but
 deterministic, processes.
 The best way to understand what pseudo random numbers are think
 of sequences of truely random numbers, for example obtained by
 counting the number of heads tossing a coin 100 times. Different
 sequences will have different values, but all of them will have common
 general properties: values between 0 and 100; mean about 50, etc.
 The values are naturally random, but they can be repeated exactly.
 Just take again the same sequence and you will obtain the same
 values.
 &
 
 9
 $
 Random events
 %
 
Lesson 4
 '
 The new equation for Quality is:
 EQUATION("Quality")
 /*
 Quality level, implemented as a Random Walk
 */
 v[0]=VL("Quality",1);
 v[1]=V("Max");
 v[2]=V("Min");
 v[3]=v[0]+UNIFORM(v[1],v[2]);
 RESULT(v[3] )
 &
 10
 $
 Extending the R.Dyn. model
 %
 
 
Lesson 4
 '
 Compile the model and make the following changes:
 • Double click on the label for Quality and then again on its label,
 until it allows to be transformed in a variable with 1 lag.
 • Add in Market the parameters Min and Max.
 • Initialize Min=-1 and Max=1.
 • Initialize Quality0 = 10 in all Firm’s.
 The model behaves “randomly”. But repeating a simulation, the
 model replicates exactly the same results. Not that random, after all.
 &
 
 11
 $
 Extending the R.Dyn. model
 %
 
Lesson 4
 '
 C++ offers several sequences of random numbers. Users can decide
 which sequence to use and obtain exactly the same results. This
 permits the replication of results, crucial for any scientific analysis. I
 can send to a colleague a model and a random sequence and he will
 observe the same results.
 In Lsd users decide which sequence to use in menu
 Model/Sim.Setting/Init. Seed. The name is due to the actual
 system used to generate random numbers. They are the results of a
 complicated (but deterministic) mathematical function generating
 the sequence of number. Given a seed, this function “grows” a
 sequence appearing as a random.
 Try using the same initialization of the model but different seeds.
 The results will differ.
 &
 
 12
 $
 Seed for the random generator
 %
 
Lesson 4
 '
 When using random models we have some parts of the model that
 depends from the model structure, and another part that depends on
 the randomness.
 We may ask if the results we obtain depend on the random part or
 depend on the structure of the model. For this we need to repeat the
 same simulation many times and seeing the frequency of a given
 results.
 Lsd offers this possibility by repeating many times a simulation run
 with identical initialization but different seeds, that is, different
 random sequences.
 &
 
 13
 $
 Testing against randomness
 %
 
Lesson 4
 '
 Let’s set our model to have all firms identical but one with a small
 advantage. We ask whether the advantage is enough to make this
 f
 irm win more frequently.
 • a=0.2, Min=-0.05 and Max=0.05.
 • All Sales0=100.
 • All Qualityi
 0=10 but the first Quality1
 0=10.5
 • Set in menu Run/Sim.Setting the values Num. of
 Simulations=100 and Num. Steps=500.
 • Use menu Run/Remove Plot Flags to avoid having 100 Run
 Time Plot windows.
 &
 
 14
 $
 Testing against randomness
 %
 
Lesson 4
 '
 Run the simulation. Now the system executes automatically the
 following steps:
 1. Set the seed to the Init. Seed.
 2. Runs the 500 steps of a simulation run with the current seed.
 3. Saves the result in a file with extension res and the seed value in
 the name.
 4. Reload the configuration.
 5. Changes the seed increasing the current seed of 1.
 6. Repeat from 2.
 Click in the Log window on the button Fast.
 &
 
 15
 $
 Running multiple simulations
 %
 
Lesson 4
 '
 At the end, we have 100 files containing each the history of the
 simulation with the seed indicated in the name. Moreover, we have a
 f
 ile, extension tot, containing the last value of each saved variable
 from each simulation. The tot file is not the history of a simulation,
 but permits to compare the final results from each simulation.
 Select all the Sales variables and click on Statistics. Nothing
 happens, but observe the Log window. We have the some descriptive
 statistics computed over the 100 values for each variable at the end of
 their simulation runs.
 The columns Min and Max show the minimum and maximum value
 for each variable. Clearly, every variable happened to win some runs.
 But the first one won more frequently, since its Average is much
 higher.
 &
 
 16
 $
 Running multiple simulations
 %
 