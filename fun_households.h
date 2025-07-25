/***** HOUSEHOLD MODELING *****/

EQUATION("Household_Avg_Real_Income")
RESULT(LAG_AVE(p, "Household_Real_Disposable_Income", V("annual_frequency"),1))

EQUATION("Household_Avg_Nominal_Income")
RESULT(LAG_AVE(p, "Household_Nominal_Disposable_Income", V("annual_frequency"),1))


EQUATION("Household_Real_Autonomous_Consumption")
/*
Household autonomous consumption depends on the average quality growth of the consumption goods sector.
Heterogeneity is introduced through persistent household-specific adjustment parameters assigned at initialization.
*/

    v[0]=CURRENT;                  // Household autonomous consumption in the last period
    v[1]=V("annual_frequency");     // Defines the household adjustment period
    v[2]=fmod((double) t, v[1]);    // Determines if it is the household adjustment period
    if (v[2]==0)                    // If it is an adjustment period
        {
            v[3]=LAG_GROWTH(consumption, "Sector_Avg_Quality", v[1], 1);
            
            // Use persistent household-specific adjustment parameter
            v[4] = V("household_autonomous_consumption_adjustment");

            // Apply adjustment to the change in autonomous consumption
            v[5]=v[0] * (1 + v[4] * v[3]);

            // Ensuring non-negative consumption
            v[6]=max(0, v[5]);
        }
    else
        v[6]=v[0]; // If not adjustment period, retain previous period's value

RESULT(v[6])



EQUATION("Household_Imports_Share") // "Keeping up with the Joneses" effect / Relative Income Theory (Duesenberry, 1949)
/*
Calculates the import share where propensity to import is a fixed,
innate household characteristic, while price elasticity to import is a
dynamic hyperbolic function of the household's income relative to the mean.
*/

    // 1. Get the household's fixed, innate propensity to import
    // This is initialized once for each household and remains constant.
    v[0] = V("household_import_propensity");

    // 2. Define parameters for the dynamic elasticity function
    v[1] = V("household_elasticity_base_factor"); // Parameter: scales the hyperbola (calibrated to 1.0)

    // 3. Get the necessary income values to calculate relative income
    v[3] = V("Household_Avg_Nominal_Income");             // This household's income
    v[4] = VS(country, "Country_Median_Household_Income"); // Use the pre-calculated economy-wide median

    // 4. Calculate the dynamic elasticity using the hyperbolic function
    //    elasticity = base_factor / relative_income
    v[5] = (v[4] > 0 && v[3] > 0) ? (v[1] / (v[3] / v[4])) : 5.0; // If income is zero, elasticity is set to the max cap value directly.
    v[6] = max(0.001, min(5.0, v[5])); // The dynamic elasticity, bounded for safety

    // 5. Get Market Prices
    v[7] = VS(consumption, "Sector_Avg_Price");
    v[8] = VS(consumption, "Sector_External_Price");
    v[9] = VS(external, "Country_Exchange_Rate");
    v[10] = (v[9] * v[8] > 0) ? (v[7] / (v[9] * v[8])) : 1.0; // Price Ratio

    // 6. Calculate the Final Import Share
    // Import Share = (Propensity to Import) * (Price Ratio) ^ (Price Elasticity to Import)
    v[11] = v[0] * pow(v[10], v[6]);

    // 7. Final bounds check
    v[12] = max(0, min(1, v[11]));

RESULT(v[12])



EQUATION("Household_Propensity_to_Spend") // "Keeping up with the Joneses" effect / Relative Income Theory (Duesenberry, 1949)
/*
Dynamic propensity to spend based on household income relative to median income.
Uses a sigmoid function: y = (1-n)(1/(1+exp(k*(x-x0)))) + n
where:
- x = household_income / median_income (relative income ratio)
- k = household_propensity_steepness (controls how quickly propensity changes with income)
- x0 = household_propensity_center (income level where propensity = 0.5)
- n = household_propensity_min (minimum propensity, creates range from n to 1)

The function creates a "Keeping up with the Joneses" effect portraying an unequal economy:
households compare their consumption to the median household. (Duesenberry, 1949)

*/
    v[0] = V("Household_Avg_Nominal_Income");  // Household's average nominal income
    v[1] = VS(country, "Country_Median_Household_Income");  // Use the pre-calculated economy-wide median
    v[2] = (v[1] > 0) ? v[0] / v[1] : 1.0;  // Relative income ratio (x = household_income / median_income)

    // Flexible sigmoid function parameters
    v[3] = V("household_propensity_steepness");  // Steepness parameter (k): controls how quickly propensity changes (calibrated to 2.0)
    v[4] = V("household_propensity_center");     // Center point (x0): income level where propensity = 0.5 (calibrated to 2.0)
    v[5] = V("household_propensity_min");        // Minimum bound (n): calibrated to 0.05

    // Truncated Sigmoid function: y = (1 - n) * (1 / (1 + exp(k * (x - x0)))) + n
    v[6] = 1 / (1 + exp(v[3] * (v[2] - v[4])));  // Base sigmoid function: 1 / (1 + exp(k * (x-x0)))
    v[7] = (1 - v[5]) * v[6] + v[5];  // Scale and shift: (1-n) * sigmoid + n
    v[8] = min(1, v[7]);  // Cap maximum at 1
RESULT(v[8])



EQUATION("Household_Real_Desired_Domestic_Consumption")
/*
Household real domestic consumption incorporates heterogeneity in propensity to consume.
*/
    v[0]=V("Household_Avg_Real_Income");		// Household's past real disposable income
    v[1]=V("Household_Propensity_to_Spend");	// Household-specific spending propensity
    v[2]=V("Household_Real_Autonomous_Consumption");
    v[4]=V("Household_Imports_Share");
    v[3]=v[0]*v[1]*(1-v[4])+v[2];
RESULT(v[3])



EQUATION("Household_Real_Desired_Imported_Consumption")
/*
Household real imported consumption depends on:
1. Effective domestic consumption * domestic price
2. Effective imported consumption * foreign price * exchange rate
*/
    v[0]=V("Household_Avg_Real_Income");		// Household's past real disposable income
    v[1]=V("Household_Propensity_to_Spend");	// Household-specific spending propensity
    v[2]=V("Household_Imports_Share");
    v[3]=v[0]*v[1]*v[2];
RESULT(v[3])



EQUATION("Household_Desired_Expenses")
/*
Household nominal desired expenses depend on:
1. Effective domestic consumption * domestic price
2. Effective imported consumption * foreign price * exchange rate
*/
	v[0]=V("Household_Real_Desired_Domestic_Consumption");  // Household's real domestic consumption demand
	v[1]=V("Household_Real_Desired_Imported_Consumption");  // Household's real imported consumption demand
	v[2]=VS(external,"Country_Exchange_Rate");              // Exchange rate
	v[3]=VS(consumption, "Sector_Avg_Price");               // Domestic consumption sector average price
	v[4]=VS(consumption, "Sector_External_Price");          // External consumption sector price

	v[5]=v[0]*v[3] + v[1]*v[2]*v[4];  // Compute total nominal expenses                  	
RESULT(v[5])



EQUATION("Household_Avg_Debt_Rate")
/*
Household avg debt rate of the last household period (equal to annual period)
*/
    v[0] = LAG_AVE(p, "Household_Debt_Rate", V("annual_frequency"),1);
RESULT(v[0])



EQUATION("Household_Interest_Rate")
/*
Interest rates paid by households, including heterogeneous risk premiums.
*/
    v[0]=VS(financial,"fs_risk_premium_household"); 		// Household-specific risk premium adjustment parameter
    v[1]=V("Household_Avg_Debt_Rate");						// Household-specific debt rate
    v[2]=VS(financial,"Financial_Sector_Avg_Interest_Rate_Short_Term"); // Baseline short-term loan rate
    v[3]=(1+v[1]*v[0])*v[2]; 								// Adjusted interest rate based on household debt risk
RESULT(v[3])



/*
EQUATION("Household_Avg_Interest_Rate")
/*
Computes the weighted average interest rate across all households, where the weight is the outstanding stock of loans.
*/
/*

    v[0] = 0;  // Sum of weighted interest rates
    v[1] = 0;  // Sum of total household loans

    CYCLE(cur, "HOUSEHOLDS")
    {
        v[2] = VS(cur, "Household_Interest_Rate"); // Individual household interest rate
        v[3] = VS(cur, "Household_Stock_Loans");  // Household loan stock

        v[0] += v[2] * v[3];  // Sum of weighted interest rates
        v[1] += v[3];         // Total loan stock
    }

    // Avoid division by zero
    v[4] = v[1] > 0 ? v[0] / v[1] : 0;

RESULT(v[4])
*/



EQUATION("Household_Interest_Payment")
/* 
Calculates total interest payment on all household loans. Interest rates can be fixed or flexible

switch_interest_payment
0-->fixed interest, defined when the loan was taken
1-->flexible interest, the rate is calculated evert period
*/

    v[0] = 0;  // Initialize total interest payment accumulator
    v[4] = V("switch_interest_payment");  // Determines fixed or flexible interest structure

    CYCLE(cur, "HOUSEHOLD_LOANS")  // Loop through all household loans
    {
        v[1] = VS(cur, "household_loan_total_amount"); // Outstanding loan amount

        // If flexible interest rate
        if(v[4] == 1)
        {
            v[2] = V("Household_Interest_Rate");  // Use household-specific interest rate
        }
        else  // If fixed interest rate
        {
            v[2] = VS(cur, "household_loan_interest_rate");  // Use pre-defined rate
        }

        v[3] = v[1] * v[2];  // Compute interest payment
        v[0] += v[3];  // Accumulate total interest payments
    }

RESULT(max(0, v[0]))  // Ensure non-negative payments



EQUATION("Household_Debt_Payment")
/* 
Sum up total debt payment on all household loans.
Amortizations are fixed for each loan.
Once a loan is fully repaid, it is automatically deleted.
*/

v[0] = SUM("household_loan_fixed_amortization"); // Sum all amortization payments for the period

CYCLE_SAFE(cur, "HOUSEHOLD_LOANS") // Loop through all household loans
{
    v[4] = VS(cur, "household_loan_total_amount");       // Current debt amount
    v[5] = VS(cur, "household_loan_fixed_amortization"); // Fixed amortization amount
    v[6] = v[4] - v[5];                                  // New total amount after amortization

    if (v[6] > 0) // If the loan still has a remaining balance
        WRITES(cur, "household_loan_total_amount", v[6]); // Update the loan balance
    else // If the loan has been fully repaid
        DELETE(cur); // Remove the loan object from the system
}

RESULT(max(0, v[0])) // Ensure non-negative payments



EQUATION("Household_Financial_Obligations")
/*
Household Financial Obligations in the current period is the sum of interest payment and debt payment.
This represents the total amount a household must pay to service its loans.
*/
	v[1] = V("Household_Interest_Payment");  // Interest due on outstanding loans
	v[2] = V("Household_Debt_Payment");      // Principal repayments (amortization)
	v[3] = v[1] + v[2];                      // Total financial obligations
RESULT(v[3])  // Output the total amount a household must pay



EQUATION("Household_Liquidity_Preference") // *
/*
Household's desired liquidity preference, determining the proportion of income kept in liquid deposits.
Evolves based on household income growth and debt levels, with persistent individual heterogeneity.
Each household maintains its own adjustment sensitivity established during initialization.
*/

v[0]=V("annual_frequency");    // Frequency of adjustment
v[1]=fmod((double)t, v[0]);    // Determines if this is an adjustment period
v[4]=LAG_GROWTH(p, "Household_Nominal_Disposable_Income", v[0], 1); // Income growth
v[5]=VL("Household_Debt_Rate",1);  // Previous period's debt rate
v[6]=V("Household_Max_Debt_Rate"); // Household's max acceptable debt rate
v[7]=CURRENT;                      // Current liquidity preference

// Use persistent household-specific adjustment parameter established during initialization
v[8] = V("household_liquidity_preference_adjustment");

if(v[1]==1)  // Adjust liquidity preference at defined intervals
{
    if(v[4] < 0 && v[5] > v[6])  // If income is falling and debt is high
        v[9] = v[7] + v[8];      // Increase liquidity preference
    else if(v[4] > 0 && v[5] < v[6]) // If income is rising and debt is low
        v[9] = v[7] - v[8];      // Decrease liquidity preference
    else
        v[9] = v[7];            // No change
}
else
    v[9]=v[7]; // Maintain last period's liquidity preference

// Ensure liquidity preference remains between 0 and 1
v[10]=max(0, min(1, v[9]));

RESULT(v[10])



EQUATION("Household_Retained_Deposits")
/*
Household retained deposits at the current period. 
Based on household liquidity preference and long-term income trends.
Ensures households do not go into debt to retain liquidity.
*/
    // Household's total financial obligations (interest + debt payments)
    v[1] = V("Household_Financial_Obligations");  // Household's total financial obligations (interest + debt payments)
    v[2] = VL("Household_Stock_Deposits", 1);    // Stock of deposits from the last period
    v[8] = VL("Household_Nominal_Disposable_Income", 1); // Use actual disposable income (for consistency with Household_Internal_Funds)
    // Compute current internal funds available
    v[3] = max(0, (v[2] + v[8] - v[1])); 
    // Desired amount of retained deposits (must be positive)
    v[4] = V("Household_Avg_Nominal_Income"); // Use average nominal income for desired retained deposits calculation
    v[5] = V("Household_Liquidity_Preference"); // Household-specific liquidity preference, as a ratio of capital
    v[6] = v[4] * v[5]; // Desired amount of retained deposits (must be positive)
    // Ensure deposits are non-negative and do not exceed internal funds
    v[7] = max(0, min(v[6], v[3])); // Ensures deposits are non-negative and do not exceed internal funds
RESULT(v[7])



EQUATION("Household_Internal_Funds")
/*
Total available funds for household expenses in the current period.
Accounts for past savings, disposable income, financial obligations, and retained deposits.
*/

v[0] = V("Household_Financial_Obligations");    // Household financial obligations (interest + debt payments)
v[1] = VL("Household_Stock_Deposits", 1);       // Household's stock of deposits from the last period
v[4] = VL("Household_Nominal_Disposable_Income", 1); // Last period's nominal disposable income
v[2] = V("Household_Retained_Deposits");        // Household savings retained for future periods

// Compute household's available internal funds for expenses
v[3] = v[4] + v[1] - v[0] - v[2];

RESULT(v[3]) // Available funds must be used for expenses, investments, or additional savings


EQUATION("Household_Max_Debt_Rate") // *
/*
Household desired debt rate.
Inspired by Moreira (2010), evolves based on nominal income growth.
Each household adjusts its debt rate based on income changes over time.
Uses persistent household-specific adjustment parameters for heterogeneity.
*/

    v[0] = V("annual_frequency");  
    v[1] = fmod((double)t, v[0]);  // Determines if it's an adjustment period
    v[4] = LAG_GROWTH(p, "Household_Nominal_Disposable_Income", v[0], 1); // Growth rate of household disposable income
    v[5] = CURRENT;  // Previous period's debt rate
    v[6] = V("household_debt_rate_adjustment"); // Household-specific debt rate adjustment parameter

    if (v[1] == 1) // If in the adjustment period
    {
        if (v[4] > 0)  // If income is growing
            v[7] = v[5] + v[6];  // Increase debt rate
         // v[7] = v[5] + (v[6]) * (v[4])  // Adjusted debt rate (positive growth)
        else if (v[4] < 0)  // If income is shrinking
            v[7] = v[5] - v[6];  // Decrease debt rate
         // v[7] = v[5] + (v[6]) * (v[4])  // Adjusted debt rate (negative growth) 
        else  // No change in income
            v[7] = v[5];
    }
    else
        v[7] = v[5]; // Maintain previous debt rate if not in the adjustment period

    // Ensure the debt rate remains within [0,1] bounds
    v[8] = max(0, min(1, v[7]));

RESULT(v[8])



EQUATION("Household_Max_Loans")
/*
Household available debt depends on the difference between desired stock of debt and current stock of debt.
If the household's current debt exceeds its desired debt, it must reduce borrowing. 
Otherwise, the difference represents the maximum possible new loan amount.
*/

v[0] = V("Household_Max_Debt_Rate"); // Desired debt-to-income ratio
v[1] = VL("Household_Stock_Loans", 1); // Previous period's outstanding loans
v[2] = VL("Household_Stock_Deposits", 1); // Household's financial reserves (savings)
v[3] = VL("Household_Nominal_Disposable_Income", 1); // Household's past disposable income

// Maximum loan households can take, ensuring no negative values
v[4] = v[0] * (v[2] + v[3]) - v[1];
v[5] = max(0, v[4]);

RESULT(v[5])



EQUATION("Household_Demand_Loans")
/*
Household loan demand is determined as the amount of desired expenses that internal funds cannot cover.
Households will only borrow up to the maximum allowable amount.
*/

v[0] = V("Household_Desired_Expenses");  // Total household expenses
v[1] = V("Household_Internal_Funds");    // Available internal funds (savings and income)
v[2] = V("Household_Max_Loans");         // Maximum loan the household can take

// Compute the required loan amount, ensuring it does not exceed borrowing capacity
v[3] = v[0] - v[1]; 
v[4] = max(0, min(v[3], v[2])); // Households borrow only what they need, within limits

RESULT(v[4])



EQUATION("Household_Effective_Loans")
/*
Household effective loans represent the amount of loans that the financial sector was able to provide.
A new loan object is created for each borrowing household.
*/

v[0] = V("Household_Demand_Loans"); // Amount the household wants to borrow
v[1] = V("Household_Interest_Rate"); // Interest rate applied to the loan
v[2] = V("annual_frequency"); // Number of periods for amortization

// Create a new loan object for the household
cur = ADDOBJ("HOUSEHOLD_LOANS");
WRITES(cur, "household_loan_total_amount", v[0]); // Store loan amount
WRITES(cur, "household_loan_interest_rate", v[1]); // Store interest rate
WRITES(cur, "household_loan_fixed_amortization", (v[0] / v[2])); // Set amortization schedule

RESULT(v[0])



EQUATION("Household_Funds")
/*
Total available funds for household expenses in the current period.
Calculated as the sum of internal funds (after debt payments) and new loans.
*/

v[0] = V("Household_Internal_Funds"); // Household's internal financial resources
v[1] = V("Household_Effective_Loans"); // New loans acquired from the financial sector
v[2] = v[0] + v[1]; // Total available funds for spending

RESULT(v[2])



EQUATION("Household_Maximum_Expenses")
/*
Nominal value of possible expenses, restricted to the amount of funds available.
Households cannot spend more than what they have.
*/

v[0] = V("Household_Desired_Expenses");  // Household's desired expenses
v[1] = V("Household_Funds");  // Total available financial resources
v[2] = max(0, min(v[0], v[1]));  // Household can only spend up to available funds

RESULT(v[2])



EQUATION("Household_Real_Domestic_Consumption_Demand")
/*
Household effective real domestic consumption.
Determined by desired consumption levels and constrained by available funds.
If budget is insufficient, spending is adjusted proportionally.
*/

v[0] = V("Household_Maximum_Expenses");  // Household's budget constraint

// Retrieve price variables
v[1] = VS(consumption, "Sector_Avg_Price");  // Domestic goods price
v[2] = VS(consumption, "Sector_External_Price");  // Foreign goods price
v[5] = VS(external, "Country_Exchange_Rate");  // Exchange rate

// Household's desired real consumption
v[3] = V("Household_Real_Desired_Domestic_Consumption");  
v[4] = V("Household_Real_Desired_Imported_Consumption");  

// Compute nominal expenses on domestic and imported goods
v[6] = v[3] * v[1];  // Nominal expense on domestic goods
v[7] = v[4] * v[2] * v[5];  // Nominal expense on imported goods

// Effective spending on domestic and imported goods
v[8] = min(v[0], v[6]);  // Prioritize domestic spending
v[9] = v[8] / v[1];  // Convert nominal to real domestic consumption

v[10] = min(v[7], v[0] - v[8]);  // Remaining budget allocated to imports
v[11] = v[10] / (v[2] * v[5]);  // Convert nominal to real imported consumption

WRITE("Household_Real_Imported_Consumption_Demand", v[11]);  
RESULT(v[9])  // Return real effective domestic consumption



EQUATION_DUMMY("Household_Real_Imported_Consumption_Demand", "Household_Real_Domestic_Consumption_Demand")



EQUATION("Household_Effective_Real_Domestic_Consumption")
/*
Household effective real domestic consumption, depending on how much the domestic consumption goods sector was able to meet demand.
*/

v[0] = VS(consumption, "Sector_Demand_Met");                    // Percentage of total demand met by the sector
v[1] = V("Household_Real_Domestic_Consumption_Demand");         // Household's real demand for domestic goods
v[2] = v[0] * v[1];                                             // Actual domestic consumption fulfilled

RESULT(v[2])                                                   // Return the effective domestic consumption


EQUATION("Household_Effective_Real_Imported_Consumption")
/*
Household effective external consumption, depending on desired level of imports plus the demand not met by the domestic production.
Sector_Demand_Met_By_Imports is a binary variable (0 or 1) that indicates whether extra imports are available to meet unmet domestic demand.
When 1, households can import the amount not met by domestic production; when 0, they cannot.

The equation has two components:
1. Extra imports to meet unmet domestic demand: (1-v[0])*v[1]*v[3]
   - (1-v[0]) is the percentage of domestic demand not met
   - v[1] is whether extra imports are available (0 or 1)
   - v[3] is the original domestic consumption demand
2. Plus the desired imported consumption: v[4]
*/

v[0] = VS(consumption, "Sector_Demand_Met");                    // Percentage of the total demand met by the sector
v[1] = VS(consumption, "Sector_Demand_Met_By_Imports");         // Binary indicator (0/1) of whether extra imports are available
v[2] = (1-v[0]) * v[1];                                         // Percentage of domestic demand that can be met by extra imports
v[3] = V("Household_Real_Domestic_Consumption_Demand");         // Desired level of domestic consumption 
v[4] = V("Household_Real_Imported_Consumption_Demand");         // Desired level of external consumption
v[5] = v[2] * v[3] + v[4];                                      // Total effective imported consumption (extra imports + desired imports)

RESULT(v[5])                                                   // Return the effective imported consumption



EQUATION("Household_Effective_Expenses")
/*
Household effective expenses is the sum of effective domestic consumption and effective imports, in nominal values.
*/

v[0] = VS(consumption,"Sector_Avg_Price");                     // Domestic price of consumption goods
v[1] = VS(consumption,"Sector_External_Price");                // External price of consumption goods
v[2] = VS(external,"Country_Exchange_Rate");                   // Exchange rate

v[3] = V("Household_Effective_Real_Domestic_Consumption");     // Household's effective real domestic consumption
v[4] = V("Household_Effective_Real_Imported_Consumption");     // Household's effective real imported consumption

v[5] = v[0] * v[3] + v[1] * v[2] * v[4]; // Compute total nominal expenses

RESULT(v[5]) // Return household's total nominal spending



EQUATION("Household_Available_Deposits")
/* 
Household available deposits after expenses and financial obligations.
Ensures that deposits remain non-negative.
*/

v[0] = V("Household_Funds");                 // Household total funds (including loans and savings)
v[1] = V("Household_Effective_Expenses");    // Household total expenses
v[2] = max(0, v[0] - v[1]);                  // Ensure deposits do not go negative

RESULT(v[2])  // Return the remaining available deposits



EQUATION("Household_Deposits_Return")
/* 
Net return on household deposits.
Interest earned on both available and retained deposits.
*/

v[0] = V("Household_Available_Deposits");   // Household's current available deposits
v[1] = V("Household_Retained_Deposits");    // Household's retained deposits for future use
v[2] = VS(financial, "Financial_Sector_Interest_Rate_Deposits"); // Interest rate on deposits

v[3] = (v[0] + v[1]) * v[2];   // Total interest income from deposits

RESULT(v[3])  // Return the household's deposit earnings


//////////////////////////////////////////////
///////////// BOTTOM-UP APPROACH /////////////
//////////////////////////////////////////////


EQUATION("Household_Employment_Status")
/*
Determines household employment status based on labor market matching.
0 = unemployed, 1 = employed in consumption sector, 2 = employed in capital sector, 3 = employed in input sector
*/

    v[1] = 0;  // Initialize as unemployed

    // Get total employment demand from all sectors
    v[2] = VS(consumption, "Sector_Employment");
    v[3] = VS(capital, "Sector_Employment");
    v[4] = VS(input, "Sector_Employment");
    v[5] = v[2] + v[3] + v[4];  // Total employment demand

    v[6] = VS(country, "Country_Total_Population");

    v[7] = v[5] / v[6];  // Employment rate (jobs per household)
        if(RND < v[7])  // Stochastic employment assignment
        {
            // Assign to sector based on relative employment
            v[9] = RND;
            v[10] = v[2] / v[5];  // Consumption sector share
            v[11] = v[3] / v[5];  // Capital sector share
            
            if(v[9] < v[10])
                v[1] = 1;  // Employed in consumption's sector
            else if(v[9] < v[10] + v[11])
                v[1] = 2;  // Employed in capital's sector
            else
                v[1] = 3;  // Employed in input's sector
        }

RESULT(v[1])



EQUATION("Household_Wage_Income")
/*
Calculates household wage income as sector wage � persistent household skill.
Heterogeneity comes from the persistent skill assigned at initialization.
Wage is updated only annually (wage stickiness).
*/

v[0] = V("Household_Employment_Status");  // Employment status (0=unemployed, 1-3=employed)
v[1] = 0;  // Initialize wage income

if(v[0] > 0)  // If employed
{
    // Get sector-specific wage
    if(v[0] == 1)  // Employed in consumption sector
    {
        v[2] = VS(consumption, "Sector_Avg_Wage");
    }
    else if(v[0] == 2)  // Employed in capital sector
    {
        v[2] = VS(capital, "Sector_Avg_Wage");
    }
    else if(v[0] == 3)  // Employed in input sector
    {
        v[2] = VS(input, "Sector_Avg_Wage");
    }

    // Set household_skill_mean = -0.5 * (household_skill_stddev)^2 to ensure E[household_skill] = 1
    v[7] = V("household_skill"); // persistent skill assigned at init

    v[1] = v[2] * v[7];
}

RESULT(v[1])



EQUATION("Household_Profit_Income")
/*
Profit income received by the household.
Uses persistent q-exponential-distributed share coefficient set at initialization.
Each household gets its fixed share of total distributed profits.
*/

    v[0] = V("household_profit_share");  // Persistent profit share coefficient (set at initialization)
v[1] = VS(country, "Country_Distributed_Profits");  // Total profits distributed in the economy

RESULT(v[0] * v[1])

/*
EQUATION("Household_Profit_Income")		// WAGE-PROFIT WEAK CORRELATION

//Household profit income is drawn from a Pareto-Tsallis distribution.
//Higher wages increase the likelihood of earning profit income, introducing weak correlation.

v[0] = V("profit_distribution_minimum");  // Minimum profit threshold
v[1] = V("profit_distribution_exponent"); // Pareto-Tsallis exponent
v[2] = V("profit_distribution_q");        // Tsallis deformation parameter

v[3] = V("Household_Wage_Income");  // Household wage income

// Define correlation factor: higher wage earners are more likely to have profit income
v[4] = max(0, (v[3] - V("profit_correlation_wage_threshold")) / V("profit_correlation_slope"));
v[5] = min(1, v[4]); // Probability factor ensuring a valid probability range [0,1]

// Draw profit income based on probability factor
if (RND < v[5])  
    v[6] = pareto_tsallis(v[0], v[1], v[2]); // Profit income for high-wage earners
else
    v[6] = 0; // Low-wage earners are less likely to receive profit income

RESULT(v[6])
*/



EQUATION("Household_Nominal_Disposable_Income")
/*
Household net nominal income is calculated using a bottom-up approach, summing individual wage and profit incomes, interest received on deposits, and unemployment benefits.
Taxation is applied based on the chosen tax structure.

switch_household_tax_structure:
0 --> No Tax
1 --> Only Wages
2 --> Only Profits
3 --> Wages and Profits
4 --> Wages, Profits, Interest
5 --> Wages, Profits, Interest, Wealth
*/

    v[0] = V("Household_Profit_Income");  // Household-specific profit income
    v[1] = V("Household_Wage_Income");    // Household-specific wage income
    v[2] = V("Household_Deposits_Return"); // Interest earned on household deposits
    v[3] = VS(government, "Government_Effective_Unemployment_Benefits"); // Total unemployment benefits available
    v[4] = V("household_direct_tax");          // Household-specific tax rate
    v[5] = V("switch_household_tax_structure"); // Switch: determines tax structure

    // --- Unemployment Benefits Allocation ---
    // Allocate unemployment benefits equally among all unemployed households
    v[6] = VS(country, "Country_Unemployed_Count"); // Use the pre-calculated count of unemployed households
    v[7] = (v[6] > 0) ? v[3] / v[6] : 0;  // Distribute equally if unemployed households exist

    // --- Compute Gross Postbenefit Income ---
    v[12] = v[0] + v[1] + v[7];  // Gross total income (wages + profits + benefits)

    // --- Apply Taxation ---
         if (v[5] == 0) v[8] = 0;                            // No tax
    else if (v[5] == 1) v[8] = v[1] * v[4];                  // Only wages taxed
    else if (v[5] == 2) v[8] = v[0] * v[4];                  // Only profits taxed
    else if (v[5] == 3) v[8] = (v[0] + v[1]) * v[4];         // Wages & profits taxed
    else if (v[5] == 4) v[8] = (v[0] + v[1] + v[2]) * v[4];  // Wages, profits & interest taxed
    else if (v[5] == 5) v[8] = (v[0] + v[1] + v[2]) * v[4];  // Wages, profits, interest & wealth taxed

    // --- Compute Final Disposable Income ---
    v[9] = VS(country, "Country_Consumer_Price_Index");  // Consumer Price Index for inflation adjustment
    WRITE("Household_Taxation", v[8]);                   // Store taxation amount
    WRITE("Household_Nominal_Gross_Income", v[12]);       // Store gross income before taxes
    WRITE("Household_Real_Disposable_Income", (v[12] - v[8]) / v[9]);  // Compute and store real disposable income

RESULT(v[12] - v[8]) // Return nominal disposable income after taxation



EQUATION_DUMMY("Household_Taxation", "Household_Nominal_Disposable_Income")
EQUATION_DUMMY("Household_Nominal_Gross_Income", "Household_Nominal_Disposable_Income")
EQUATION_DUMMY("Household_Real_Disposable_Income", "Household_Nominal_Disposable_Income")



EQUATION("Household_Stock_Loans")
/*
Household stock of loans
*/
    v[0] = SUM("household_loan_total_amount");
RESULT(v[0])



EQUATION("Household_Stock_Deposits")
/*
Stock = Available deposits after expenses + retained deposits (liquidity buffer) + net redistribution
This formulation captures credit dynamics, behavioral consumption, and macro-financial feedbacks.
*/
    v[0] = V("Household_Available_Deposits"); // Available deposits after expenses
    v[1] = V("Household_Retained_Deposits"); // Retained deposits (liquidity buffer)
    v[2] = V("household_profit_share"); // Share of profit income to be redistributed
    v[3] = V("Exit_Deposits_Distributed"); // Deposits redistributed by exiters
    v[4] = SUMS(country, "Sector_Entry_Deposits_Needed");
    v[5] = v[0] + v[1] + v[2] * (v[3] - v[4]);

RESULT(max(v[5], 0))


EQUATION("Household_Debt_Rate")
/*
Household degree of indebtedness, calculated as the ratio of total loans to the sum of deposits and average income.
If denominator is non-positive, assigns a default high risk value (1.1).
*/
    v[0] = V("Household_Stock_Loans");          // Household total outstanding loans
    v[1] = V("Household_Stock_Deposits");       // Household total deposits
    v[2] = V("Household_Avg_Nominal_Income");   // Household average nominal income

    // Calculate the denominator (financial capacity)
    v[3] = v[1] + v[2];

    // Calculate debt rate, handling potential division by zero or negative capacity
    if (v[3] > 0)
        v[4] = v[0] / v[3];                     // Debt rate = Loans / (Deposits + Avg Income)
    else
        v[4] = 1.1;                             // Default to high debt rate if denominator is non-positive

RESULT(v[4])


/*
EQUATION("Household_Income_Percentile")
/*
Calculates this household's income percentile (0-1) relative to all households.
This variable is updated once every annual_frequency.
Uses SORTS to sort all households by income, then SEARCH_INSTS to find this
household's rank directly.
*/
/*
v[0] = V("annual_frequency");
if (fmod((double) t, v[0]) == 0 && t > 0)
{
  // Sort all sibling households under the parent object by their average nominal income
  SORTS(PARENT, "HOUSEHOLDS", "Household_Avg_Nominal_Income", UP);

  // Get the total number of households for the percentile calculation
  v[1] = COUNT("HOUSEHOLDS");

  if (v[1] > 0)
  {
    // Find the rank of the current household (1-based). The position in the sorted
    // list of siblings is the rank.
    v[2] = SEARCH_INSTS(PARENT, THIS);

    // Calculate percentile: (rank - 1) / (total - 1).
    // If only one household, it's the 50th percentile.
    v[3] = (v[1] > 1) ? ((v[2] - 1) / (v[1] - 1)) : 0.5;
  }
  else
  {
    v[3] = 0.5; // Default for case with no households
  }
}
else
{
  // If not an update period, use the last calculated value
  v[3] = CURRENT;
}
RESULT(v[3])
*/


EQUATION("Household_Income_Share")
/*
Household share of total nominal disposable income across all households.
*/
    v[0] = V("Household_Nominal_Disposable_Income");         // Household's nominal disposable income
    v[1] = SUMS(PARENT, "Household_Nominal_Disposable_Income"); // Total nominal disposable income of all households
    v[2] = (v[1] != 0) ? v[0] / v[1] : 0;                      // Calculate share, handle division by zero
RESULT(v[2])



EQUATION("Household_Net_Wealth")
/*
Household net wealth = deposits (assets) minus loans (liabilities).
This is the true measure of household wealth that accounts for both assets and debt.
Positive values indicate net wealth, negative values indicate net debt.
*/
    v[0] = V("Household_Stock_Deposits");       // Household's liquid assets (deposits)
    v[1] = V("Household_Stock_Loans");          // Household's total outstanding debt
    v[2] = v[0] - v[1];                         // Net wealth = assets - liabilities
RESULT(v[2])



EQUATION("Household_Wealth_Share")
/*
Share of total positive net wealth.
Only households with positive net wealth are included.
*/
    v[0] = V("Household_Net_Wealth");
    if (v[0] > 0) {
        v[1] = SUM_CND(PARENT, "Household_Net_Wealth", ">", 0); // Sum of positive net wealth
        v[2] = (v[1] != 0) ? v[0] / v[1] : 0;
    } else {
        v[2] = 0;
    }
RESULT(v[2])



EQUATION("Household_Debt_Share")
/*
Share of total household debt (absolute value of negative net wealth).
Only households with negative net wealth are included. Others get zero.
*/
    v[0] = V("Household_Net_Wealth");
    if (v[0] < 0) {                     // Only households with negative net wealth are included. Others get zero.
        v[1] = abs(SUM_CND(PARENT, "Household_Net_Wealth", "<", 0)); // Take absolute value of the sum
        v[2] = (v[1] != 0) ? abs(v[0]) / v[1] : 0;  // Calculate share (positive � positive = positive)
    } else {
        v[2] = 0;                        // Others get zero.
    }
RESULT(v[2])
