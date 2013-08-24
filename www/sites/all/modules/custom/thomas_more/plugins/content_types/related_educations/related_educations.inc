<?php

/**
 * @file
 * Plugin to handle related educations.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Related educations block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the related education link block.
 */
function thomas_more_related_educations_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();

  if ($node && ($node->type == 'education' || $node->type == 'specialization')) {

    // Fetch the related educations.
    $field_related_educations = field_get_items('node', $node, 'field_related_educations');

    if (!empty($field_related_educations)) {
      // Node has related interests.
      $content .= '<p>Is deze opleiding toch niet helemaal je ding? Andere studenten vonden de volgende opleidingen ook interessant:</p>';
      $content .= '<ul class="links-list">';

      foreach ($field_related_educations as $related_edu_id) {
        $related_education = node_load($related_edu_id['target_id']);
        $link = l($related_education->title, 'node/' . $related_education->nid);
        $content .= '<li>' . $link . '</li>';
      }
      $content .= '</ul>';

      $view_all = l(t('View all educations'), 'opleidingen/zoeken', array('attributes' => array('class' => 'btn')));
      $content .= $view_all;
    }
  }

  if (!empty($content)) {
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'related_educations';
    $block->title       = 'Misschien ook interessant voor jou?';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_related_educations_content_type_admin_title($subtype, $conf) {
  return t('Related educations block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_related_educations_content_type_admin_info($subtype, $conf) {
  return t('Related educations block');
}
