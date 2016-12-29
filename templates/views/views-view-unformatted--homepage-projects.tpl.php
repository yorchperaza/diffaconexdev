<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php $count = 1; ?>
<div class="mosaic">
  <div class="mosaic__column mosaic__column--1">
    <?php foreach (array_slice($rows, 0, 2, true) as $id => $row): ?>
      <div class="mosaic__item mosaic__item--<?php print $count; ?>">
        <?php print $row; ?>
      </div>
      <?php $count++; ?>
    <?php endforeach; ?>
  </div>

  <div class="mosaic__column mosaic__column--2">
    <div class="mosaic__item mosaic__item--3">
      <?php print $rows[2]; ?>
      <?php $count++; ?>
    </div>
  </div>

  <div class="mosaic__column mosaic__column--3">
    <div class="mosaic__item mosaic__item--4">
      <?php print $rows[3]; ?>
      <?php $count++; ?>
    </div>
  </div>

  <div class="mosaic__column mosaic__column--4">
    <?php foreach (array_slice($rows, 4, 3, true) as $id => $row): ?>
      <div class="mosaic__item mosaic__item--<?php print $count; ?>">
        <?php print $row; ?>
      </div>
      <?php $count++; ?>
    <?php endforeach; ?>
  </div>
</div>
