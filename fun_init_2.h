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
It is set in a specific simple configuration: 3 sectors and 3 income classes. Next step is to generalize this variable for N sectors.
Additionally, there is a strong hypothesis here: all sector are equals, except for how their demand is calculated.
*/

//Define Global Pointers
country=SEARCH("COUNTRY");
external=SEARCH("EXTERNAL_SECTOR");
government=SEARCH("GOVERNMENT");
financial=SEARCH("FINANCIAL");
consumption=SEARCH_CND("id_consumption_goods_sector",1);
capital=SEARCH_CND("id_capital_goods_sector",1);
input=SEARCH_CND("id_intermediate_goods_sector",1);


//Macro Parameters			
v[6]=V("scale_autonomous_consumption");

//Household Parameters
v[20]=V("number_of_households"); // Total number of households
v[21]=V("wage_mean");            // Mean of log-normal wage distribution
v[22]=V("wage_stddev");          // Standard deviation of wage distribution
v[23]=V("profit_lambda");        // Scale parameter for q-exponential distribution
v[25]=V("profit_q");             // Entropic index for q-exponential distribution (0 < q < 2)
v[250]=V("profit_participation_rate"); // Fraction of households receiving profits (e.g., 0.05)
v[26]=V("household_direct_tax"); // Base tax rate for households
v[27]=V("household_initial_propensity_import"); // Base import propensity
v[28]=V("household_import_elasticity_price");   // Price elasticity of imports
// Set household_skill_mean = -0.5 * (household_skill_stddev)^2 to ensure E[household_skill] = 1
v[29]=V("household_skill_mean");   // Mean parameter for household skill log-normal distribution
v[30]=V("household_skill_stddev"); // Standard deviation parameter for household skill log-normal distribution
v[19]=V("avg_propensity_to_spend"); // Average propensity to spend for approximation


cur1=SEARCH_CND("id_consumption_goods_sector",1);
cur2=SEARCH_CND("id_capital_goods_sector",1);
cur3=SEARCH_CND("id_intermediate_goods_sector",1);

v[40]=V("fs_number_object_banks");																			//sector control parameter

v[41]=VS(consumption, "sector_number_object_firms");													//sector control parameter
v[42]=VS(capital, "sector_number_object_firms");														//sector control parameter
v[43]=VS(input, "sector_number_object_firms");															//sector control parameter

v[44]=VS(consumption, "sector_initial_productivity");													//sector control parameter
v[45]=VS(capital, "sector_initial_productivity");														//sector control parameter
v[46]=VS(input, "sector_initial_productivity");															//sector control parameter

v[47]=VS(consumption, "sector_initial_markup");															//sector control parameter
v[48]=VS(capital, "sector_initial_markup");																//sector control parameter
v[49]=VS(input, "sector_initial_markup");																//sector control parameter

v[50]=VS(consumption, "sector_initial_wage");															//sector control parameter
v[51]=VS(capital, "sector_initial_wage");																//sector control parameter
v[52]=VS(input, "sector_initial_wage");																	//sector control parameter

v[53]=VS(consumption, "sector_input_tech_coefficient");													//sector control parameter
v[54]=VS(capital, "sector_input_tech_coefficient");														//sector control parameter
v[55]=VS(input, "sector_input_tech_coefficient");														//sector control parameter

v[56]=VS(consumption, "sector_capital_output_ratio");													//sector control parameter
v[57]=VS(capital, "sector_capital_output_ratio");														//sector control parameter
v[58]=VS(input, "sector_capital_output_ratio");															//sector control parameter

v[59]=VS(consumption, "sector_rnd_revenue_proportion");													//sector control parameter
v[60]=VS(capital, "sector_rnd_revenue_proportion");														//sector control parameter
v[61]=VS(input, "sector_rnd_revenue_proportion");														//sector control parameter

v[62]=VS(consumption, "sector_profits_distribution_rate");												//sector control parameter
v[63]=VS(capital, "sector_profits_distribution_rate");													//sector control parameter
v[64]=VS(input, "sector_profits_distribution_rate");													//sector control parameter

v[65]=VS(consumption, "sector_indirect_tax_rate");														//sector control parameter
v[66]=VS(capital, "sector_indirect_tax_rate");															//sector control parameter
v[67]=VS(input, "sector_indirect_tax_rate");															//sector control parameter

v[74]=v[41]+v[42]+v[43];																		//total number of firms
v[75]=v[41]/v[74];																				//sector share of firms
v[76]=v[42]/v[74];																				//sector share of firms
v[77]=v[43]/v[74];																				//sector share of firms

v[100]=(v[49]*v[52]/v[46])/(1-v[49]*v[55]);														//intermediate sector price
v[101]=v[47]*((v[50]/v[44])+(v[100]*v[53]));													//consumption sector price
v[102]=v[48]*((v[51]/v[45])+(v[100]*v[54]));													//capital sector price

v[103]=(v[50]/v[44]) + v[59]*(1-v[65])*v[101];													//sector effective wage margin over production including RND
v[104]=(v[51]/v[45]) + v[60]*(1-v[66])*v[102];													//sector effective wage margin over production including RND
v[105]=(v[52]/v[46]) + v[61]*(1-v[67])*v[100];													//sector effective wage margin over production including RND

v[106]=v[101]*(1-v[65])*(1-v[59])-((v[50]/v[44]) + v[53]*v[100]);								//sector effective profit margin over production
v[107]=v[102]*(1-v[66])*(1-v[60])-((v[51]/v[45]) + v[54]*v[100]);								//sector effective profit margin over production
v[108]=v[100]*(1-v[67])*(1-v[61])-((v[52]/v[46]) + v[55]*v[100]);								//sector effective profit margin over production

v[109]=(v[101]*v[65] + v[26]*v[62]*v[106] + v[26]*v[103]) / (1 - v[26]);							//MODIFIED: sector effective tax-public wage (using avg tax v[26])
v[110]=(v[102]*v[66] + v[26]*v[63]*v[107] + v[26]*v[104]) / (1 - v[26]);							//MODIFIED: sector effective tax-public wage (using avg tax v[26])
v[111]=(v[100]*v[67] + v[26]*v[64]*v[108] + v[26]*v[105]) / (1 - v[26]);							//MODIFIED: sector effective tax-public wage (using avg tax v[26])

v[112]=(v[103] + v[109])*v[27] + (v[106]*v[62])*v[27];											//MODIFIED: sector effective imports propensity (using avg import prop v[27])
v[113]=(v[104] + v[110])*v[27] + (v[107]*v[63])*v[27];											//MODIFIED: sector effective imports propensity (using avg import prop v[27])
v[114]=(v[105] + v[111])*v[27] + (v[108]*v[64])*v[27];											//MODIFIED: sector effective imports propensity (using avg import prop v[27])

// Approximate domestic spending propensity
double avg_prop_spend_domestic = v[19] * (1 - v[27]);

v[115]=((avg_prop_spend_domestic + (v[27]*v[75]))*(v[103]+v[109]) + (avg_prop_spend_domestic + (v[27]*v[75]))*v[106]*v[62]) / v[101]; //MODIFIED: sector effective consumption propensity (using avg spend/import)
v[116]=((avg_prop_spend_domestic + (v[27]*v[75]))*(v[104]+v[110]) + (avg_prop_spend_domestic + (v[27]*v[75]))*v[107]*v[63]) / v[101]; //MODIFIED: sector effective consumption propensity (using avg spend/import)
v[117]=((avg_prop_spend_domestic + (v[27]*v[75]))*(v[105]+v[111]) + (avg_prop_spend_domestic + (v[27]*v[75]))*v[108]*v[64]) / v[101]; //MODIFIED: sector effective consumption propensity (using avg spend/import)

v[118]=v[53] + ((v[27]*v[77]*(v[103]+v[109])) + (v[27]*v[77]*v[106]*v[62])) / v[100];				//MODIFIED: sector input tech coefficient (using avg import prop v[27])
v[119]=v[54] + ((v[27]*v[77]*(v[104]+v[110])) + (v[27]*v[77]*v[107]*v[63])) / v[100];				//MODIFIED: sector input tech coefficient (using avg import prop v[27])
v[120]=v[55] + ((v[27]*v[77]*(v[105]+v[111])) + (v[27]*v[77]*v[108]*v[64])) / v[100];				//MODIFIED: sector input tech coefficient (using avg import prop v[27])

v[121]=((v[27]*v[76]*(v[103]+v[109])) + (v[27]*v[76]*v[106]*v[62])) / v[102];						//MODIFIED: sector effective capital exports propensity (using avg import prop v[27])
v[122]=((v[27]*v[76]*(v[104]+v[110])) + (v[27]*v[76]*v[107]*v[63])) / v[102];						//MODIFIED: sector effective capital exports propensity (using avg import prop v[27])
v[123]=((v[27]*v[76]*(v[105]+v[111])) + (v[27]*v[76]*v[108]*v[64])) / v[102];						//MODIFIED: sector effective capital exports propensity (using avg import prop v[27])

v[124]=v[118] / (1 - v[120]);																		//sector direct and indirect input tech (uses modified v[118], v[120])
v[125]=v[119] / (1 - v[120]);																		//sector direct and indirect input tech (uses modified v[119], v[120])

v[126]=v[115] + v[117] * v[124];																	//sector effective direct and indirect propensity to consume (uses modified inputs)
v[127]=v[116] + v[117] * v[125];																	//sector effective direct and indirect propensity to consume (uses modified inputs)

v[128]=v[121] + v[123] * v[124];																	//sector effective direct and indirect capital propensity (uses modified inputs)
v[129]=v[122] + v[123] * v[125];																	//sector effective direct and indirect capital propensity (uses modified inputs)

//Begin Aggregate Calculations
v[141]=v[6]*v[41]/(1-v[126]-v[127]*v[128]/(1-v[129]));				//consumption sector initial demand
v[142]=(v[141]*v[128])/(1-v[129]);									//capital sector initial demand
v[143]=v[141]*v[124]+v[142]*v[125];									//intermediate sector initial demand

v[144]=v[109]*v[141] + v[110]*v[142] + v[111]*v[143];							 				//total taxes
v[145]=v[65]*v[101]*v[141] + v[66]*v[102]*v[142] + v[67]*v[100]*v[143];							//indirect taxes
v[146]=v[103]*v[141] + v[104]*v[142] + v[105]*v[143] + v[144];									//total wages including public
v[147]=v[106]*v[141] + v[107]*v[142] + v[108]*v[143];							 				//total profits
v[148]=v[62]*v[106]*v[141] + v[63]*v[107]*v[142] + v[64]*v[108]*v[143];							//distributed profits
v[149]=v[112]*v[141] + v[113]*v[142] + v[114]*v[143];											//total imports
v[150]=v[146]+v[147]+v[145];																	//GDP
v[151]=(v[141]*v[101]+v[142]*v[102]+v[143]*v[100])/(v[141]+v[142]+v[143]);						//initial price index

v[152]=V("initial_firm_desired_debt_rate");
v[153]=V("initial_firm_liquidity_preference");
v[155]=V("household_initial_max_debt_rate");
v[156]=V("household_initial_liquidity_preference");

v[157]=V("scale_prod_cap");
v[158]=V("scale_bank_pro");
v[159]=V("scale_debt");

//Begin Writting Macro Variables
		WRITELLS(country,"Country_Nominal_Exports", v[149], 0, 1);
		WRITELLS(country,"Country_Nominal_Imports", v[149], 0, 1);
		WRITELLS(country,"Country_Annual_Growth", 0, 0, 1);													//zero by definition, no growth initally
		WRITELLS(country,"Country_Annual_Real_Growth", 0, 0, 1);                 							//zero by definition, no growth initally
		WRITELLS(country,"Country_Annual_Inflation", 0, 0, 1);	
	for (i=1 ; i<=(V("annual_frequency")+1) ; i++)                  												//for (annual period +1) lags
		{
		WRITELLS(country,"Country_Price_Index", v[151], 0, i);									 			//writes Price_Index, all initial price index is 1
		WRITELLS(country,"Country_Consumer_Price_Index", v[101], 0, i);          							//writes Consumper_Price_Index, all initial price index is 1
		WRITELLS(country,"Country_Capital_Goods_Price", v[102], 0, i);
		WRITELLS(country,"Country_Avg_Productivity", AVE("sector_initial_productivity"), 0, i);
		}
	for (i=1 ; i<=(2*V("annual_frequency")) ; i++)                  												//for (2*annual_period) lags
		{
		WRITELLS(country,"Country_GDP", v[150], 0, i);                     	 								//GDP
		WRITELLS(country,"Country_Real_GDP", (v[150]/v[151]), 0, i);                  						//Real GDP will be equal to nominal GDP because price index always begins as 1
		}


//Calculate theoretical median income from distribution parameters (for single-pass propensity calculation)
v[168] = exp(v[21]);  // Theoretical median from log-normal wage distribution
v[169] = 0;  // Profit income median set to 0 (profits distributed during simulation)
v[170] = v[168] + v[169];  // Combined theoretical median income (wage only initially)

//Begin Writing Household Variables
CYCLE(cur, "HOUSEHOLDS")
{
    // Initialize household-specific parameters with random variations around base values
    // Base values read earlier: v[26]=tax, v[27]=import_prop, v[28]=import_elast
    v[163] = v[26];  // Flat tax rate for all households
    v[164] = max(0, min(1, v[27] * norm(1.0, 0.20)));  // Household-specific import propensity (normal distribution, σ=0.20)
    v[165] = max(0.1, min(2.0, v[28] * norm(1.0, 0.25)));  // Household-specific price elasticity (normal distribution, σ=0.25, realistic bounds)

    // Generate initial income based on distributions defined earlier
    // Parameters read earlier: v[21]=wage_mean, v[22]=wage_stddev
    v[161] = lnorm(v[21], v[22]);  // Initial wage income for this household
    v[162] = 0;  // Initial profit income set to 0 (will be calculated during simulation using profit shares)

    // Calculate initial disposable income for this household
    v[166] = (v[161] + v[162]) * (1 - v[163]); // Income * (1 - household tax rate)
    
    // Calculate propensity to spend using single-pass algorithm
    v[167] = v[161] + v[162]; // Total gross income
    v[171] = v[167] / v[170];  // Relative income (1.0 = theoretical median household)
    
    // Income-inverse propensity relationship with proper bounds
    // Poor households (v[171] < 1) get higher propensity, rich households (v[171] > 1) get lower
    v[172] = 0.05 + 1.15 / (1 + v[171] * v[171]);  // Base propensity: ranges from ~1.2 (poor) to ~0.05 (rich)
    
    // Add individual heterogeneity around income-based baseline
    v[173] = v[172] * norm(1.0, 0.15);  // ±15% individual variation around income-based baseline
    
    // Apply final bounds: minimum 0.05, maximum 1.3 (allows rare cases >1)
    v[174] = max(0.05, min(1.3, v[173]));

    // Initialize household lagged variables and stocks
    // Use v[101] = consumption sector price, v[20] = number of households, v[6]=total autonomous consumption scale
    // Use v[155]=initial max debt rate, v[156]=initial liquidity preference
	for (i=1; i<=V("annual_frequency"); i++)		// Loop for each period in a year
		{
		WRITELLS(cur, "Household_Nominal_Disposable_Income", v[166], 0, i);    		// Set initial nominal income for each lag
		WRITELLS(cur, "Household_Real_Disposable_Income", (v[166]/v[101]), 0, i);   // Set initial real income for each lag
		}
    WRITELLS(cur, "Household_Avg_Nominal_Income", v[166], 0, 1);
    WRITELLS(cur, "Household_Avg_Real_Income", (v[166]/v[101]), 0, 1);
    WRITELLS(cur, "Household_Real_Autonomous_Consumption", v[6]/v[20], 0, 1); // Distribute total autonomous consumption evenly
    WRITELLS(cur, "Household_Liquidity_Preference", v[156], 0, 1); // Use global initial value
    WRITELLS(cur, "Household_Max_Debt_Rate", v[155], 0, 1);      // Use global initial value
    WRITELLS(cur, "Household_Debt_Rate", 0, 0, 1);              // 0, no debt initially
    WRITELLS(cur, "Household_Stock_Deposits", 0, 0, 1);         // 0 initial deposits
    WRITELLS(cur, "Household_Stock_Loans", 0, 0, 1);            // 0 initial loans

    // Store household-specific parameters for later use if needed
    WRITES(cur, "household_direct_tax", v[163]);
    WRITES(cur, "household_import_propensity", v[164]);
    WRITES(cur, "household_import_elasticity", v[165]);
    WRITES(cur, "household_propensity_baseline", v[174]); // Store calculated propensity baseline

    // Assign persistent skill to each household (log-normal distribution)
    v[100] = lnorm(v[29], v[30]);  // Set household_skill_mean = -0.5 * (household_skill_stddev)^2 to ensure E[household_skill] = 1
    WRITES(cur, "household_skill", v[100]); // household_skill, persistent
    
    // Initialize profit share coefficient using q-exponential distribution
    // Only a fraction of households participate in profit distribution
    v[175] = RND;  // Random draw for participation
    if (v[175] < v[250])  // v[250] = profit_participation_rate (e.g., 0.05 for 5%)
    {
        // This household participates in profits - use q-exponential distribution
        // Note: v[25] = profit_q (shape parameter), v[23] = profit_lambda (scale parameter)
		// FOR LATER: Add a simple equation that occasionally adjusts them (e.g., every few years)
		// Use a switch parameter to enable/disable dynamic adjustments
        v[176] = qexponential(v[25], v[23]);  // Generate q-exponential distributed profit share
        WRITES(cur, "household_profit_share", v[176]);
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

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// INITIALIZATION 2 ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

EQUATION("Initialization_2")

consumption=SEARCH_CND("id_consumption_goods_sector",1);
capital=SEARCH_CND("id_capital_goods_sector",1);
input=SEARCH_CND("id_intermediate_goods_sector",1);
government=SEARCH("GOVERNMENT");
financial=SEARCH("FINANCIAL");
external=SEARCH("EXTERNAL_SECTOR");
country=SEARCH("COUNTRY");
centralbank=SEARCH("CENTRAL_BANK");

//COUNTRY PARAMETERS
v[0]=VS(country, "annual_frequency");
v[1]=VS(country, "country_initial_depreciation_share_GDP");
v[2]=VS(country, "country_initial_government_share_GDP");
v[3]=VS(country, "country_initial_exports_share_GDP");
//CONSUMPTION PARAMETERS
v[10]=VS(consumption, "sector_initial_depreciation_scale");
v[11]=VS(consumption, "sector_investment_frequency");
v[12]=VS(consumption, "sector_number_object_firms");
v[13]=VS(consumption, "sector_initial_price");
v[14]=VS(consumption, "sector_input_tech_coefficient");
v[15]=VS(consumption, "sector_initial_propensity_import_inputs");
v[16]=VS(consumption, "sector_initial_exports_share");
v[17]=VS(consumption, "sector_initial_external_price");
//CAPITAL PARAMETERS
v[20]=VS(capital, "sector_initial_depreciation_scale");
v[21]=VS(capital, "sector_investment_frequency");
v[22]=VS(capital, "sector_number_object_firms");
v[23]=VS(capital, "sector_initial_price");
v[24]=VS(capital, "sector_input_tech_coefficient");
v[25]=VS(capital, "sector_initial_propensity_import_inputs");
v[26]=VS(capital, "sector_initial_exports_share");
v[27]=VS(capital, "sector_initial_external_price");
//INPUT PARAMETERS
v[30]=VS(input, "sector_initial_depreciation_scale");
v[31]=VS(input, "sector_investment_frequency");
v[32]=VS(input, "sector_number_object_firms");
v[33]=VS(input, "sector_initial_price");
v[34]=VS(input, "sector_input_tech_coefficient");
v[35]=VS(input, "sector_initial_propensity_import_inputs");
v[36]=VS(input, "sector_initial_exports_share");
v[37]=VS(input, "sector_initial_external_price");
//EXTERNAL SECTOR PARAMETERS
v[40]=VS(external, "external_interest_rate");
v[41]=VS(external, "initial_external_income_scale");
v[42]=VS(external, "external_capital_flow_adjustment");
v[43]=VS(external, "initial_reserves_ratio");
v[44]=VS(external, "initial_exchange_rate");
//FINANCIAL PARAMETERS
v[50]=VS(financial, "cb_annual_real_interest_rate");
v[51]=VS(financial, "fs_initial_leverage");
v[52]=VS(financial, "fs_spread_deposits");
v[53]=VS(financial, "fs_spread_short_term");
v[54]=VS(financial, "fs_spread_long_term");
v[55]=VS(financial, "fs_risk_premium_short_term");
v[56]=VS(financial, "fs_risk_premium_long_term");
v[57]=VS(financial, "fs_number_object_banks");
v[58]=VS(financial, "cb_minimum_capital_ratio");
v[59]=VS(financial, "fs_sensitivity_debt_rate");
//GOVERNMENT PARAMETERS
v[60]=VS(government, "government_initial_debt_gdp_ratio");
v[61]=VS(government, "government_initial_share_consumption");
v[62]=VS(government, "government_initial_share_capital");
v[63]=VS(government, "government_initial_share_input");
//CENTRAL BANK PARAMETERS
v[70]=VS(centralbank, "cb_target_annual_inflation");
	
	if(V("switch_monetary_policy")==2)			//smithin rule
		v[71]=v[70];	
	else if(V("switch_monetary_policy")==3)		//pasinetti rule
		v[71]=v[70];
	else if(V("switch_monetary_policy")==4)		//kansas city rule.
		v[71]=0;
	else					//taylor rule or fixed monetary policy
		v[71]=v[50]+v[70];	

	v[100]=(((v[20]*v[22]/v[21])+(v[30]*v[32]/v[31])+(v[10]*v[12]/v[11]))*v[23])/v[1];				//nominal GDP
	LOG("\nNominal GDP is %f.",v[100]);
		
	//GOVERNMENT INTERMEDIATE CALCULATION
	v[101]=v[100]*v[60];								//government debt
	v[102]=pow((1+v[71]),(1/v[0]))-1;					//quarterly basic interest rate
	v[103]=v[102]*v[101];								//government interest payment
	v[104]=v[2]*v[100];									//government expenses
	v[105]=v[103]+v[104];								//government total taxes
	v[106]=v[104]*v[61];								//government nominal consumption
	v[107]=v[104]*v[62];								//government nominal investment
	v[108]=v[104]*v[63];								//government nominal inputs
	v[109]=v[106]/v[13];								//government real consumption
	v[110]=v[107]/v[23];								//government real investment
	v[111]=v[108]/v[33];								//government real inputs
	v[112]=v[104]-v[106]-v[107]-v[108];					//government wages
	v[113]=v[103]/v[100];								//government surplus rate target
	
	//WRITTING GOVERNMENT LAGGED VALUES
	WRITELLS(government, "Government_Desired_Wages", v[112], 0, 1);
	WRITELLS(government, "Government_Desired_Unemployment_Benefits", 0, 0, 1);
	WRITELLS(government, "Government_Desired_Consumption", v[106], 0, 1);
	WRITELLS(government, "Government_Desired_Investment", v[107], 0, 1);
	WRITELLS(government, "Government_Desired_Inputs", v[108], 0, 1);
	WRITELLS(government, "Government_Surplus_Rate_Target", v[113], 0, 1);
	WRITELLS(government, "Government_Debt", v[101], 0, 1);
	WRITELLS(government, "Government_Total_Taxes", v[105], 0, 1);
	WRITELLS(government, "Government_Max_Expenses_Ceiling", v[104], 0, 1);//olhar depois
	WRITELLS(government, "Government_Max_Expenses_Surplus", v[104], 0, 1);//olhar depois
	WRITELLS(government, "Government_Max_Expenses", v[104], 0, 1);//olhar depois
	for(i=1;i<=v[0]+1;i++) 
		WRITELLS(government, "Government_Debt_GDP_Ratio", v[60], 0, i);
	for(i=1;i<=v[0];i++) 
		WRITELLS(government, "Government_Effective_Expenses", v[104], 0, i);

	//EXTERNAL INTERMEDIATE CALCULATION
	v[120]=v[41]*v[100];						        //external nominal income
	v[121]=v[100]*v[42]*(v[71]-v[40]);					//capital flows
	v[122]=v[43]*v[100];								//international reserves
	v[123]=v[100]*v[3];									//country nominal exports
	v[124]=v[123]+v[121];								//country nominal imports
	v[125]=v[123]*v[16];								//country nominal consuption exports
	v[126]=v[123]*v[26];								//country nominal capital exports
	v[127]=v[123]*v[36];								//country nominal input exports
	v[128]=v[125]/v[13];								//country real consumption exports
	v[129]=v[126]/v[23];								//country real capital exports
	v[130]=v[127]/v[33];								//country real input exports

	//SECTORAL DEMAND CALCULATION
	v[140]=v[100]*(1-v[1]-v[2]-v[3])-v[103];														//nominal domestic consumption
	v[141]=(v[140]/v[13])+v[128]+v[109];															//real consumption demand
	v[142]=(v[20]*v[22]/v[21])+(v[30]*v[32]/v[31])+(v[10]*v[12]/v[11])+v[129]+v[110];				//real capital demand
	v[143]=(v[141]*v[14]*(1-v[15])+v[142]*v[24]*(1-v[25])+v[130]+v[111])/(1-v[34]*(1-v[35]));		//real input demand
	WRITES(consumption, "sector_initial_demand", v[141]);
	WRITES(capital, "sector_initial_demand", v[142]);
	WRITES(input, "sector_initial_demand", v[143]);

	v[270]=WHTAVE("sector_initial_price", "sector_initial_demand")/SUM("sector_initial_demand");	//average price
	
	//WRITTING EXTERNAL SECTOR LAGGED VALUES
	WRITELLS(external, "External_Real_Income", v[120]/v[270], 0, 1);
	WRITELLS(external, "External_Real_Income", v[120]/v[270], 0, 2);
	WRITELLS(external, "Country_Exchange_Rate", v[44], 0, 1);
	WRITELLS(external, "Country_Nominal_Exports", v[123], 0, 1);
	WRITELLS(external, "Country_Nominal_Imports", v[124], 0, 1);
	WRITELLS(external, "Country_International_Reserves", v[122], 0, 1);
	WRITELLS(external, "Country_Trade_Balance", v[123]-v[124], 0, 1);
	WRITELLS(external, "Country_Capital_Flows", v[121], 0, 1);
	WRITELLS(external, "Country_International_Reserves_GDP_Ratio", v[43], 0, 1);
	WRITELLS(external, "Country_External_Debt", 0, 0, 1);
	
v[210]=v[211]=v[212]=v[213]=v[214]=v[215]=v[216]=v[217]=v[218]=v[219]=v[226]=0;
CYCLE(cur, "SECTORS")
{
	v[150]=VS(cur, "sector_initial_demand");
	v[151]=VS(cur, "sector_investment_frequency");
	v[152]=VS(cur, "sector_number_object_firms");
	v[153]=VS(cur, "sector_initial_price");
	v[154]=VS(cur, "sector_input_tech_coefficient");
	v[155]=VS(cur, "sector_initial_propensity_import_inputs");
	v[156]=VS(cur, "sector_desired_degree_capacity_utilization");
	v[157]=VS(cur, "sector_initial_external_price");
	v[158]=VS(cur, "sector_capital_output_ratio");
	v[159]=VS(cur, "sector_initial_productivity");
	v[160]=VS(cur, "sector_indirect_tax_rate");
	v[161]=VS(cur, "sector_rnd_revenue_proportion");
	v[162]=VS(cur, "sector_initial_debt_rate");
	v[163]=VS(cur, "sector_initial_liquidity_preference");
	v[164]=VS(cur, "sector_initial_profit_rate");
	v[165]=VS(cur, "sector_capital_duration");
	v[166]=VS(cur, "sector_initial_depreciation_scale");
	v[167]=VS(cur, "sector_initial_quality");
	v[168]=VS(cur, "sector_desired_inventories_proportion");
	v[169]=VS(cur, "sector_price_frequency");
	
	v[170]=v[150]*v[153];											//sector revenue
	v[171]=v[150]*v[153]*v[160];									//sector taxation
	v[172]=v[150]*v[153]*(1-v[160])*v[161];							//sector rnd expenses
	v[173]=v[150]*v[154]*(1-v[155])*v[33];							//sector domestic input expenses
	v[174]=v[150]*v[154]*v[155]*v[37]*v[44];						//sector imported input expenses
	v[175]=v[173]+v[174];											//sector total input expenses
	v[176]=v[150]*v[164];											//sector gross profits
	
	v[177]=v[150]/v[156];											//sector desired capacity
	v[178]=v[177]/v[152];											//firm desired capacity
	v[179]=ROUND(v[178]*v[158], "UP");								//firm number capitals
	v[180]=v[179]*v[152];											//sector number capitals
	v[181]=v[180]*v[23];											//sector nominal capital
	v[182]=v[163]*v[181];											//sector stock deposits
	v[183]=v[181]*(1+v[163])*v[162];								//sector stock loans
	v[184]=v[102]+v[54]+v[56]*v[162];								//sector avg interest rate long term
	v[185]=v[184]*v[183];											//sector interest payment
	v[186]=v[182]*max(0,v[102]-v[52]);								//sector interest receivment
	v[187]=v[170]-v[171]-v[172]-v[175]-v[185]+v[186]-v[176];		//sector wage payment
	v[188]=v[187]*v[159]/v[150];									//sector wage rate
	v[189]=(v[188]/v[159])+(v[175]/v[150]);							//sector unit variable cost
	v[190]=v[153]/v[189];											//sector markup
	v[191]=v[150]/v[159];											//sector employment
	v[192]=v[183]/v[165];											//sector amortization expenses
	v[193]=v[23]*(v[166]*v[152]/v[151]);							//sector investment expenses
	v[194]=v[193]-v[192];											//sector retained profits
	v[195]=v[176]-v[194];											//sector distributed profits
	v[196]=v[195]/v[176];											//sector profit distribution rate
	v[197]=v[180]*v[158];											//sector productive capacity
	v[198]=v[150]/v[197];											//sector capacity utilization
	v[199]=(VS(cur,"sector_initial_exports_share")*v[123]/v[153])/(pow((v[157]*v[44]/v[153]),VS(cur,"sector_exports_elasticity_income"))*pow(v[120],VS(cur,"sector_exports_elasticity_income")));

	//WRITTING SECTOR LAGGED VALUES
	WRITES(cur, "sector_exports_coefficient", v[199]);
	WRITES(cur, "sector_desired_degree_capacity_utilization", v[198]);
	WRITES(cur, "sector_profits_distribution_rate", v[196]);
	WRITELLS(cur, "Sector_External_Price", v[157], 0, 1);
	WRITELLS(cur, "Sector_Productive_Capacity", v[197], 0, 1);
	WRITELLS(cur, "Sector_Capacity_Utilization", v[198], 0, 1);
	WRITELLS(cur, "Sector_Idle_Capacity", 1-v[198], 0, 1);
	WRITELLS(cur, "Sector_Productive_Capacity_Available", 0, 0, 1);
	WRITELLS(cur, "Sector_Number_Firms", v[152], 0, 1);
	WRITELLS(cur, "Sector_Avg_Productivity", v[159], 0, 1);
	WRITELLS(cur, "Sector_Max_Productivity", v[159], 0, 1);
	WRITELLS(cur, "Sector_Avg_Wage", v[188], 0, 1);
	WRITELLS(cur, "Sector_Max_Quality", v[167], 0, 1);
	WRITELLS(cur, "Sector_Propensity_Import_Inputs", v[155], 0, 1);
	WRITELLS(cur, "Sector_Exports_Share", (VS(cur,"sector_initial_exports_share")*v[123]/v[153])/v[150], 0, 1);
	for(i=1;i<=v[0]+1;i++) 
		WRITELLS(cur, "Sector_Avg_Price", v[153], 0, i);
	for(i=1;i<=v[0]+1;i++) 
		WRITELLS(cur, "Sector_Avg_Quality", v[167], 0, i);
	for(i=1;i<=v[0]+1;i++) 
		WRITELLS(cur, "Sector_Employment", v[191], 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur, "Sector_Demand_Met", 0, 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur, "Sector_Demand_Met_By_Imports", 1, 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur, "Sector_Effective_Orders", v[150], 0, i);
	
	LOG("\nSector %f.0",SEARCH_INST(cur));LOG(" Desired Capacity Uilization is %f.",v[198]);
	LOG("\nSector %f.0",SEARCH_INST(cur));LOG(" Profit Distribution Rate is %f.",v[196]);
	LOG("\nSector %f.0",SEARCH_INST(cur));LOG(" Wage Rate is %f.",v[188]);
	
	//WRITTING FIRM LAGGED VALUES
	cur1=SEARCHS(cur, "FIRMS");																	
	WRITES(cur1, "firm_date_birth", 0);   
	WRITELLS(cur1, "Firm_Effective_Market_Share", 1/v[152], 0, 1);
	WRITELLS(cur1, "Firm_Avg_Productivity", v[159], 0, 1);
	WRITELLS(cur1, "Firm_Price", v[153], 0, 1);
	WRITELLS(cur1, "Firm_Quality", v[167], 0, 1);
	WRITELLS(cur1, "Firm_Competitiveness", 1, 0, 1);
	WRITELLS(cur1, "Firm_Stock_Inventories", v[150]*v[168]/v[152], 0, 1);
	WRITELLS(cur1, "Firm_Delivery_Delay", 0, 0, 1);
	WRITELLS(cur1, "Firm_Stock_Deposits", v[182]/v[152], 0, 1);
	WRITELLS(cur1, "Firm_Wage", v[188], 0, 1);
	WRITELLS(cur1, "Firm_Desired_Markup", v[190], 0, 1);
	WRITELLS(cur1, "Firm_Avg_Debt_Rate", v[162], 0, 1);
	WRITELLS(cur1, "Firm_Max_Debt_Rate", 2*v[162], 0, 1);
	WRITELLS(cur1, "Firm_Stock_Inputs", v[150]*v[154]/v[152], 0, 1);
	WRITELLS(cur1, "Firm_Liquidity_Preference", v[163], 0, 1);
	WRITELLS(cur1, "Firm_Capital", v[181]/v[152], 0, 1);
	WRITELLS(cur1, "Firm_Stock_Loans", v[183]/v[152], 0, 1);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Expansion", 0, 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Replacement", 0, 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Frontier_Productivity", v[159], 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Productive_Capacity", v[197]/v[152], 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Interest_Payment", v[185]/v[152], 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Debt_Rate", v[162], 0, i);
	for(i=1;i<=v[151];i++) 
		WRITELLS(cur1, "Firm_Net_Profits", v[176]/v[152], 0, i);
	for(i=1;i<=v[151]-1;i++) 
		WRITELLS(cur1, "Firm_Effective_Orders_Capital_Goods", v[150]/v[152], 0, i);
	for(i=1;i<=2*v[151]-1;i++) 
		WRITELLS(cur1, "Firm_Effective_Orders", v[150]/v[152], 0, i);
	for(i=1;i<=v[169];i++) 
		WRITELLS(cur1, "Firm_Market_Share", 1/v[152], 0, i);
	for(i=1;i<=v[0]+1;i++) 
		WRITELLS(cur1, "Firm_Avg_Productivity", v[159], 0, i);
	
	//WRITTING CAPITAL LAGGED VALUES
	cur2=SEARCHS(cur1, "CAPITALS");														
	WRITELLS(cur2, "Capital_Good_Acumulated_Production", 0, 0, 1);      				
	WRITES(cur2, "capital_good_productive_capacity", 1/v[158]);     					
	WRITES(cur2, "capital_good_productivity_initial", v[159]);       		  			
	WRITES(cur2, "capital_good_to_replace", 0);
	WRITES(cur2, "capital_good_date_birth", 0);
	WRITES(cur2, "id_capital_good_number", 1);    
	
	//CREATING FIRM OBJECTS
	for(i=1; i<=(v[152]-1); i++)															
	cur4=ADDOBJ_EXLS(cur,"FIRMS", cur1, 0);
	CYCLES(cur, cur1, "FIRMS")                                                 				
		{
			v[200]=SEARCH_INSTS(cur, cur1);
			WRITES(cur1, "firm_id", v[200]);                         	
			v[201]=v[200]/(v[152]/v[57]);
			//WRITES(cur1, "firm_bank", ROUND(v[201], "UP"));
			WRITES(cur1, "firm_bank", uniform_int(1,v[57]));
			
			//WRITTING FIRM_LOANS LAGGED VALUES
			cur2=SEARCHS(cur1, "FIRM_LOANS");
			WRITES(cur2, "id_firm_loan_long_term", 1);     					
			WRITES(cur2, "id_firm_loan_short_term", 0);   
			WRITES(cur2, "firm_loan_total_amount", v[183]/v[152]);			
			WRITES(cur2, "firm_loan_interest_rate", v[184]);
			WRITES(cur2, "firm_loan_fixed_amortization", v[192]/v[152]);
			WRITES(cur2, "firm_loan_fixed_object", 0);
			
			//CREATING CAPITAL OBJECTS
			cur2=SEARCHS(cur1, "CAPITALS");   
			for(i=1; i<=(v[179]-1); i++)                        								
			{                                 			
			cur3=ADDOBJ_EXLS(cur1,"CAPITALS", cur2, 0);			                       		
			WRITES(cur3, "id_capital_good_number", (i+1));										
			}
			
			CYCLES(cur1, cur2, "CAPITALS")                                            			
				{
				v[202]=fmod(v[200]+v[151], v[151]);
				v[203]=VS(cur2, "id_capital_good_number");
				v[204]=v[202]+(v[203]-1)*v[151];			
				WRITES(cur2, "capital_good_depreciation_period", v[204]);
				}
		}

v[210]+=v[171];														//total indirect taxation
v[211]+=v[172];														//total RND expenses
v[212]+=v[174];														//total imported imput expenses
v[213]+=v[182];														//total firms stock deposits
v[214]+=v[183];														//total stock loans
v[215]+=v[185];														//total interest payment
v[216]+=v[186];														//total interest receivment
v[217]+=v[187];														//total wage payment
v[218]+=v[195];														//total distributed profits
v[219]+=v[181];														//total nominal capital
v[226]+=(v[193]-v[194]);											//total demand loans
}

	v[220]=v[214]/(v[213]+v[219]);									//average debt rate
	v[221]=v[214]/v[57];											//bank stock of debt
	v[222]=v[221]*(v[58]+v[59]*v[220]);								//bank initial accumulated profits
	v[223]=v[215]-v[216]+v[103];									//financial sector profits
	v[224]=v[214]/v[51];											//total stock deposits

	//WRITTING FINANCIAL LAGGED VALUES
	WRITELLS(centralbank, "Central_Bank_Basic_Interest_Rate", v[102], 0, 1);
	WRITELLS(financial, "Financial_Sector_Avg_Competitiveness", 1, 0, 1);
	WRITELLS(financial, "Financial_Sector_Avg_Interest_Rate_Short_Term", v[102]+v[53], 0, 1);
	WRITELLS(financial, "Financial_Sector_Avg_Interest_Rate_Long_Term", v[102]+v[54], 0, 1);
	WRITELLS(financial, "Financial_Sector_Total_Stock_Loans_Growth", 0, 0, 1);
	WRITELLS(financial, "Financial_Sector_Total_Stock_Loans", v[214], 0, 1);
	
	//CREATING BANK OBJECTS
	cur1=SEARCHS(financial, "BANKS");
	for(i=1; i<=(v[57]-1); i++)																
	cur2=ADDOBJ_EXLS(financial,"BANKS", cur1, 0);

	//WRITTING BANK LAGGED VALUES
	CYCLES(financial, cur1, "BANKS")                                                 				
		{												
		WRITES(cur1, "bank_id", SEARCH_INSTS(root, cur1)); 
		WRITELLS(cur1, "Bank_Market_Share", 1/v[57], 0, 1);
		WRITELLS(cur1, "Bank_Default_Share", 0, 0, 1);
		WRITELLS(cur1, "Bank_Accumulated_Defaulted_Loans", 0, 0, 1);
		WRITELLS(cur1, "Bank_Total_Stock_Loans", v[214]/v[57], 0, 1);
		WRITELLS(cur1, "Bank_Competitiveness", 1, 0, 1);
		WRITELLS(cur1, "Bank_Demand_Met", 1, 0, 1);
		WRITELLS(cur1, "Bank_Demand_Loans", v[226]/v[57], 0, 1);
		WRITELLS(cur1, "Bank_Desired_Short_Term_Spread", v[53], 0, 1);
		WRITELLS(cur1, "Bank_Desired_Long_Term_Spread", v[54], 0, 1);
		WRITELLS(cur1, "Bank_Interest_Rate_Short_Term", v[102]+v[53], 0, 1);
		WRITELLS(cur1, "Bank_Interest_Rate_Long_Term", v[102]+v[54], 0, 1);
		WRITELLS(cur1, "Bank_Accumulated_Profits", v[222], 0, 1);
		}
		
	//AGGREGATE INTERMEDIATE VARIABLES
	v[230]=v[211]+v[217]+v[112];									//total wages
	v[231]=v[218]+v[223];											//total distributed profits
	v[232]=v[230]+v[231];											//total households gross income	
	v[233]=v[105]-v[210];											//total income taxation
	v[235]=v[124]-v[212];											//total imported consumption expenses

v[271]=WHTAVE("sector_initial_productivity", "sector_initial_demand")/SUM("sector_initial_demand");
v[272]=WHTAVE("sector_desired_degree_capacity_utilization", "sector_initial_demand")/SUM("sector_initial_demand");
	
//WRITTING COUNTRY LAGGED VALUES  
WRITELLS(country, "Country_Debt_Rate_Firms", v[220], 0, 1);
WRITELLS(country, "Country_Idle_Capacity", 1-v[272], 0, 1);
WRITELLS(country, "Country_Avg_Productivity", v[271], 0, 1);
WRITELLS(country, "Country_Avg_Productivity", v[271], 0, 2);
WRITELLS(country, "Country_Annual_CPI_Inflation", v[70], 0, 1);
for(i=1;i<=v[0]+1;i++)
	WRITELLS(country, "Country_Price_Index", v[270], 0, i);
for(i=1;i<=v[0]+1;i++)
	WRITELLS(country, "Country_Consumer_Price_Index", v[13], 0, i);
for(i=1;i<=2*v[0]+1;i++)
	WRITELLS(country, "Country_GDP", v[100], 0, i);
for(i=1;i<=2*v[0]+1;i++)
	WRITELLS(country, "Country_Real_GDP", v[100]/v[270], 0, i);
for(i=1;i<=v[0];i++)
	WRITELLS(country, "Country_Capital_Goods_Price", v[23], 0, i);
	
PARAMETER
RESULT(0)

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// INITIALIZATION 3 ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking


EQUATION("Initialization_3")

consumption=SEARCH_CND("id_consumption_goods_sector",1);
capital=SEARCH_CND("id_capital_goods_sector",1);
input=SEARCH_CND("id_intermediate_goods_sector",1);
government=SEARCH("GOVERNMENT");
financial=SEARCH("FINANCIAL");
external=SEARCH("EXTERNAL_SECTOR");
country=SEARCH("COUNTRY");
centralbank=SEARCH("CENTRAL_BANK");

//v[0]=V("depreciation_scale");
v[0]=1;

v[1]=VS(consumption, "sector_number_object_firms");
v[2]=VS(capital, "sector_number_object_firms");
v[3]=VS(input, "sector_number_object_firms");

v[4]=VS(consumption, "sector_investment_frequency");
v[5]=VS(capital, "sector_investment_frequency");
v[6]=VS(input, "sector_investment_frequency");

//v[7]=VS(country, "investment_share_GDP");
//v[8]=VS(country, "country_initial_exports_share_GDP");
//v[9]=VS(country, "country_initial_government_share_GDP");
v[7]=0.1;
v[8]=0.1;
v[9]=0.2;

v[10]=VS(consumption, "sector_initial_price");
v[11]=VS(capital, "sector_initial_price");
v[12]=VS(input, "sector_initial_price");

v[13]=VS(consumption, "sector_exports_share");
v[14]=VS(capital, "sector_exports_share");
v[15]=VS(input, "sector_exports_share");

v[16]=VS(government, "government_initial_consumption_share");
v[17]=VS(government, "government_initial_capital_share");
v[18]=VS(government, "government_initial_input_share");

v[19]=v[0]*((v[1]/v[4])+(v[2]/v[5])+(v[3]/v[6]));//domestic real capital demand
	LOG("\nDomestic Capital Demand is %f.",v[19]);
v[20]=(v[11]*v[19])/v[7];//nominal quarterly GDP
	LOG("\nNominal Quarterly GDP is %f.",v[20]);

v[21]=VS(government, "initial_government_debt_share_GDP");
v[22]=VS(country, "annual_frequency");
v[23]=v[20]*v[21]*v[22];//government debt
	LOG("\nGovernment Debt is %f.",v[23]);
v[24]=VS(financial, "cb_annual_real_interest_rate")+VS(centralbank, "cb_target_annual_inflation");
v[25]=v[24]*v[23];//government interest payment
	LOG("\nGovernment Interest Payment is %f.",v[25]);
v[26]=v[9]*v[20];//government total expenses
	LOG("\nGovernment Total Expenses is %f.",v[26]);
v[27]=v[25]+v[26];//government total taxes
	LOG("\nGovernment Total Taxes is %f.",v[27]);
v[28]=v[16]*v[26];//government consumption expenses
	LOG("\nGovernment Nominal Consumption is %f.",v[28]);
v[29]=v[17]*v[26];//government capital expenses
	LOG("\nGovernment Nominal Investment is %f.",v[29]);
v[30]=v[18]*v[26];//government input expenses
	LOG("\nGovernment Nominal Inputs is %f.",v[30]);
v[31]=v[28]/v[10];//government consumption real demand
	LOG("\nGovernment Real Consumption is %f.",v[31]);
v[32]=v[29]/v[11];//government capital real demand
	LOG("\nGovernment Real Capital is %f.",v[32]);
v[33]=v[30]/v[12];//government input real demand
	LOG("\nGovernment Real Inputs is %f.",v[33]);
v[34]=v[26]*(1-v[16]-v[17]-v[18]);//government wages
	LOG("\nGovernment Wages is %f.",v[34]);
		
WRITELLS(government,"Government_Total_Taxes", v[27], 0, 1);														//write initial total taxes, initial total taxes is calculated in the demand calibration based only on parameters
WRITELLS(government,"Government_Max_Expenses", v[26], 0, 1);        									//initial max government expenses equals total taxes calculated in the calibration
WRITELLS(government,"Government_Desired_Wages", v[34], 0, 0);		            		//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity		            				    
WRITELLS(government,"Government_Desired_Consumption", v[28], 0, 0);		            		//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity	
WRITELLS(government,"Government_Desired_Investment", v[29], 0, 0);		            			//initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity	
WRITELLS(government,"Government_Desired_Inputs", v[30], 0, 0);		            			    //initial government expenses is only wages, which thereafter will grow depending on inflation and average productivity	
WRITELLS(government,"Government_Surplus_Rate_Target", v[169], 0, 1);
for (i=1 ; i<=V("annual_frequency")+1 ; i++)		              													//for (government_period) lags	
{
	WRITELLS(government,"Government_Debt", V("initial_debt_gdp")*V("annual_frequency")*v[150], 0, i);                  									//no debt initially																	//base interest rate parameter
	WRITELLS(government,"government_initial_debt_gdp_ratio", V("initial_debt_gdp"), 0, i);
	WRITELLS(government,"Government_Effective_Expenses", v[25]/v[20], 0, i);
}
	
v[35]=v[20]*v[8];//total exports
	LOG("\nTotal Exports is %f.",v[35]);
//v[36]=VS(external,"initial_trade_balance_share_GDP");
v[36]=0;
v[37]=v[35]-v[36]*v[20];//total imports
	LOG("\nTotal Imports is %f.",v[35]);
v[38]=v[35]*v[13];//nominal consumption exports
	LOG("\nNominal Consumption Exports is %f.",v[38]);
v[39]=v[35]*v[14];//nominal capital exports
	LOG("\nNominal Capital Exports is %f.",v[39]);
v[40]=v[35]*v[15];//nominal input exports
	LOG("\nNominal Input Exports is %f.",v[40]);

v[41]=v[38]/v[10];//real consumption exports
	LOG("\nReal Consumption Exports is %f.",v[41]);
v[42]=v[39]/v[11];//real capital exports
	LOG("\nReal Capital Exports is %f.",v[42]);
v[43]=v[40]/v[12];//real input exports
	LOG("\nReal Input Exports is %f.",v[43]);
	
v[44]=v[42]+v[32]+v[19];//total capital demand
	LOG("\nReal Total Capital Demand is %f.",v[44]);
	WRITES(capital, "sector_initial_demand", v[44]);
v[45]=VS(capital, "sector_desired_degree_capacity_utilization");
v[46]=v[44]/v[2];//capital sector firm demand
	LOG("\nCapital Sector Firm Demand is %f.",v[46]);
v[47]=v[46]/v[45];//capital sector firm productive capacity
	LOG("\nCapital Sector Firm Capacity is %f.",v[47]);
v[48]=VS(capital, "sector_capital_output_ratio");
v[49]=ROUND(v[48]*v[47], "UP");
	LOG("\nCapital Sector Firm Number Capitals is %f.",v[49]);
v[50]=v[46]/v[49];//effective capacity utilization
	LOG("\nCapital Sector Effective Capaicty Utilization is %f.",v[50]);

v[51]=v[20]*(1-v[7]-v[8]-v[9])-v[25];//domestic consumption
	LOG("\nNominal Domestic Consumtpion is %f.",v[51]);
v[52]=v[51]+v[37];//total classes expenses
	LOG("\nTotal Classes Expenses is %f.",v[52]);
	
v[53]=v[51]/v[10];//domestic real consumption
	LOG("\nReal Domestic Consumtpion is %f.",v[53]);
v[54]=v[53]+v[31]+v[41];//consumption sector real demand
	LOG("\nReal Total Consumption Demand is %f.",v[54]);
	WRITES(consumption, "sector_initial_demand", v[54]);
v[55]=VS(consumption, "sector_desired_degree_capacity_utilization");
v[56]=v[54]/v[1];//consumption sector firm demand
	LOG("\nConsumption Sector Firm Demand is %f.",v[56]);
v[57]=v[56]/v[55];//consumption sector firm productive capacity
	LOG("\nConsumpion Sector Firm Capacity is %f.",v[57]);
v[58]=VS(consumption, "sector_capital_output_ratio");
v[59]=ROUND(v[58]*v[57], "UP");
	LOG("\nConsumption Sector Firm Number Capitals is %f.",v[59]);
v[60]=v[56]/v[59];//effective capacity utilization
	LOG("\nConsumption Sector Effective Capaicty Utilization is %f.",v[60]);
	
v[61]=VS(consumption,"sector_input_tech_coefficient");
v[62]=VS(capital,"sector_input_tech_coefficient");
v[63]=VS(input,"sector_input_tech_coefficient");	

v[64]=(v[54]*v[61] + v[44]*v[62] + v[33] + v[43])/(1-v[63]);
	LOG("\nReal Total Input Demand is %f.",v[64]);
	WRITES(input, "sector_initial_demand", v[64]);
v[65]=VS(input, "sector_desired_degree_capacity_utilization");
v[66]=v[64]/v[3];//input sector firm demand
	LOG("\nInput Sector Firm Demand is %f.",v[66]);
v[67]=v[66]/v[65];//input sector firm productive capacity
	LOG("\nInput Sector Firm Capacity is %f.",v[67]);
v[68]=VS(input, "sector_capital_output_ratio");
v[69]=ROUND(v[68]*v[67], "UP");
	LOG("\nInput Sector Firm Number Capitals is %f.",v[69]);
v[70]=v[66]/v[69];//effective capacity utilization
	LOG("\nInput Sector Effective Capaicty Utilization is %f.",v[70]);
	
v[71]=VS(financial, "fs_spread_long_term");
v[72]=VS(financial, "fs_risk_premium_long_term");
v[73]=VS(financial, "fs_spread_deposits");

v[124]=v[125]=v[126]=v[127]=v[128]=v[129]=v[135]=v[139]=v[140]=v[142]=v[144]=0;
CYCLE(cur, "SECTORS")
{
	v[100]=VS(cur, "sector_initial_demand");
	v[101]=VS(cur, "sector_initial_debt_ratio");
	v[102]=VS(cur, "sector_initial_liquidity_preference");
	v[103]=VS(cur, "sector_capital_output_ratio");
	v[104]=VS(cur, "sector_desired_degree_capacity_utilization");
	v[105]=VS(cur, "sector_initial_price");
	v[106]=VS(cur, "sector_initial_productivity");
	v[107]=VS(cur, "sector_indirect_tax_rate");
	v[108]=VS(cur, "sector_rnd_revenue_proportion");
	v[109]=VS(cur, "sector_input_tech_coefficient");
	v[110]=VS(cur, "sector_profit_rate");
	v[111]=VS(cur, "sector_number_object_firms");
	
	v[112]=ROUND((((v[100]/v[111])/v[104])*v[103]),"UP")*v[111]*v[11];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Capital is %f.",v[112]);
	v[113]=v[112]*v[102];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Deposits is %f.",v[113]);
	v[114]=v[112]*(1+v[102])*v[101];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Loans is %f.",v[114]);
	v[115]=(v[24]-v[73])*v[113];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Interest on Deposits is %f.",v[115]);
	v[116]=(v[24]+v[71]+v[72]*v[101])*v[114];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Interest Payment is %f.",v[116]);
	v[117]=v[100]*v[105];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Revenue is %f.",v[117]);
	v[118]=v[100]*v[105]*v[107];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Taxation is %f.",v[118]);
	v[119]=v[100]*v[105]*(1-v[107])*v[108];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("RND Expenses is %f.",v[119]);
	v[120]=v[100]*v[109]*v[12];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Input Expenses is %f.",v[120]);
	v[121]=v[100]*v[110];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Gross Profits is %f.",v[121]);
	v[122]=v[117]-v[118]-v[119]-v[120]-v[116]+v[115]-v[121];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Wage Payment is %f.",v[122]);
	v[123]=(v[122]/v[100])*v[106];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Nominal Wage Rate is %f.",v[123]);
		
	v[124]=v[124]+v[115];//total interest receivment
	v[125]=v[125]+v[116];//total interest payment
	v[126]=v[126]+v[119]+v[122];//total wage payment including RND
	v[127]=v[127]+v[120];//total input expenses
	v[128]=v[128]+v[121];//total profits
	v[129]=v[129]+v[118];//total indirect taxation
	
	v[130]=VS(cur, "sector_investment_frequency");
	v[131]=VS(cur, "sector_amortization_period");
	v[132]=v[0]*v[111]/v[130];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Capital Demand is %f.",v[132]);
	v[133]=v[132]*v[11];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Investment Expenses is %f.",v[133]);
	v[134]=v[114]/v[131];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Amortization Expenses is %f.",v[134]);
	v[135]=v[135]+v[133];
	v[136]=v[133]-v[134];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Retained Profits is %f.",v[136]);
	v[137]=v[121]-v[136];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Distributed Profits is %f.",v[137]);
	v[138]=v[137]/v[121];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Profit Distribution Rate is %f.",v[138]);
	v[139]=v[139]+v[137];
	v[140]=v[140]+v[136];
	v[141]=v[100]/v[106];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Employment is %f.",v[141]);
	v[142]=v[142]+v[141];
	v[143]=v[141]/v[111];
		LOG("\nSector %.0f ", SEARCH_INST(cur)); LOG("Firm Employment is %f.",v[143]);
	v[144]=v[144]+v[123]*v[141];
	
	for (i=1 ; i<=VS(cur, "sector_investment_frequency") ; i++)																	//for (investment_period) lags 
		{
		WRITELLS(cur, "Sector_Demand_Met", 1, 0, i); 										    //it is assumed that all demand is met initially. Equals 1 by definition
		WRITELLS(cur, "Sector_Demand_Met_By_Imports", 1, 0, i);                      			//it is assumed thatt all imports are met initially. Equals 1 by definition
		WRITELLS(cur, "Sector_Effective_Orders", v[100], 0, i);               					//Effective_Orders_Sectors equals demand_initial
		}		
	for (i=1 ; i<=(V("annual_frequency")+1) ; i++)                        		 								//for (class_period+1) lags
		{
		WRITELLS(cur, "Sector_Avg_Quality", 1, 0, i);               							//Effective_Orders_Sectors equals demand_initial
		WRITELLS(cur, "Sector_Employment", v[141], 0, i);               					//Effective_Orders_Sectors equals demand_initial
		WRITELLS(cur, "Sector_Avg_Price", v[105], 0, i);                                   		//Avg_Price equals avg_price initial
		}
		WRITELLS(cur, "Sector_Productive_Capacity_Available", 0, 0, 1);                  		//it is assumed that there is no entry or exit initially. Equals 0 by definition
		WRITELLS(cur, "Sector_Avg_Competitiveness", 1, 0, 1);                     				//if all firms are the same, equals 1 by definition
		WRITELLS(cur, "Sector_External_Price", v[105], 0, 1);                               	//Foreign_Price equals foreign_price initial
		WRITELLS(cur, "Sector_Avg_Productivity", v[106], 0,  1);               	 				//If all firms are the same, Avg Productivity will be the initial productivivity for all firms
		WRITELLS(cur, "Sector_Max_Productivity", v[106], 0,  1);                      			//If all capital goods have the same productivity, Max_Productivity equals productivity_initial 
		WRITELLS(cur, "Sector_Max_Quality", 1, 0, 1);
		WRITELLS(cur, "Sector_Inventories", (v[100]*VS(cur,"sector_desired_inventories_proportion"), 0, 1);                  			//Firms operate with desired level of inventories, thus, Current stock of inventories is the desired level times effective production
		WRITELLS(cur, "Sector_Productive_Capacity", v[100]/v[104], 0, 1);								//All firms start operating at desired degree of utilization, thus, productive capacity is endogenous calculated based on effective production and desired degree
		WRITELLS(cur, "Sector_Real_Exports", vs(cur, "sector_exports_share")*v[35]/v[105], 0, 1);										//Total exports are divided equally among sectors.
		WRITES(cur, "sector_exports_coefficient", vs(cur, "sector_exports_share")*v[35]/pow(v[20],VS(cur, "sector_exports_elasticity_income")));										//write the exports coefficient, assuming external price and foreign price starts as 1, so the exchange rate
	
		cur1=SEARCHS(cur, "FIRMS");																	//search the first and only instance of firms below each sector
		//Begin Writting Firm Parameters
		WRITES(cur1, "firm_date_birth", 0);                                   					//zero by definition
		
		//Begin Writting Independent Firm Variables
	for (i=1 ; i<=VS(cur, "sector_investment_frequency") ; i++)                                									//for (investment_period) lags
	  	{
	  	WRITELLS(cur1, "Firm_Demand_Productive_Capacity_Replacement", 0, 0, i);					//no replacement initially
	  	WRITELLS(cur1, "Firm_Debt_Rate", 0, 0, i);												//no debt initially
	  	WRITELLS(cur1, "Firm_Demand_Capital_Goods", 0, 0, i);
	  	WRITELLS(cur1, "Firm_Frontier_Productivity", v[106], 0, i);                 			//frontier productivity will be the initial frontier productivity
	  	WRITELLS(cur1, "Firm_Max_Productivity", v[106], 0, i);        							//max capital goods productivity will be the initial frontier productivity that will be the same for all capital goods
	  	WRITELLS(cur1, "Firm_Avg_Productivity", v[106], 0, i);									//firm's avg productivity will be the initial frontier productivity since all capital goods have the same productivity
	for(i=1; i<=(VS(cur, "sector_investment_frequency")+1); i++)										 							//for (investment period+1) lags (7)
		{
		WRITELLS(cur1, "Firm_Productive_Capacity_Depreciation", 0, 0, i);  						//write 0 
		WRITELLS(cur1, "Firm_Demand_Productive_Capacity_Expansion", 0, 0, i);     				//write 0 
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Expansion", 0, 0, i);     					//write 0
		WRITELLS(cur1, "Firm_Demand_Capital_Goods_Replacement", 0, 0, i);     					//write 0
		WRITELLS(cur1, "Firm_Effective_Orders_Capital_Goods", 0, 0, i);  						//write 0 
		}
	for (i=1 ; i<=(2*VS(cur, "sector_investment_frequency")) ; i++)																//for (2*investment period+1) lags
	  	WRITELLS(cur1, "Firm_Effective_Orders", (v[100]/v[111]), 0, i);                    		//firm's effective orders will be sector's effective orders (given by demand_initial) divided by the number of firms
	for (i=1 ; i<=(VS(cur, "sector_price_frequency")+1) ; i++)																//for (markup_period-1) lags
		{
		WRITELLS(cur1, "Firm_Market_Share", (1/v[111]), 0, i);             						//firm's market share will be the inverse of the number of firms in the sector (initial market share)
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
	
	
	
	
	
	
	
	
	
}
	LOG("\nTotal Interest Receivment is %f.",v[124]);
	LOG("\nTotal Interest Payment is %f.",v[125]);
	LOG("\nTotal Wages is %f.",v[126]+v[34]);
	LOG("\nTotal Input Expenses is %f.",v[127]+v[30]+v[40]);
	LOG("\nTotal Productive Profits is %f.",v[128]);
	LOG("\nTotal Indirect Taxation is %f.",v[129]);
	LOG("\nFinancial Sector Profits is %f.",v[125]-v[124]+v[25]);
	LOG("\nNominal GDP Income is %f.",v[126]+v[34]+v[128]+v[125]-v[124]+v[25]);
	LOG("\nTotal Investment Expenses is %f.",v[135]+v[29]+v[39]);
	LOG("\nTotal Distributed Profits is %f.",v[139]);
	LOG("\nTotal Retained Profits is %f.",v[140]);
	LOG("\nTotal Sectors Employment is %f.",v[142]);
	LOG("\nAvg Wage Rate is %f.",v[144]/v[142]);
	LOG("\nGovernment Employment is %f.",v[34]/(v[144]/v[142]));
	LOG("\nTotal Labor Force is %f.",v[142]+v[34]/(v[144]/v[142]));
	
//v[160]=VS(country, "unemployment_rate");
v[160]-0;
v[161]=(v[142]+v[34]/(v[144]/v[142]))/(1-v[160]);
	LOG("\nTotal Population is %f.", ROUND(v[161], "UP"));
v[162]=VS(financial, "fs_number_object_banks");
v[163]=SUM("sector_number_object_firms");
v[164]=v[162]+v[163]+ROUND(v[142]+v[34]/(v[144]/v[142]),"UP");

v[150]=v[139]+v[125]-v[124]+v[25]+v[126]+v[34];
	LOG("\nHouseholds Gross Income is %f.",v[150]);
v[151]=v[27]-v[129];
	LOG("\nTotal Income Tax is %f.",v[151]);
v[152]=v[150]-v[151];
	LOG("\nHouseholds Disposable Income is %f.",v[152]);
v[153]=v[52]/v[152];
	LOG("\nHouseholds Propensity to Spend is %f.",v[153]);
	LOG("\nHouseholds Domestic Consumption is %f.",v[51]);
	LOG("\nHouseholds Inported Consumption is %f.",v[37]);
	LOG("\nHouseholds Total Consumption is %f.",v[51]+v[37]);
v[154]=v[151]/v[150];
	LOG("\nHouseholds Tax Rate is %f.",v[154]);
v[155]=v[37]/(v[51]+v[37]);
	LOG("\nHouseholds Imports Rate is %f.",v[155]);
	LOG("\nTotal Consumpion Expenses is %f.",v[51]+v[28]+v[38]);
	
v[198]=WHTAVE("sector_initial_price","sector_initial_demand")/SUM("sector_initial_demand");

		WRITELLS(country,"Country_Nominal_Exports", v[35], 0, 1);
		WRITELLS(country,"Country_Nominal_Imports", v[35], 0, 1);
		WRITELLS(country,"Country_Annual_Growth", 0, 0, 1);													//zero by definition, no growth initally
		WRITELLS(country,"Country_Annual_Real_Growth", 0, 0, 1);                 							//zero by definition, no growth initally
		WRITELLS(country,"Country_Annual_Inflation", 0, 0, 1);	
	for (i=1 ; i<=(V("annual_frequency")+1) ; i++)                  												//for (annual period +1) lags
		{
		WRITELLS(country,"Country_Price_Index", v[198], 0, i);									 			//writes Price_Index, all initial price index is 1
		WRITELLS(country,"Country_Consumer_Price_Index", v[10], 0, i);          							//writes Consumper_Price_Index, all initial price index is 1
		WRITELLS(country,"Country_Capital_Goods_Price", v[11], 0, i);
		WRITELLS(country,"Country_Avg_Productivity", AVE("sector_initial_productivity"), 0, i);
		}
	for (i=1 ; i<=(2*V("annual_frequency")) ; i++)                  												//for (2*annual_period) lags
		{
		WRITELLS(country,"Country_GDP", v[20], 0, i);                     	 								//GDP
		WRITELLS(country,"Country_Real_GDP", (v[20]/v[198]), 0, i);                  						//Real GDP will be equal to nominal GDP because price index always begins as 1
		}

WRITES(external, "Country_Trade_Balance", 0);
WRITES(external, "Country_Capital_Flows", 0);
WRITELLS(external, "External_Income",  v[20], 0, 1);
WRITELLS(external, "External_Income",  v[20], 0, 2);
WRITELLS(external, "Country_International_Reserves",  v[20]*V("annual_frequency"), 0, 1);	

PARAMETER
RESULT(0)


