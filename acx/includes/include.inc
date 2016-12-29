<?php

/**
 * Create header to be used on site
 * This may be better served somewhere else but here for now...
**/
function acx_header($vars)
{
	$main_nav = get_main_nav();
	$top_nav = get_top_nav();
  $header_img = array('path' => path_to_theme().'/images/aconex.png',
								      'alt' => t('Aconex'),
								      'id' => 'logo');
  $header_logo = theme('image', $header_img);

  $search_form = module_invoke('search', 'block_view', 'search');

	$header_html = '
  	<div class="search-form-top">
			<div class="container clear">
		' . render($search_form) . '
			</div>
		</div>

    <header data-role="header" class="clear header-default">
    	<div class="container clear">'.
    		l($header_logo, language_homepage(), array('html' => TRUE, 'attributes' => array('class' => array('logo'), 'title' => t('Home')))).
				'<div class="expandable nav-container clear">
					<div class="expand-trigger nav-trigger">
						<i class="fa fa-bars"></i>
					</div>
					<nav role="navigation" class="expand-item">
						<div class="cancel">'.t('Cancel').'</div>'.
						l(t('Watch 3-minute demo'), 'http://info.aconex.com/what-is-online-project-collaboration-video-US-2.html', array('attributes' => array('class' => 'button button-demo'))).
						$main_nav . '
						' . $top_nav . '
					</nav>
				</div>
    	</div>
    </header>

		<div class="sticky-space"></div>
		<div class="header-shim"></div>';

	return $header_html;
}


/**
 * Create header to be used on site
 * This may be better served somewhere else but here for now...
**/
function acx_footer($omit_orange = FALSE)
{
	$footer_links = get_footer_links();
	$legal_links = get_legal_links();

	$white_img = array('path' => path_to_theme().'/images/aconex-white.png',
							      'alt' => t('Aconex'));
  $footer_img_white = theme('image', $white_img);

  $search_form = module_invoke('search', 'block_view', 'search');

	$footer_html = '
	<footer>';

	if(!$omit_orange)
	{
		// Button
		$button = language_block(92);
		$footer_html .= '<section class="cta">
				<div class="container container-medium clear">
					<h2>'.t('Think we might be a good fit for your project?').'</h2>'.
					$button['content'].'
					</div>
				</section>';
	}

	$footer_html .= '<section class="footer clear">
			<div class="container">
				<div class="search-form-bottom">
				' . render($search_form) . '
				</div>
				<div class="columnize clear">
				' . $footer_links . '
				</div>
				<section class="social-media">
					<a href="https://www.linkedin.com/company/aconex" target="_blank"><i class="fa fa-linkedin"></i></a>
					<a href="https://www.facebook.com/Aconex" target="_blank"><i class="fa fa-facebook"></i></a>
					<a href="https://twitter.com/aconex" target="_blank"><i class="fa fa-twitter"></i></a>
					<a href="https://google.com/+aconex" target="_blank"><i class="fa fa-google-plus"></i></a>
					<a href="https://www.youtube.com/user/Aconex1" target="_blank"><i class="fa fa-youtube"></i></a>
					<a href="http://www.aconex.com/blogs" target="_blank"><i class="fa fa-rss"></i></a>
				</section>
				<section class="logo">
					'.$footer_img_white.'
				</section>
				<section class="legal">
					<div class="copyright">&copy; Aconex Ltd.</div>
					' . $legal_links . '
				</section>
			</div>
		</section>
	</footer>';

	return $footer_html;
}

function get_main_nav() {
	global $language;

	$menu_main_nav = menu_tree_all_data('menu-main-nav');
	menu_tree_add_active_path($menu_main_nav);

	$main_nav = '';
	$main_nav .= '<div class="main-nav">' . "\r\n";
	foreach($menu_main_nav as $top_level) {
		// Is active
		if(isset($top_level['link']['hidden']) && $top_level['link']['hidden'] == '1')
			continue;

		// Correct language
		if(isset($top_level['link']['language']) && $top_level['link']['language'] != LANGUAGE_NONE && $top_level['link']['language'] != $language->language)
			continue;

		$single_col = (isset($top_level['link']['options']['attributes']['class']) && in_array('single-col', $top_level['link']['options']['attributes']['class'])) ? true : false;
		$classes = 'heading clear';
		$classes .= ($top_level['link']['in_active_trail'] == 1) ? ' selected' : '';
		$fa = '';
		if (!empty($top_level['below'])) {
			$classes .= ' expand-trigger';
			$fa = ' fa-caret-right';
			$expandable = ($single_col == true) ? 'expandable single-col' : 'expandable';
			$main_nav .= '<div class="' . $expandable . '">' . "\r\n";
		}
		$classes .= (!empty($top_level['link']['options']['attributes']['class'])) ? ' ' . implode(' ', $top_level['link']['options']['attributes']['class']) : '';
		$id = (!empty($top_level['link']['options']['attributes']['id'])) ? ' id="' . $top_level['link']['options']['attributes']['id'] . '"' : '';
		$name = (!empty($top_level['link']['options']['attributes']['name'])) ? ' name="' . $top_level['link']['options']['attributes']['name'] . '"' : '';
		$rel = (!empty($top_level['link']['options']['attributes']['rel'])) ? ' rel="' . $top_level['link']['options']['attributes']['rel'] . '"' : '';
		$target = (!empty($top_level['link']['options']['attributes']['target'])) ? ' target="' . $top_level['link']['options']['attributes']['target'] . '"' : '';

		$_rel = isset($top_level['link']['options']['attributes']['rel']) ? $top_level['link']['options']['attributes']['rel'] : FALSE;
		$url = $_rel && $_rel == 'nofollow' ? '#' : url($top_level['link']['link_path']);

		$main_nav .= '<a href="' . $url . '" class="' . $classes . '"' . $id . $name . $rel . $target . '><i class="fa' . $fa . '"></i><span class="link">' . $top_level['link']['link_title'] . '</span></a>' . "\r\n";

		if (!empty($top_level['below'])) {
			$expand_trigger = ($single_col == true) ? 'expand-item' : 'expand-item columnize';
			$main_nav .= '<div class="' . $expand_trigger . '">' . "\r\n";

			$i=0;
			foreach($top_level['below'] as $second_level) {
				// hide 2nd level items not in correct language
				if(isset($second_level['link']['language']) && $second_level['link']['language'] != LANGUAGE_NONE && $second_level['link']['language'] != $language->language)
					continue;

				$sub_heading = (!empty($second_level['link']['options']['attributes']['class'])) ? ' class="' . implode(' ', $second_level['link']['options']['attributes']['class']) . '"' : '';
				$id = (!empty($second_level['link']['options']['attributes']['id'])) ? ' id="' . $second_level['link']['options']['attributes']['id'] . '"' : '';
				$name = (!empty($second_level['link']['options']['attributes']['name'])) ? ' name="' . $second_level['link']['options']['attributes']['name'] . '"' : '';
				$rel = (!empty($second_level['link']['options']['attributes']['rel'])) ? ' rel="' . $second_level['link']['options']['attributes']['rel'] . '"' : '';
				$target = (!empty($second_level['link']['options']['attributes']['target'])) ? ' target="' . $second_level['link']['options']['attributes']['target'] . '"' : '';
				$_rel = isset($second_level['link']['options']['attributes']['rel']) ? $second_level['link']['options']['attributes']['rel'] : FALSE;
				$url = $_rel && $_rel == 'nofollow' ? 'javascript:void(0)' : url($second_level['link']['link_path']);

				if (!empty($second_level['below'])) {
					$main_nav .= '<ul>';
					if ($url == 'javascript:void(0)')
						$main_nav .= '<li class="nolink"><span' . $sub_heading . $id . $name . $rel . $target . '>' . $second_level['link']['link_title'] . '</span></li>';
					else
						$main_nav .= '<li><a href="' . $url . '"' . $sub_heading . $id . $name . $rel . $target . '>' . $second_level['link']['link_title'] . '</a></li>';

					foreach($second_level['below'] as $third_level) {
						// hide disabled 3rd level items - or not in correct language
						if($third_level['link']['hidden'] == '1' || (isset($third_level['link']['language']) && $third_level['link']['language'] != LANGUAGE_NONE && $third_level['link']['language'] != $language->language))
							continue;

						$id = (!empty($third_level['link']['options']['attributes']['id'])) ? ' id="' . $third_level['link']['options']['attributes']['id'] . '"' : '';
						$name = (!empty($third_level['link']['options']['attributes']['name'])) ? ' name="' . $third_level['link']['options']['attributes']['name'] . '"' : '';
						$rel = (!empty($third_level['link']['options']['attributes']['rel'])) ? ' rel="' . $third_level['link']['options']['attributes']['rel'] . '"' : '';
						$target = (!empty($third_level['link']['options']['attributes']['target'])) ? ' target="' . $third_level['link']['options']['attributes']['target'] . '"' : '';
						$sub_heading = (!empty($third_level['link']['options']['attributes']['class'])) ? ' class="' . implode(' ', $third_level['link']['options']['attributes']['class']) . '"' : '';

						$_rel = isset($third_level['link']['options']['attributes']['rel']) ? $third_level['link']['options']['attributes']['rel'] : FALSE;
						$url = $_rel && $_rel == 'nofollow' ? '#' : url($third_level['link']['link_path']);

						$main_nav .= '<li><a href="' . $url . '"' . $sub_heading . '>' . $third_level['link']['link_title'];

						if (!empty($third_level['below'])) {
							$main_nav .= '<i class="fa fa-caret-right"></i></a>';
							$main_nav .= '<ul>';
							foreach ($third_level['below'] as $fourth_level) {
								// hide disabled 4th level items - or not in correct language
								if($fourth_level['link']['hidden'] == '1' || (isset($fourth_level['link']['language']) && $fourth_level['link']['language'] != LANGUAGE_NONE && $fourth_level['link']['language'] != $language->language))
									continue;

								$id = (!empty($fourth_level['link']['options']['attributes']['id'])) ? ' id="' . $fourth_level['link']['options']['attributes']['id'] . '"' : '';
								$name = (!empty($fourth_level['link']['options']['attributes']['name'])) ? ' name="' . $fourth_level['link']['options']['attributes']['name'] . '"' : '';
								$rel = (!empty($fourth_level['link']['options']['attributes']['rel'])) ? ' rel="' . $fourth_level['link']['options']['attributes']['rel'] . '"' : '';
								$target = (!empty($fourth_level['link']['options']['attributes']['target'])) ? ' target="' . $fourth_level['link']['options']['attributes']['target'] . '"' : '';
								$sub_heading = (!empty($fourth_level['link']['options']['attributes']['class'])) ? ' class="' . implode(' ', $fourth_level['link']['options']['attributes']['class']) . '"' : '';

								$_rel = isset($fourth_level['link']['options']['attributes']['rel']) ? $fourth_level['link']['options']['attributes']['rel'] : FALSE;
								$url = $_rel && $_rel == 'nofollow' ? '#' : url($fourth_level['link']['link_path']);
								
								$main_nav .= '<li><a href="' . $url . '"' . $sub_heading . '>' . $fourth_level['link']['link_title'] . '</a></li>';
							}
							$main_nav .= '</ul>';
						} else {
							$main_nav .= '</a>';
						}

						$main_nav .= '</li>';
					}

					$main_nav .= '</ul>';
				} else {
					$_rel = isset($second_level['link']['options']['attributes']['rel']) ? $second_level['link']['options']['attributes']['rel'] : FALSE;
					$url = $_rel && $_rel == 'nofollow' ? '#' : url($second_level['link']['link_path']);
					$main_nav .= ($i == 0) ? '<ul>' : '';
					$main_nav .= '<li><a href="' . $url . '"' . $sub_heading . $id . $name . $rel . $target . '>' . $second_level['link']['link_title'] . '</a></li>';
					$main_nav .= ($i == count($second_level)) ? '</ul>' : '';
				}

				$i++;
			}

			$main_nav .= '</div><!-- .expand-item -->' . "\r\n";
			$main_nav .= '</div><!-- .expandable -->' . "\r\n";
		}
	}
	$main_nav .= '</div>' . "\r\n";
	return $main_nav;
}

function get_top_nav() {
	global $language;

	$menu_top_nav = menu_tree_all_data('menu-top-nav');
	menu_tree_add_active_path($menu_top_nav);

	$top_nav = '';
	$top_nav .= '<div class="top-nav">' . "\r\n";
	foreach($menu_top_nav as $top_level) {
		// Is active
		if(isset($top_level['link']['hidden']) && $top_level['link']['hidden'] == '1')
			continue;

		// Correct language
		if(isset($top_level['link']['language']) && $top_level['link']['language'] != LANGUAGE_NONE && $top_level['link']['language'] != $language->language)
			continue;

		$search = (isset($top_level['link']['options']['attributes']['class']) && in_array('search', $top_level['link']['options']['attributes']['class'])) ? true : false;
		$classes = 'heading clear';
		$classes .= ($top_level['link']['in_active_trail'] == 1) ? ' selected' : '';
		$fa = '';
		if (!empty($top_level['below'])) {
			$classes .= ' expand-trigger';
			$fa = ' fa-caret-right';
			$top_nav .= '<div class="expandable">' . "\r\n";
		}
		$fa = ($search == true) ? ' fa-search' : $fa;
		$classes .= (!empty($top_level['link']['options']['attributes']['class'])) ? ' ' . implode(' ', $top_level['link']['options']['attributes']['class']) : '';
		$id = (!empty($top_level['link']['options']['attributes']['id'])) ? ' id="' . $top_level['link']['options']['attributes']['id'] . '"' : '';
		$name = (!empty($top_level['link']['options']['attributes']['name'])) ? ' name="' . $top_level['link']['options']['attributes']['name'] . '"' : '';
		$rel = (!empty($top_level['link']['options']['attributes']['rel'])) ? ' rel="' . $top_level['link']['options']['attributes']['rel'] . '"' : '';
		$target = (!empty($top_level['link']['options']['attributes']['target'])) ? ' target="' . $top_level['link']['options']['attributes']['target'] . '"' : '';

		$_rel = isset($top_level['link']['options']['attributes']['rel']) ? $top_level['link']['options']['attributes']['rel'] : FALSE;
		$url = $_rel && $_rel == 'nofollow' ? '#' : url($top_level['link']['link_path']);

		$top_nav .= '<a href="' . $url . '" class="' . $classes.'"'. $id . $name . $rel . $target . '><i class="fa' . $fa . '"></i><span class="link">' . $top_level['link']['link_title'] . '</span></a>' . "\r\n";

		if (!empty($top_level['below'])) {
			$top_nav .= '<div class="expand-item">' . "\r\n";

			$i=1;
			foreach($top_level['below'] as $second_level) {
				// hide disabled 2nd level items - or not in correct language
				if($second_level['link']['hidden'] == '1' || (isset($second_level['link']['language']) && $second_level['link']['language'] != LANGUAGE_NONE && $second_level['link']['language'] != $language->language))
					continue;

				$sub_heading = (!empty($second_level['link']['options']['attributes']['class'])) ? ' class="' . implode(' ', $second_level['link']['options']['attributes']['class']) . '"' : '';
				$id = (!empty($second_level['link']['options']['attributes']['id'])) ? ' id="' . $second_level['link']['options']['attributes']['id'] . '"' : '';
				$name = (!empty($second_level['link']['options']['attributes']['name'])) ? ' name="' . $second_level['link']['options']['attributes']['name'] . '"' : '';
				$rel = (!empty($second_level['link']['options']['attributes']['rel'])) ? ' rel="' . $second_level['link']['options']['attributes']['rel'] . '"' : '';
				$target = (!empty($second_level['link']['options']['attributes']['target'])) ? ' target="' . $second_level['link']['options']['attributes']['target'] . '"' : '';

				$onclick = '';
				if (isset($second_level['link']['options']['attributes']['rel']) && $second_level['link']['options']['attributes']['rel'] == 'alternate') {
					$parse_url = parse_url($second_level['link']['link_path']);
					$lang = str_replace('/', '', $parse_url['path']);
					$onclick = '';//' onclick="_gaq.push([\'_trackEvent\', \'LOTE\', \'Click\', \'' . $lang . '\']);"';
				}

				$_rel = isset($second_level['link']['options']['attributes']['rel']) ? $second_level['link']['options']['attributes']['rel'] : FALSE;
				$url = $_rel && $_rel == 'nofollow' ? '#' : url($second_level['link']['link_path']);
				$top_nav .= ($i == 1) ? '<section>' . "\r\n" : '';
				$top_nav .= '<a href="' . $url . '"' . $sub_heading . $id . $name . $rel . $target . $onclick . '>' . $second_level['link']['link_title'] . '</a>' . "\r\n";
				$top_nav .= ($i == count($second_level)) ? '</section>' . "\r\n" : '';
				$i++;
			}

			$top_nav .= '</div><!-- .expand-item -->' . "\r\n";
			$top_nav .= '</div><!-- .expandable -->' . "\r\n";
		}
	}
	$top_nav .= '
							<div class="button-container">
								<a href="' . url(language_link("node/734")) . '" class="heading clear"><i class="fa"></i><span class="link">'.t('Register').'</span></a>
								<a href="' . url(language_link("node/32")) . '" class="heading modal clear" onclick=""><i class="fa"></i><span class="link">'.t('Login').'</span></a>
							</div>
							';
	$top_nav .= '</div>' . "\r\n";
	return $top_nav;
	//return '<pre>'.print_r(menu_tree_all_data('menu-main-nav'),true).'</pre>';
}

function get_footer_links() {
	global $language;

	$menu_footer_links = menu_tree_all_data('menu-footer-links');

	$footer_links = '';
	$i = 0;
	foreach($menu_footer_links as $top_level) {
		// Is active
		if(isset($top_level['link']['hidden']) && $top_level['link']['hidden'] == '1')
			continue;

		// Correct language
		if(isset($top_level['link']['language']) && $top_level['link']['language'] != LANGUAGE_NONE && $top_level['link']['language'] != $language->language)
			continue;

		$classes = 'heading clear';
		$footer_links .= '<section' . ($i == 0 ? ' class="columnize-break-after"' : '') . '>' . "\r\n";
		$footer_links .= '<div class="container">' . "\r\n";

		$classes .= (!empty($top_level['link']['options']['attributes']['class'])) ? ' ' . implode(' ', $top_level['link']['options']['attributes']['class']) : '';
		$id = (!empty($top_level['link']['options']['attributes']['id'])) ? ' id="' . $top_level['link']['options']['attributes']['id'] . '"' : '';
		$name = (!empty($top_level['link']['options']['attributes']['name'])) ? ' name="' . $top_level['link']['options']['attributes']['name'] . '"' : '';
		$rel = (!empty($top_level['link']['options']['attributes']['rel'])) ? ' rel="' . $top_level['link']['options']['attributes']['rel'] . '"' : '';
		$target = (!empty($top_level['link']['options']['attributes']['target'])) ? ' target="' . $top_level['link']['options']['attributes']['target'] . '"' : '';

		$footer_links .= '<h3 class="' . $classes . '">' . $top_level['link']['link_title'] . '</h3>' . "\r\n";

		if (!empty($top_level['below'])) {
			foreach($top_level['below'] as $second_level) {
				// hide disabled 2nd level items - or not in correct language
				if($second_level['link']['hidden'] == '1' || (isset($second_level['link']['language']) && $second_level['link']['language'] != LANGUAGE_NONE && $second_level['link']['language'] != $language->language))
					continue;

				$sub_heading = (!empty($second_level['link']['options']['attributes']['class'])) ? ' class="' . implode(' ', $second_level['link']['options']['attributes']['class']) . '"' : '';
				$id = (!empty($second_level['link']['options']['attributes']['id'])) ? ' id="' . $second_level['link']['options']['attributes']['id'] . '"' : '';
				$name = (!empty($second_level['link']['options']['attributes']['name'])) ? ' name="' . $second_level['link']['options']['attributes']['name'] . '"' : '';
				$rel = (!empty($second_level['link']['options']['attributes']['rel'])) ? ' rel="' . $second_level['link']['options']['attributes']['rel'] . '"' : '';
				$target = (!empty($second_level['link']['options']['attributes']['target'])) ? ' target="' . $second_level['link']['options']['attributes']['target'] . '"' : '';

				$footer_links .= '<a href="' . url($second_level['link']['link_path']) . '"' . $sub_heading . $id . $name . $rel . $target . '>' . $second_level['link']['link_title'] . '</a>' . "\r\n";
			}

		}
		$footer_links .= '</div><!-- .container -->' . "\r\n";
		$footer_links .= '</section>' . "\r\n";
		$i++;
	}
	return $footer_links;
}

function get_legal_links() {
	global $language;

	$menu_legal_links = menu_tree_all_data('menu-footer-legal-links');

	$legal_links = '';
	foreach($menu_legal_links as $top_level) {
		// Is active
		if(isset($top_level['link']['hidden']) && $top_level['link']['hidden'] == '1')
			continue;

		// Correct language
		if(isset($top_level['link']['language']) && $top_level['link']['language'] != LANGUAGE_NONE && $top_level['link']['language'] != $language->language)
			continue;

		$classes = '';

		$classes .= (!empty($top_level['link']['options']['attributes']['class'])) ? ' ' . implode(' ', $top_level['link']['options']['attributes']['class']) : '';
		$id = (!empty($top_level['link']['options']['attributes']['id'])) ? ' id="' . $top_level['link']['options']['attributes']['id'] . '"' : '';
		$name = (!empty($top_level['link']['options']['attributes']['name'])) ? ' name="' . $top_level['link']['options']['attributes']['name'] . '"' : '';
		$rel = (!empty($top_level['link']['options']['attributes']['rel'])) ? ' rel="' . $top_level['link']['options']['attributes']['rel'] . '"' : '';
		$target = (!empty($top_level['link']['options']['attributes']['target'])) ? ' target="' . $top_level['link']['options']['attributes']['target'] . '"' : '';

		$legal_links .= '<a href="' . url($top_level['link']['link_path']) . '" class="' . $classes . '"' . $id . $name . $rel . $target . '>' . $top_level['link']['link_title'] . '</a>' . "\r\n";

	}
	return $legal_links;
}

/**
 * Get taxonomy info for use in form option
 *
**/
function get_options($vid, $parent = 0, $depth = 1){
	$all_terms = array();

	$terms = taxonomy_get_tree($vid, $parent, $depth, FALSE);

	foreach($terms as $term)
		$all_terms[$term->tid] = $term->name;

	return $all_terms;
}

/**
 * Get node id from current page data
 *
**/
function get_page_node($page) {
	if(!isset($page['content']['system_main']['nodes']))
		return false;

	$ak = array_keys($page['content']['system_main']['nodes']);
	return (isset($page['content']['system_main']['nodes'])) ? $page['content']['system_main']['nodes'][array_shift($ak)]["#node"] : false;
}

/**
 * Pull client logo based on desired criteria
 *
 * $opts: Array
 * $logo: Array
 * return: Array
**/
function get_client_logo($opts = array('industry' => FALSE, 'region' => FALSE, 'limit' => 1, 'industry_table' => 'field_data_field_project_industry', 'exclude' => array()), $logo = array())
{
	$client_logo_query = db_select('node', 'n');
	$client_logo_query->join('field_data_field_client_grid_image', 'gi', 'n.nid = gi.entity_id');

	if($opts['industry'])
	{
		if($opts['industry_table'] == 'field_data_field_client_org_type')
		{
			$client_logo_query->leftJoin($opts['industry_table'], 'ci', 'n.nid = ci.entity_id');
		}
		else
		{
			$client_logo_query->leftJoin('field_data_field_project_industry', 'ci', 'n.nid = ci.entity_id');
			$client_logo_query->leftJoin('taxonomy_term_hierarchy', 'th', 'ci.field_project_industry_tid = th.tid');
		}
	}

	if($opts['region'])
	$client_logo_query->leftJoin('field_data_field_region', 'r', 'n.nid = r.entity_id');

	$client_logo_query->fields('n', array('nid', 'title'))
										->fields('gi', array('field_client_grid_image_fid', 'field_client_grid_image_alt'));

	$client_logo_query->condition('gi.bundle', 'client', '=')
										->condition('n.status', '1', '=');

	if($opts['industry'])
	{
		$clause_cond = $opts['industry_table'] == 'field_data_field_client_org_type' ? 'ci.field_client_org_type_tid': 'th.parent';
		$client_logo_query->condition($clause_cond, $opts['industry'], '=');
	}

	if($opts['region'])
		$client_logo_query->condition('r.field_region_tid', $opts['region'], '=');

	if(!empty($opts['exclude']))
		$client_logo_query->condition('n.nid', $opts['exclude'], 'NOT IN');

	$client_logo_query->range(0, $opts['limit'])
											->orderRandom();
	$project_result = $client_logo_query->execute();

	if($project_result->rowCount() > 0)
		while($client_logo = $project_result->fetchObject())
			$logo[] = $client_logo;

	if($project_result->rowCount() != $opts['limit'])
	{
		// Fallback: give priority to the industry over the region
		if($opts['industry'] && !$opts['region']) $opts['industry'] = FALSE;
		if($opts['industry'] && $opts['region']) $opts['region'] = FALSE;
		$opts['limit'] = ($opts['limit']-$project_result->rowCount());
		foreach($logo as $i=>$l)
			$opts['exclude'][] = $l->nid;

		$logo = get_client_logo($opts, $logo);
	}

	return $logo;
}

/**
 * Pull project info based on desired criteria
 *	-- potential replacement for get_project_image() ? --
 *
 * @param: mixed
 * return: object
**/
function get_project_random($opts = array('industry' => FALSE, 'region' => FALSE, 'exclude' => NULL, 'solution' => NULL, 'parent' => NULL, 'priority' => 'industry'))
{
	global $language;

	$in_depth = term_depth($opts['industry']);

	// No projects should be in the top depth, get something from the child instead
	if(array_key_exists('industry', $opts) && $opts['industry'] != FALSE && $in_depth == '1')
	{
		$children = taxonomy_get_children($opts['industry']);
		if(!empty($children))
		{
			$tids = array_keys($children);
			shuffle($tids);
			$opts['industry'] = $tids[0];
		}
	}

	$project_query = db_select('node', 'n');
	$project_query->join('field_data_field_project_preview_title', 'ppt', 'n.nid = ppt.entity_id');
	$project_query->join('field_data_field_project_preview_desc', 'ppd', 'n.nid = ppd.entity_id');
	$project_query->join('field_data_field_featured_circle_image', 'gci', 'n.nid = gci.entity_id');
	$project_query->join('field_data_field_grid_image', 'gi', 'n.nid = gi.entity_id');
	$project_query->leftJoin('field_data_field_project_pull_quote', 'pq', 'n.nid = pq.entity_id');
	$project_query->leftJoin('field_data_field_pull_quote_credit', 'pqc', 'n.nid = pqc.entity_id');
	$project_query->leftJoin('field_data_field_project_industry', 'pi', 'n.nid = pi.entity_id');
	$project_query->leftJoin('field_data_field_project_size', 'ps', 'n.nid = ps.entity_id');
	if(isset($opts['solution']) && $opts['solution'])
	$project_query->leftJoin('field_data_field_project_solutions', 'psol', 'n.nid = psol.entity_id');
	if(isset($opts['region']) && $opts['region'])
	$project_query->leftJoin('field_data_field_project_region', 'pr', 'n.nid = pr.entity_id');
	if(isset($opts['parent']) && $opts['parent'])
	$project_query->leftJoin('taxonomy_term_hierarchy', 'tth', 'pi.field_project_industry_tid = tth.tid');

	$project_query->fields('n', array('nid', 'title'))
								->fields('ppt', array('field_project_preview_title_value'))
								->fields('ppd', array('field_project_preview_desc_value'))
								->fields('gci', array('field_featured_circle_image_fid', 'field_featured_circle_image_alt'))
								->fields('gi', array('field_grid_image_fid', 'field_grid_image_alt'))
								->fields('pq', array('field_project_pull_quote_value'))
								->fields('pqc', array('field_pull_quote_credit_value'))
								->fields('pi', array('field_project_industry_tid', 'bundle'))
								->fields('ps', array('field_project_size_value'));

	$project_query->condition('gi.bundle', 'project', '=');

	// Mostly industry is the priority, but sometimes it is solution
	if(isset($opts['priority']) && $opts['priority'] != 'industry')
	{
		if(isset($opts['solution']) && $opts['solution'])
			$project_query->condition('psol.field_project_solutions_tid', $opts['solution'], '=');
	}
	elseif(isset($opts['parent']) && $opts['parent'])
	{
		$project_query->condition('tth.parent', $opts['parent'], '=');
	}
	else
	{
		if(isset($opts['industry']) && $opts['industry'])
			$project_query->condition('pi.field_project_industry_tid', $opts['industry'], '=');
	}

	if(isset($opts['region']) && $opts['region'])
		$project_query->condition('pr.field_project_region_tid', $opts['region'], '=');

	if(isset($opts['exclude']) && !empty($opts['exclude']))
	{
		if(is_array($opts['exclude']))
		{
			$project_query->condition('n.nid', $opts['exclude'], 'NOT IN');
		}
		elseif($opts['exclude'])
		{
			$project_query->condition('n.nid', $opts['exclude'], '!=');
		}
	}

	// Choose from current language
	$project_query->condition('n.language', $language->language, '=');

	$project_query->range(0, 1)
											->orderRandom();
	// dpq($project_query);
	$project_result = $project_query->execute();

	if($project_result->rowCount() == 0)
	{
		// First if's are geared to LOTE (parent) entries
		// If we have parent - toss the region first
		if(isset($opts['parent']) && $opts['region'])
		{
			$opts['region'] = FALSE;
		}
		elseif(isset($opts['parent']) && !$opts['region'])
		{
			$opts['industry'] = $opts['parent'];
			$opts['parent'] = FALSE;
		}
		else
		{
			// Geared for NON-LOTE
			// Fallback: give priority to the industry over the region
			if( (array_key_exists('industry', $opts) || $opts['industry'] === NULL) && $opts['region'])
			{
				$opts['region'] = FALSE;
			}
			elseif(array_key_exists('industry', $opts) && !$opts['region'])
			{
				//try the search again but this time without the industry and with the region
				$opts['industry'] = FALSE;
				$opts['region'] = $_SESSION['akamai']['region_info']->tid;
			}

			// Solutions are are slightly different priority
			if(array_key_exists('solution', $opts) && $opts['solution']){
				$opts['priority'] = 'industry';
				$opts['solution'] = FALSE;
			}
		}

		// We've exhausted all of our criteria - return nothing to avoid endless loop
		// This is mainly because we may not have enough LOTE sites to qualify the $language criteria
		if( $opts['region'] == FALSE && $opts['solution'] == FALSE && $opts['industry'] == FALSE && $opts['parent'] == FALSE )
			return NULL;

		$project = get_project_random($opts);
	}
	else
	{
		$project_obj = $project_result->fetchObject();
		$project = $project_obj;
	}

	return $project;
}

/**
 * Pull project image based on desired criteria
 *
 * $industry: int
 * $region: int
 * $type: string
 * return: object
**/
function get_project_image($industry = FALSE, $region = FALSE, $type = 'grid')
{
	$image = '';

	$project_image_query = db_select('node', 'n');
	$project_image_query->leftJoin('field_data_field_project_industry', 'pi', 'n.nid = pi.entity_id');
	if($region)
	$project_image_query->leftJoin('field_data_field_project_region', 'pr', 'n.nid = pr.entity_id');
	$project_image_query->leftJoin('field_data_field_project_size', 'ps', 'n.nid = ps.entity_id');

	switch($type)
	{
		case 'circle':
			$project_image_query->join('field_data_field_featured_circle_image', 'gi', 'n.nid = gi.entity_id');
			$project_image_query->fields('gi', array('field_featured_circle_image_fid', 'field_featured_circle_image_alt'));
		break;
		case 'grid':
		default:
			$project_image_query->join('field_data_field_grid_image', 'gi', 'n.nid = gi.entity_id');
			$project_image_query->fields('gi', array('field_grid_image_fid', 'field_grid_image_alt'));
		break;
	}

	$project_image_query->fields('n', array('nid', 'title'))
											->fields('pi', array('field_project_industry_tid', 'bundle'))
											->fields('ps', array('field_project_size_value'));

	$project_image_query->condition('gi.bundle', 'project', '=');

	if($industry)
		$project_image_query->condition('pi.field_project_industry_tid', $industry, '=');

	if($region)
		$project_image_query->condition('pr.field_project_region_tid', $region, '=');

	$project_image_query->range(0, 1)
											->orderRandom();

	// dpq($project_image_query);
	$project_result = $project_image_query->execute();

	if($project_result->rowCount() == 0)
	{
		// Fallback: give priority to the industry over the region
		if($industry && !$region) $industry = FALSE;
		if($industry && $region) $region = FALSE;
		$image = get_project_image($industry, $region, $type);
	}
	else
	{
		$image_obj = $project_result->fetchObject();
		$image = $image_obj;
	}

	return $image;
}

/**
 * Determine the region based on the country code from Akamai
 *
 * @param: string
 * return: int
**/
function get_region_info($country_code = NULL)
{
	$region = NULL;

	if($country_code)
	{
		$cc_tid_query = db_select('taxonomy_term_data', 'td');
		// Joining on name is not viable - see Hong Kong
		// It's not perfect but use code/description instead
		//$cc_tid_query->join('location_country', 'lc', 'td.name = lc.name');
		$cc_tid_query->join('location_country', 'lc', 'td.description = lc.code');
		$cc_tid_query->fields('td', array('tid'))
								 ->condition('lc.code', strtolower($country_code));

		$region = $cc_tid_query->execute()->fetchObject();
    $current_region_tid = $region->tid;
		$parents = taxonomy_get_parents($region->tid);
		$p = sizeof($parents);
		// 8 = "All" and we only want that if we need a default
		if($p > 0 && $p != 1)
		{
			unset($parents[8]);
		}
		foreach($parents as $p => $parent)
			$region = $parent;
	}

  $region->current_region_tid = $current_region_tid;

	return $region;
}

/**
 * Check against current user region
 *
**/
function is_current_region($region_tid)
{
	// 8 = All - qualifies as current region
	if(is_array($region_tid))
	{
		foreach($region_tid as $i => $tid)
		{
			if(isset($tid['tid']))
				if ($tid['tid'] == '8' || $tid['tid'] == $_SESSION['akamai']['current_region_tid'] || $tid['tid'] == $_SESSION['akamai']['region_tid']) {
          return true;
        }
		}
	}
	else
	{
    if ($region_tid == '8' || $region_tid == $_SESSION['akamai']['current_region_tid'] || $region_tid == $_SESSION['akamai']['region_tid']) {
      return true;
    }
	}

	return false;
}

function image_link($image, $url, $add_opt = array())
{
	$add_opt['html'] = true;

	return l($image, $url, $add_opt);
}

function get_login_location_select($type = '') {
	global $language;

	$sql = "SELECT
						node.nid AS nid,
						node.title AS location,
						login.field_location_login_url_value AS login_url,
						signup.field_location_signup_url_value AS signup_url,
						node.type AS node_type,
						node.vid AS node_vid
					FROM
						node
					INNER JOIN field_data_field_location_login_url login
						ON node.vid = login.revision_id
					INNER JOIN field_data_field_location_signup_url signup
						ON node.vid = signup.revision_id
					LEFT OUTER JOIN nodequeue_nodes nn
						ON node.nid = nn.nid
					LEFT JOIN nodequeue_queue nq
						ON nq.qid = nn.qid
					WHERE
						(node.status <> 0) AND
						(node.type in ('location_url'))
					AND node.language=:lang
					ORDER BY
						nn.position ASC,
						node.created ASC";

	$result = db_query($sql, array(':lang' => $language->language));

	$location_select = '<select name="location_login_nid" id="location_login_nid" class="custom-select">';
	$location_select .= '<option value="">'.t('Select project location').'</option>';
	foreach($result as $row)
	{
		$value = ($type == 'login') ? $row->login_url : $row->signup_url;
		if(isset($_COOKIE['location_login_nid']) && !empty($_COOKIE['location_login_nid']) && ($_COOKIE['location_login_nid'] == $row->nid) ) {
			$location_select .= '<option data-link="'.$value.'" selected="selected" value="' . $row->nid . '">'.$row->location.'</option>';
		} else {
			$location_select .= '<option data-link="'.$value.'" value="' . $row->nid . '">'.$row->location.'</option>';
		}
	}
	$location_select .= '</select>';

	return $location_select;
}


/**
 * Creates a simple text rows array from a field collections, to be used in a
 * field_preprocess function.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 *
 * @param $field_name
 *   The name of the field being altered.
 *
 * @param $field_array
 *   Array of fields to be turned into rows in the field collection.
 */
function rows_from_field_collection(&$vars, $field_name, $field_array)
{
  $vars['rows'] = array();
  foreach($vars['element']['#items'] as $key => $item)
  {
    $entity_id = $item['value'];
    $entity = field_collection_item_load($entity_id);
    $wrapper = entity_metadata_wrapper('field_collection_item', $entity);
    $row = array();
    foreach($field_array as $field)
    {
      $row[$field] = $wrapper->$field->value();
    }
    $vars['rows'][] = $row;
  }
}

/**
 * Return the depth of the term id
 * @param: int
 * @return: int
**/
function term_depth($tid) {
  $parent = db_query("SELECT parent FROM {taxonomy_term_hierarchy} WHERE tid = :tid", array(':tid' => $tid))->fetchField();
  if($parent == 0) {
    return 1;
  }else  {
    return 1+term_depth($parent);
  }
}

function demandbase_user_sector($industry_sector) {

	// Use this if session not availabe (first page request)
	global $db_company_industry;
	global $db_company_sub_industry;

	$main_sector = isset($_SESSION['demandbase']['industry']) && !empty($_SESSION['demandbase']['industry']) ? $_SESSION['demandbase']['industry'] : $db_company_industry;
	$sub_sector = isset($_SESSION['demandbase']['sub_industry']) && !empty($_SESSION['demandbase']['sub_industry']) ? $_SESSION['demandbase']['sub_industry'] :$db_company_sub_industry;

	switch ($main_sector) {
		case 'Energy & Utilities':
			switch($sub_sector) {
				case 'Distribution':
				case 'Services':
				case 'Electric Services':
				case 'Transmission':
				case 'Machinery':
					if ($industry_sector == '329')
						return true;
					return 'power';
				break;
				case 'Exploration':
				case 'Natural Gas':
				case 'Refining':
				case 'Petroleum':
					if ($industry_sector == '327')
						return true;
					return 'oilgas';
				break;
				case 'Water':
				case 'Sanitation':
					if ($industry_sector == '30')
						return true;
					return 'infrastructure';
				break;
				default:
					return 'generic';
				break;
			}
		break;
		case 'Mining':
			if ($industry_sector == '326')
				return true;
			return 'mining';
		break;
		case 'Construction':
			switch($sub_sector){
				case 'Civil Construction':
					if ($industry_sector == '30')
						return true;
					return 'infrastructure';
				break;
				case 'Contractors':
				case 'Materials':
				case 'Machinery':
				case 'Commercial':
				case 'Residential':
				case 'Supplies':
				case 'Retail':
				case 'Services':
					if ($industry_sector == '31')
						return true;
					return 'construction';
				break;
				default:
					return 'generic';
				break;
			}
		break;
		case 'Real Estate':
			if ($industry_sector == '31')
				return true;
			return 'construction';
		break;
		case 'Transportation & Logistics':
		case 'Aerospace & Defense':
			if ($industry_sector == '30')
				return true;
			return 'infrastructure';
		break;
		default:
			return 'generic';
		break;
	}

	// Return generic as base case
	return 'generic';
}
