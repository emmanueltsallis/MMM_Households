/*****INPUTS VARIABLES*****/

EQUATION("Firm_Available_Inputs_Ratio")
/*
This variable defines the ratio between available inputs and inputs demanded for each sector in order to fulfil desired production.
*/
	v[0]=V("Firm_Planned_Production");                      
	v[1]=V("sector_input_tech_coefficient");	
	v[2]=v[0]*v[1];                        					//total amount of imputs to required to fulfil planned production
	v[3]=VL("Firm_Stock_Inputs",1);                   		//stock of remaining imputs from the last period	
	if(v[2]>0)                                         		//if required imputs is a positive value
		v[4]=v[3]/v[2];                                  	//gives the ratio between necessary imputs and available imputs
	else                                               		//if required imputs is not a positive value
		v[4]=1;                                          	//the ratio between necessary imputs and available imputs equals 1
	v[5]=min(1,v[4]);                                  		//the ratio can never be smaller then 1
RESULT(v[5])


EQUATION("Sector_Propensity_Import_Inputs")
	v[1]=V("sector_initial_propensity_import_inputs");							//firm propensity to import
	v[3]=VS(input, "Sector_Avg_Price");                       		//input sector average price
	v[4]=VS(input, "Sector_External_Price");                  		//input sector external price
	v[5]=VS(external,"Country_Exchange_Rate");						//exchange rate
	v[6]=V("sector_input_import_elasticity_price");
	v[7]=v[1]*pow((v[3]/(v[4]*v[5])),v[6]);
	v[8]=max(0,min(v[7],1));
RESULT(v[8])


EQUATION("Firm_Input_Demand_Next_Period")
/*
The demand for inputs of each sector of intermediate goods, which should be produced during current period and to be used in the next period, is calculated based on the necessity of programed production, in which a expected growth rate is applied and the remaing stock is discounted. 
The expected growth rate is defined by the average of effective orders of the last two periods, extrapolated by a expectation parameter.
The intermediate goods sectors demand exactly the amount they will need to produce in the next period, without discouting the initial stock, which is now know, since the intermediate goods production in the current period will be defined by the demand for inputs of all sectors and not the programed production of the intermediate sector.
*/

	v[0]=V("Firm_Planned_Production");                     	//firm's planned production for the current period
	v[1]=V("sector_input_tech_coefficient");           		//input technical coefficient
	v[2]=V("id_intermediate_goods_sector");           		//identifies intermediate good sectors
	
	v[5]=VL("Firm_Effective_Orders", 1);                   	//firm's effective orders lagged 1 
	v[6]=VL("Firm_Effective_Orders", 2);                   	//firm's effective orders lagged 1
	v[7]=V("sector_expectations");                          //firm's expectation parameter
	if(v[6]!=0)                                       		//if effective orders is not 0
		v[8]=1+(v[7]*((v[5]-v[6])/v[6]));               	//gives an expected growth rate, based on the effective orders
	else                                              		//if effective orders is 0
		v[8]=1;                                         	//the expected growth rate is 1
	
	v[9]=VL("Firm_Stock_Inputs",1);                   		//gives the stock of imputs remaining from the last period
	v[10]=V("Firm_Available_Inputs_Ratio");             	//gives the minimium available imput ratio
	v[12]=v[9]-(v[10]*v[0]);                          		//subtracts from the stock of imputs the total amount expected to produce, determined by the required amount multiplied by the minimum available ratio.
	v[4]=max(v[12], 0);                               		//the stock of imputs can never be negative
	
	if (v[2]==0)                                      		//if it is not intermediate goods sector
		v[14]=(v[0]*v[1])*(v[8])-v[4];    					//gives the amount of imputs necessary for the next period, multiplying the current planned production plus the desired amount of investories by the exptected growth rate and by the imput techinical relanshionship, and subtracting the current stock of imputs, already discounting the amount to be used in current production
	else                                              		//if it is intermediate goods sector
		v[14]=(v[0]*v[1])*(v[8]);                     		//gives the amount of imputs necessary for the next period, multiplying the current planned production by the exptected growth rate and by the imput techinical relanshionship
	
	v[15]=max(v[14],0);                               		//the demand of imputs for the next period can never be negative
	v[16]=V("Sector_Propensity_Import_Inputs");
	v[17]=v[15]*(1-v[16]);
	v[18]=v[15]*v[16];
	WRITE("Firm_Input_Imports",v[18]);
RESULT(v[17])

EQUATION_DUMMY("Firm_Input_Imports", "Firm_Input_Demand_Next_Period")


EQUATION("Firm_Stock_Inputs")
/*
The stock of inputs of each firm at the end of the period is calculated by summing the stock of inputs in the last period with the amount demanded for the production in the next period minus the amount used in the production of the current period
*/
	v[1]=V("Firm_Input_Demand_Next_Period");              //amount of inputs demanded in the current period to be used in the production of the next period                      
	v[2]=VS(input,"Sector_Demand_Met");                   //percentage of the total demand met by the sector                
	v[3]=VS(input,"Sector_Demand_Met_By_Imports");        //identifies if firms were capable of inporting the amount not mey by the domestic production
	v[4]=v[2]+(1-v[2])*v[3];                              //percentage of the demand met by the domestic production and by the external producers                     
	v[5]=V("Firm_Input_Imports");
	v[6]=V("sector_input_tech_coefficient");              //input technical coefficient               			 
	v[7]=V("Firm_Effective_Production");                  //firm's effective production   
	v[8]=VL("Firm_Stock_Inputs", 1);	                  //firm's stock of inputs in the last period
	v[9]=v[8]+v[1]*v[4]+v[5]-(v[6]*v[7]);                 //the current stock of inputs is the stock in the last period plus the amount of the demand for the next period that was effetivly met, minus the amount used in effective production                 
	v[10]=max(v[9],0);                                    //the current stock can never be negative
RESULT(v[10])










