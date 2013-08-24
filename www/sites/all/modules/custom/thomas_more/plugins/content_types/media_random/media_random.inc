<?php

/**
 * @file
 * Plugin to handle random media on nodes.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Random media block'),
  'defaults' => array('limit' => 4, 'add_more_link' => TRUE),
  'category' => t('Thomas More'),
);

/**
 * The configuration form..
 */
function thomas_more_media_random_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Limit'),
    '#required' => TRUE,
    '#default_value' => !empty($conf['limit']) ? $conf['limit'] : 4,
  );

  $form['read_more'] = array(
    '#type' => 'checkbox',
    '#default_value' => !empty($conf['read_more']),
    '#title' => t('Add read more link'),
  );

  return $form;
}

/**
 * Save the form.
 */
function thomas_more_media_random_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('limit', 'read_more') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Output function for the education link block.
 *
 * This kind of functionality also exists in thomas_more_lightbox_media().
 */
function thomas_more_media_random_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();

  if ($node && ($node->type == 'education' || $node->type == 'area_of_interest' || $node->type == 'specialization' || $node->type == 'event' || $node->type == 'news')) {

    // Default args.
    $args = array();

    // Default query.
    $query = "SELECT field_media_fid FROM {field_data_field_media} WHERE entity_id IN (:entity_ids) ORDER BY RAND() limit " . $conf['limit'];

    if ($node->type == 'area_of_interest') {
      $nids = array();
      $result = db_query("SELECT entity_id FROM {field_data_field_interessegebied} WHERE bundle = 'education' AND field_interessegebied_target_id IN (:entity_ids)", array(':entity_ids' => array($node->nid)));
      foreach ($result as $record) {
        $nids[] = $record->entity_id;
        $sub_results = db_query("SELECT entity_id FROM {field_data_field_opleiding} WHERE bundle = 'specialization' AND field_opleiding_target_id IN (:entity_ids)", array(':entity_ids' => array($record->entity_id)));
        foreach ($sub_results as $sub_record) {
          $nids[] = $sub_record->entity_id;
        }
      }
      $args[':entity_ids'] = $nids;
    }
    elseif ($node->type == 'education') {
      // Get all specalizations for this education.
      $nids = array($node->nid);
      $result = db_query("SELECT entity_id FROM {field_data_field_opleiding} WHERE bundle = 'specialization' AND field_opleiding_target_id IN (:entity_ids)", array(':entity_ids' => array($node->nid)));
      foreach ($result as $record) {
        $nids[] = $record->entity_id;
      }
      // Also add education as a search nid.
      $args[':entity_ids'] = $nids;
    }
    // Specialization, event or news.
    elseif ($node->type == 'specialization' || $node->type == 'event' || $node->type == 'news') {
      $args[':entity_ids'] = array($node->nid);
    }

    if (empty($args[':entity_ids'])) {
      return;
    }

    $fids = array();
    $results = db_query($query, $args);
    if (!empty($results)) {

      $file_ids = array();
      foreach ($results as $record) {
        $file_ids[] = $record->field_media_fid;
      }

      if (count($file_ids) > 0) {
        // Load and view media files.
        $files = entity_load('file', $file_ids);
        $view = entity_view('file', $files, 'teaser');
        $content = drupal_render($view);

        // Read more link.
        if ($conf['read_more']) {
          $content .= '<div class="read-more">' . l(t('View all images and videos'), 'media/lightbox/' . $node->nid, array('attributes' => array('class' => array('colorbox-load')))) . '</div>';
        }
      }
    }
  }


  if (!empty($content)) {
    $content = '<div class="random-media">'. $content .'</div>';
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'random_media';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_media_random_content_type_admin_title($subtype, $conf) {
  return t('Random media block');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_media_random_content_type_admin_info($subtype, $conf) {
  return t('Random media block');
}
