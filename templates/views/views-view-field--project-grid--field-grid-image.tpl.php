<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
	$project_size = (isset($row->field_field_project_size[0]['raw']['value']) && !empty($row->field_field_project_size[0]['raw']['value'])) ? $row->field_field_project_size[0]['raw']['value'] : '';
	$project_industry = (isset($row->field_field_project_industry[0]['rendered']['#markup']) && !empty($row->field_field_project_industry[0]['rendered']['#markup'])) ? $row->field_field_project_industry[0]['rendered']['#markup'] : '';
?>
	<div class="image">
		<?php if (!empty($project_industry)) : ?><h4><?php echo $project_industry; ?></h4><?php endif; ?>
		<?php
		$g_target = NULL;
		if(isset($row->{field_field_resources_title_link}))
		{
			$g_link = $row->{field_field_resources_title_link}[0]['raw']['value'];
			$g_target = $row->{field_field_resource_in_new_window}[0]['raw']['value'];
		}
		else
		{
			$g_link = 'node/'.$row->nid;
		}
		$l_opts = array('target' => ($g_target == '1' ? '_blank' : ''));
		$grid_image = theme('image', array('path' => $row->{field_field_grid_image}[0]['rendered']['#item']['uri'], 'alt' => ''));
		echo image_link($grid_image, $g_link, $l_opts); ?>
		<?php if (!empty($project_size)) : ?><div class="value"><?php echo $project_size; ?></div><?php endif; ?>
	</div>