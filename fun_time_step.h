EQUATION("Time_Step")
/*
Root Variable
Determines the order in which the variables will be calculated in each time step. It is the logical sequence of the model in each time step.
*/

/*****INTEREST RATES*****/
    V("Central_Bank_Basic_Interest_Rate");  
    V("Financial_Sector_Interest_Rate_Deposits");
    V("Bank_Competitiveness");
    V("Financial_Sector_Avg_Competitiveness");
    V("Bank_Market_Share");
    V("Bank_Desired_Long_Term_Spread");
    V("Bank_Desired_Interest_Rate_Long_Term");
    V("Bank_Interest_Rate_Long_Term");  
    V("Financial_Sector_Avg_Interest_Rate_Long_Term");
    V("Bank_Desired_Short_Term_Spread");
    V("Bank_Desired_Interest_Rate_Short_Term");
    V("Bank_Interest_Rate_Short_Term");  
    V("Financial_Sector_Avg_Interest_Rate_Short_Term");
    V("Firm_Avg_Debt_Rate");							   		
    V("Firm_Interest_Rate_Short_Term");
    V("Firm_Interest_Rate_Long_Term");
    V("Household_Avg_Debt_Rate"); 
    V("Household_Interest_Rate");   
    V("Bank_Max_Total_Loans"); 

    /*****PRICE SETTING*****/    
    V("Sector_Bargain_Power"); 
    V("Country_Annual_Inflation");  
    V("Country_Annual_CPI_Inflation"); 
    V("Firm_Competitiveness");                                  
    V("Firm_Market_Share");                          
    V("Firm_Wage");                                      	   	                                  		
    V("Firm_Input_Cost");                                       
    V("Firm_Variable_Cost");                                                             
    V("Firm_Desired_Markup");                                  
    V("Firm_Desired_Price");                                    
    V("Firm_Price");                                            
    V("Sector_Avg_Price"); 
    V("Sector_External_Price");
    V("Country_Capital_Goods_Price");  

    /*****EXPORTS*****/  
    V("External_Real_Income");                                  		                          
    V("Country_Exchange_Rate");                                     
    V("Sector_Real_Exports");   

    /*****GOVERNMENT*****/  
    V("Government_Desired_Wages");                                  		                          
    V("Government_Desired_Unemployment_Benefits");                                     
    V("Government_Desired_Investment");   
    V("Government_Desired_Consumption");  
    V("Government_Desired_Inputs");  
    V("Government_Surplus_Rate_Target");  
    V("Government_Max_Expenses_Surplus");  
    V("Government_Max_Expenses_Ceiling");  
    V("Government_Max_Expenses");  
    V("Government_Effective_Expenses");  
    V("Government_Effective_Wages");  
    V("Government_Effective_Unemployment_Benefits");  
    V("Government_Effective_Consumption");  
    V("Government_Effective_Investment"); 
    V("Government_Effective_Inputs"); 
                            
    /*****CAPITAL GOODS DEMAND*****/
    V("Firm_Demand_Capital_Goods");                             
    V("Country_Domestic_Capital_Goods_Demand");                          		                  		
    V("Firm_Effective_Orders_Capital_Goods");              		

    /*****PLANNED PRODUCTION*****/
    V("Firm_Expected_Demand");                                   
    V("Firm_Planned_Production");                              

    /*****EFFECTIVE PRODUCTION AND INPUT DEMAND*****/
    V("Firm_Available_Inputs_Ratio");                       	
    V("Capital_Good_Productivity");                        		                                                                     
    V("Firm_Input_Demand_Next_Period");                         
    V("Country_Domestic_Intermediate_Demand");                     		                        		                    		
    V("Firm_Effective_Production");   
    V("Sector_Effective_Production");                           
    V("Capital_Good_Production");                           	
    V("Firm_Avg_Productivity"); 
    V("Firm_Capacity_Utilization");	
    V("Sector_Capacity_Utilization");		
    V("Country_Capacity_Utilization");							

    /*****CONSUMPTION DEMAND AND IMPORTS*****/
    V("Household_Avg_Real_Income");
    V("Household_Avg_Nominal_Income");
    V("Household_Real_Autonomous_Consumption");
    V("Household_Real_Desired_Domestic_Consumption");
    V("Household_Real_Desired_Imported_Consumption");
    V("Household_Desired_Expenses");
    V("Household_Interest_Payment");
    V("Household_Debt_Payment");
    V("Household_Financial_Obligations");
    V("Household_Liquidity_Preference");
    V("Household_Retained_Deposits");
    V("Household_Internal_Funds");
    V("Household_Max_Debt_Rate");
    V("Household_Max_Loans");
    V("Household_Demand_Loans");
    V("Household_Effective_Loans");
    V("Household_Funds");
    V("Household_Maximum_Expenses");
    V("Household_Real_Domestic_Consumption_Demand");
    V("Household_Real_Imported_Consumption_Demand");
    V("Country_Domestic_Consumption_Demand"); 

    /*****EFFECTIVE ORDERS, SALES AND PROFITS*****/
    V("Sector_Effective_Orders");                          		
    V("Firm_Effective_Orders");                                 
    V("Firm_Sales");                                           
    V("Firm_Delivery_Delay");                                  
    V("Sector_Sales");                                     		
    V("Firm_Stock_Inventories");                               
    V("Firm_Effective_Market_Share");                           
    V("Firm_Revenue");  
    V("Firm_Net_Revenue");                                        
    V("Firm_Indirect_Tax");                                     							   										   	                             		           		
    V("Firm_Interest_Payment");
    V("Firm_Debt_Payment");
    V("Firm_Financial_Obligations");
    V("Firm_Deposits_Return");
    V("Firm_Net_Profits");
    V("Firm_RND_Expenses");                                      
    V("Firm_Retained_Profits");                                 
    V("Firm_Distributed_Profits");                             
    V("Firm_Profit_Rate");	                     		                                   		                                 		
    V("Sector_Demand_Met");                                		
    V("Sector_Extra_Imports");                                     
    V("Sector_Demand_Met_By_Imports");                            		

    /*****R&D*****/
    V("Firm_Innovation_Productivity");                          
    V("Firm_Imitation_Productivity");                           
    V("Firm_Frontier_Productivity");                            
    V("Firm_Quality");										   	

    /*****CAPITAL AND INVESTMENT DECISIONS*****/
    V("Firm_Investment_Period");						   		
    V("Firm_Productive_Capacity_Depreciation");                 
    V("Firm_Effective_Productive_Capacity_Variation"); 
    V("Firm_Effective_Capital_Goods_Expansion");
    V("Firm_Effective_Capital_Goods_Replacement");         
    V("Firm_Productive_Capacity");   
    V("Firm_Capital");                          
    V("Firm_Max_Productivity");                   				
    V("Firm_Expected_Sales_Long_Term");                         
    V("Firm_Desired_Expansion_Investment_Expenses");            
    V("Firm_Desired_Replacement_Investment_Expenses");			
    V("Firm_Desired_Investment_Expenses");

    /*****FINANCIAL CONSTRAINTS*****/
    V("Firm_Liquidity_Preference");								
    V("Firm_Retained_Deposits");								
    V("Firm_Internal_Funds");									
    V("Firm_Max_Debt_Rate");								
    V("Firm_Available_Loans");                                  
    V("Firm_Demand_Loans");
    V("Bank_Demand_Loans");
    V("Bank_Effective_Loans");
    V("Bank_Demand_Met");
    V("Loans_Distribution_Firms");
    V("Firm_Effective_Loans");
    V("Firm_Credit_Rationing");
    V("Firm_Total_Funds");                                       

    /*****EFFECTIVE INVESTMENT*****/
    V("Firm_Effective_Expansion_Investment_Expenses");          
    V("Firm_Demand_Productive_Capacity_Expansion");              
    V("Firm_Available_Funds_Replacement");                       
    V("Firm_Demand_Productive_Capacity_Replacement");           
    V("Firm_Replacement_Expenses");							   	
    V("Firm_Effective_Investment_Expenses");
    V("Firm_Available_Funds_After_Replacement");		
    V("Firm_Modernization_Rate");		

    /*****DEBT*****/
    V("Firm_Stock_Loans_Short_Term");
    V("Firm_Stock_Loans_Long_Term");
    V("Firm_Stock_Loans");                                       
    V("Firm_Stock_Deposits");									                                          
    V("Firm_Debt_Rate");  
    V("Firm_Financial_Position");                                      

    /*****ENTRY & EXIT*****/                            	
    V("Sector_Avg_Productivity");                           	
    V("Sector_Avg_Quality");                         			
    V("Sector_Max_Quality"); 
    V("Exit"); 
    V("Exit_Deposits_Distributed"); 
    V("Exit_Defaulted_Loans");                     			
    V("Sector_Entry_Condition");                                
    V("Sector_Productive_Capacity_Exit");						
    V("Sector_Productive_Capacity_Entry");						
    V("Sector_Productive_Capacity_Available"); 

    /*****HOUSEHOLD INCOME*****/
    V("Country_Price_Index");                                       	
    V("Country_Consumer_Price_Index"); 
    V("Financial_Sector_Profits");
    V("Financial_Sector_Distributed_Profits");  
    V("Country_Distributed_Profits"); 
    V("Country_Total_Profits"); 
    V("Country_Total_Wages");  
    V("Household_Nominal_Disposable_Income"); 
    V("Household_Taxation");                             		
    V("Household_Real_Disposable_Income"); 

    /*****FINANCIAL SECTOR CONSOLIDATION*****/
    V("Sector_Stock_Loans");
    V("Sector_Stock_Deposits");
    V("Household_Available_Deposits");
    V("Household_Stock_Loans");
    V("Household_Stock_Deposits");
    V("Bank_Stock_Loans_Short_Term");
    V("Bank_Stock_Loans_Long_Term");
    V("Bank_Total_Stock_Loans");
    V("Bank_Stock_Deposits");
    V("Bank_Default_Share");
    V("Financial_Sector_Accumulated_Profits");
    V("Financial_Sector_Stock_Loans_Short_Term");
    V("Financial_Sector_Stock_Loans_Long_Term");
    V("Financial_Sector_Total_Stock_Loans");
    V("Financial_Sector_Short_Term_Rate");
    V("Financial_Sector_Stock_Deposits");
    V("Financial_Sector_Normalized_HHI");

    V("Bank_Effective_Profit_Rate");
    V("Sector_Effective_Loans");
    V("Sector_Short_Term_Rate");

    /*****MACRO RESULTS*****/
    V("Country_Inventories");                             	
    V("Country_Total_Nominal_Production");                            	
    V("Country_Capacity_Utilization");               	
    V("Country_Nominal_Consumption_Production");                                    		               
    V("Country_Nominal_Capital_Production");                                     		
    V("Country_Nominal_Input_Production");											
    V("Sector_Participation");									
    V("Government_Indirect_Taxes");                                  
    V("Country_Profit_Share");                                      	
    V("Country_Wage_Share"); 
    V("Country_Avg_Profit_Rate");                                       	
    V("Country_GDP");                                            		
    V("Country_GDP_Demand");                                   	    	
    V("Country_Annual_Growth");                                     	                           	
    V("Country_Real_GDP");                                          	
    V("Country_Annual_Real_Growth");                                	
    V("Country_Likelihood_Crisis");                                 	
    V("Sector_Employment");                                 						    	
    V("Sector_Idle_Capacity");									
    V("Country_Idle_Capacity");  
    V("Country_Gini_Income");
    V("Country_Gini_Wealth");

    /*****ANALYSIS*****/
    V("Household_Income_Share");
    V("Household_Wealth_Share");
    V("P");                                                
    V("IDLE");                                               
    V("G_n");                                              
    V("Cri");                                              
    V("C");                                                
    V("I");                                                
    V("C_r");                                              
    V("I_r");                                              
    V("G_r");
    V("M_r");
    V("PDEBT");
    V("PROD");                                       
    V("PROFITS");
    V("GDP_G");
    V("CON_G");
    V("INV_G");
    V("GOV_G");
    V("PROFITS_G");
    V("WAGE_G");
    V("PDEBT_G");
    V("PROD_G");

RESULT(t)
