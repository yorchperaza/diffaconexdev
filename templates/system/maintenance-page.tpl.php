<?php

/**
 * @file
 * Override of the default maintenance page.
 *
 * This is an override of the default maintenance page. Used for Garland and
 * Minnelli, this file should not be moved or modified since the installation
 * and update pages depend on this file.
 *
 * This mirrors closely page.tpl.php for Garland in order to share the same
 * styles.
 */
?><!DOCTYPE html>
<html dir="<?php print $language->dir; ?>" lang="<?php print $language->language; ?>"<?php print ' '.$rdf_namespaces; ?>>
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <?php print render($head_elements); ?>
	<!--[if lt IE 9]>
	<script src="<?php echo $theme_url; ?>/js/html5shiv.min.js" type="text/javascript"></script>
	<script src="<?php echo $theme_url; ?>/js/respond.min.js" type="text/javascript"></script>
	<![endif]-->
	<!--[if lte IE 9]>
	<script type="text/javascript" src="<?php echo $theme_url; ?>/js/jquery.columnizer.min.js"></script>
	<script type="text/javascript">
		(function ($) {
			$(document).ready(function () {
				if ($('.columnize').length) {
					$('.columnize').columnize();
				}
			});
		})(jQuery);
	</script>
	<![endif]-->
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <?php print render($google_tags); ?>
  <?php print $page_top; ?>
  <div data-role="page" class="clear">
		<?php print $aconex_header; ?>
		
		<section class="banner<?php echo ($page['banner']['xlg_banner'] == true) ? ' banner-xlg' : ''; ?>"<?php echo (!empty($page['banner']['image'])) ? ' style="background-image: url(' . $page['banner']['image'] . ');"' : ''; ?>>
			<div class="background">
				<?php if ($page['banner']['has_container'] == true) : ?>
				<div class="container clear">
					<?php if (!empty($page['banner']['head1'])) : ?><h2><?php echo $page['banner']['head1']; ?></h2><?php endif; ?>
					<?php if (!empty($page['banner']['head2'])) : ?><h3><?php echo $page['banner']['head2']; ?></h3><?php endif; ?>
					<?php if (!empty($page['banner']['caption'])) : ?><figcaption><?php echo $page['banner']['caption']; ?></figcaption><?php endif; ?>
					<?php if (!empty($page['banner']['cta_button'])) echo $page['banner']['cta_button']; ?>
				</div>
				<?php endif; ?>
			</div>
		</section>

    <section class="content">
    	<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	    <a id="main-content"></a>
	    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
	    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	    <?php print render($tabs2); ?>
	    <?php print $messages; ?>
	    <?php print render($page['help']); ?>
	    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	    <div class="container clear">
				<?php if ($title): ?><h2><?php print $title ?></h2><?php endif; ?>
				<?php print $content ?>
			</div>
    </section>
    
		<?php print $aconex_footer; ?>
  </div>
  <?php print $page_bottom; ?>
</body>
</html>
