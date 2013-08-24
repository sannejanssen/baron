<?php

/**
 * @file
 * Block callbacks.
 */

/**
 * Return the eduction search form.
 *
 * Depending on the path, this will return different
 * forms.
 */
function thomas_more_education_search_block_form() {
  $block['subject'] = '';

  if (arg(1) == 'zoeken' || (arg(0) == 'opleidingen' && arg(1) == '')) {
    $form = drupal_get_form('thomas_more_education_form', 'simple');
  }
  else {
    $form = drupal_get_form('thomas_more_education_form', 'extended');
  }

  $block['content'] = drupal_render($form);

  // Oh Drupal and CTools Content types.
  if (arg(1) == 'zoeken' || (arg(0) == 'opleidingen' && arg(1) == '')) {
    return $block;
  }
  else {
    return (object) $block;
  }
}

/**
 * Form education callback.
 */
function thomas_more_education_form($form, &$form_state, $type) {
  form_load_include($form_state, 'inc', 'thomas_more', 'includes/blocks');

  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type,
  );

  // Extended search form.
  if ($type == 'extended') {

    $vocabulary = taxonomy_vocabulary_machine_name_load(CATEGORY_ID);
    $terms = taxonomy_get_tree($vocabulary->vid);
    $areas_of_interest = array('' => t('Choose your area of interest'). '...');
    foreach ($terms as $term) {
      $areas_of_interest[$term->tid] = $term->name;
    }

    $form['area_of_interest'] = array(
      '#type' => 'select',
      '#options' => $areas_of_interest,
    );

    $form['container'] = array(
      '#type' => 'container',
    );
    $form['container']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Show educations'),
      '#validate' => array('thomas_more_education_form_interest_validate'),
      '#submit' => array('thomas_more_education_form_interest_submit'),
    );
    $form['container']['item'] = array(
      '#markup' => t('Or <a href="!url">subscribe me</a>', array('!url' => url('subscribe'))),
    );
  }

  $search_title = ($type == 'extended') ? t('Or search your education') : t('Search your education');

  $form[$type. '_container_keyword'] = array(
    '#type' => 'container',
  );
  $form[$type. '_container_keyword']['keyword'] = array(
    '#type' => 'textfield',
    '#autocomplete_path' => 'apachesolr_autocomplete',
    '#attributes' => array(
      'class' => array('apachesolr-autocomplete', 'unprocessed'),
      'placeholder' => $search_title,
    ),
  );
  $form[$type. '_container_keyword']['search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#validate' => array('thomas_more_education_form_keyword_validate'),
    '#submit' => array('thomas_more_education_form_keyword_submit'),
  );

  return $form;
}

/**
 * Validate handler: interest search.
 */
function thomas_more_education_form_interest_validate($form, &$form_state) {
  if (empty($form_state['values']['area_of_interest']) && empty($form_state['values']['keyword'])) {
    form_set_error('area_of_interest', t('You must select an interest'));
  }
}

/**
 * Validate handler: keyword search.
 */
function thomas_more_education_form_keyword_validate($form, &$form_state) {
  if (empty($form_state['values']['keyword'])) {
    form_set_error('area_of_interest', t('You must enter a keyword to search'));
  }
}

/**
 * Submit handler: interest search.
 */
function thomas_more_education_form_interest_submit($form, &$form_state) {
  $query = array();
  $interest = $form_state['values']['area_of_interest'];
  if (!empty($interest)) {
    $query = array('query' => array('f[0]' => 'im_field_category:' . $interest));
  }
  $keyword = $form_state['values']['keyword'];
  if (!empty($keyword)) {
    $keyword = '/' . $keyword;
  }

  $form_state['redirect'] = array('opleidingen/zoeken' . $keyword, $query);
}

/**
 * Submit handler: keyword search.
 */
function thomas_more_education_form_keyword_submit($form, &$form_state) {
  $keyword = $form_state['values']['keyword'];
  $form_state['redirect'] = 'opleidingen/zoeken/' . $keyword;
}

/**
 * Return the header search form.
 */
function thomas_more_header_search_form($form, &$form_state) {

  $form['#action'] = "/zoeken";
  $form['keyword'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'placeholder' => t('Enter your search term'),
      'autocomplete' => 'off',
    )
  );

  $form['search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#submit' => array('thomas_more_header_form_keyword_submit'),
  );

  return $form;
}

/**
 * Return the header search form.
 */
function thomas_more_header_search_block_form() {

  $form = drupal_get_form('thomas_more_header_search_form');

  $block['subject'] = '';
  $block['content'] = drupal_render($form);

  return $block;
}

/**
 * Return the header search form.
 */
function thomas_more_subheader_search_block_form() {

  $form = drupal_get_form('thomas_more_header_search_form');

  $block['subject'] = '';
  $block['content'] = drupal_render($form);

  return $block;
}

/**
 * Submit handler: interest search.
 */
function thomas_more_header_form_keyword_submit($form, &$form_state) {
  $keyword = $form_state['values']['keyword'];
  $form_state['redirect'] = array('zoeken/'. $keyword);
}


/**
 * Block callback: return OG menu.
 */
function thomas_more_opleiding_menu() {

  // Only return on OG enabled node.
  $node = menu_get_object('node');
  if (isset($node->nid) && (og_is_group_type('node', $node->type) || og_is_group_content_type('node', $node->type))) {

    // Make sure we have the group node so we can get the
    // links and the menu.
    if (!og_is_group_type('node', $node->type)) {
      $group_node = field_get_items('node', $node, 'og_group_ref');
      if (!empty($group_node)) {
        $node = node_load($group_node[0]['target_id']);
      }
    }

    // Make sure this is a group.
    $group_group = field_get_items('node', $node, 'group_group');
    if (empty($group_group) || $group_group[0]['value'] === 0) {
      return;
    }

    // Get the links (if any).
    $content_links = '';
    $links = field_get_items('node', $node, 'field_links');
    if (!empty($links)) {
      $content_links = '<div class="page-links">';
      foreach ($links as $link) {
        $content_links .= l($link['title'], $link['url'], array('attributes' => array('class' => 'btn')));
      }
      $content_links .= '</div>';
    }

    // Get the OG menu.
    $content_menu_links = '';
    $menu = og_menu_get_group_menus(array('node' => array($node->nid)));

    // In case this is a specialization and there's no menu
    // get the parent menu.
    if ($node->type == 'specialization') {
      $education = field_get_items('node', $node, 'field_opleiding');
      if (!empty($education)) {
        $menu = og_menu_get_group_menus(array('node' => array($education[0]['target_id'])));
      }
    }

    if (!empty($menu)) {

      // Set the title to the parent node.
      // To make sure this doesn't mess to much with breadcrumbs
      // we put this in $GLOBALS and change it in page.tpl.php.
      $GLOBALS['alternate_title'] = $node->title;

      // There should only be one.
      $menu_name = $menu[0]['menu_name'];
      $conf = array(
        'menu_name' => $menu_name,
        'expanded' => TRUE,
        'parent_mlid' => 0,
        'follow' => FALSE,
        'depth' => 0,
        'level' => 0,
        'sort' => FALSE,
        'delta' => 'tm-' . $menu_name,
        'title_link' => TRUE,
        'override_title' => FALSE,
      );

      $tree = menu_tree_build($conf);
      $content_menu_links .= drupal_render($tree['content']);
    }

    if (!empty($content_links) || !empty($content_menu_links)) {
      $content = '<div id="subnav"><div id="subnav-content">'
        . $content_links . $content_menu_links .
      '</div></div>';

      $block['subject'] = '';
      $block['content'] = $content;
      return $block;
    }
  }
}

