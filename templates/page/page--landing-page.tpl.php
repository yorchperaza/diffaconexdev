<?php
/**
 * @file
 * Page template for a landing page node.
 */
?>
<main>
  <?php print render($page['content']); ?>
</main>

<?php if ($tabs): ?>
  <div id="tabs-wrapper" class="clearfix">
    <?php print render($tabs); ?>
  </div>
<?php endif; ?>
