<?php

/**
 * @file
 * Plugin to show testimonials - depending on context also.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Testimonials'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * The configuration form..
 */
function thomas_more_testimonials_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Output function for the 'testimonials' block.
 */
function thomas_more_testimonials_content_type_render($subtype, $conf, $panel_args) {
  $args = array();

  $query = new EntityFieldQueryExtraFields();
  $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'testimonial')
    ->propertyCondition('status', 1);

  if (drupal_is_front_page()) {
    $query->propertyCondition('promote', 1);
  }
  elseif (arg(0) == 'node' && is_numeric(arg(1))) {
    // It's possible we look at an area of interest, education or specialization.
    $operator = '=';
    $node = menu_get_object('node');
    // Education or specialization.
    if ($node->type == 'education' || $node->type == 'specialization') {
      $args = $node->nid;
    }
    // Area of interest, get all education and specializations underneath.
    elseif ($node->type == 'area_of_interest') {
      $operator = 'IN';

      $mquery = new EntityFieldQueryExtraFields();
      $main_courses = $mquery->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'education')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_interessegebied', 'target_id', $node->nid)
        ->execute();

      if (!empty($main_courses)) {
        foreach ($main_courses['node'] as $nid => $info) {
          // Store education nid.
          $args[] = $nid;

          $squery = new EntityFieldQueryExtraFields();
            $specializations = $squery->entityCondition('entity_type', 'node')
            ->propertyCondition('type', 'specialization')
            ->propertyCondition('status', 1)
            ->fieldCondition('field_opleiding', 'target_id', $nid, '=')
            ->execute();

          if (!empty($specializations)) {
            foreach ($specializations['node'] as $snid => $sinfo) {
              // Store specialization nid.
              $args[] = $nid;
            }
          }
        }
      }

      $args = array_unique($args);
    }

    // Add field opleiding condition. $args and $operator vary
    // depending on the type of testimonial.
    $query->fieldCondition('field_opleiding', 'target_id', $args, $operator);

    if (empty($args)) {
      return;
    }
  }

  $all_testimonials = $query->execute();

  if (!empty($all_testimonials)) {

    $content = '<div class="prev inactive"></div>';
    $content .= '<div class="window">';
    $content .= '<div class="inner">';

    foreach ($all_testimonials['node'] as $tm_nid => $tm_info) {

      $testimonial = node_load($tm_nid);

      $fid = array();
      $fid[] = $testimonial->field_media['und'][0]['fid'];
      if (!empty($fid)) {
        $file = entity_load('file', $fid);
        if (!empty($file)) {
          $file[$fid[0]]->testimonial = TRUE;
          $view = entity_view('file', $file, '239px_159px');
          $content .= '<div class="testimonial">';
          $content .= '<div class="left">';
          // Add colorbox link
          $path = 'media/lightbox/'. $tm_nid .'/' . $fid[0];

          // Only videos should appear in a popup.
          if ($view[$fid[0]]['#bundle'] == 'video') {
            $content .= l(drupal_render($view), $path, array('html' => TRUE, 'attributes' => array('class' => array('colorbox-load'))));
          }
          else {
           $content .= drupal_render($view);
          }
          $content .= '</div>';
          $content .= '<div class="right">';
          $quote = field_get_items('node', $testimonial, 'field_testimonial');
          if (!empty($quote)) {
            $content .= $quote[0]['safe_value'];
          }
          $content .= '<h3>' . $testimonial->title . '</h3>';

          $background = field_get_items('node', $testimonial, 'field_background');
          if (!empty($background)) {
            $content .= '<span>' . $background[0]['safe_value'] . '</span>';
          }
          $content .= '</div>';
          $content .= '</div>';
        }
      }
    }
    $content .= '</div>'; // end inner
    $content .= '</div>'; // end testimonials
    $content .= '<div class="next inactive"></div>';
  }

  if (!empty($content)) {
    $content = '<div id="testimonials-wrapper">'. $content .'</div>';

    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'testimonials';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_testimonials_content_type_admin_title($subtype, $conf) {
  return t('Testimonials');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_testimonials_content_type_admin_info($subtype, $conf) {
  return t('Testimonials');
}
