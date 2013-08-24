<?php

/**
 * @file
 * Plugin to handle the campus facilities.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Campus facilities block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the campus facilities block.
 */
function thomas_more_campus_facilities_content_type_render($subtype, $conf, $panel_args) {
  $node = menu_get_object();

  if ($node && $node->type == 'campus') {

    // Get all the available facilities for this campus.
    $query = new EntityFieldQueryExtraFields();
    $all_facilities = $query->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'facility')
      ->propertyCondition('status', 1)
      ->addExtraField('field_facility_campus', 'target_id', 'nid')
      ->addExtraField('', 'title', 'title', 'node')
      ->fieldCondition('field_facility_campus', 'target_id', $node->nid, '=')
      ->execute();

    if (!empty($all_facilities)) {

      $content = '<ul>';

      // Loop through all the facilities for this campus.
      foreach ($all_facilities['node'] as $facility_nid => $facility_info) {
        $content .= '<li>' . l($facility_info->extraFields->title, 'node/' . $facility_nid) . '</li>';
      }

      $content .= '</ul>';
    }
  }

  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'campus_facilities';
    $block->title       = 'Voorzieningen';
    $block->content     = $content;
    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_campus_facilities_content_type_admin_title($subtype, $conf) {
  return t('Campus facilities block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_campus_facilities_content_type_admin_info($subtype, $conf) {
  return t('Campus facilities block');
}
