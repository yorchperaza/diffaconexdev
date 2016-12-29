<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup themeable
 */
?><!DOCTYPE html>
<!--[if IE 7]>
<html class="ie ie7" dir="<?php print $language->dir; ?>" lang="<?php print $language->language; ?>"<?php print ' '.$rdf_namespaces; ?>>
<![endif]-->
<!--[if IE 8]>
<html class="ie ie8" dir="<?php print $language->dir; ?>" lang="<?php print $language->language; ?>"<?php print ' '.$rdf_namespaces; ?>>
<![endif]-->
<!--[if !(IE 7) | !(IE 8) ]><!-->
<html dir="<?php print $language->dir; ?>" lang="<?php print $language->language; ?>"<?php print ' '.$rdf_namespaces; ?>>
<!--<![endif]-->
<head>
  <title>{page-title listing="Jobs - Recent Jobs" search="Jobs - Search Results" detail="Jobs - Job Details - [job.title]"}</title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <?php print $page_top; ?>
  <div data-role="page" class="clear">
		<?php print $aconex_header;?>
		<main data-role="content">
			<section class="banner">
				<div class="background">
					<div class="container clear">
						<h2>Current Opportunities</h2>
					</div>
				</div>
			</section>

			{form}
	    <section class="content">
		    <div class="container clear">
		    	<article>

		    		{messages}
						{pages}

					</article>
		    	<aside class="sticky-aside" role="complementary">
		    		<section class="aside-section">
							<h2>Job Search</h2>
							{search-keyword placeholder="Search for jobs"}
							{search-filters button-text="Filter Results"}
						</section>
						<section>
							<h2>Why work at Aconex?</h2>
							<p>You'll be joining an established, fast-growing SaaS business, part of a smart, global team that's transforming how iconic projects are delivered around the world.</p>
							<a href="http://www.aconex.com/company/careers" class="button">Learn more</a>
						</section>
		    	</aside>
				</div>
	    </section>
	    {/form}

		</main>
		<?php print $pageup_footer; ?>
  </div>
  <?php print $page_bottom; ?>
	<!--[if lte IE 9]>
	<script type="text/javascript" src="js/jquery.columnizer.min.js"></script>
	<script type="text/javascript">
		if ($('.columnize').length) {
			$('.columnize').columnize();
		}
	</script>
	<![endif]-->
</body>
</html>
