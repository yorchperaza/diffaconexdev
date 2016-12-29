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
$title = $row->{node_title};
$title .= (isset($row->{field_field_state_country_abrvn}[0]['raw']['value']) && !empty($row->{field_field_state_country_abrvn}[0]['raw']['value'])) ? ', ' . $row->{field_field_state_country_abrvn}[0]['raw']['value'] : '';

$region_office = (isset($row->{field_field_office_type_1}[0]['raw']['value'])) ? $row->{field_field_office_type_1}[0]['raw']['value'] : '';

$department = (isset($row->{field_field_office_department}[0]['rendered']['#title'])) ? $row->{field_field_office_department}[0]['rendered']['#title'] : '';

$address = (isset($row->{field_field_office_address}[0]['raw']['value'])) ? $row->{field_field_office_address}[0]['raw']['value'] : '';

$map_link = (isset($row->{location_latitude}) && !empty($row->{location_latitude}) && isset($row->{location_longitude}) && !empty($row->{location_longitude})) ? 'http://maps.google.com/maps?z=2&saddr=&daddr=' . $row->{location_latitude} . ',' . $row->{location_longitude} : '';

$phone = (isset($row->{field_field_office_phone}[0]['raw']['value'])) ? $row->{field_field_office_phone}[0]['raw']['value'] : '';

$fax = (isset($row->{field_field_office_fax}[0]['raw']['value'])) ? $row->{field_field_office_fax}[0]['raw']['value'] : '';

$helpline = (isset($row->{field_field_office_helpline}[0]['raw']['value'])) ? $row->{field_field_office_helpline}[0]['raw']['value'] : '';
?>
<h3><?php echo $title; ?></h3>
<?php if (isset($region_office) && $region_office == 1) : ?><h3 class="subhead"><?php echo t('Regional Office');?></h3><?php endif; ?>
<?php if (!empty($department)) : ?><h4><?php echo $department; ?></h4><?php endif; ?>
<?php echo $address; ?>
<?php if (!empty($map_link)) : ?><p><a class="view-project-link" href="<?php echo $map_link; ?>" target="_blank"><?php echo t('Map and directions');?></a></p><?php endif; ?>
<p>
<?php if (!empty($phone)) : ?><b><?php echo t('T');?></b> <?php echo $phone; ?><br><?php endif; ?>
<?php if (!empty($fax)) : ?><b><?php echo t('F');?></b> <?php echo $fax; ?><br><?php endif; ?>
<?php if (!empty($helpline)) : ?><b><?php echo t('HELP');?></b> <?php echo $helpline; ?><?php endif; ?>
</p>
