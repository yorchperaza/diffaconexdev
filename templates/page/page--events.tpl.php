	<?php render($page['content']['metatags']); ?>
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

    <section class="content">
			<?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
	    <?php if ($tabs): ?><div id="tabs-wrapper" class="clearfix"><?php endif; ?>

	    <?php if ($tabs): ?><?php print render($tabs); ?></div><?php endif; ?>
	    <?php print render($tabs2); ?>
	    <?php print $messages; ?>
	    <?php print render($page['help']); ?>
	    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

			<div class="container clear">
	    	<article>
	    		<?php if($title):?>
	    		<h1><?php echo $title;?></h1>
	    		<?php endif; ?>
	    		<section class="clear"><?php
					print render($page['content']); ?>
	    		</section>
	    	</article>
	    	<aside class="sticky-aside" role="complementary">
					<?php
					if ($page['sidebar_misc']):
						print render($page['sidebar_misc']);
					endif;?>
	    	</aside>
			</div>
    </section>
	</main>
