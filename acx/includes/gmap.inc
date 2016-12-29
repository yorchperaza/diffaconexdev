<?php
/**
 * Given a gmap element array containing an array of markers,
 * set one of the markers to be "open" (autoclick=true)
 * based on the user's region.
 *
 * See aconex_subtheme_gmap() function in template.php
 */
function acx_map_set_autoclick(&$element)
{
	global $language;

	// should figure out how to set the map ID for better identification
	$pg = current_path();
	$node_type = NULL;

	$map_select = "SELECT n.nid FROM node n";
	$map_join = "";
	$map_clause = "\nWHERE n.status = 1";

  if ($pg == 'node/133')
  {
    $node_type = 'project';
    $region_table = 'field_data_field_project_region';
    $region_field_name = 'field_project_region';
    $autoclick_field_name = 'field_map_autoclick';
    $region_key = 'field_region'; //submitted form field

    $map_join .= "\nINNER JOIN {field_data_field_map_autoclick} ac ON n.nid = ac.entity_id";
    $map_clause .= "\nAND ac.field_map_autoclick_value = 1
	            			AND r.field_project_region_tid = :tid";
  }
  else if($pg == 'node/129')
  {
    $node_type = 'office';
    $region_table = 'field_data_field_office_region';
    $region_field_name = 'field_office_region_tid';
    $autoclick_field_name = 'field_office_type';
    $region_key = 'field_region_office'; //submitted form field - currently not used as there is no form on offices locations

    $map_join .= "\nINNER JOIN {field_data_field_office_type} ot ON n.nid = ot.entity_id";
	  $map_clause .= "\nAND ot.field_office_type_value = 1
				            AND r.field_office_region_tid = :tid";
  }

	$map_join .= "\nINNER JOIN {$region_table} r ON n.nid = r.entity_id";
	$map_clause .= "\nAND n.type = '$node_type'
									AND n.language = '".$language->language."'
									LIMIT 1";

	$sql = $map_select.$map_join.$map_clause;

  if (!empty($node_type) && !empty($element['#gmap_settings']['markers']))
  {
    $region_field = field_info_fields($region_field_name);
    $autoclick_field = field_info_fields($autoclick_field_name);

    if (isset($region_field) && isset($autoclick_field))
    {
    	//Source region_tid in this order: _get/_post, user session, db attempt from akamai info
      $region_tid = !empty($_REQUEST[$region_key]) && is_numeric($_REQUEST[$region_key]) ?  $_REQUEST[$region_key] : (isset($_SESSION['akamai']['region_tid']) && !empty($_SESSION['akamai']['region_tid']) ? $_SESSION['akamai']['region_tid'] : get_region_info(get_akamai_country())->tid);

      if (!empty($region_tid))
      {
        // Get the node in the user's region that is
        $clause = array(':tid' => $region_tid);
        $results = db_query($sql, $clause);
        foreach($results as $row)
        {
          $node = node_load(language_node($row->nid)->nid);
          if (isset($node->location) &&
              isset($node->location['longitude']) &&
              isset($node->location['latitude']) ) {
            foreach ($element['#gmap_settings']['markers'] as $idx => $marker) {
              if ($node->location['latitude'] == $marker['latitude'] &&
                  $node->location['longitude'] == $marker['longitude']) {
                $element['#gmap_settings']['markers'][$idx]['autoclick'] = TRUE;
                break; //no need to keep looking for another marker. 1 is good.
              }
            }
          }
        }
      }
    }
  }
}