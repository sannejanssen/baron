<?php

/**
 * @file
 * Plugin to show all facilities.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('All facilities'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the 'all facilities' block.
 */
function thomas_more_facilities_overview_content_type_render($subtype, $conf, $panel_args) {

  // Get all facility terms
  $vocabulary = taxonomy_vocabulary_machine_name_load(FACILITY_ID);
  $all_facilities = taxonomy_get_tree($vocabulary->vid, 0);
  $content = '';
  $counter = 1;

  if (!empty($all_facilities)) {
    foreach ($all_facilities as $facility) {

      $term = taxonomy_term_load($facility->tid);

      $clear_class = '';
      if ($counter % 4 == 0) {
        $clear_class = ' clear';
      }


      // Add image
      $popup = '<div class="icon">';
      $popup .= theme('image_style', array('style_name' => 'icon', 'path' => $term->field_icon['und'][0]['uri'], 'alt' => $term->name));
      $popup .= '</div>';

      // Add title.
      $popup .= '<h2>' . check_plain($term->name) . '</h2>';

      // Add content
      $popup .= check_markup($term->description, $term->format, '', TRUE);


      // Add link
      $content .= l($popup, 'media/lightbox/voorzieningen/' . $term->tid, array('query' => array('width' => 300, 'height' => 110), 'html' => TRUE, 'attributes' => array('class' => array('colorbox-load hover-block facility-popup popup'))));

      $counter++;

    }
  }

  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'facilities_overview';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_facilities_overview_content_type_admin_title($subtype, $conf) {
  return t('All facilities');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_facilities_overview_content_type_admin_info($subtype, $conf) {
  return t('All facilities');
}
