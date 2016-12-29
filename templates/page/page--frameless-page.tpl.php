<?php
/**
 * Template for a frameless page.
 */
?>

<?php print render($page['content']); ?>

<?php if ($tabs): ?>
  <div id="tabs-wrapper" class="clearfix">
    <?php print render($tabs); ?>
  </div>
<?php endif; ?>
