<?php
/**
 * If map filter is triggered, alter the plotted locations
 *
**/
function acx_views_query_alter(&$view, &$query)
{
	// Use for both the map & the grid results
  $views = array('projects_map', 'project_grid');
	if(isset($_REQUEST) && in_array($view->name, $views))
	{
		// Do we have filter vars?
		$filter_region = $filter_industry = NULL;
		if($_SERVER['REQUEST_METHOD'] == 'POST')
		{
			if(isset($_REQUEST['field_region']) && !empty($_REQUEST['field_region']) && $_REQUEST['field_region'] != '8')
			{
				$filter_region = $_REQUEST['field_region'];
			}
			elseif(in_array($view->name, $views) && isset($_SESSION['p_filter']) && !empty($_SESSION['p_filter']['field_region']))
			{
				$filter_region = $_SESSION['p_filter']['field_region'];
			}

			if(isset($_REQUEST['field_industry']) && !empty($_REQUEST['field_industry']) && $_REQUEST['field_industry'] != '0')
			{
				$filter_industry = $_REQUEST['field_industry'];
			}
			elseif(in_array($view->name, $views) && isset($_SESSION['p_filter']['field_industry']))
			{
				$filter_industry = $_SESSION['p_filter']['field_industry'];
			}
		}

		if(
				$filter_region &&
				$filter_region != '8'
			)
		{
			// 8 = 'All'
			$region_join = new views_join();
			$region_join->table = 'field_data_field_project_region';
			$region_join->field = 'entity_id';
			$region_join->left_table = 'node';
			$region_join->left_field = 'nid';
			$region_join->type = 'left';

			$query->add_relationship('region', $region_join, 'node');
			$query->add_where(sizeof($query->where)+1, 'region.field_project_region_tid', $filter_region, '=');
		}
		if(
				$filter_industry &&
				$filter_industry != '0'
			)
		{
			$industry_join = new views_join();
			$industry_join->table = 'field_data_field_project_industry';
			$industry_join->field = 'entity_id';
			$industry_join->left_table = 'node';
			$industry_join->left_field = 'nid';
			$industry_join->type = 'left';

			$query->add_relationship('industry', $industry_join, 'node');
			$query->add_where(sizeof($query->where)+1, 'industry.field_project_industry_tid', $filter_industry, '=');
		}

		if($view->name == 'projects_map')
		{
		}
		if($view->name == 'project_grid')
		{
		}
	}
}

