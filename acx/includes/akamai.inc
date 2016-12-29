<?php

/**
 * Get country values from akamai data
 *
**/
function get_akamai_country() {
	if(!$_SERVER['HTTP_X_AKAMAI_EDGESCAPE']) {
		return false;
	}
	parse_str(str_replace(",", "&", $_SERVER['HTTP_X_AKAMAI_EDGESCAPE']), $akamai); // convert georegion=16,country_code=AU,region_code=NSW,city=SYDNEY,.. into an array
	return $akamai ? $akamai['country_code'] : false;
}

/**
 * This is probably a misnomer as we are really only returning the country code
 *
**/
function parse_akamai_info(){
	$parts = array();
  if (function_exists('getallheaders')) {
    foreach (getallheaders() as $name => $value) {
      if(strtolower($name) == strtolower('X-Akamai-Edgescape'))
      {
        $parts = explode(",",$value);
        break;
      }
    }
    if(!empty($parts)){
      foreach($parts as $region_data){
        $region_item = explode("=",$region_data);
        if(!empty($region_item)){
          foreach($region_item as $region){
            if(strtolower(trim($region)) == 'country_code'){
              $country = $region_item;
              break;
            }
          }
        }
      }
    }
    if(!empty($country) && isset($country[1])){
      return $country[1];
    }
  }
}


function get_user_country_code($default = 'US'){
	global $get_user_country_code_data;
	if (!isset($get_user_country_code_data))
	{
		if($akamai_country = get_akamai_country())
		{
			$get_user_country_code_data = $akamai_country;
		}
		else
		{ // degrade to smart_ip if we don't have the data from akamai
			if(!$_SESSION['smart_ip_country_code'] || $_SESSION['smart_ip_used_ip'] != ip_address())
			{ // NB: wrap in session to stop hitting the DB too many times
				$_SESSION['smart_ip_used_ip'] = ip_address();
				$smart_ip = smart_ip_get_location(ip_address());
				if(!empty($smart_ip['country_code']))
				{
					$get_user_country_code_data = $_SESSION['smart_ip_country_code'] = $smart_ip['country_code'];
				}
				else
				{
					$get_user_country_code_data = $_SESSION['smart_ip_country_code'] = $default;
				}
			}
		}
	}
	return $get_user_country_code_data;
}