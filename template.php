<?php
/**
* Aconex 2014 Redesign/Rebrand
* Garland used to create working template
*
**/

/**
 * Override of theme_breadcrumb().
 */
function aconex_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb">' . implode(' › ', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Override or insert variables into the maintenance page template.
 */
function aconex_preprocess_maintenance_page(&$vars) {
  // While markup for normal pages is split into page.tpl.php and html.tpl.php,
  // the markup for the maintenance page is all in the single
  // maintenance-page.tpl.php template. So, to have what's done in
  // aconex_preprocess_html() also happen on the maintenance page, it has to be
  // called here.
  aconex_preprocess_html($vars);
}

/**
 * Override or insert variables into the html template.
 */
function aconex_preprocess_html(&$vars) {
	global $base_url;
	$vars['base_url'] = $base_url;
	$vars['theme_url'] = $base_url . '/' . drupal_get_path('theme', 'aconex');

	$viewport = array(
		'#tag' => 'meta',
		'#attributes' => array(
			'name' => 'viewport',
			'content' => 'width=device-width, initial-scale=1.0, maximum-scale=1.0'
		),
		'#weight' =>  -100
	);
	drupal_add_html_head($viewport, 'viewport');

  // Add conditional CSS for IE
  drupal_add_css(path_to_theme() . '/css/ie9.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 9', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/font-awesome-ie7.min.css', array('browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 8', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css('//cloud.typography.com/6674492/790884/css/fonts.css', array('type' => 'external'));
  drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css', array('type' => 'external'));

  // IE  Conditional scripts
  $ie_scripts = array(
    path_to_theme() . '/js/html5shiv.min.js',
    path_to_theme() . '/js/respond.min.js',
  );
  foreach ($ie_scripts as $key => $value) {
    $ie_script =  array(
      '#browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE),
      '#tag' => 'script',
      '#attributes' => array(
        'type' => "text/javascript",
        'src' => $value,
      ),
      '#pre_render' => array('drupal_pre_render_conditional_comments'),
      '#weight' =>  999 + $key,
    );
    //drupal_add_html_head($ie_script, "foo$key");
    //drupal_add_js($value, array('group' => 'JS_THEME', 'weight' => 0 + $key));

  }

  drupal_add_js('//code.jquery.com/ui/1.10.4/jquery-ui.min.js', array('type' => 'external', 'group' => 'JS_LIBRARY', 'weight' => -20));
  drupal_add_js(drupal_get_path('theme', 'aconex') .'/js/aconex.js');
  drupal_add_js(drupal_get_path('theme', 'aconex') .'/js/sticky-header.js');

	// Customize $page_top section with our own header
	if (module_exists('acx')) {
    $vars['aconex_header'] = acx_header($vars);
    $vars['aconex_footer'] = acx_footer();
    $vars['pageup_footer'] = acx_footer($omit_orange = TRUE);

    // Do not show on frameless page.
    $node = menu_get_object();
    if ($node && $node->type == 'frameless_page') {
      $vars['aconex_header'] = '';
      $vars['aconex_footer'] = '';
      $vars['pageup_footer'] = '';
    }
	}

	// Custom Head blocks
	$vars['head_elements'] = block_get_blocks_by_region('head_elements');
	$vars['google_tags'] = block_get_blocks_by_region('google_tags');
	$vars['liveperson_monitor'] = block_get_blocks_by_region('liveperson_monitor');
	$vars['liveperson_buttons'] = block_get_blocks_by_region('liveperson_buttons');

	// Add body classes
	$classes = array();
	$match = array_values(preg_grep('/node-type-/i', $vars['classes_array']));
	if ($match[0] != 'node-type-page') {
		$match[0] = str_replace('-page', '', $match[0]);
		$vars['classes_array'][] = str_replace('node-type-', '', $match[0]) . '-page';
	}
	foreach ($vars['page']['content']['system_main']['nodes'] as $key => $node) {
		if(isset($node['#node']->type) && $node['#node']->type == 'homepage')
			$vars['classes_array'][] = 'home-page';

		switch($key)
		{
			// Login page
			case '32'://English
			case '1619'://Chinese, Simplified
			case '1620'://Japanese
			case '1621'://Korean
			case '1623'://Spanish
			case '1622'://Italian
			case '1624'://French
				$vars['classes_array'][] = 'login-page';
			break;
			case '119':
				// Home page
				$vars['classes_array'][] = 'home-page';
			break;
			// Resources overview page
			case '616'://en
			case '1639'://zh-hans
			case '1638'://ja
			case '1637'://ko
			case '1636'://es
			case '1634'://it
			case '1635'://fr
			case '619':
			case '620':
			case '1312':
			case '1313':
			case '1314':
				$vars['classes_array'][] = 'resources-page';
			break;
			// Solutions page
			case '1168'://en
			case '1462'://zh-hans
			case '1463'://ja
			case '1632'://ko
			case '1464'://es
			case '1465'://it
			case '1466'://fr
				$vars['classes_array'][] = 'solutions-page';
			break;
			// Industries overview
			case '1169'://en
			case '1458'://zh-hans
			case '1459'://ja
			case '1633'://ko
			case '1452'://es
			case '1460'://it
			case '1461'://fr
				$vars['classes_array'][] = 'industries-page';
			break;
			// Customers page
			case '133'://en
			case '1567'://zh-hans
			case '1568'://ja
			case '1618'://ko
			case '1569'://es
			case '1570'://it
			case '1571'://fr
				$vars['classes_array'][] = 'customers-page';
			break;
			//Events overview
			case '237'://en
			case '1572'://zh-hans
			case '573'://ja
			case '1631'://ko
			case '1574'://es
			case '1575'://it
			case '1576'://fr
				$vars['classes_array'][] = 'events-page';
			break;
			case '234':
				// News page
				$vars['classes_array'][] = 'news-page';
			break;
			case '855':
			case '232':
				// Company page
				$vars['classes_array'][] = 'company-page';
			break;
			case '231':
				// Partners page
				$vars['classes_array'][] = 'partners-page';
			break;
			//Offices page
			case '129'://en
			case '1582'://zh-hans
			case '1583'://ja
			case '1641'://ko
			case '1584'://es
			case '1585'://it
			case '1586'://fr
				$vars['classes_array'][] = 'contact-page';
			break;
			//Register page
			case '734'://en
			case '1625'://zh-hans
			case '1626'://ja
			case '1627'://ko
			case '1628'://es
			case '1629'://it
			case '1630'://fr
				$vars['classes_array'][] = 'register-page';
			break;
		}
	}

	// For PageUp People jobs template
	if (isset($_GET['destination']))
	{
		if($_GET['destination'] == 'pageup')
		{
			// Without these, pageup gets a 404
			drupal_add_http_header('Status', '200');
			drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
			drupal_send_headers();
			$vars['theme_hook_suggestions'][] = 'html__pageup';
			$vars['classes_array'][] = 'pageup-page';
		}
	}

  // Add custom css classed based on the path.
  $path = drupal_get_path_alias();
  $aliases = explode('/', $path);
  foreach($aliases as $alias) {
    $vars['classes_array'][] = 'page--' . drupal_clean_css_identifier($alias);
  }
}

/**
 * Override or insert variables into the html template.
 */
function aconex_process_html(&$vars) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
}

/**
 * Override or insert variables into the page template.
 */
function aconex_preprocess_page(&$vars) {
	// New Aconex theme functionality

	// Certain pages have custom templates that we'd like to use
	// Here we look for specific node id's
	if(isset($vars['node']->nid))
	{
		$solutions_pages = variable_get('acx_soltuions_pages', '');
		$solutions_pages = explode('|', $solutions_pages);

		switch($vars['node']->nid)
		{
			//Login page
			case '32'://English
			case '1619'://Chinese, Simplified
			case '1620'://Japanese
			case '1621'://Korean
			case '1623'://Spanish
			case '1622'://Italian
			case '1624'://French
				$vars['theme_hook_suggestions'][] = 'page__login';
			break;
			//Offices page
			case '129'://en
			case '1582'://zh-hans
			case '1583'://ja
			case '1641'://ko
			case '1584'://es
			case '1585'://it
			case '1586'://fr
				$vars['theme_hook_suggestions'][] = 'page__contact__about';
				break;
			// Projects map/listing page
			case '133'://en
			case '1567'://zh-hans
			case '1568'://ja
			case '1618'://ko
			case '1569'://es
			case '1570'://it
			case '1571'://fr
				$vars['theme_hook_suggestions'][] = 'page__projects__overview';
			break;
			case '231':
				// Partners overview
				$vars['theme_hook_suggestions'][] = 'page__partners';
			break;
			case '234':
				// Articles & news overview
				$vars['theme_hook_suggestions'][] = 'page__articles__news';
			break;
			//Events overview
			case '237'://en
			case '1572'://zh-hans
			case '573'://ja
			case '1631'://ko
			case '1574'://es
			case '1575'://it
			case '1576'://fr
				$vars['theme_hook_suggestions'][] = 'page__events__overview';
			break;
			case '619':
			case '620':
			case '1312':
			case '1313':
			case '1314':
				// Resources category view
				$vars['theme_hook_suggestions'][] = 'page__resources__detail';
			break;
			// Resources overview page
			case '616'://en
			case '1639'://zh-hans
			case '1638'://ja
			case '1637'://ko
			case '1636'://es
			case '1634'://it
			case '1635'://fr
				$vars['theme_hook_suggestions'][] = 'page__resources__overview';
			break;
			// Solutions sub page view
			/*
			case '509': // Document Management
			case '722': // BIM Collaboration
			case '564': // Bidding & Tenders
			case '562': // Workflows
			case '705': // Handover / O&M Manuals
			case '559': // Reporting & Insights
			case '27': // Mail & Forms or Forms & Correspondence
			case '1327': // Quality & Safety
			case '1467': // Document Management Chinese
			case '1472': // BIM Collaboration Chinese
			case '1482': // Bidding & Tenders Chinese
			case '1487': // Workflows Chinese
			case '1512': // Handover / O&M Manuals Chinese
			case '1517': // Reporting & Insights Chinese
			case '1477': // Mail & Forms or Forms & Correspondence Chinese
			case '1507': // Quality & Safety Chinese
			case '1468': // Document Management Japanese
			case '1473': // BIM Collaboration Japanese
			case '1483': // Bidding & Tenders Japanese
			case '1488': // Workflows Japanese
			case '1513': // Handover / O&M Manuals Japanese
			case '1518': // Reporting & Insights Japanese
			case '1478': // Mail & Forms or Forms & Correspondence Japanese
			case '1508': // Quality & Safety Japanese
			case '2124': // Document Management Korean
			case '2123': // BIM Collaboration Korean
			case '2126': // Bidding & Tenders Korean
			case '2127': // Workflows Korean
			case '2132': // Handover / O&M Manuals Korean
			case '2133': // Reporting & Insights Korean
			case '2125': // Mail & Forms or Forms & Correspondence Korean
			case '2131': // Quality & Safety Korean
			case '1469': // Document Management Spanish
			case '1474': // BIM Collaboration Spanish
			case '1484': // Bidding & Tenders Spanish
			case '1489': // Workflows Spanish
			case '1514': // Handover / O&M Manuals Spanish
			case '1519': // Reporting & Insights Spanish
			case '1479': // Mail & Forms or Forms & Correspondence Spanish
			case '1509': // Quality & Safety Spanish
			case '1470': // Document Management Italian
			case '1475': // BIM Collaboration Italian
			case '1485': // Bidding & Tenders Italian
			case '1490': // Workflows Italian
			case '1515': // Handover / O&M Manuals Italian
			case '1520': // Reporting & Insights Italian
			case '1480': // Mail & Forms or Forms & Correspondence Italian
			case '1510': // Quality & Safety Italian
			case '1471': // Document Management French
			case '1476': // BIM Collaboration French
			case '1486': // Bidding & Tenders French
			case '1491': // Workflows French
			case '1516': // Handover / O&M Manuals French
			case '1521': // Reporting & Insights French
			case '1481': // Mail & Forms or Forms & Correspondence French
			case '1511': // Quality & Safety French

				$vars['theme_hook_suggestions'][] = 'page__solutions__subpage';
			break;
			*/
			//Register page
			case '734'://en
			case '1625'://zh-hans
			case '1626'://ja
			case '1627'://ko
			case '1628'://es
			case '1629'://it
			case '1630'://fr
				$vars['theme_hook_suggestions'][] = 'page__register';
			break;
			case '855':
				// Resources overview page
				$vars['theme_hook_suggestions'][] = 'page__leadership';
			break;
			// Solutions overview grid/listing page
			case '1168'://en
			case '1462'://zh-hans
			case '1463'://ja
			case '1632'://ko
			case '1464'://es
			case '1465'://it
			case '1466'://fr
				$vars['theme_hook_suggestions'][] = 'page__solutions__overview';
			break;
			// Industries overview
			case '1169'://en
			case '1458'://zh-hans
			case '1459'://ja
			case '1633'://ko
			case '1452'://es
			case '1460'://it
			case '1461'://fr
				$vars['theme_hook_suggestions'][] = 'page__industries__overview';
			break;
		}

		if ( in_array( $vars['node']->nid, $solutions_pages ) ) $vars['theme_hook_suggestions'][] = 'page__solutions__subpage';
	}
	// Here we make a suggestion for a specific content type
	if (isset($vars['node']->type))
	{
		//echo 'adding '.'page__'.$vars['node']->type."<br>\n";
		$vars['theme_hook_suggestions'][] = 'page__'.$vars['node']->type;

		switch($vars['node']->type)
		{
			case  'solutions':
				// Add the solutions menu where necessary
				$vars['solutions_menu'] = menu_navigation_links('menu-solutions-menu');
			break;
		}
  }

	// Inherited Garland theme functionality
  // Move secondary tabs into a separate variable.
  $vars['tabs2'] = array(
    '#theme' => 'menu_local_tasks',
    '#secondary' => $vars['tabs']['#secondary'],
  );
  unset($vars['tabs']['#secondary']);

  if (isset($vars['main_menu'])) {
    $vars['primary_nav'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('links', 'inline', 'main-menu'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['primary_nav'] = FALSE;
  }
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_nav'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'inline', 'secondary-menu'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['secondary_nav'] = FALSE;
  }

  // Prepare header.
  $site_fields = array();
  if (!empty($vars['site_name'])) {
    $site_fields[] = $vars['site_name'];
  }
  if (!empty($vars['site_slogan'])) {
    $site_fields[] = $vars['site_slogan'];
  }
  $vars['site_title'] = implode(' ', $site_fields);
  if (!empty($site_fields)) {
    $site_fields[0] = '<span>' . $site_fields[0] . '</span>';
  }
  $vars['site_html'] = implode(' ', $site_fields);

  // Set a variable for the site name title and logo alt attributes text.
  $slogan_text = $vars['site_slogan'];
  $site_name_text = $vars['site_name'];
  $vars['site_name_and_slogan'] = $site_name_text . ' ' . $slogan_text;
}

/**
 * Override or insert variables into the node template.
 */
function aconex_preprocess_node(&$vars) {
  $vars['submitted'] = $vars['date'] . ' — ' . $vars['name'];

  // Add custom classes to node.
  $vars['classes_array'][] = $vars['type'];
  $vars['classes_array'][] = $vars['type'] . '--' . $vars['view_mode'];

  // Add Js to Solutions nodes.
  if ($vars['type'] == 'solutions_page') {
    drupal_add_js(drupal_get_path('theme', 'aconex') .'/js/solutions.js');
  }

  if ($vars['type'] == 'homepage_v2') {
    drupal_add_css(drupal_get_path('theme', 'aconex') . '/js/slick-carousel/slick.css');
    drupal_add_js(drupal_get_path('theme', 'aconex') .'/js/slick-carousel/slick.min.js');
    drupal_add_js(drupal_get_path('theme', 'aconex') .'/js/hero.js');
    drupal_add_js(drupal_get_path('theme', 'aconex') .'/js/mosaic.js');
  }

  if ($vars['type'] == 'project') {
    $wrapper = entity_metadata_wrapper('node', $vars['node']);
    if (isset($vars['node']->field_project_portfolio)) {
      if (!$wrapper->field_project_portfolio->value()) {
        $vars['content']['field_project_portfolio']['#access'] = false;
      }
    }
  }
}

/**
 * Override or insert variables into the comment template.
 */
function aconex_preprocess_comment(&$vars) {
  $vars['submitted'] = $vars['created'] . ' — ' . $vars['author'];
}

/**
 * Override or insert variables into the block template.
 */
function aconex_preprocess_block(&$vars) {
  $vars['title_attributes_array']['class'][] = 'title';
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Override or insert variables into the page template.
 */
function aconex_process_page(&$vars) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Override or insert variables into the region template.
 */
function aconex_preprocess_region(&$vars) {
  if ($vars['region'] == 'header') {
    $vars['classes_array'][] = 'clearfix';
  }
}

/**
 * Alter blocks.
 */
function aconex_block_view_alter(&$data, $block) {
	// Sidebar links
  if ( ($block->region == 'sidebar_links') || ($block->region == 'sidebar_links_industries') || ($block->region == 'sidebar_links_solutions') ) {
		$data_content = $data['content']['#content'];
    $content = '';
    foreach ($data_content as $link) {
    	$selected = ($link['#original_link']['in_active_trail'] == 1) ? ' class="selected"' : '';
      $content .= (!empty($link['#href'])) ? '<h3><a href="' . url($link['#href']) . '"' . $selected . '>' . $link['#title'] . '</a></h3>' . "\r\n" : '';
      if (!empty($link['#below'])) {
      	foreach($link['#below'] as $sublink) {
					$selected = ($sublink['#original_link']['in_active_trail'] == 1) ? ' class="selected"' : '';
					$content .= (!empty($link['#href'])) ? '<a href="' . url($sublink['#href']) . '"' . $selected . '>' . $sublink['#title'] . '</a>' . "\r\n" : '';
      	}
      }
    }
    $data['content'] = $content;
  }

	// Subnav links
  if ( ($block->region == 'subnav_resources' || $block->region == 'subnav_solutions') ) {
		$data_content = $data['content']['#content'];
    $content = '';
    foreach ($data_content as $link) {
    	$classes = '';
			$classes .= (!empty($link['#original_link']['options']['attributes']['class'])) ? implode(' ', $link['#original_link']['options']['attributes']['class']) . ' ' : '';
			$id = (!empty($link['#original_link']['options']['attributes']['id'])) ? ' id="' . $link['#original_link']['options']['attributes']['id'] . '"' : '';
			$name = (!empty($link['#original_link']['options']['attributes']['name'])) ? ' name="' . $link['#original_link']['options']['attributes']['name'] . '"' : '';
			$rel = (!empty($link['#original_link']['options']['attributes']['rel'])) ? ' rel="' . $link['#original_link']['options']['attributes']['rel'] . '"' : '';
			$target = (!empty($link['#original_link']['options']['attributes']['target'])) ? ' target="' . $link['#original_link']['options']['attributes']['target'] . '"' : '';
			$url = ($link['#original_link']['attributes']['rel'] != 'nofollow') ? url($link['#href']) : '#';
    	$classes .= ($link['#original_link']['in_active_trail'] == 1) ? $classes . 'selected' : $classes;
    	$class = (!empty($classes)) ? ' class="' . $classes . '"' : '';

      $content .= (!empty($link['#href'])) ? '<a href="' . $url . '"' . $class . $id . $name . $rel . $target . '><span>' . $link['#title'] . '</span></a>' . "\r\n" : '';
    }
    $data['content'] = $content;
  }
}

/**
 * Alter forms.
 */
function aconex_form_alter(&$form, &$form_state, $form_id) {
	if ( ($form_id == 'search_block_form') || ($form_id == 'search_form') ) {
		// Replace standard submit with search icon button
		$form['#action'] = language_homepage().'search/node/';
		$form['button'] = array(
			'#type' => 'item',
			'#markup' => '<button type="submit" name="op" value="search" class="button-search"><i class="fa fa-search"></i></button>',
			'#weight' => 1000,
		);
		$form['submit_button']['#type'] = 'button';

		// Form classes
		$form['search_block_form']['#attributes']['class'][] = 'prefill';
		$form['#attributes']['class'][] = 'clear';
	}
}

function aconex_preprocess_search_result(&$variables) {
	global $language;

	$result = $variables['result'];

	$variables['url'] = check_url($result['link']);
	$variables['title'] = check_plain($result['title']);
	if (isset($result['language']) && $result['language'] != $language->language && $result['language'] != LANGUAGE_NONE) {
		$variables['title_attributes_array']['xml:lang'] = $result['language'];
		$variables['content_attributes_array']['xml:lang'] = $result['language'];
	}

	$info = array();
	if (!empty($result['module'])) {
		$info['module'] = check_plain($result['module']);
	}
	/*if (!empty($result['user'])) {
		$info['user'] = $result['user'];
	}*/
	/*if (!empty($result['date'])) {
		$info['date'] = format_date($result['date'], 'short');
	}*/
	if (isset($result['extra']) && is_array($result['extra'])) {
		$info = array_merge($info, $result['extra']);
	}
	// Check for existence. User search does not include snippets.
	$variables['snippet'] = isset($result['snippet']) ? $result['snippet'] : '';
	// Provide separated and grouped meta information..
	$variables['info_split'] = $info;
	$variables['info'] = implode(' - ', $info);
	$variables['theme_hook_suggestions'][] = 'search_result__' . $variables['module'];
}

/**
 * Override or insert variables into the views view
 */
function aconex_preprocess_views_view(&$vars) {
	$view = $vars['view'];
	if($view->name == 'project_grid')
	{
		// Additional classes for the project_grid view
		$vars['classes_array'][] = 'container';
		$vars['classes_array'][] = 'clear';
	}
}


/**
 * @todo looks like this is a part of feature GmapDraw class
 * Gmap element theme hook
 */
function aconex_gmap($variables)
{
  $element = $variables['element'];

  // Track the mapids we've used already.
  static $mapids = array();

  $mapid = FALSE;
  if (isset($element['#map']) && $element['#map']) {
    // The default mapid is #map.
    $mapid = $element['#map'];
  }
  if (isset($element['#gmap_settings']['id'])) {
    // Settings overrides it.
    $mapid = $element['#gmap_settings']['id'];
  }
  if (!$mapid) {
    // Hmm, no mapid. Generate one.
    $mapid = gmap_get_auto_mapid();
  }
  // Push the mapid back into #map.
  $element['#map'] = $mapid;

  //
  // OUR MODIFICATIONS ARE CONTAINED IN THIS SECTION:
  //
  if (module_exists('acx')) {
    acx_map_set_autoclick($element);
  }
  //
  // END MODIFICATIONS
  //

  gmap_widget_setup($element, 'gmap', $mapid);

  if (!isset($element['#gmap_settings'])) {
    $element['#gmap_settings'] = array();
  }

  // Push the mapid back into #gmap_settings.
  $element['#gmap_settings']['id'] = $mapid;

  $mapdefaults = gmap_defaults();
  $map = array_merge($mapdefaults, $element['#gmap_settings']);
  // Styles is a subarray.
  if (isset($element['#gmap_settings']['styles'])) {
    $map['styles'] = array_merge($mapdefaults['styles'], $element['#gmap_settings']['styles']);
  }
  gmap_map_cleanup($map);

  // Add a class around map bubble contents.
  // @@@ Bdragon sez: Becw, this doesn't belong here. Theming needs to get fixed instead..
  if (isset($map['markers'])) {
    foreach ($map['markers'] as $i => $marker) {
      if (isset($marker['text'])) {
        $map['markers'][$i]['text'] = '<div class="gmap-popup">' . $marker['text'] . '</div>';
      }
    }
  }

  switch (strtolower($map['align'])) {
    case 'left':
      $element['#attributes']['class'][] = 'gmap-left';
      break;
    case 'right':
      $element['#attributes']['class'][] = 'gmap-right';
      break;
    case 'center':
    case 'centre':
      $element['#attributes']['class'][] = 'gmap-center';
  }

  $style = array();
  $style[] = 'width: ' . $map['width'];
  $style[] = 'height: ' . $map['height'];

  $element['#attributes']['class'] = array_merge($element['#attributes']['class'], array(
    'gmap',
    'gmap-map',
    'gmap-' . $mapid . '-gmap'
  ));

  // Some markup parsers (IE) don't handle empty inners well. Use the space to let users know javascript is required.
  // @@@ Bevan sez: Google static maps could be useful here.
  // @@@ Bdragon sez: Yeah, would be nice, but hard to guarantee functionality. Not everyone uses the static markerloader.
  $o = '<div style="' . implode('; ', $style) . ';" id="' . $element['#id'] . '"' . drupal_attributes($element['#attributes']) . '><noscript>' . t('Javascript is required to view this map.') . '</noscript></div>';

  gmap_module_invoke('pre_theme_map', $map);

  if (isset($mapids[$element['#map']])) {
    drupal_set_message(t('Duplicate map detected! GMap does not support multiplexing maps onto one MapID! GMap MapID: %mapid', array('%mapid' => $element['#map'])), 'error');
    // Return the div anyway. All but one map for a given id will be a graymap,
    // because obj.map gets stomped when trying to multiplex maps!
    return $o;
  }
  $mapids[$element['#map']] = TRUE;

  // Put map data in a setting.
  drupal_add_js(array('gmap' => array($element['#map'] => $map)), 'setting');

  return $o;
}

/**
 * Implements hook_css_alter().
 */
function aconex_css_alter(&$css) {
  // Allow themes to set preprocess to FALSE.
  // Enable the ability to toggle <link> as opposed to <style> @import.
  // Useful for injecting CSS.
  foreach ($css as $key => $value) {
    $css[$key]['preprocess'] = variable_get('preprocess_css', FALSE);
  }
}

/**
 * Implements theme_field_collection_view().
 */
function aconex_field_collection_view($variables) {
  $element = $variables['element'];
  $field_collection_item = array_shift($element['entity']['field_collection_item']);

  // No wrappers for field_hero.
  if ($field_collection_item['#bundle'] == 'field_hero') {
    return $element['#children'];
  }

  // Keep this for legacy support.
  return '<div' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</div>';
}
