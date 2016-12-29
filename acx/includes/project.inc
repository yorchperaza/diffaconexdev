<?php
/*
 *
 *
 */

class project {
	var $type;

	function __construct() {
		global $language;

		$this->language = $language;

		$this->tax_id = NULL;
		$this->omit = array();
		$this->parent = NULL;
		$this->priority = 'industry';
		$this->region = $_SESSION['akamai']['region_info']->tid;
		$this->solution = NULL;
		$this->type = 'industry';

		// We need to identify LOTE sites because they don't necessarily adhere to the same industry structure
		if($language->language != 'en')
		{
		}

	}

	/*
	 * Return a random project based on the construct criteria
	 *
	*/
	public function get_project_random() {

		$in_depth = term_depth($this->tax_id);
		//  var_dump($in_depth);exit;
		// No projects should be in the top depth, get something from the child instead
		if ($this->tax_id && $in_depth == '1')
		{
			$children = taxonomy_get_children($this->tax_id);
			if (!empty($children)) {
				$tids = array_keys($children);
				shuffle($tids);
				$this->tax_id = $tids[0];
			}
		}

		$project_query = db_select('node', 'n');
		$project_query->join('field_data_field_project_preview_title', 'ppt', 'n.nid = ppt.entity_id');
		$project_query->join('field_data_field_project_preview_desc', 'ppd', 'n.nid = ppd.entity_id');
		$project_query->join('field_data_field_featured_circle_image', 'gci', 'n.nid = gci.entity_id');
		$project_query->join('field_data_field_grid_image', 'gi', 'n.nid = gi.entity_id');
		$project_query->leftJoin('field_data_field_project_pull_quote', 'pq', 'n.nid = pq.entity_id');
		$project_query->leftJoin('field_data_field_pull_quote_credit', 'pqc', 'n.nid = pqc.entity_id');
		$project_query->leftJoin('field_data_field_project_size', 'ps', 'n.nid = ps.entity_id');

		if ($this->type == 'org_type')
			$project_query->leftJoin('field_data_field_project_org_type', 'pot', 'n.nid = pot.entity_id');
		elseif ($this->type == 'industry')
			$project_query->leftJoin('field_data_field_project_industry', 'pi', 'n.nid = pi.entity_id');

		if ($this->solution)
			$project_query->leftJoin('field_data_field_project_solutions', 'psol', 'n.nid = psol.entity_id');

		if ($this->region)
			$project_query->leftJoin('field_data_field_project_region', 'pr', 'n.nid = pr.entity_id');

		if ($this->parent)
			$project_query->leftJoin('taxonomy_term_hierarchy', 'tth', 'pi.field_project_industry_tid = tth.tid');

		$project_query->fields('n', array('nid', 'title'))
			->fields('ppt', array('field_project_preview_title_value'))
			->fields('ppd', array('field_project_preview_desc_value'))
			->fields('gci', array('field_featured_circle_image_fid', 'field_featured_circle_image_alt'))
			->fields('gi', array('field_grid_image_fid', 'field_grid_image_alt'))
			->fields('pq', array('field_project_pull_quote_value'))
			->fields('pqc', array('field_pull_quote_credit_value'))
			->fields('ps', array('field_project_size_value'));

		if ($this->tax_id == 'org_type')
			$project_query->fields('pot', array('field_project_org_type_tid', 'bundle'));
		elseif ($this->type == 'industry')
			$project_query->fields('pi', array('field_project_industry_tid', 'bundle'));

		$project_query->condition('gi.bundle', 'project', '=')
									->condition('n.language', $this->language->language, '=');

		if ($this->region)
			$project_query->condition('pr.field_project_region_tid', $this->region, '=');

		if ($this->parent)
			$project_query->condition('tth.parent', $this->parent, '=');

		// Mostly industry is the priority, but sometimes it is solution
		if ($this->priority == 'solution')
		{
			if ($this->solution)
				$project_query->condition('psol.field_project_solutions_tid', $this->solution, '=');
		}
		else
		{
			if ( $this->type == 'org_type')
			{
				$project_query->condition('pot.field_project_org_type_tid', $this->tax_id, '=');
			}
			elseif ($this->type == 'industry')
				$project_query->condition('pi.field_project_industry_tid', $this->tax_id, '=');
		}

		if ( !empty($this->omit))
		{
			if (is_array($this->omit))
			{
				$project_query->condition('n.nid', $this->omit, 'NOT IN');
			}
			elseif ($this->omit)
			{
				$project_query->condition('n.nid', $this->omit, '!=');
			}
		}

		$project_query->range(0, 1)
			->orderRandom();

		// dpq($project_query);
		$project_result = $project_query->execute();

		if ($project_result->rowCount() == 0)
		{
			// First remove the solutions
			if ($this->solution)
			{
				$this->priority = 'industry';
				$this->solution = FALSE;
			}
			elseif ($this->parent)
			{
				if($this->region)
				{
					// Geared to LOTE (parent) entries, if we have parent - toss the region first
					$this->region = FALSE;
				}
				else
				{
					// Re-instate the region, kill the parent and move on to the next clause
					$this->region = $_SESSION['akamai']['region_info']->tid;
					$this->parent = FALSE;
				}
			}
			elseif ($this->type == 'org_type')
			{
				if($this->region)
				{
					// Geared to LOTE (parent) entries, if we have parent - toss the region first
					$this->region = FALSE;
				}
				else
				{
					// Re-instate the region, kill the industry the parent and move on to the next clause
					$this->region = $_SESSION['akamai']['region_info']->tid;
					$this->type = FALSE;
				}
			}
			else
			{
				// Geared for NON-LOTE
				// Fallback: give priority to the industry over the region
				if ($this->type && $this->region) {
					$this->region = FALSE;
				}
				elseif ($this->type && !$this->region) {
					//try the search again but this time without the industry and with the region
					$this->region = $_SESSION['akamai']['region_info']->tid;
					$this->type = FALSE;
				}
				elseif (!$this->type && $this->region)
				{
					// one last attempt - should have no values remaining at this point
					$this->region = FALSE;
				}
				else
				{
					// We've run out of options...
					return NULL;
				}
			}
			// Try again now that we've changed the priority
			$project = $this->get_project_random();
		}
		else {
			$project_obj = $project_result->fetchObject();
			$project = $project_obj;
		}

		return $project;
	}

}
/** project.inc **/