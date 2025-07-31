# Economic Analysis of Household Disaggregation in the MMM Model: From Class-Based Aggregates to Individual Agent Dynamics

## Executive Summary

This document provides a comprehensive economic analysis of the transformation from a class-based aggregated model to a fully disaggregated household-based agent system in the Micro-Macro Multisectoral (MMM) model. The disaggregation represents a fundamental methodological advancement from representative agent assumptions to genuine heterogeneous agent modeling, with profound implications for understanding distributional dynamics, consumption behavior, and macro-financial linkages in Post-Keynesian economic modeling.

## 1. Theoretical Foundation and Economic Motivation

### 1.1 The Aggregation Problem in Macroeconomic Modeling

The transformation addresses the classical **aggregation problem** in macroeconomic modeling identified by Kirman (1992) and others. Traditional class-based approaches, while computationally efficient, impose restrictive assumptions:

- **Representative Agent Fallacy**: Classes assumed identical behavior within income brackets
- **Distributional Blindness**: Within-class inequality dynamics ignored
- **Static Heterogeneity**: Fixed class boundaries prevent mobility analysis
- **Behavioral Homogeneity**: Identical preferences and constraints within classes

### 1.2 Post-Keynesian Justification for Disaggregation

The disaggregation aligns with core Post-Keynesian principles:

**Methodological Individualism vs. Ontological Individualism**: While maintaining that aggregate phenomena cannot be reduced to individual choices (rejecting neoclassical ontological individualism), the model embraces methodological individualism by modeling distinct household decision-making processes.

**Distributional Considerations**: Following Kalecki's emphasis on class conflict and Minsky's financial instability hypothesis, the model now captures:
- Income and wealth distribution dynamics
- Heterogeneous financial fragility across households
- Differential consumption patterns by income position

**Endogenous Instability**: Household heterogeneity creates multiple sources of endogenous instability beyond firm investment decisions, including:
- Consumption volatility from heterogeneous propensities
- Financial fragility cascades across household wealth distribution
- Employment status transitions affecting aggregate demand

## 2. Structural Transformation Analysis

### 2.1 From Classes to Households: Architectural Changes

#### Old Structure: Class-Based System (`fun_classes.h`)
```
CLASSES (3-5 income classes)
├── Class_Nominal_Disposable_Income
├── Class_Propensity_to_Spend (fixed parameter)
├── Class_Imports_Share (fixed parameter)
├── Class_Real_Desired_Consumption
└── Class_Financial_Behavior (uniform within class)
```

#### New Structure: Household-Based System (`fun_households.h`)
```
HOUSEHOLDS (N individual agents)
├── Household_Employment_Status (Markov process)
├── Household_Wage_Income (skill × sector_wage)
├── Household_Profit_Income (q-exponential distribution)
├── Household_Propensity_to_Spend (income-dependent sigmoid)
├── Household_Imports_Share (hyperbolic relative income function)
└── Household_Financial_Behavior (heterogeneous parameters)
```

### 2.2 Key Economic Transformations

#### Consumption Function Evolution

**Old Approach** (Class-based):
```
Class_Real_Consumption = Class_Avg_Income × class_propensity_to_spend + Autonomous_Consumption
```

**New Approach** (Household-based):
```
Household_Propensity_to_Spend = (1-n) × (1/(1+exp(k×(relative_income-x₀)))) + n
Household_Real_Consumption = Income × Propensity × (1-Import_Share) + Autonomous_Consumption
```

This transformation introduces **Duesenberry's Relative Income Hypothesis** through the sigmoid function, where:
- `k` = propensity steepness (how quickly propensity changes with income)
- `x₀` = midpoint (income level where propensity = 0.5)  
- `n` = minimum propensity bound
- `relative_income` = household_income/median_income

**Economic Significance**: The consumption function now exhibits **"keeping up with the Joneses"** effects, where consumption propensity depends on relative rather than absolute income position, consistent with empirical evidence on consumption inequality.

#### Import Behavior Sophistication

**Old Approach**: Fixed import propensity by class
```
Class_Imports_Share = class_propensity_import × (price_ratio)^elasticity
```

**New Approach**: Dynamic relative income-based import behavior
```
Import_Elasticity = base_factor / relative_income_ratio
Import_Share = propensity_import × (price_ratio)^Import_Elasticity
```

**Economic Insight**: Higher-income households become less price-sensitive in import decisions (lower elasticity), reflecting empirical patterns where wealthy households maintain import consumption despite price changes.

## 3. Heterogeneity Implementation: Sources and Mechanisms

### 3.1 Multi-Dimensional Heterogeneity Architecture

The disaggregation introduces heterogeneity across multiple dimensions:

#### A. **Earning Capacity Heterogeneity**
- **Skill Distribution**: Log-normal distribution `lnorm(μ, σ)` with E[skill] = 1
- **Employment Status**: Markov process with pro-cyclical hiring/counter-cyclical firing
- **Sectoral Allocation**: Probabilistic assignment based on relative employment demand

#### B. **Preference Heterogeneity**
- **Autonomous Consumption Adjustment**: `N(household_avg_baseline, 0.20σ)`
- **Import Propensity**: `N(economy_avg_import_propensity, 0.20σ)`
- **Liquidity Preference Adjustment**: `N(baseline, 0.60σ)`
- **Debt Rate Adjustment**: `N(baseline, 0.40σ)`

#### C. **Wealth Distribution Heterogeneity**
- **Profit Participation**: Only fraction `λ` of households receive profits
- **Profit Shares**: Q-exponential distribution `qexp(q, λ)` for participants
- **Initial Wealth**: Zero initial debt, differentiated by employment status

### 3.2 Persistence vs. Adaptation in Behavioral Parameters

The model elegantly balances **persistent heterogeneity** with **adaptive behavior**:

**Persistent Elements** (set at initialization):
- Individual skill levels (`household_skill`)
- Behavioral adjustment sensitivities
- Profit participation status and shares

**Adaptive Elements** (evolve during simulation):
- Employment status (Markov transitions)
- Liquidity preference (responds to income growth and debt levels)
- Maximum debt rates (adjust to income changes)
- Consumption propensities (via relative income effects)

**Economic Rationale**: This structure captures both **deep parameters** (personality, skills) that remain stable over time and **behavioral responses** that adapt to changing economic conditions.

## 4. Aggregation and Macro Consistency

### 4.1 Bottom-Up Aggregation Mechanisms

The model maintains macroeconomic consistency through systematic aggregation using LSD's `SUM()` and `SUMS()` functions:

#### Consumption Aggregation
```cpp
Country_Domestic_Consumption_Demand = SUM("Household_Real_Domestic_Consumption_Demand")
```

#### Financial Aggregation
```cpp
Country_Total_Household_Demand_Loans = SUM("Household_Demand_Loans")
Country_Total_Household_Stock_Deposits = SUM("Household_Stock_Deposits")
```

#### Income Distribution Aggregation
```cpp
Household_Income_Share = Household_Income / SUMS(PARENT, "Household_Nominal_Disposable_Income")
```

### 4.2 Stock-Flow Consistency Preservation

The disaggregation maintains strict **stock-flow consistency** principles:

**Balance Sheets**: Every household maintains `Household_Net_Wealth = Deposits - Loans`

**Flow Consistency**: `Household_Stock_Deposits[t] = Available_Deposits + Retained_Deposits + Redistributed_Profits`

**Sectoral Balances**: Household sector aggregates must equal corresponding class-based aggregates in equilibrium, ensuring model validation.

### 4.3 Financial Circuit Closure

The model ensures **monetary circuit closure** through:

1. **Credit Creation**: Banks create deposits when extending loans to households
2. **Deposit Redistribution**: Firm exit/entry creates deposit flows between households
3. **Profit Distribution**: Distributed profits flow according to household profit shares
4. **Government Transfers**: Unemployment benefits distributed to unemployed households

## 5. Employment and Labor Market Dynamics

### 5.1 Employment Status Determination

The model replaces wage shares by income class with individual employment dynamics:

**Markov Employment Process**:
- Unemployment Rate = 1 - (Total_Employment_Demand / Total_Population)
- Hiring Probability = f(aggregate employment rate) [pro-cyclical]
- Firing Probability = f(aggregate unemployment rate) [counter-cyclical]

**Sectoral Assignment**: Employed households allocated across sectors based on relative employment demand.

**Wage Determination**: `Household_Wage = Sector_Wage × household_skill`

### 5.2 Economic Implications of Employment Disaggregation

**Cyclical Amplification**: Individual employment transitions create stronger cyclical dynamics than aggregate wage bill changes.

**Distributional Effects**: Employment risk heterogeneity affects consumption and saving decisions differently across the income distribution.

**Precautionary Behavior**: Unemployed households face directly reduced income rather than averaged class effects, intensifying precautionary saving motives.

## 6. Financial Behavior and Credit Market Dynamics

### 6.1 Household Credit Demand

The disaggregation introduces sophisticated household credit behavior:

#### Credit Rationing Hierarchy
```cpp
// Households receive priority in credit allocation
v[12] = SUM("Household_Demand_Loans");  // Total household demand
v[14] = Bank_Market_Share × v[12];      // Bank-specific household allocation
// Firms receive remaining credit proportionally
```

**Economic Justification**: Households face less credit rationing than firms, reflecting empirical patterns in banking where consumer lending often receives priority due to lower default rates and regulatory requirements.

#### Heterogeneous Debt Capacity
```cpp
Household_Max_Loans = Max_Debt_Rate × (Deposits + Avg_Income) - Current_Loans
```

**Dynamic Debt Tolerance**: Maximum debt rates evolve based on income growth, following Moreira (2010):
- Rising income → increased debt tolerance
- Falling income → reduced debt tolerance

### 6.2 Liquidity Preference Heterogeneity

Each household maintains individual liquidity preferences that adapt to:
- **Income volatility**: Higher income growth volatility → higher liquidity preference
- **Debt burden**: Higher debt levels → increased precautionary demand for liquidity
- **Persistent individual differences**: Capturing behavioral heterogeneity in risk aversion

## 7. Distributional Dynamics and Inequality

### 7.1 Endogenous Inequality Generation

The disaggregation enables analysis of endogenous inequality through:

#### Income Distribution Evolution
- **Skill Premium Effects**: Productivity differentials across households
- **Employment Status Dynamics**: Unemployment risk heterogeneity
- **Profit Participation**: Concentrated profit receipts among subset of households

#### Wealth Distribution Dynamics
- **Saving Rate Heterogeneity**: Via income-dependent consumption propensities
- **Financial Return Differentials**: Risk premiums on household loans vary by debt status
- **Credit Access Differentials**: Debt capacity varies by income and wealth position

### 7.2 Inequality Measurement Implementation

The model implements multiple inequality measures:

**Income Shares**: `Household_Income_Share` for individual positions in distribution
**Wealth Shares**: Separate calculations for positive net wealth (`Household_Wealth_Share`) and debt positions (`Household_Debt_Share`)
**Conditional Aggregation**: `SUM_CND()` functions enable percentile and quintile analysis

## 8. Policy Analysis Capabilities Enhanced

### 8.1 Distributional Impact Analysis

The disaggregation enables sophisticated policy analysis:

#### Tax Policy Analysis
Multiple tax structure options (`switch_household_tax_structure`):
- Wage-only taxation
- Profit-only taxation  
- Comprehensive income taxation
- Wealth taxation capabilities

**Distributional Incidence**: Individual household tax burdens calculable, enabling analysis of tax progressivity and distributional effects.

#### Transfer Policy Analysis
- **Unemployment Benefits**: Targeted to unemployed households specifically
- **Universal Basic Income**: Implementable as uniform transfer across all households
- **Means-Tested Transfers**: Conditional transfers based on income thresholds

### 8.2 Monetary Policy Transmission

Disaggregation improves monetary policy transmission analysis:

#### Interest Rate Heterogeneity
```cpp
Household_Interest_Rate = (1 + Debt_Rate × Risk_Premium) × Base_Rate
```

**Heterogeneous Transmission**: Different households face different borrowing costs based on financial fragility, creating distributional effects of monetary policy.

#### Credit Channel Analysis
Individual household credit constraints enable analysis of:
- **Bank lending channel**: Via heterogeneous credit rationing
- **Balance sheet channel**: Via household debt capacity constraints
- **Asset price channel**: Via household wealth effects (when asset markets included)

## 9. Calibration and Empirical Validation

### 9.1 Parameter Calibration Strategy

The disaggregation requires careful calibration to match empirical distributions:

#### Skill Distribution Calibration
```cpp
household_skill_mean = -0.5 × (household_skill_stddev)²  // Ensures E[skill] = 1
```

#### Profit Distribution Calibration
- **Participation Rate** (`household_profit_participation_rate`): Typically 5-20% of households
- **Q-exponential Parameters**: Calibrated to match empirical wealth concentration
- **Normalization**: Profit shares sum to unity across participating households

### 9.2 Validation Against Stylized Facts

The model can be validated against key empirical regularities:

**Consumption Function**: 
- Higher consumption propensity for lower-income households
- Relative income effects in consumption decisions
- Import elasticity variation by income level

**Employment Dynamics**:
- Duration dependence in unemployment spells
- Sectoral mobility patterns
- Wage-skill correlations

**Financial Behavior**:
- Debt-to-income ratio variations across income distribution
- Liquidity holding patterns by income and wealth position
- Credit constraint patterns

## 10. Computational and Methodological Considerations

### 10.1 Computational Complexity

The disaggregation significantly increases computational requirements:

**Scaling**: Computational time scales approximately O(N) with household number
**Memory**: Individual household state variables require substantial memory allocation
**Convergence**: More complex dynamics may affect model convergence properties

### 10.2 LSD Framework Advantages

The LSD framework provides essential capabilities for disaggregation:

**Automatic Aggregation**: Built-in `SUM()`, `SUMS()`, `COUNT()` functions
**Object Management**: Automatic creation/deletion of loan objects for each household
**Hierarchical Structure**: Natural parent-child relationships for aggregation
**Lag Management**: Automatic handling of lagged variables for each household

## 11. Next Steps: Integrating Wealth Taxation and Evasion into the Disaggregated Model

The successful implementation of wealth taxation and capital flight dynamics at the aggregate class level in `fun_classes_wealth.h` provides a clear and validated blueprint for the next major development phase: transposing these mechanisms to the disaggregated household level in `fun_households.h`.

This transition will replace class-level averages and distributional assumptions (e.g., Pareto) with direct, heterogeneous agent behavior, capturing the micro-foundations of tax compliance and wealth mobility with greater precision.

### 11.1 Transposition Plan

The core objective is to adapt the logic from `fun_classes_wealth.h` to `fun_households.h`, moving from class-wide parameters to individual household attributes.

| Original `fun_classes_wealth.h` Logic | Target `fun_households.h` Implementation | Key Adaptation Challenge |
| :--- | :--- | :--- |
| **`Class_Taxpayer_Proportion`** | **`Household_Is_Taxpayer`** (Dummy Variable) | Replace statistical estimation (Pareto assumption) with a direct comparison: `Household_Stock_Deposits > wealth_tax_threshold`. This eliminates the need for intra-class distribution assumptions. |
| **`Class_Potential_Wealth_Tax`** | **`Household_Potential_Wealth_Tax`** | Direct calculation for each liable household: `(Household_Stock_Deposits - wealth_tax_threshold) * wealth_tax_rate`. |
| **`Class_Payoff_*` Equations** | **`Household_Payoff_*` Equations** | Payoff calculations will now be based on each household's individual state variables (domestic/external wealth, expected audit rate), rather than class averages. |
| **`class_propensity_to_evade`** (Parameter) | **`household_propensity_to_evade`** (Variable) | This can be initialized as a heterogeneous parameter and evolved over time based on the household's past success or failure with evasion, creating an adaptive learning mechanism. |
| **`Class_Evasion_Rate`** | **`Household_Evasion_Decision`** (Dummy Variable) | The evasion rate (a proportion) becomes a discrete choice for each household. The decision can be modeled probabilistically based on the ratio of `Payoff_Evasion` to `Payoff_Comply`, triggering a 0 or 1 outcome. |
| **`Class_Capital_Flight`** | **`Household_Capital_Flight`** | For evading households, this will be the amount of wealth they move abroad, calculated as `Household_Stock_Deposits * evasion_decision_outcome`. |
| **`Class_Wealth_Penalties`** | **`Household_Wealth_Penalties`** | Penalties will be applied individually to households whose capital flight is detected probabilistically (`RND < Government_Audit_Rate`). |
| **`Class_External_Stock_Deposits`** | **`Household_External_Stock_Deposits`** | Each household will now have its own external account, which accumulates based on individual capital flight, repatriation decisions, foreign interest rates, and exchange rate changes. |

### 11.2 Expected Outcomes and Research Opportunities

This adaptation will enable a more granular and realistic analysis of:
- **Distributional Impact of Wealth Taxes**: Directly observe which households are most affected and how their behavior changes.
- **Micro-Foundations of Capital Flight**: Identify the specific characteristics (e.g., wealth level, risk aversion) of households most likely to evade taxes.
- **Policy Effectiveness**: Test how different audit rates, penalty schemes, and tax thresholds impact compliance across the entire household distribution.
- **Emergent Inequality**: Analyze how tax evasion and capital mobility, as heterogeneous behaviors, shape the evolution of wealth inequality from the bottom up.

This step will complete the primary goal of the household disaggregation project, creating a powerful tool for analyzing the complex interplay between microeconomic behavior and macroeconomic outcomes.

## 12. Conclusions

### 12.1 Methodological Significance

The transformation from class-based to household-based modeling represents a significant methodological advancement:

**Theoretical Coherence**: Maintains Post-Keynesian macro foundations while incorporating microeconomic heterogeneity
**Empirical Realism**: Enables realistic modeling of distributional dynamics and inequality evolution
**Policy Relevance**: Provides detailed analysis of policy distributional impacts

### 12.2 Economic Insights

The disaggregation reveals important economic insights:

**Emergent Macroeconomic Dynamics**: Aggregate behavior emerges from heterogeneous individual decisions rather than being imposed through representative agents
**Distributional Feedback Effects**: Income and wealth distribution changes affect aggregate consumption and financial stability
**Financial Fragility Heterogeneity**: Individual household financial conditions create complex systemic risk patterns

### 12.3 Model Validation

The successful implementation demonstrates:
- **Stock-flow consistency** maintained despite increased complexity
- **Macroeconomic coherence** preserved through careful aggregation mechanisms  
- **Computational feasibility** achieved through efficient LSD implementation

The household disaggregation represents a successful synthesis of Post-Keynesian macroeconomic theory with modern agent-based modeling techniques, providing a powerful framework for analyzing distributional dynamics in capitalist economies.

---

**Technical Implementation Note**: The complete transformation required systematic replacement of approximately 50 class-based equations with corresponding household-level equations, modification of initialization procedures to create heterogeneous household populations, and implementation of comprehensive aggregation mechanisms to maintain macroeconomic consistency. The result is a theoretically coherent, empirically realistic, and computationally efficient model suitable for advanced economic analysis.