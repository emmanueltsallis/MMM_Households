# GEMINI.md

This file provides guidance to Gemini CLI (https://github.com/google-gemini/gemini-cli) when working with code in this repository.

## Initial instructions

Whenever I type "ss" followed by an optional number:
- "ss" - run `./lastshot` and display the latest screenshot
- "ss2" - run `./lastshot 2` and display the 2 latest screenshots  
- "ss3" - run `./lastshot 3` and display the 3 latest screenshots
- "ssN" (where N is any number) - run `./lastshot N` and display the N latest screenshots

Use the Read tool to display all screenshot files returned.

## Project Overview

The MMM_Households project is a Micro-Macro Multisectoral Model (ver. 4.0) - a dynamic, agent-based simulation model of a capitalist economy. The model combines theoretical foundations from Post-Keynesian, Kaleckian, and Evolutionary (Neo-Schumpeterian) approaches to investigate the dynamic properties of capitalist economies.

### Current Development Focus

**Household Disaggregation Project**: This model is transitioning from a class-based aggregated approach to a fully disaggregated household-based model. The original model used income classes to represent micro-level behavior at the meso-level (income classes aggregation), but the new approach models individual households as distinct agents with heterogeneous behaviors.

#### Key Transition Elements:
- **From**: `fun_classes.h` - Aggregated income class equations
- **To**: `fun_households.h` - Individual household agent equations  
- **Goal**: Replace class-level averages with individual household decision-making
- **Challenge**: Maintain economic realism while introducing behavioral heterogeneity
- **Status**: Equations are being converted and validated for economic consistency

## Core Architecture

### Model Structure
- **Agent-Based**: Households, firms, banks, government, and external sector as individual agents
- **Multisectoral**: Capital goods, intermediate goods, and consumption goods sectors
- **Dynamic**: Discrete time steps representing production periods (quarters)
- **Disequilibrium**: No equilibrium conditions imposed

### Key Components
1. **Households** (replacing income classes): Individual economic units making consumption, savings, and accumulation decisions. They are the main agents in the MMM-WEALTH model
2. **Firms**: Sector-specific entities handling production, investment, pricing, and R&D. They are the main agents in the original MMM model
3. **Banks**: Financial intermediaries managing loans and deposits
4. **Government**: Fiscal policy agent with taxation and spending
5. **External Sector**: Handles exports, imports, and exchange rates. In the Wealth-augmented MMM model, a financial sector is incorporated into the external sector

## Build System

### Dependencies
- C++ compiler (g++)
- Make build tool
- LSD simulation framework (expected at `C:/LSD`)
- R environment with libraries: `LSDinterface`, `LSDsensitivity`, `gplots`, `mFilter`

### Build Commands
```bash
# Compile the model
make

# Clean build files
make clean
```

## Running Simulations

### Execution
```bash
# Run a specific simulation scenario
./lsd.exe -f Sim_1.lsd

# Available scenarios: Baseline.lsd, Sim_1.lsd through Sim_6.lsd
```

### Analysis
```bash
# Run R analysis scripts (example)
Rscript R/mm_global_analysis.R ./Results_folder Sim_prefix
```

## Code Organization

### Core Files
- `fun_micro_macro.cpp`: Main entry point including all model logic
- `fun_*.h`: Modular header files for different economic functions
- `fun_init_2.h`: Model initialization and calibration procedures (other init files are legacy)
- `fun_support.h`: Support functions (`ROUND`, `LAG_SUM`, `LAG_AVE`, `LAG_GROWTH`)

### Analysis Files (R/)
- `mm_*_analysis.R`: Macroeconomic, financial, and sectoral analysis
- `box-plots*.R`, `time-plots*.R`: Visualization scripts
- `support-functions.R`: Helper functions for analysis
- `*SA.R`: Sensitivity analysis scripts

### Configuration Files
- `*.lsd`: Simulation scenarios with different policy combinations (these should not edited in code, but in the LSD interface)
- `elements.txt`: Complete list of variables and parameters
- `description.txt`: Comprehensive model documentation

## Naming Conventions

### Variables and Objects
- **OBJECTS**: All uppercase (e.g., `COUNTRY`, `FIRMS`, `BANKS`)
- **Variables**: Initial capital letter (e.g., `Country_GDP`, `Firm_Profits`)
- **parameters**: All lowercase (e.g., `sector_initial_price`)

### Prefixes
- `Country_`: Country-level variables
- `Sector_`: Sector-level variables  
- `Firm_`: Firm-level variables
- `Class_`: Income class variables (to be replaced by `Household_`)
- `Household_`: Household-level variables
- `Bank_`: Bank-level variables
- `Government_`: Government variables
- `Financial_Sector_`: Financial sector aggregates

## Model Control Parameters

### Policy Switches
- `switch_household_tax_structure`: Determines the tax structure for households
- `switch_monetary_policy`: Monetary policy rules (0=Fixed, 1=Taylor, 2=Smithin, 3=Pasinetti, 4=Kansas City)
- `switch_entry`: Firm entry/exit dynamics (0=No entry, 1=Entry allowed)
- `switch_extra_imports`: Import behavior for unmet demand
- `switch_interest_payment`: Interest rate structure (0=Fixed, 1=Flexible)

### Timing Parameters
- `begin_*`: Define when specific policies activate (-1 = never activate)
- `annual_frequency`: Frequency of annual decisions
- `sector_investment_frequency`: Investment decision frequency
- `sector_price_frequency`: Price adjustment frequency

## Initialization System

The model uses automatic initialization and calibration through the `Initialization_2` variable. Key principles:
1. **Heterogeneity for households**: Although all households start with zero income, they inherit wealth and have different preference choices
2. **Homogeneity for firms**: All firms start identically within sectors
3. **Stock-Flow Consistency**: All initial ratios are coherent
4. **Steady State**: Economy begins in non-growth steady state
5. **Endogenous Dynamics**: Growth and cycles emerge during simulation

## Sample Configurations

- **Sim_1**: Taylor Rule + Flexible Surplus Target + Flexible Exchange Rate + Credit Rationing
- **Sim_2**: Taylor Rule + Flexible Surplus Target + Flexible Exchange Rate + No Credit Rationing
- **Sim_3**: Taylor Rule + Flexible Surplus Target + Fixed Exchange Rate + No Credit Rationing
- **Sim_4**: Fixed Interest + Flexible Surplus Target + Fixed Exchange Rate + No Credit Rationing
- **Sim_5**: Fixed Interest + Unconstrained Fiscal + Simple Government + Fixed Exchange Rate + No Credit Rationing

## Global Pointers

The model uses global pointers for key objects:
- `country`: Main country object
- `consumption`, `capital`, `input`: Sector objects
- `government`, `financial`, `external`: Policy objects
- `centralbank`: Central bank object
- `households`: Household disaggregation (replaces `classes`)

## LSD Framework Overview

### What is LSD?
LSD (Laboratory for Simulation Development) is a C++11-based simulation platform specifically designed for agent-based modeling in social sciences. It provides:
- **Split Architecture**: Separate equation code (.cpp) from model configuration (.lsd)
- **Automatic Compilation**: LMM (LSD Model Manager) handles compilation and execution
- **Graphical Interface**: Complete GUI for model configuration, execution, and analysis
- **Agent-Based Focus**: Hierarchical object structure optimized for multi-agent simulations

### Core LSD Concepts

#### Model Structure
- **Objects**: Hierarchical containers representing economic entities (e.g., `COUNTRY`, `FIRMS`, `HOUSEHOLDS`)
- **Variables**: Computed values updated each time step using equations
- **Parameters**: Fixed values (unless modified by equations) used in calculations
- **Equations**: C++ code blocks that compute variable values at each time step

#### Time Management
- Simulation runs in discrete time steps (t = 1, 2, 3, ...)
- Each variable computed once per time step automatically
- Lagged values automatically saved based on variable definitions
- Use `fmod((double) t, frequency)` for periodic adjustments

#### Object Hierarchy and Search
- Variables search follows hierarchy: same object → descendants → parent → grandparent
- Global pointers (`country`, `consumption`, etc.) provide direct access to key objects
- Object instances automatically managed by LSD framework
- Use `CYCLE(cur, "ObjectName")` to iterate through all instances

### Essential LSD Macros

#### Basic Equation Structure
```cpp
EQUATION("VariableName")
/*
Variable description and computation logic
*/
v[0] = V("SomeParameter");           // Get current value
v[1] = VL("SomeVariable", 1);        // Get lagged value (t-1)
v[2] = VS(object, "SomeValue");      // Get value from specific object
RESULT(v[0] + v[1] + v[2])           // Return computed value
```

#### Core Macros
- **Equation Definition**: `EQUATION("VarName")`, `RESULT(value)`
- **Variable Access**: `V("VarName")`, `VL("VarName", lag)`, `VS(object, "VarName")`
- **Current State**: `CURRENT` (current value of variable being computed)
- **Aggregation**: `SUM("VarName")`, `SUMS(object, "VarName")`
- **Object Operations**: `SEARCH("ObjectName")`, `ADDOBJ("ObjectName")`, `DELETE(object)`
- **Data Modification**: `WRITE("VarName", value)`, `WRITES(object, "VarName", value)`
- **Iteration**: `CYCLE(cur, "ObjectName")`, `CYCLE_SAFE(cur, "ObjectName")`

#### Support Functions
- **LAG Operations**: `LAG_SUM()`, `LAG_AVE()`, `LAG_GROWTH()` (defined in `fun_support.h`)
- **Utility**: `ROUND()`, `MAX()`, `MIN()`, `RND` (random 0-1)
- **Time**: `t` (current time step), `fmod()` for periodic checks

### Development Workflow

#### 1. Model Creation Process
1. **Design**: Define entities, variables, and relationships on paper
2. **LMM Setup**: Use `File > New Model` to create model structure
3. **Equation Writing**: Write equations in LMM using `Model > Show Equations`
4. **Compilation**: LMM automatically compiles when running `Model > Run`
5. **Configuration**: Use LSD Browser to define object structure and initial values
6. **Simulation**: Run and analyze results using built-in tools

#### 2. Common Development Tasks
- **Add Variables**: Write equation in LMM, add to model structure in LSD Browser
- **Debugging**: Use LSD debugger to trace equation execution step-by-step
- **Parameter Tuning**: Modify values in LSD Browser without recompilation
- **Analysis**: Use built-in Analysis of Results or export to R

### Error Handling and Debugging

#### Common Errors
- **Compilation Errors**: Missing semicolons, undefined variables, syntax errors
- **Runtime Errors**: Missing equations, misspelled variable names, division by zero
- **Deadlock Errors**: Circular dependencies between variables (use lagged values)
- **Search Failures**: Variables not found in object hierarchy

#### Debugging Tools
- **LSD Debugger**: Step-by-step equation execution with variable inspection
- **DEBUG/DEBUG_AT Macros**: Log variable calculations to trace execution
- **INTERACT Macro**: Pause simulation for manual inspection
- **Log Window**: Shows detailed error messages and suggestions

### File Structure and Organization

#### Key Files
- **Equation File** (`fun_*.h`): Contains all variable equations
- **Configuration Files** (`*.lsd`): Model structure and initialization data
- **Main File** (`fun_micro_macro.cpp`): Includes all equation files
- **Support Functions** (`fun_support.h`): Custom mathematical functions

#### Best Practices
- **One equation per variable**: Each `EQUATION("VarName")` should be independent
- **Use temporary variables**: `v[0]` to `v[999]` for intermediate calculations
- **Comment extensively**: Document complex equations with clear descriptions
- **Modular design**: Split equations into logical files (e.g., `fun_households.h`)

### Integration with External Tools

#### R Integration
- **LSDinterface**: Direct access to LSD results in R without format conversion
- **LSDsensitivity**: Sensitivity analysis tools (Morris Elementary Effects, Sobol)
- **Automatic Export**: Built-in export to various formats (CSV, R, Stata)

#### Model Documentation
- **Automatic Reports**: HTML and LaTeX documentation generation
- **Cross-referenced**: Hyperlinked reports showing variable relationships
- **Model Structure**: Graphical representation of object hierarchy

### LSD Documentation Files

The `LSD_documentation/` folder contains comprehensive documentation for the LSD framework:

#### Core Documentation
- `lsd_macros.md`: Complete LSD macro documentation and reference guide (most important)
- `lsd_quick_help.md`: Quick reference guide for common LSD operations
- `lsd_glossary.md`: Glossary of LSD terms and concepts
- `lsd_faq.md`: Frequently asked questions and troubleshooting
- `lsd_changelog.md`: Version history and change log

#### Tutorial Series
- `lsd_tutorial_1.md`: Basic LSD introduction and setup
- `lsd_tutorial_2.md`: Intermediate LSD modeling concepts
- `lsd_tutorial_3.md`: Advanced LSD features and techniques

#### Course Materials
- `lsd_course1_intro.md`: Introduction to agent-based modeling with LSD
- `lsd_course2_linear_model.md`: Linear models and basic dynamics
- `lsd_course3_logistic_chaotic_model.md`: Nonlinear and chaotic systems
- `lsd_course4_random_walks.md`: Stochastic processes and random walks
- `lsd_course5_replicator_dynamics.md`: Evolutionary dynamics and selection
- `lsd_course6_network_externalities.md`: Network effects and externalities
- `lsd_course7_fashion_waves.md`: Social dynamics and fashion cycles
- `lsd_course8_consumers_model.md`: Consumer behavior and market dynamics

## LSD Development Rules and Best Practices

### 1. Macro Documentation Awareness

- Regularly check the file `lsd_macros.md` for relevant macros and functions that may improve:
  a. Agent behavior definitions.
  b. Economic mechanism implementations.
  c. Time control, randomization, and simulation logic.
- Revisit `lsd_macros.md` especially when:
  a. Creating or modifying agent behavior or decision structures.
  b. Implementing or adjusting stochastic dynamics or time loops.
  c. Debugging macro-related compilation errors.

### 2. Circular Dependency Checks

- After every code edit, automatically check for circular dependencies in:
  - Variable and equation definitions.
  - The execution order of simulation blocks.
- If a circular dependency is detected:
  - Identify the dependency loop and affected variables.
  - Suggest a resolution, such as using `LAG`, `LAG_AVE`, or reordering computations.

### 3. Default Coding Behavior

- Prioritize modularity: differentiate economic logic from simulation mechanics.
- Prefer clarity and maintainability over compact or cryptic optimizations.
- Any new parameter or macro must include an inline comment explaining its purpose.
- New variables must come with a brief text as annotation under the EQUATION("Variable") term.

### 4. LSD Macro Syntax Conventions & Linter False Positives

The LSD framework uses macros that deviate from standard C++ syntax. Standard C++ linters may report false errors. Follow these rules:

- **Implicit `v[]` array**: Within `EQUATION` blocks, `v[index]` is implicitly declared. Ignore linter errors like "identifier 'v' is undefined" and **do not** declare it manually.
- **Implicit `cur` object**: In `CYCLE(...)` or `SEARCH(...)`, `cur` is also implicit. Ignore linter complaints and **do not** declare `object *cur;`.
- **Macro structure**: `EQUATION { ... } RESULT(...)` is valid LSD syntax. Disregard errors such as "expected declaration" or "invalid type specifier" after these macros.

## Model Structure

### Code Organization and File Structure

#### Core Files
- `fun_micro_macro.cpp`: Main entry point including all model logic
- `fun_*.h`: Modular header files for different economic functions
- `fun_init_2.h`: Model initialization and calibration procedures (other init files are legacy)
- `fun_support.h`: Support functions (`ROUND`, `LAG_SUM`, `LAG_AVE`, `LAG_GROWTH`)

#### Analysis Files (R/)
- `mm_*_analysis.R`: Macroeconomic, financial, and sectoral analysis
- `box-plots*.R`, `time-plots*.R`: Visualization scripts
- `support-functions.R`: Helper functions for analysis
- `*SA.R`: Sensitivity analysis scripts

#### Configuration Files
- `*.lsd`: Simulation scenarios with different policy combinations (these should not edited in code, but in the LSD interface)
- `elements.txt`: Complete list of variables and parameters
- `description.txt`: Comprehensive model documentation

## Development Guidelines

### Best Practices

#### 1. Macro Documentation Awareness
- Regularly check the file `lsd_macros.md` for relevant macros and functions
- Revisit especially when creating agent behavior, implementing stochastic dynamics, or debugging macro-related errors

#### 2. Circular Dependency Checks
- After every code edit, check for circular dependencies in variable and equation definitions
- Use `LAG`, `LAG_AVE`, or reorder computations to resolve dependency loops

#### 3. Default Coding Behavior
- Prioritize modularity: differentiate economic logic from simulation mechanics
- Prefer clarity and maintainability over compact optimizations
- Any new parameter or macro must include an inline comment explaining its purpose
- New variables must include brief annotation under the `EQUATION("Variable")` term

#### 4. Development Rules
- All equation logic is contained in modular `.h` files
- The LSD framework handles object creation and variable management
- Support functions in `fun_support.h` provide common mathematical operations
- The code includes extensive line-by-line documentation for non-trivial variables
- Use LMM (LSD Model Manager) for integrated development environment
- Model configurations (.lsd files) should never be edited manually
- Always use `EQUATION_DUMMY` for variables computed elsewhere but needed in structure

## Gemini Response Guidelines

- **Avoid excessive flattery**: Don't over-praise user decisions or approaches
- **Apply critical thinking**: Provide what the user NEEDS to know, not what they WANT to hear
- **Identify unknown unknowns**: Actively search for and explain potential issues the user hasn't considered
- **Prioritize correctness**: Economic realism and mathematical consistency over convenience
- **Provide examples**: Use examples to illustrate points

### ONLY WHEN NECESSARY:
- **Present critical analysis**: Highlight gaps, inconsistencies, or overlooked aspects in the user's approach
- **Focus on constructive criticism**: Point out potential problems clearly and offer solutions
- **Challenge assumptions**: Question design choices when they may lead to issues
- **Provide alternative solutions**: Offer different approaches or considerations when appropriate. Use Quadrant Thinking Mode.
- **Provide references**: Provide references to relevant literature or documentation

## Quadrant Thinking Mode:
A structured, multi-perspective solution generation mode to enhance robustness, creativity, and critical validation.

### Task: Spin out 4 instances of the solution/problem to test its robustness:

### Activation: Only activate when explicitly requested by the user. Default solution behavior remains standard unless the user prompts:

### Instances
1. "The Blind" (Asynchronous, fully independent, Double Blind, Alternative):
- Create a solution that is completely unaware of the user’s approach (if any) and all other solutions above.
This version acts as an external check, simulating a fresh mind tackling the problem from scratch.
- Goal: Provide a robustness control — if this solution resembles others, it confirms reliability.
- Action: Generate first while "cognitively fresh" (i.e. not thinking about the user's approach or the other solutions)

2. "The Outsider" (Cross-Framework Alternative):
- After the first instance, propose a new solution using a different framework or paradigm.
This explores radically different perspectives to the problem.
- Goal: Test whether a totally different approach might be simpler, more efficient, or more insightful.
- Action: Leverage diverse training patterns early

3. "The Echo" (Asynchronous, User-Aware, Solution-Blind Alternative):
- Think of a solution that knows the user's original idea (if any), but is unaware of the solutions in instances 1 and 2. Its role is to serve as a blind robustness test of the other subagents’ ideas.
- Goal: See if another reasonable solution arrives at similar conclusions independently.
- Action: Test convergence with partial context

4. "The Sibling" (In-Framework Alternative):
- Propose a different solution from the user's idea, but still within the same logic, model, or framework the user is using.
This tests creativity without leaving the user’s current context.
- Goal: Show there's more than one way to solve a problem in the same paradigm.
- Action: Refine within established parameters last

### Explicit Cognitive Barriers

- Memory Partitioning: Each instance should explicitly "forget" previous solutions
- Perspective Prompting: Use different reasoning styles (analytical, intuitive, systematic, creative)

### Quality Controls

- Convergence Scoring: Measure how similar solutions are (high = robust, low = unstable problem)
- Risk Assessment: What could go wrong with each approach?

## Global Git Ignore Setup

### Configuration
```bash
git config --global core.excludesfile ~/.gitignore_global
```

### Hidden Files
```gitignore
# Personal development files
.env
.env.local
.cursor/
GEMINI.md
CLAUDE.md
lastshot
screenshots/
```

### Benefits
- **Invisible to Git**: Personal files hidden without repository traces
- **Clean repository**: Professional appearance on GitHub
- **Universal**: Applies to all repositories automatically

### Repository .gitignore
Minimal since personal files handled globally:
```gitignore
# This file is intentionally minimal since personal files are handled by global Git ignore
```

**Note**: Ideal for personal projects requiring maximum privacy while maintaining functionality.