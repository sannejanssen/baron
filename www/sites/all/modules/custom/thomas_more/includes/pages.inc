<?php

/**
 * @file
 * Page callbacks for Thomas more.
 */

/**
 * Returns a form to choose a campus.
 */
function thomas_more_lightbox_choose_campus($term) {
  $form = drupal_get_form('thomas_more_lightbox_choose_campus_form', $term);

  print drupal_render($form);
  drupal_page_footer();
  drupal_exit();
}

/**
 * Form callback.
 */
function thomas_more_lightbox_choose_campus_form($form, $form_state, $term) {
  $options = array();
  $query = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->distinct()
    ->condition('n.type', 'campus')
    ->condition('n.status', '1');
  $query->innerJoin('field_data_field_facility_campus', 'ffc', 'ffc.field_facility_campus_target_id = n.nid' );
  $query->innerJoin('field_data_field_facility_type', 'fft', 'fft.entity_id = ffc.entity_id AND field_facility_type_tid = ' . $term->tid);

  $records = $query->execute();

  foreach ($records as $record) {
    $options[str_replace(' ', '-', strtolower($record->title))] = $record->title;
  }

  $form['campus'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t('Select your campus').':',
  );

  $form['term'] = array(
    '#type' => 'hidden',
    '#value' => str_replace(' ', '-', strtolower($term->name)),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
  );

  return $form;
}

/**
 * Returns media for a node, depending on the type in lightbox.
 *
 * This kind of functionality also exists in thomas_more_media_random_content_type_render().
 */
function thomas_more_lightbox_media($node, $file = '') {
  // Load the main file if possible.
  if (!empty($file)) {
    $file = file_load($file);
  }
  $content = '';

  drupal_set_title(t('Media for !title', array('!title' => $node->title)));

  // Output with big picture and thumbnails.
  if ($node->type == 'education' || $node->type == 'area_of_interest' || $node->type == 'specialization' || $node->type == 'event' || $node->type == 'news') {

    // Default args.
    $args = array();

    // Default query.
    $query = "SELECT field_media_fid FROM {field_data_field_media} WHERE entity_id IN (:entity_ids)";

    if ($node->type == 'area_of_interest') {
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
    // testimonial only.
    elseif ($node->type == 'testimonial') {
      $nids = array($node->nid);
      $result = db_query("SELECT entity_id FROM {field_data_field_opleiding} WHERE bundle = 'testimonial' AND field_opleiding_target_id IN (:entity_ids)", array(':entity_ids' => array($node->nid)));
      foreach ($result as $record) {
        $nids[] = $record->entity_id;
      }
      // Also add education as a search nid.
      $args[':entity_ids'] = $nids;
    }

    $fids = array();
    $results = db_query($query, $args);

    if (!empty($results)) {
      $file_ids = array();
      foreach ($results as $record) {
        $file_ids[] = $record->field_media_fid;
      }

      // Load and view media files.
      $files = entity_load('file', $file_ids);
      $view = entity_view('file', $files, 'popup_thumbnail');

      // First file in case there wasn't a file.
      if (empty($file)) {
        $fid = array_shift($file_ids);
        $file = file_load($fid);
      }

      $full = entity_view('file', array($file), 'popup_full');
      $content = '<div id="popup-content">' . drupal_render($full) . '</div>';
      $content .= '<div id="popup-thumbs-wrapper"><div class="prev inactive"></div><div class="window"><div class="inner">' . drupal_render($view) . '</div></div><div class="next inactive"></div></div>';
    }
  }

  // Single file output.
  else if ($node->type == 'testimonial') {

    // Default query.
    $query = "SELECT field_media_fid FROM {field_data_field_media} WHERE entity_id IN (:entity_ids)";

     $nids = array($node->nid);
    // Also add education as a search nid.
    $args[':entity_ids'] = $nids;

    $fids = array();
    $results = db_query($query, $args);

    if (!empty($results)) {
      $file_ids = array();
      foreach ($results as $record) {
        $file_ids[] = $record->field_media_fid;
      }

      // Load and view media files.
      $files = entity_load('file', $file_ids);

      // First file in case there wasn't a file.
      if (empty($file)) {
        $fid = array_shift($file_ids);
        $file = file_load($fid);
      }

      $full = entity_view('file', array($file), 'popup_full');
      $content = '<div id="popup-content">' . drupal_render($full) . '</div>';
    }
  }

  print $content;
  drupal_page_footer();
  drupal_exit();
}

/**
 * Returns JSON for a single ajax.
 */
function thomas_more_lightbox_media_ajax($node = '', $file = '') {
  $status = TRUE;
  $error = FALSE;

  // Load the main file if possible.
  if (!empty($file)) {
    $file = file_load($file);
  }

  $full = entity_view('file', array($file), 'popup_full');
  $content = drupal_render($full);

  drupal_add_http_header('Content-Type', 'text/javascript; charset=utf-8');
  print drupal_json_encode(array(
    'status' => $status,
    'content' => $content,
    'errorMessage' => $error,
  ));
  drupal_page_footer();
  exit();
}
