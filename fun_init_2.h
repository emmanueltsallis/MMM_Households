EQUATION("Initialization")
/*
***************
READ CAREFULLY
***************
This variable initializes the model.
It calls all control parameters defined by the user in the control object.
Then, it perform initial calculations to define other parameters and lagged values based only on the control parameters.
It also writes the dependent parameters and lagged values. User do not need to do it by hand.
Finally, it also creates objects based on control parameters. 1 object of each kind must be defined by the user first.
It is set in a specific simple configuration: 3 sectors and multiple households. Next step is to generalize this variable for N sectors.
Additionally, there is a strong hypothesis here: all sector are equals, except for how their demand is calculated.
*/

//Define Global Pointers
country=SEARCH("COUNTRY"); // Country pointer
external=SEARCH("EXTERNAL_SECTOR"); // External sector pointer
government=SEARCH("GOVERNMENT"); // Government pointer
financial=SEARCH("FINANCIAL"); // Financial sector pointer
consumption=SEARCH_CND("id_consumption_goods_sector",1); // Consumption sector pointer
capital=SEARCH_CND("id_capital_goods_sector",1); // Capital sector pointer
input=SEARCH_CND("id_intermediate_goods_sector",1); // Intermediate sector pointer
households=SEARCH("HOUSEHOLDS"); // Household pointer


//Macro Parameters			
v[6]=V("scale_autonomous_consumption"); // Autonomous consumption scale

//Household Parameters
v[21]=V("household_wage_mean");            // Mean of log-normal wage distribution
v[22]=V("household_wage_stddev");          // Standard deviation of wage distribution
v[23]=V("household_profit_lambda");        // Scale parameter for q-exponential distribution
v[25]=V("household_profit_q");             // Entropic index for q-exponential distribution (0 < q < 2)
v[250]=V("household_profit_participation_rate"); // Fraction of households receiving profits (e.g., 0.05)
v[26]=V("household_direct_tax"); // Base tax rate for households
v[29]=V("household_skill_mean");   // Mean parameter for household skill log-normal distribution // Set household_skill_mean = -0.5 * (household_skill_stddev)^2 to ensure E[household_skill] = 1
v[30]=V("household_skill_stddev"); // Standard deviation parameter for household skill log-normal distribution
v[27]=V("household_avg_import_propensity"); // Economy-wide average import propensity (used to generate household-specific values)
v[31]=V("household_avg_autonomous_consumption_adjustment"); // Global baseline for autonomous consumption adjustment
v[32]=V("household_avg_liquidity_preference_adjustment"); // Global baseline for household liquidity preference adjustment
v[33]=V("household_avg_debt_rate_adjustment"); // Global baseline for household debt rate adjustment

cur1=SEARCH_CND("id_consumption_goods_sector",1); // Consumption sector pointer
cur2=SEARCH_CND("id_capital_goods_sector",1); // Capital sector pointer
cur3=SEARCH_CND("id_intermediate_goods_sector",1); // Intermediate sector pointer

v[40]=V("fs_number_object_banks"); // Number of object banks

v[41]=VS(consumption, "sector_number_object_firms"); // Number of object firms in consumption sector
v[42]=VS(capital, "sector_number_object_firms"); // Number of object firms in capital sector
v[43]=VS(input, "sector_number_object_firms"); // Number of object firms in intermediate sector

v[44]=VS(consumption, "sector_initial_productivity"); // Initial productivity in consumption sector
v[45]=VS(capital, "sector_initial_productivity"); // Initial productivity in capital sector
v[46]=VS(input, "sector_initial_productivity"); // Initial productivity in intermediate sector

v[47]=VS(consumption, "sector_initial_markup"); // Initial markup in consumption sector
v[48]=VS(capital, "sector_initial_markup"); // Initial markup in capital sector
v[49]=VS(input, "sector_initial_markup"); // Initial markup in intermediate sector

v[50]=VS(consumption, "sector_initial_wage"); // Initial wage in consumption sector
v[51]=VS(capital, "sector_initial_wage"); // Initial wage in capital sector
v[52]=VS(input, "sector_initial_wage"); // Initial wage in intermediate sector

v[53]=VS(consumption, "sector_input_tech_coefficient"); // Input tech coefficient in consumption sector
v[54]=VS(capital, "sector_input_tech_coefficient"); // Input tech coefficient in capital sector
v[55]=VS(input, "sector_input_tech_coefficient"); // Input tech coefficient in intermediate sector

v[56]=VS(consumption, "sector_capital_output_ratio"); // Capital output ratio in consumption sector
v[57]=VS(capital, "sector_capital_output_ratio"); // Capital output ratio in capital sector
v[58]=VS(input, "sector_capital_output_ratio"); // Capital output ratio in intermediate sector

v[59]=VS(consumption, "sector_rnd_revenue_proportion"); // R&D revenue proportion in consumption sector
v[60]=VS(capital, "sector_rnd_revenue_proportion"); // R&D revenue proportion in capital sector
v[61]=VS(input, "sector_rnd_revenue_proportion"); // R&D revenue proportion in intermediate sector

v[62]=VS(consumption, "sector_profits_distribution_rate"); // Profits distribution rate in consumption sector
v[63]=VS(capital, "sector_profits_distribution_rate"); // Profits distribution rate in capital sector
v[64]=VS(input, "sector_profits_distribution_rate"); // Profits distribution rate in intermediate sector

v[65]=VS(consumption, "sector_indirect_tax_rate"); // Indirect tax rate in consumption sector
v[66]=VS(capital, "sector_indirect_tax_rate"); // Indirect tax rate in capital sector
v[67]=VS(input, "sector_indirect_tax_rate"); // Indirect tax rate in intermediate sector

v[74]=v[41]+v[42]+v[43]; // Total number of firms
v[75]=v[41]/v[74]; // Sector share of consumption firms
v[76]=v[42]/v[74]; // Sector share of capital firms
v[77]=v[43]/v[74]; // Sector share of intermediate firms

v[100]=(v[49]*v[52]/v[46])/(1-v[49]*v[55]);	  // Intermediate sector price
v[101]=v[47]*((v[50]/v[44])+(v[100]*v[53]));  // Consumption sector price
v[102]=v[48]*((v[51]/v[45])+(v[100]*v[54]));  // Capital sector price

v[103]=(v[50]/v[44]) + v[59]*(1-v[65])*v[101];  // Sector effective wage margin over production including RND
v[104]=(v[51]/v[45]) + v[60]*(1-v[66])*v[102];  // Sector effective wage margin over production including RND
v[105]=(v[52]/v[46]) + v[61]*(1-v[67])*v[100];  // Sector effective wage margin over production including RND

v[106]=v[101]*(1-v[65])*(1-v[59])-((v[50]/v[44]) + v[53]*v[100]);  // Sector effective profit margin over production
v[107]=v[102]*(1-v[66])*(1-v[60])-((v[51]/v[45]) + v[54]*v[100]);  // Sector effective profit margin over production
v[108]=v[100]*(1-v[67])*(1-v[61])-((v[52]/v[46]) + v[55]*v[100]);  // Sector effective profit margin over production

v[109]=(v[101]*v[65] + v[26]*v[62]*v[106] + v[26]*v[103]) / (1 - v[26]);  // Sector effective tax-public wage (using avg tax v[26])
v[110]=(v[102]*v[66] + v[26]*v[63]*v[107] + v[26]*v[104]) / (1 - v[26]);  // Sector effective tax-public wage (using avg tax v[26])
v[111]=(v[100]*v[67] + v[26]*v[64]*v[108] + v[26]*v[105]) / (1 - v[26]);  // Sector effective tax-public wage (using avg tax v[26])

v[112]=(v[103] + v[109])*v[27] + (v[106]*v[62])*v[27];  // Sector effective imports propensity (using avg import prop v[27])
v[113]=(v[104] + v[110])*v[27] + (v[107]*v[63])*v[27];  // Sector effective imports propensity (using avg import prop v[27])
v[114]=(v[105] + v[111])*v[27] + (v[108]*v[64])*v[27];  // Sector effective imports propensity (using avg import prop v[27])

// Approximate domestic spending propensity
double avg_prop_spend_domestic = v[19] * (1 - v[27]); 

v[115]=((avg_prop_spend_domestic + (v[27]*v[75]))*(v[103]+v[109]) + (avg_prop_spend_domestic + (v[27]*v[75]))*v[106]*v[62]) / v[101]; //MODIFIED: sector effective consumption propensity (using avg spend/import)
v[116]=((avg_prop_spend_domestic + (v[27]*v[75]))*(v[104]+v[110]) + (avg_prop_spend_domestic + (v[27]*v[75]))*v[107]*v[63]) / v[101]; //MODIFIED: sector effective consumption propensity (using avg spend/import)
v[117]=((avg_prop_spend_domestic + (v[27]*v[75]))*(v[105]+v[111]) + (avg_prop_spend_domestic + (v[27]*v[75]))*v[108]*v[64]) / v[101]; //MODIFIED: sector effective consumption propensity (using avg spend/import)

v[118]=v[53] + ((v[27]*v[77]*(v[103]+v[109])) + (v[27]*v[77]*v[106]*v[62])) / v[100];  // Sector input tech coefficient (using avg import prop v[27])
v[119]=v[54] + ((v[27]*v[77]*(v[104]+v[110])) + (v[27]*v[77]*v[107]*v[63])) / v[100];  // Sector input tech coefficient (using avg import prop v[27])
v[120]=v[55] + ((v[27]*v[77]*(v[105]+v[111])) + (v[27]*v[77]*v[108]*v[64])) / v[100];  // Sector input tech coefficient (using avg import prop v[27])

v[121]=((v[27]*v[76]*(v[103]+v[109])) + (v[27]*v[76]*v[106]*v[62])) / v[102];  // Sector effective capital exports propensity (using avg import prop v[27])
v[122]=((v[27]*v[76]*(v[104]+v[110])) + (v[27]*v[76]*v[107]*v[63])) / v[102];  // Sector effective capital exports propensity (using avg import prop v[27])
v[123]=((v[27]*v[76]*(v[105]+v[111])) + (v[27]*v[76]*v[108]*v[64])) / v[102];  // Sector effective capital exports propensity (using avg import prop v[27])

v[124]=v[118] / (1 - v[120]);  // Sector direct and indirect input tech (uses modified v[118], v[120])
v[125]=v[119] / (1 - v[120]);  // Sector direct and indirect input tech (uses modified v[119], v[120])

v[126]=v[115] + v[117] * v[124];  // Sector effective direct and indirect propensity to consume (uses modified inputs)
v[127]=v[116] + v[117] * v[125];  // Sector effective direct and indirect propensity to consume (uses modified inputs)

v[128]=v[121] + v[123] * v[124];  // Sector effective direct and indirect capital propensity (uses modified inputs)
v[129]=v[122] + v[123] * v[125];  // Sector effective direct and indirect capital propensity (uses modified inputs)

//Begin Aggregate Calculations
v[141]=v[6]*v[41]/(1-v[126]-v[127]*v[128]/(1-v[129]));  // Consumption sector initial demand
v[142]=(v[141]*v[128])/(1-v[129]);  // Capital sector initial demand
v[143]=v[141]*v[124]+v[142]*v[125];  // Intermediate sector initial demand

v[144]=v[109]*v[141] + v[110]*v[142] + v[111]*v[143];  // Total taxes
v[145]=v[65]*v[101]*v[141] + v[66]*v[102]*v[142] + v[67]*v[100]*v[143];  // Indirect taxes
v[146]=v[103]*v[141] + v[104]*v[142] + v[105]*v[143] + v[144];  // Total wages including public
v[147]=v[106]*v[141] + v[107]*v[142] + v[108]*v[143];  // Total profits
v[148]=v[62]*v[106]*v[141] + v[63]*v[107]*v[142] + v[64]*v[108]*v[143];  // Distributed profits
v[149]=v[112]*v[141] + v[113]*v[142] + v[114]*v[143];  // Total imports
v[150]=v[146]+v[147]+v[145];  // GDP
v[151]=(v[141]*v[101]+v[142]*v[102]+v[143]*v[100])/(v[141]+v[142]+v[143]);  // Initial price index

v[152]=V("initial_firm_desired_debt_rate");			// Initial firm desired debt rate
v[153]=V("initial_firm_liquidity_preference");		// Initial firm liquidity preference

v[157]=V("scale_prod_cap"); // Scale production capacity
v[158]=V("scale_bank_pro"); // Scale bank profits
v[159]=V("scale_debt"); // Scale debt

//Begin Writting Macro Variables
		WRITELLS(country,"Country_Nominal_Exports", v[149], 0, 1); // Country nominal exports
		WRITELLS(country,"Country_Nominal_Imports", v[149], 0, 1); // Country nominal imports
		WRITELLS(country,"Country_Annual_Growth", 0, 0, 1); // Country annual growth (zero by definition, no growth initially)
		WRITELLS(country,"Country_Annual_Real_Growth", 0, 0, 1); // Country annual real growth (zero by definition, no growth initially)
		WRITELLS(country,"Country_Annual_Inflation", 0, 0, 1); // Country annual inflation
	for (i=1 ; i<=(V("annual_frequency")+1) ; i++) // for (annual period +1) lags
		{
		WRITELLS(country,"Country_Price_Index", v[151], 0, i); // writes Price_Index, all initial price index is 1
		WRITELLS(country,"Country_Consumer_Price_Index", v[101], 0, i); // writes Consumper_Price_Index, all initial price index is 1
		WRITELLS(country,"Country_Capital_Goods_Price", v[102], 0, i); // writes Capital_Goods_Price
		WRITELLS(country,"Country_Avg_Productivity", AVE("sector_initial_productivity"), 0, i); // writes Avg_Productivity
		}
	for (i=1 ; i<=(2*V("annual_frequency")) ; i++)                  												//for (2*annual_period) lags
		{
		WRITELLS(country,"Country_GDP", v[150], 0, i); // writes GDP
		WRITELLS(country,"Country_Real_GDP", (v[150]/v[151]), 0, i); // writes Real GDP (will be equal to nominal GDP because price index always begins as 1)
		}


//Calculate theoretical median income from distribution parameters (for single-pass propensity calculation)
v[168] = exp(v[21]);  // Theoretical median from log-normal wage distribution
v[169] = 0;  // Profit income median set to 0 (profits distributed during simulation)
v[170] = v[168] + v[169];  // Combined theoretical median income (wage only initially)

//Begin Writing Household Variables
CYCLE(cur, "HOUSEHOLDS") // Cycle through all households
{
    // Initialize household-specific parameters with random variations around base values
    v[163] = v[26];  // Flat tax rate for all households
    v[164] = max(0, min(1, v[27] * norm(1.0, 0.20)));  // Household-specific import propensity (normal distribution, ?=0.20)
    v[166] = max(0, min(1, v[31] * norm(1.0, 0.20)));  // Household-specific autonomous consumption adjustment (normal distribution, ?=0.20)

    // Generate initial income based on distributions defined earlier
    // Parameters read earlier: v[21]=wage_mean, v[22]=wage_stddev
    v[161] = lnorm(v[21], v[22]);  // Initial wage income for this household
    v[162] = 0;  // Initial profit income set to 0 (will be calculated during simulation using profit shares)

    // Calculate initial disposable income for this household
    v[167] = (v[161] + v[162]) * (1 - v[163]); // Income * (1 - household tax rate)
    
    // Calculate propensity to spend using single-pass algorithm
    v[168] = v[161] + v[162]; // Total gross income
    v[172] = v[168] / v[170];  // Relative income (1.0 = theoretical median household)
    
    // Income-inverse propensity relationship with proper bounds
    // Poor households (v[172] < 1) get higher propensity, rich households (v[172] > 1) get lower
    v[173] = 0.05 + 1.15 / (1 + v[172] * v[172]);  // Base propensity: ranges from ~1.2 (poor) to ~0.05 (rich)
    
    // Add individual heterogeneity around income-based baseline
    v[174] = v[173] * norm(1.0, 0.15);  // �15% individual variation around income-based baseline
    
    // Apply final bounds: minimum 0.05, maximum 1.3 (allows rare cases >1)
    v[175] = max(0.05, min(1.3, v[174]));

    // Initialize household lagged variables and stocks
    // Use v[101] = consumption sector price, Country_Total_Population = number of households, v[6]=total autonomous consumption scale
	for (i=1; i<=V("annual_frequency"); i++)		// Loop for each period in a year
		{
		WRITELLS(cur, "Household_Nominal_Disposable_Income", v[167], 0, i);    		// Set initial nominal income for each lag
		WRITELLS(cur, "Household_Real_Disposable_Income", (v[167]/v[101]), 0, i);   // Set initial real income for each lag
		}
    WRITELLS(cur, "Household_Avg_Nominal_Income", v[167], 0, 1);
    WRITELLS(cur, "Household_Avg_Real_Income", (v[167]/v[101]), 0, 1);
    WRITELLS(cur, "Household_Real_Autonomous_Consumption", v[6]/VS(country, "Country_Total_Population"), 0, 1); // Distribute total autonomous consumption evenly
    WRITELLS(cur, "Household_Liquidity_Preference", 0, 0, 1); 	// 0 initial liquidity preference
    WRITELLS(cur, "Household_Max_Debt_Rate", 0, 0, 1);      	// 0 initial max debt rate
    WRITELLS(cur, "Household_Debt_Rate", 0, 0, 1);              // 0, no debt initially
    WRITELLS(cur, "Household_Stock_Deposits", 0, 0, 1);         // 0 initial deposits
    WRITELLS(cur, "Household_Stock_Loans", 0, 0, 1);            // 0 initial loans

    // Store household-specific parameters for later use if needed
    WRITES(cur, "household_direct_tax", v[163]);
    WRITES(cur, "household_import_propensity", v[164]);
    WRITES(cur, "household_autonomous_consumption_adjustment", v[166]); // Store persistent autonomous consumption adjustment
    
    // Generate persistent household-specific liquidity preference adjustment parameter
    // Use normal distribution around the household average baseline for consistency
    v[178] = max(0, min(1, v[32] * norm(1.0, 0.6))); // +-60% individual variation around household_avg_liquidity_preference_adjustment
    WRITES(cur, "household_liquidity_preference_adjustment", v[178]); // Store persistent liquidity preference adjustment

    // Generate persistent household-specific debt rate adjustment parameter
    // Use normal distribution around the household average baseline for consistency
    v[179] = max(0, min(1, v[33] * norm(1.0, 0.4))); // +-40% individual variation around household_avg_debt_rate_adjustment
    WRITES(cur, "household_debt_rate_adjustment", v[179]); // Store persistent debt rate adjustment

    // Assign persistent skill to each household (log-normal distribution)
    v[100] = lnorm(v[29], v[30]);  // Set household_skill_mean = -0.5 * (household_skill_stddev)^2 to ensure E[household_skill] = 1
    WRITES(cur, "household_skill", v[100]); // household_skill, persistent
    
    // Initialize profit share coefficient using q-exponential distribution
    // Only a fraction of households participate in profit distribution
    v[176] = RND;  // Random draw for participation
    if (v[176] < v[250])  // v[250] = profit_participation_rate (e.g., 0.05 for 5%)
    {
        // This household participates in profits - use q-exponential distribution
        // Note: v[25] = profit_q (shape parameter), v[23] = profit_lambda (scale parameter)
		// FOR LATER: Add a simple equation that occasionally adjusts them (e.g., every few years)
		// Use a switch parameter to enable/disable dynamic adjustments
        v[177] = qexponential(v[25], v[23]);  // Generate q-exponential distributed profit share
        WRITES(cur, "household_profit_share", v[177]);
    }
    else
    {
        // This household does not participate in profits
        WRITES(cur, "household_profit_share", 0);
    }
}

// Normalize profit share coefficients to sum to 1
// This ensures that the total of all profit shares equals 1
    v[180] = SUMS(PARENT, "household_profit_share");  // Sum of all profit shares
if (v[180] > 0)  // Avoid division by zero
{
    CYCLE(cur, "HOUSEHOLDS")
    {
        v[181] = VS(cur, "household_profit_share");  // Get current profit share
        v[182] = v[181] / v[180];  // Normalize by dividing by total
        WRITES(cur, "household_profit_share", v[182]);  // Write normalized value
    }
}

//Begin Writing External Variables
WRITES(external, "Country_Trade_Balance", 0);
WRITES(external, "Country_Capital_Flows", 0);
WRITELLS(external, "External_Income",  v[150], 0, 1);
WRITELLS(external, "External_Income",  v[150], 0, 2);
WRITELLS(external, "Country_International_Reserves",  v[150]*V("annual_frequency"), 0, 1);											//writes initial external income equal to domestic GDP

//Begin Writing Government Variables																
v[168]=VS(government, "switch_government_composition");
v[169]=VS(government, "government_surplus_rate_target");
v[170]=VS(government, "government_initial_consumption_share");
v[171]=VS(government, "government_initial_capital_share");
v[172]=VS(government, "government_initial_input_share");
v[173]=v[170]+v[171]+v[172];

WRITELLS(government,"Government_Total_Taxes", v[144], 0, 1);														//write initial total taxes, initial total taxes is calculated in the demand calibration based only on parameters
WRITELLS(government,"Government_Max_Expenses", v[144], 0, 1);        									//initial max government expenses equals total taxes calculated in the calibration
if (v[168]!=2)
	WRITELLS(government,"Government_Desired_Wages", v[144], 0, 0);										//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity
if (v[168]==2)
	WRITELLS(government,"Government_Desired_Wages", (1-v[173])*v[144], 0, 0);		            		//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity		            				    
WRITELLS(government,"Government_Desired_Consumption", v[170]*v[144], 0, 0);		            		//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity	
WRITELLS(government,"Government_Desired_Investment", v[170]*v[144], 0, 0);		            			//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity	
WRITELLS(government,"Government_Desired_Inputs", v[172]*v[144], 0, 0);		            			    //initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity	
WRITELLS(government,"Government_Surplus_Rate_Target", v[169], 0, 1);
for (i=1 ; i<=V("annual_frequency")+1 ; i++)		              													//for (government_period) lags	
{
	WRITELLS(government,"Government_Debt", V("initial_debt_gdp")*V("annual_frequency")*v[150], 0, i);                  									//no debt initially																	//base interest rate parameter
	WRITELLS(government,"government_initial_debt_gdp_ratio", V("initial_debt_gdp"), 0, i);
	WRITELLS(government,"Government_Effective_Expenses", v[144], 0, i);
}

//Begin Writing Sector Variables
CYCLE(cur, "SECTORS")
{
	v[0]=VS(cur,"sector_investment_frequency"); 
	v[1]=VS(cur,"sector_price_frequency");	
	v[5]=VS(cur,"sector_capital_duration");
	v[201]=VS(cur, "id_consumption_goods_sector");
	v[202]=VS(cur, "id_capital_goods_sector");
	v[203]=VS(cur, "id_intermediate_goods_sector");
	
	v[205]=VS(cur,"sector_initial_productivity");
	v[206]=VS(cur,"sector_initial_markup");
	v[207]=VS(cur,"sector_initial_quality");
	v[209]=VS(cur,"sector_initial_wage");
	v[210]=VS(cur,"sector_input_tech_coefficient");
	v[211]=VS(cur,"sector_capital_output_ratio");
	v[212]=VS(cur,"sector_number_object_firms");
	v[213]=VS(cur,"sector_rnd_revenue_proportion");
	v[214]=VS(cur,"sector_profits_distribution_rate");
	v[215]=VS(cur,"sector_indirect_tax_rate");
	v[216]=VS(cur,"sector_exports_elasticity_income");
	v[217]=VS(cur,"sector_desired_inventories_proportion");	
	v[218]=VS(cur,"sector_desired_degree_capacity_utilization");
	
	if(v[201]==1)																				//if it is a consumption good sector
	{
		v[200]=v[141];																			//intial demand, production and sales
		v[204]=v[101];																			//initial price
		v[222]=v[200]*(1+v[217])/v[218];														//sector productive capacity
		v[223]=v[210]*v[200];
	}
	if(v[202]==1)																				//if it is a capital good sector
	{
		v[200]=v[142];																			//intial demand, production and sales
		v[204]=v[102];																			//initial price
		v[222]=v[157]*((v[41]*v[56]+v[42]*v[57]+v[43]*v[58])/v[0]);								//sector productive capacity, different for the capital good sector
		v[223]=v[210]*v[222];
	}
	if(v[203]==1)																				//if it is a intermediate goods sector
	{
		v[200]=v[143];																			//initial demand production and sales
		v[204]=v[100];																			//initial price
		v[222]=v[200]*(1+v[217])/v[218];														//sector productive capacity
		v[223]=v[210]*v[200];
	}

	
	v[219]=v[222]*v[211]/v[212];																//number of capital goods of each firm
	v[220]=v[204]*((v[149]*v[212]/v[74])/(pow(v[150], v[216])));								//calculate sector exports coefficient
	v[221]=(1+v[217])*v[211]/v[218];
	//v[222]=SEARCH_INSTS(root, cur);	
	
	for (i=1 ; i<=v[0] ; i++)																	//for (investment_period) lags 
		{
		WRITELLS(cur, "Sector_Demand_Met", 1, 0, i); 										    //it is assumed that all demand is met initially. Equals 1 by definition
		WRITELLS(cur, "Sector_Demand_Met_By_Imports", 1, 0, i);                      			//it is assumed thatt all imports are met initially. Equals 1 by definition
		WRITELLS(cur, "Sector_Effective_Orders", v[200], 0, i);               					//Effective_Orders_Sectors equals demand_initial
		}		
	for (i=1 ; i<=(V("annual_frequency")+1) ; i++)                        		 								//for (class_period+1) lags
		{
		WRITELLS(cur, "Sector_Avg_Quality", 1, 0, i);               							//Effective_Orders_Sectors equals demand_initial
		WRITELLS(cur, "Sector_Employment", v[200]/v[205], 0, i);               					//Effective_Orders_Sectors equals demand_initial
		WRITELLS(cur, "Sector_Avg_Price", v[204], 0, i);                                   		//Avg_Price equals avg_price initial
		}
		WRITELLS(cur, "Sector_Productive_Capacity_Available", 0, 0, 1);                  		//it is assumed that there is no entry or exit initially. Equals 0 by definition
		WRITELLS(cur, "Sector_Avg_Competitiveness", 1, 0, 1);                     				//if all firms are the same, equals 1 by definition
		WRITELLS(cur, "Sector_External_Price", v[204], 0, 1);                               	//Foreign_Price equals foreign_price initial
		WRITELLS(cur, "Sector_Avg_Productivity", v[205], 0,  1);               	 				//If all firms are the same, Avg Productivity will be the initial productivivity for all firms
		WRITELLS(cur, "Sector_Max_Productivity", v[205], 0,  1);                      			//If all capital goods have the same productivity, Max_Productivity equals productivity_initial 
		WRITELLS(cur, "Sector_Max_Quality", 1, 0, 1);
		WRITELLS(cur, "Sector_Inventories", (v[200]*v[217]), 0, 1);                  			//Firms operate with desired level of inventories, thus, Current stock of inventories is the desired level times effective production
		WRITELLS(cur, "Sector_Productive_Capacity", v[222], 0, 1);								//All firms start operating at desired degree of utilization, thus, productive capacity is endogenous calculated based on effective production and desired degree
		WRITELLS(cur, "Sector_Real_Exports", (v[149]/3), 0, 1);										//Total exports are divided equally among sectors.
		WRITES(cur, "sector_initial_price", v[204]);
		WRITES(cur, "sector_exports_coefficient", v[220]);										//write the exports coefficient, assuming external price and foreign price starts as 1, so the exchange rate
	
	cur1=SEARCHS(cur, "FIRMS");																	//search the first and only instance of firms below each sector
		//Begin Writting Firm Parameters
		WRITES(cur1, "firm_date_birth", 0);                                   					//zero by definition
		
		//Begin Writting Independent Firm Variables
	for (i=1 ; i<=v[0] ; i++)                                									//for (investment_period) lags
	  	{
	  	WRITELLS(cur1, "Firm_Demand_Productive_Capacity_Replacement", 0, 0, i);					//no replacement initially
	  	WRITELLS(cur1, "Firm_Debt_Rate", 0, 0, i);												//no debt initially
	  	WRITELLS(cur1, "Firm_Demand_Capital_Goods", 0, 0, i);
	  	WRITELLS(cur1, "Firm_Frontier_Productivity", v[205], 0, i);                 			//frontier productivity will be the initial frontier productivity
	  	WRITELLS(cur1, "Firm_Max_Productivity", v[205], 0, i);        							//max capital goods productivity will be the initial frontier productivity that will be the same for all capital goods
	  	WRITELLS(cur1, "Firm_Avg_Productivity", v[205], 0, i);									//firm's avg productivity will be the initial frontier productivity since all capital goods have the same productivity
		WRITELLS(cur1, "Firm_Capacity_Utilization", v[218], 0, i);}
	for(i=1; i<=(v[0]+1); i++)										 							//for (investment period+1) lags (7)
		{
		WRITELLS(cur1, "Firm_Productive_Capacity_Depreciation", 0, 0, i);  						//write 0 
		WRITELLS(cur1, "Firm_Demand_Productive_Capacity_Expansion", 0, 0, i);     				//write 0 
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Expansion", 0, 0, i);     					//write 0
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Replacement", 0, 0, i);     					//write 0
		WRITELLS(cur1, "Firm_Effective_Orders_Capital_Goods", 0, 0, i);  						//write 0 
		}
	for (i=1 ; i<=(2*v[0]) ; i++)																//for (2*investment period+1) lags
	  	WRITELLS(cur1, "Firm_Effective_Orders", (v[200]/v[212]), 0, i);                    		//firm's effective orders will be sector's effective orders (given by demand_initial) divided by the number of firms
	for (i=1 ; i<=(v[1]+1) ; i++)																//for (markup_period-1) lags
		{
		WRITELLS(cur1, "Firm_Market_Share", (1/v[212]), 0, i);             						//firm's market share will be the inverse of the number of firms in the sector (initial market share)
	  	WRITELLS(cur1, "Firm_Potential_Markup", v[206], 0, i);                      			//potential markup will be the initial markup
		}
		WRITELLS(cur1, "Firm_Effective_Market_Share", (1/v[212]), 0, 1);                    	//firm's effective market share will be the initial market share       
	  	WRITELLS(cur1, "Firm_Desired_Market_Share", (1/v[212]), 0, 1);                  		//firm's desired market share will be twice the initial market share  
	  	WRITELLS(cur1, "Firm_Avg_Market_Share", (1/v[212]), 0, 1);                     			//firm's avg market share will be the initial market share
	  	WRITELLS(cur1, "Firm_Price", v[204], 0, 1);                                      		//firm's price will be the initial price of the sector, the same for all firms
	  	WRITELLS(cur1, "Firm_Avg_Potential_Markup", v[206], 0, 1);								//avg potential markup will be the initial markup
	  	WRITELLS(cur1, "Firm_Desired_Markup", v[206], 0, 1); 									//desired markup will be the initial markup
	  	WRITELLS(cur1, "Firm_Sales", (v[200]/v[212]), 0, 1);									//firm's sales will be equal to effective orders, no delivery delay
	  	WRITELLS(cur1, "Firm_Revenue", (v[204]*v[200]/v[212]), 0, 1);                           //firm's revenue will be the firm's sales times firm price
	  	WRITELLS(cur1, "Firm_Stock_Inventories", ((v[200]/v[212])*v[217]), 0, 1);               //firm's inventories will be the sales times the desired inventories proportion (parameter)
	  	WRITELLS(cur1, "Firm_Stock_Inputs", v[223]/v[212], 0, 1);                    			//firm's stock of imputs will be the sales times the input tech relationship
	  	WRITELLS(cur1, "Firm_Productive_Capacity", v[222]/v[212], 0, 1);						//firm productive capacity will be the sales divided by the desired degree of capacity utlization (parameter)
	  	WRITELLS(cur1, "Firm_Capital", (v[219]*v[102]), 0, 1);									//firm nominal capital equals number of capital if capital goods price equals 1
	  	WRITELLS(cur1, "Firm_Wage", v[209], 0, 1); 												//firm's nominal wage equals sector nominal wage initial
		WRITELLS(cur1, "Firm_Variable_Cost", ((v[209]/v[205])+v[210]*v[100]), 0, 1);			//firm variable cost equals unitary wage plus unitary cost of inputs. The last equals the tech coefficient if input price equals 1
		WRITELLS(cur1, "Firm_Competitiveness", 1, 0, 1);                           				//if all firms are the same
	  	WRITELLS(cur1, "Firm_Delivery_Delay", 1, 0, 1);                           		  		//it is assumed that all demand is met initially, so equals 1 by definition
		WRITELLS(cur1, "Firm_Stock_Deposits", 0, 0, 1);											//no financial assets initially
	  	WRITELLS(cur1, "Firm_Stock_Loans", v[159]*(v[219]*v[102]), 0, 1);                       //no debt initially
	  	WRITELLS(cur1, "Firm_Avg_Debt_Rate", v[159], 0, 1);                       				//no debt initially
	  	WRITELLS(cur1, "Firm_Max_Debt_Rate", v[152], 0, 1);                       			//no debt initially
	  	WRITELLS(cur1, "Firm_Liquidity_Preference", v[153], 0, 1);                       		//no debt initially
		
	  		//Begin writting Capital Goods Variables and parameters
	  		cur2=SEARCHS(cur1, "CAPITALS");														//search the first and only instance of capital below firms
	  		WRITELLS(cur2, "Capital_Good_Acumulated_Production", 0, 0, 1);      				//zero by definition
			WRITES(cur2, "capital_good_productive_capacity", (1/v[211]));     					//inverse of capital output ratio  
			WRITES(cur2, "capital_good_productivity_initial", v[205]);       		  			//defined in the control parameters
			WRITES(cur2, "capital_good_to_replace", 0);
			WRITES(cur2, "id_capital_good_number", 1);                       					//1 for the first and only initial firm (the others will be created below)
	 			
	 	//Begin Creating Firms and writting some parameters
	 	for(i=1; i<=(v[212]-1); i++)															//for the number of firms of each sector (defined by the parameter)
	 	cur4=ADDOBJ_EXLS(cur,"FIRMS", cur1, 0);                             					//create new firm using the first and only firm as example
	 			
	 	CYCLES(cur, cur1, "FIRMS")                                                 				//CYCLE trough all firms
			{
			v[230]=SEARCH_INSTS(cur, cur1);														//search current firm position in the total economy
			WRITES(cur1, "firm_id", v[230]);                         					//write the firm number as the current position (only initial difference between firms)
			//WRITES(cur1, "firm_bank",(uniform_int(1, v[40])));								//firm's bank identifier
			v[225]=v[230]/(v[212]/v[40]);
			v[226]=round(v[225]);
			if(v[226]<v[225])
				v[227]=v[226]+1;
			else
				v[227]=v[226];
			WRITES(cur1, "firm_bank", v[227]);
			v[231]=fmod((double) (v[230]+v[0]), v[0]);                                 			//divide the firm's number plus investment period by the investment period and takes the rest (possible results if investment period =6 are 0, 5, 4, 3, 2, 1)
			
			//Begin creating capital goods and writting "capital_good_date_birth"		
			for(i=1; i<=(v[219]-1); i++)                        								//for the number of capital goods of each firm
			{
			cur2=SEARCHS(cur1, "CAPITALS");                                         			//search the first and only capital good of each firm
			cur3=ADDOBJ_EXLS(cur1,"CAPITALS", cur2, 0);			                       			//create new capital goods using the first one as example
			WRITES(cur3, "id_capital_good_number", (i+1));										//write the capital good number
			}
			CYCLES(cur1, cur5, "CAPITALS")                                            			//CYCLE trough all capital goods
				{
				v[232]=VS(cur5, "id_capital_good_number");
				v[233]=(-v[5]+v[231]+1)+(v[232]-1)*v[0];                                  		//calculates the capital good date of birth based on the firm number and the number of the capital good
				v[224]=uniform_int(30, 60);
				WRITES(cur5, "capital_good_date_birth", 0);										//write the capital good date of birth
				WRITES(cur5, "capital_good_depreciation_period", v[224]);
				}
			}					
}

//Begin Writting Bank Variables
	v[250]=VS(financial, "cb_annual_real_interest_rate");
	v[251]=VS(financial, "fs_spread_deposits");
	v[252]=VS(financial, "fs_spread_short_term");
	v[253]=VS(financial, "fs_spread_long_term");
	v[254]=VS(financial, "cb_target_annual_inflation");

	WRITELLS(financial, "Central_Bank_Basic_Interest_Rate", v[250]+v[254], 0, 1);
	WRITELLS(financial, "Financial_Sector_Avg_Competitiveness", 1, 0, 1);
	WRITELLS(financial, "Financial_Sector_Avg_Interest_Rate_Long_Term", (v[253]+v[250]+v[254]), 0, 1);
	WRITELLS(financial, "Financial_Sector_Avg_Interest_Rate_Short_Term", (v[252]+v[250]+v[254]), 0, 1);
	
	cur1=SEARCHS(financial, "BANKS");
	for(i=1; i<=(v[40]-1); i++)																//for the number of firms of each sector (defined by the parameter)
	 	cur4=ADDOBJ_EXLS(financial,"BANKS", cur1, 0);
	CYCLES(financial, cur1, "BANKS")                                                 				//CYCLE trough all firms
		{
		v[255]=SEARCH_INSTS(root, cur1);													//search current firm position in the total economy
		WRITES(cur1, "bank_id", v[255]); 
		if(v[255]==1)
			WRITES(cur1, "id_public_bank", 0);
		else
			WRITES(cur1, "id_public_bank", 0);
		//WRITES(cur1, "fragility_sensitivity", uniform(0.5, 1.5));
		//WRITES(cur1, "default_sensitivity", uniform(0.5, 1.5));
		WRITELLS(cur1, "Bank_Market_Share", (1/v[40]), 0, 1); 
		WRITELLS(cur1, "Bank_Competitiveness", 1, 0, 1);
		WRITELLS(cur1, "Bank_Accumulated_Profits", v[158]*((v[41]+v[42]+v[43])/v[40]), 0, 1);
		WRITELLS(cur1, "Bank_Demand_Met", 1, 0, 1);
		WRITELLS(cur1, "Bank_Desired_Long_Term_Spread", v[253], 0, 1);
		WRITELLS(cur1, "Bank_Desired_Short_Term_Spread", v[252], 0, 1);
		WRITELLS(cur1, "Bank_Interest_Rate_Long_Term", (v[253]+v[250]+v[254]), 0, 1);
		WRITELLS(cur1, "Bank_Interest_Rate_Short_Term", (v[252]+v[250]+v[254]), 0, 1);
		}


PARAMETER
RESULT(0)
