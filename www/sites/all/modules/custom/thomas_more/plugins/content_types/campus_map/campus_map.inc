<?php

/**
 * @file
 * Plugin to handle campus google map.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Campus map'),
  'defaults' => array('width' => '40', 'height' => '40'),
  'category' => t('Thomas More'),
);

/**
 * The configuration form.
 */
function thomas_more_campus_map_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('Enter the width of the map in pixels or percentage. Example: 400px or 100%.'),
    '#required' => TRUE,
    '#default_value' => !empty($conf['width']) ? $conf['width'] : '40',
  );

  $form['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#description' => t('Enter the height of the map in pixels. Example: 400px.'),
    '#required' => TRUE,
    '#default_value' => !empty($conf['height']) ? $conf['height'] : '40',
  );

  return $form;
}

/**
 * Save the form.
 */
function thomas_more_campus_map_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('width', 'height') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Output function for the education link block.
 *
 * This kind of functionality also exists in thomas_more_lightbox_media().
 */
function thomas_more_campus_map_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $show_teaser = !drupal_is_front_page();
  $node = menu_get_object();
  $marker_info = $markers = $settings = array();
  $all_campus = entity_load('node', array(), array('type' => 'campus' , 'status' => 1));

  $campus_marker_icon = '/' . drupal_get_path('theme', 'wundertheme') . '/images/gmap-marker.png';

  // We are looking at a node.
  if (isset($node->nid) && ($node->type == 'education' || $node->type == 'specialization' || $node->type == 'campus')) {

    if ($node->type != 'campus') {
      $campus = field_get_items('node', $node, 'field_campus');
    }
    else {
      $campus = TRUE;
    }
    if (!empty($campus)) {
      if ($node->type != 'campus') {
        foreach ($campus as $info) {
          $marker_info[$info['target_id']] = $all_campus[$info['target_id']];
        }
      }
      else {
        $show_teaser = FALSE;
        $marker_info[$node->nid] = $node;
      }
    }

    // Get specializations in case we're looking at a main education.
    if ($node->type == 'education') {

      $query = new EntityFieldQueryExtraFields();
        $specializations = $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'specialization')
        ->propertyCondition('status', 1)
        ->addExtraField('field_campus', 'target_id', 'nid')
        ->fieldCondition('field_opleiding', 'target_id', $node->nid, '=')
        ->execute();

      if (!empty($specializations)) {

        foreach ($specializations['node'] as $snid => $sinfo) {
          if (is_array($sinfo->extraFields->field_campus_nid)) {
            foreach ($sinfo->extraFields->field_campus_nid as $cid) {

              /* Needs review */
              if (is_array($cid)) {
                foreach ($cid as $cid_detail) {
                  $marker_info[$cid_detail] = $all_campus[$cid_detail];
                }
              }
              else {
                $marker_info[$cid] = $all_campus[$cid];
              }

            }
          }
          else {
            $cid = $sinfo->extraFields->field_campus_nid;
            $marker_info[$cid] = $all_campus[$cid];
          }
        }
      }
    }
  }
  // This is the frontpage.
  elseif (drupal_is_front_page()) {
    $marker_info = $all_campus;
  }

  if (!empty($marker_info)) {

    foreach ($marker_info as $nid => $info) {
      $lat_long = field_get_items('node', $info, 'field_map');
      if (!empty($lat_long)) {
        $markers[] = array(
          'nid' => drupal_is_front_page() ? $info->nid : '',
          'longitude' => $lat_long[0]['longitude'],
          'latitude' => $lat_long[0]['latitude'],
          'icon' => $campus_marker_icon,
        );
      }
    }

    $settings = array(
      'nodeForm' => FALSE,
      'overview' => TRUE,
      'width' => $conf['width'],
      'height' => $conf['height'],
    );

    // Generate the map.
    $map = wunderkraut_gmap_render_map($settings, $markers);
    $map = drupal_render($map);
    $content = '<div class="campus-map">' . $map . '</div>';

    // Show contact info.
    if ($show_teaser) {
      $content .= '<div class="info">';
      if (!empty($node->field_campus_info[LANGUAGE_NONE][0]['safe_value'])) {
        $markup = $node->field_campus_info[LANGUAGE_NONE][0]['safe_value'];
      }
      else {
        $markup = node_view_multiple($marker_info, 'teaser');
        $markup = drupal_render($markup);
      }
      $content .= '<div class="campus-info">' . $markup . '</div>';
      $content .= '</div>';
    }

    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'campus_map';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_campus_map_content_type_admin_title($subtype, $conf) {
  return t('Campus map');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_campus_map_content_type_admin_info($subtype, $conf) {
  return t('Campus map');
}
