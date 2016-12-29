<?php
	// Create a new demandbase object and get the industry and sub industry
	global $db_company_industry;
	global $db_company_sub_industry;

	// Only create DemandBase request when necessary
	if (module_exists('demandbase') && !isset($_SESSION['demandbase']['industry']))
	{
		$demandbase_client_obj = new demandbase_client();
		$db_company_industry = $demandbase_client_obj->fetch_data('industry');
		$db_company_sub_industry = $demandbase_client_obj->fetch_data('sub_industry');

		$_SESSION['demandbase']['industry'] = $db_company_industry;
		$_SESSION['demandbase']['sub_industry'] = $db_company_sub_industry;
	}
