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
		    	<section class="news-columnize clear">
						<section class="dontsplit columnize-break-after">
							<div class="container">
								<h2><?php echo t('News releases'); ?></h2>
								<?php print render($page['news_page_news']);?>
							</div>
						</section>
						<section class="dontsplit">
							<div class="container">
								<h2><?php echo t('Articles'); ?></h2>
								<?php print render($page['news_page_article']);?>
							</div>
						</section>
					</section>
		    	<aside role="complementary"><?php
						if ($page['sidebar_news_cta']):
							print render($page['sidebar_news_cta']);
						endif;?>
		    	</aside>

				</div>

    </section>

	</main>
