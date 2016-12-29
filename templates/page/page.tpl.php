		<?php render($page['content']['metatags']); ?>
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

    <section class="content<?php echo (empty($page['sidebar_links_solutions']) && empty($page['sidebar_cta']) && empty($page['sidebar_misc'])) ? ' full-width' : ''; ?>">
    	<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	    <a id="main-content"></a>
	    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
	    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	    <?php print render($tabs2); ?>
	    <?php print $messages; ?>
	    <?php print render($page['help']); ?>
	    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	    <?php $sidebar_cta = trim(render($page['sidebar_cta'])); ?>
	    
	    <div class="container clear">
	    	<article>
	    		<section class="clear"><?php
					print render($page['content']);
					// need to section-out left/right content ?>
	    		</section>
	    		<section class="clear"><?php
			      print render($page['left_right_section']);
		      ?>
	    		</section>
					<?php // Bonus SEO block
					if(isset($page['sub_body']) && !empty($page['sub_body'])):?>
					<section class="with-headline sub-body">
						<?php print render($page['sub_body']);// requires aconex module ?>
					</section><?php
					endif;?>
	    	</article>
	    	<aside class="sticky-aside" role="complementary">
			    <?php if ($page['sidebar_links_solutions']): ?>
		      <section class="links">
		        <?php print render($page['sidebar_links_solutions']); ?>
		      </section>
					<?php endif;
					if ($page['sidebar_cta']):
						print render($page['sidebar_cta']);
					endif;
					if ($page['sidebar_misc']):
						print render($page['sidebar_misc']);
					endif;?>
	    	</aside>
			</div>
    </section>
    <?php
    // This should currently only be utilized by 'is solution' pages
		if(isset($page['project_highlights']) && !empty($page['project_highlights'])):?>
    <section class="with-headline">
    	<div class="container clear">
    		<h2><?php echo t('Aconex project highlights');?></h2><?php
				print render($page['project_highlights']);// requires aconex module ?>
    	</div>
    </section><?php endif; ?>
		<?php if ($full_body_cta = render($page['full_body_cta'])) : ?>
		<section class="content cta">
			<div class="container container-medium clear"><?php
				print $full_body_cta;?>
			</div>
		</section>
		<?php endif; ?>
