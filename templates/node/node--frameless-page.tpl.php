<?php
/**
 * @file
 * Template for a frameless page node.
 */
?>
<header>
  <h1><?php print $title; ?></h1>

  <?php if (!empty($content['field_frameless_page_header'])): ?>
    <?php print render($content['field_frameless_page_header']); ?>
  <?php endif; ?>
</header>

<main class="container">
  <?php print render($content['body']); ?>

  <div class="clearfix">
    <?php if (!empty($content['field_frameless_page_left'])): ?>
      <?php print render($content['field_frameless_page_left']); ?>
    <?php endif; ?>

    <?php if (!empty($content['field_frameless_page_right'])): ?>
      <?php print render($content['field_frameless_page_right']); ?>
    <?php endif; ?>
  </div>
  
  <?php if (!empty($content['field_frameless_page_footer'])): ?>
    <?php print render($content['field_frameless_page_footer']); ?>
  <?php endif; ?>
</main>
