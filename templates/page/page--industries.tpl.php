	<?php render($page['content']['metatags']); ?>
  <?php print render($page['header']); ?>

  <main data-role="content">
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

		<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	  <a id="main-content"></a>
	  <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
	  <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	  <?php print render($tabs2); ?>
	  <?php print $messages; ?>
	  <?php print render($page['help']); ?>
	  <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
    <section class="content">
	    <div class="container clear">
	    	<article>
	    		<section class="clear"><?php
					print render($page['content']);
					// need to section-out left/right content ?>
	    		</section>
	    		<section class="clear"><?php
			      print render($page['left_right_p_section']);
			      print render($page['left_right_section']);
		      ?>
	    		</section>
	    	</article>
	    	<aside class="sticky-aside" role="complementary">
			    <?php if ($page['sidebar_links_industries']): ?>
		      <section class="links">
		        <?php print render($page['sidebar_links_industries']); ?>
		      </section>
					<?php endif;
					if ($page['sidebar_cta']):
						print render($page['sidebar_cta']);
					endif;?>
	    	</aside>
			</div>
    </section><?php
    if($full_body_cta = render($page['full_body_cta'])):?>
    <section class="content cta">
    	<div class="container clear"><?php
			print $full_body_cta;?>
    	</div>
    </section><?php
		endif;
		if(isset($page['client_grid']) && !empty($page['client_grid'])):?>
    <section class="customers"><?php
			print render($page['client_grid']);// requires aconex module?>
    </section><?php
		endif;
		if(isset($page['project_highlights']) && !empty($page['project_highlights'])):?>
    <section class="with-headline">
    	<div class="container clear">
    		<h2><?php echo t('Aconex project highlights');?></h2><?php
				print render($page['project_highlights']);// requires aconex module ?>
    	</div>
    </section><?php
		endif;
		if(isset($page['body_resource_offers']) && !empty($page['body_resource_offers'])):
		?>
    <section class="content">
			<div class="container with-headline clear">
				<h2><?php echo t("Trusted by the world's largest projects. Learn more.");?></h2><?php
				print render($page['body_resource_offers']);// requires aconex module?>
			</div>
    </section><?php
    endif;?>

	</main>
