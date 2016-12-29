<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php
$cta_html = $cta_h = $cta_a = $cta_l = '';
$cta_opts = array('attributes' => array('class' => 'button'));
$cta_h_opts = array('attributes' => array());

if(sizeof($fields) > 0)
{
	foreach ($fields as $id => $field):
		// Construct usable CTA view
		switch($id)
		{
			case 'nid':
				$event = node_load($field->raw);
				$cta_l = 'node/'.$field->nid;
				if($event->field_resource_in_new_window[LANGUAGE_NONE][0]['value'] === '1') {
					$cta_opts['attributes']['target'] = '_blank';
					$cta_h_opts['attributes']['target'] = '_blank';
				}

				$cta_h = '<h3>'.l($event->field_cta_headline[LANGUAGE_NONE][0]['value'], $cta_l, $cta_h_opts).'</h3>';
				$cta_p = '<p>'.$event->field_cta_body[LANGUAGE_NONE][0]['value'].'</p>';
				$cta_a = $event->field_cta_button[LANGUAGE_NONE][0]['value'];
			break;
		}
		?>
	<?php endforeach;

	if(!empty($cta_a) && !empty($cta_l))
		$cta_html = '<section class="cta">'.$cta_h.$cta_p.l($cta_a, $cta_l, $cta_opts).'</section>';
}
echo $cta_html;
