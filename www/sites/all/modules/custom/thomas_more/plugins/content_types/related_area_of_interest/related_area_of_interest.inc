<?php

/**
 * @file
 * Plugin to handle related area's of interest.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Related area\'s of interest block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the related area's link block.
 */
function thomas_more_related_area_of_interest_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();

  if ($node && $node->type == 'area_of_interest') {

    // Fetch the related interests
    $field_related_interests = field_get_items('node', $node, 'field_related_interests');

    if (!empty($field_related_interests)) {
      // Node has related interests.
      $content .= '<p>Is dit interessegebied toch niet helemaal je ding? Andere studenten vonden de volgende interessegebieden ook interessant:</p>';
      $content .= '<ul class="links-list">';

      foreach ($field_related_interests as $related_interest_id) {
        $related_interest = node_load($related_interest_id['target_id']);
        $link = l($related_interest->title, 'node/' . $related_interest->nid);
        $content .= '<li>' . $link . '</li>';
      }
      $content .= '</ul>';

      $view_all = l(t('View all areas of interest'), 'interessegebieden', array('attributes' => array('class' => 'btn')));
      $content .= $view_all;
    }
  }

  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'related_area_of_interest';
    $block->title       = 'Misschien ook interessant voor jou?';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_related_area_of_interest_content_type_admin_title($subtype, $conf) {
  return t('Related area\'s of interest block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_related_area_of_interest_content_type_admin_info($subtype, $conf) {
  return t('Related area\'s of interest block');
}
