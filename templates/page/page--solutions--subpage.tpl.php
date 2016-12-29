	<?php render($page['content']['metatags']); ?>
	<section class="banner<?php echo ($page['banner']['xlg_banner'] == true) ? ' banner-xlg' : ''; ?> banner-solution"<?php echo (!empty($page['banner']['image'])) ? ' style="background-image: url(' . $page['banner']['image'] . ');"' : ''; ?>>
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
		<?php if (isset($page['section_menu_anchors'])): ?>
		<div class="sub-nav solutions-nav">
			<div class="container menu-anchors">
			<?php echo $page['section_menu_anchors']; ?>
			</div>
		</div>
		<?php endif; ?>
	</section>

    <section class="content<?php echo (empty($page['sidebar_links_solutions']) && empty($page['sidebar_cta']) && empty($page['sidebar_misc'])) ? ' full-width' : ''; ?> content-solution">
    	<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	    <a id="main-content"></a>
	    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>
	    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	    <?php print render($tabs2); ?>
	    <?php print $messages; ?>
	    <?php print render($page['help']); ?>
	    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	    <?php $sidebar_cta = trim(render($page['sidebar_cta'])); ?>
	    
	    <div class="container-solution clear">
	    	<article>
	    		<section <?php if (isset($page['body_id'])) { ?>id="<?php echo $page['body_id']; ?>"<?php } ?> class="clear">
					<div class="container">
					<?php print render($page['content']); // need to section-out left/right content ?>
					</div>
	    		</section>
				
				<section class="left-right-solution-section clear">
					<?php print render($page['left_right_solution_section']); ?>
				</div>

				<?php 
					// Bonus SEO block
					if (isset($page['sub_body']) && !empty($page['sub_body'])) :
				?>
				<section class="with-headline sub-body">
					<div class="container">
					<?php print render($page['sub_body']);// requires aconex module ?>
					</div>
				</section>
				<?php
					endif;
				?>
	    	</article>
		</div>
    </section>
    <?php
    // This should currently only be utilized by 'is solution' pages
		if(isset($page['project_highlights']) && !empty($page['project_highlights'])):?>
    <section class="with-headline project-highlights">
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